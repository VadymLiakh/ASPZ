#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILES 1024

int is_c_binary(const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0)
        return 0;

    // Перевірка: виконуваний файл, не каталог, не скрипт
    if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
        return 1;

    return 0;
}

int ask_permission(const char *filename) {
    char response[8];
    printf("Додати дозвіл на читання для інших: %s ? (y/n): ", filename);
    if (fgets(response, sizeof(response), stdin)) {
        return response[0] == 'y' || response[0] == 'Y';
    }
    return 0;
}

int main() {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    char *c_binaries[MAX_FILES];
    int count = 0;

    // Пошук потенційних C-програм (виконуваних файлів у поточній директорії)
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_c_binary(entry->d_name)) {
            c_binaries[count++] = strdup(entry->d_name);
        }
    }
    closedir(dir);

    // Виведення знайдених програм
    if (count == 0) {
        printf("Виконуваних C-програм не знайдено.\n");
        return 0;
    }

    printf("Знайдено C-програми:\n");
    for (int i = 0; i < count; i++) {
        printf("  %s\n", c_binaries[i]);
    }

    // Запит і оновлення дозволів
    for (int i = 0; i < count; i++) {
        if (ask_permission(c_binaries[i])) {
            struct stat st;
            if (stat(c_binaries[i], &st) == 0) {
                mode_t new_mode = st.st_mode | S_IROTH;
                if (chmod(c_binaries[i], new_mode) == 0) {
                    printf("✔ Дозвіл додано: %s\n", c_binaries[i]);
                } else {
                    perror("chmod");
                }
            }
        }
        free(c_binaries[i]);
    }

    return 0;
}
