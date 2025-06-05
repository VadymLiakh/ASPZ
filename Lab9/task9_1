#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UID_THRESHOLD 1000 

int main() {
    FILE *fp;
    char line[1024];
    char *username, *uid_str;
    int uid;

    uid_t current_uid = getuid();

    // Відкриваємо потік для читання результату команди
    fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    printf("Звичайні користувачі (UID > %d), окрім поточного UID = %d:\n", UID_THRESHOLD, current_uid);

    while (fgets(line, sizeof(line), fp) != NULL) {
        // Формат рядка: name:passwd:UID:GID:GECOS:home:shell
        char *copy = strdup(line);
        username = strtok(copy, ":");
        strtok(NULL, ":"); // passwd
        uid_str = strtok(NULL, ":");

        if (uid_str != NULL) {
            uid = atoi(uid_str);
            if (uid >= UID_THRESHOLD && uid != current_uid) {
                printf("Користувач: %s, UID: %d\n", username, uid);
            }
        }

        free(copy);
    }

    pclose(fp);
    return 0;
}
