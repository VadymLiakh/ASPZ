#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FILE_NAME "dice_results.txt"
#define MAX_FILE_SIZE 1024  // Максимальний розмір файлу в байтах

int get_file_size(FILE *fp) {
    long current_pos = ftell(fp); // запам'ятати поточну позицію
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fseek(fp, current_pos, SEEK_SET); // повернутись назад
    return (int)size;
}

int main() {
    FILE *file = fopen(FILE_NAME, "a+"); // відкриваємо в режимі дописування
    if (file == NULL) {
        perror("Не вдалося відкрити файл");
        return 1;
    }

    srand((unsigned int)time(NULL));

    int throw_count = 0;
    while (1) {
        int roll = rand() % 6 + 1; // випадкове число від 1 до 6
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "Throw %d: %d\n", ++throw_count, roll);

        if (get_file_size(file) + strlen(buffer) >= MAX_FILE_SIZE) {
            printf("Досягнуто ліміту розміру файлу. Запис зупинено.\n");
            break;
        }

        fputs(buffer, file);
        fflush(file); // гарантуємо запис у файл
    }

    fclose(file);
    return 0;
}
