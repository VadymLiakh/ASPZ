#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void list_files_recursively(const char *base_path) {
    struct dirent *dp;
    DIR *dir = opendir(base_path);

    if (!dir) {
        perror(base_path);
        return;
    }

    char path[1024];

    while ((dp = readdir(dir)) != NULL) {
        // Пропускаємо "." та ".."
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", base_path, dp->d_name);

        struct stat st;
        if (stat(path, &st) == -1) {
            perror(path);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            // Рекурсивно обходимо підкаталог
            list_files_recursively(path);
        } else if (S_ISREG(st.st_mode)) {
            printf("%s\n", path);
        }
    }

    closedir(dir);
}

int main() {
    list_files_recursively(".");
    return 0;
}
