#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_ENTRIES 1024

int is_directory(const char *name) {
    struct stat st;
    if (stat(name, &st) == 0 && S_ISDIR(st.st_mode))
        return 1;
    return 0;
}

int compare_strings(const void *a, const void *b) {
    const char **sa = (const char **)a;
    const char **sb = (const char **)b;
    return strcmp(*sa, *sb);
}

int main() {
    DIR *dir;
    struct dirent *entry;
    char *dirs[MAX_ENTRIES];
    int count = 0;

    dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // Пропускаємо "." та ".."
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            // Додаємо в список
            dirs[count] = strdup(entry->d_name);
            if (dirs[count] != NULL)
                count++;
        }
    }

    closedir(dir);

    // Сортуємо
    qsort(dirs, count, sizeof(char *), compare_strings);

    // Виводимо
    for (int i = 0; i < count; i++) {
        printf("%s/\n", dirs[i]);
        free(dirs[i]);
    }

    return 0;
}
