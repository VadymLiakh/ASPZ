#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int confirm_deletion(const char *filename) {
    char response[8];
    printf("Видалити %s? (y/n): ", filename);
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
    struct stat st;

    while ((entry = readdir(dir)) != NULL) {
        // Пропускаємо "." та ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Перевіряємо, чи це звичайний файл
        if (stat(entry->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
            if (confirm_deletion(entry->d_name)) {
                if (remove(entry->d_name) == 0) {
                    printf("Видалено: %s\n", entry->d_name);
                } else {
                    perror(entry->d_name);
                }
            }
        }
    }

    closedir(dir);
    return 0;
}
