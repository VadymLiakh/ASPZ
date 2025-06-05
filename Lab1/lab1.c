#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define ADDRESS_LEN 100
#define DATE_LEN 11
#define FILE_NAME "students.dat"

typedef struct {
    char name[NAME_LEN];
    char birthdate[DATE_LEN];
    char address[ADDRESS_LEN];
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void load_students();
void save_students();
void add_student();
void list_students();
void edit_student();
void delete_student();
void search_student();
void clear_input_buffer();

int main() {
    load_students(); 

    int choice;
    while (1) {
        printf("\nStudent Database Menu:\n");
        printf("1. Add Student\n");
        printf("2. List Students\n");
        printf("3. Edit Student\n");
        printf("4. Delete Student\n");
        printf("5. Search Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1: add_student(); break;
            case 2: list_students(); break;
            case 3: edit_student(); break;
            case 4: delete_student(); break;
            case 5: search_student(); break;
            case 6: 
                save_students();
                printf("Exiting program...\n");
                return 0;
            default: 
                printf("Invalid choice, try again.\n");
        }
    }
}

void load_students() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("No previous data found. Starting fresh.\n");
        return;
    }

    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
}

void save_students() {
    FILE *file = fopen(FILE_NAME, "wb");
    if (!file) {
        printf("Error saving data!\n");
        return;
    }

    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
}

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Database is full!\n");
        return;
    }

    Student new_student;
    printf("Enter student name: ");
    fgets(new_student.name, NAME_LEN, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = '\0';

    printf("Enter birthdate (YYYY-MM-DD): ");
    fgets(new_student.birthdate, DATE_LEN, stdin);
    new_student.birthdate[strcspn(new_student.birthdate, "\n")] = '\0';

    clear_input_buffer();  // Очищуємо залишковий символ '\n'

    printf("Enter address: ");
    fgets(new_student.address, ADDRESS_LEN, stdin);
    new_student.address[strcspn(new_student.address, "\n")] = '\0';

    students[student_count++] = new_student;
    printf("Student added successfully!\n");

    save_students();  // Автозбереження після додавання студента
}

void list_students() {
    if (student_count == 0) {
        printf("No students in the database.\n");
        return;
    }

    printf("\nList of Students:\n");
    for (int i = 0; i < student_count; i++) {
        printf("%d. %s | Birthdate: %s | Address: %s\n",
               i + 1, students[i].name, students[i].birthdate, students[i].address);
    }
}

void edit_student() {
    int index;
    list_students();
    if (student_count == 0) return;

    printf("Enter student number to edit (1-%d): ", student_count);
    scanf("%d", &index);
    clear_input_buffer();

    if (index < 1 || index > student_count) {
        printf("Invalid index!\n");
        return;
    }
    
    index--;

    printf("Editing student: %s\n", students[index].name);

    printf("Enter new name (or press Enter to keep current): ");
    char new_name[NAME_LEN];
    fgets(new_name, NAME_LEN, stdin);
    if (new_name[0] != '\n') {
        new_name[strcspn(new_name, "\n")] = '\0';
        strcpy(students[index].name, new_name);
    }

    printf("Enter new birthdate (or press Enter to keep current): ");
    char new_birthdate[DATE_LEN];
    fgets(new_birthdate, DATE_LEN, stdin);
    if (new_birthdate[0] != '\n') {
        new_birthdate[strcspn(new_birthdate, "\n")] = '\0';
        strcpy(students[index].birthdate, new_birthdate);
    }

    clear_input_buffer(); // Очищуємо буфер після дати народження, щоб не було автоматичного пропуску адреси

    printf("Enter new address (or press Enter to keep current): ");
    char new_address[ADDRESS_LEN];
    fgets(new_address, ADDRESS_LEN, stdin);
    if (new_address[0] != '\n') {
        new_address[strcspn(new_address, "\n")] = '\0';
        strcpy(students[index].address, new_address);
    }

    printf("Student updated successfully!\n");

    save_students(); // Автоматичне збереження після редагування
}


void delete_student() {
    int index;
    list_students();
    if (student_count == 0) return;

    printf("Enter student number to delete (1-%d): ", student_count);
    scanf("%d", &index);
    clear_input_buffer();

    if (index < 1 || index > student_count) {
        printf("Invalid index!\n");
        return;
    }
    
    index--;

    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    student_count--;

    printf("Student deleted successfully!\n");

    save_students();  // Автозбереження після видалення
}

void search_student() {
    char query[NAME_LEN];
    printf("Enter name or part of the name to search: ");
    fgets(query, NAME_LEN, stdin);
    query[strcspn(query, "\n")] = '\0';

    printf("\nSearch Results:\n");
    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (strstr(students[i].name, query)) {
            printf("%d. %s | Birthdate: %s | Address: %s\n",
                   i + 1, students[i].name, students[i].birthdate, students[i].address);
            found = 1;
        }
    }
    if (!found) {
        printf("No matches found.\n");
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
