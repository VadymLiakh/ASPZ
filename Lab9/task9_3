#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
    const char *src = "/tmp/userfile.txt";
    const char *dst = "/home/guest/copiedfile.txt";

    printf("1. Створення файлу від імені звичайного користувача...\n");
    FILE *f = fopen(src, "w");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fprintf(f, "Це звичайний користувач створив цей файл.\n");
    fclose(f);

    printf("2. Копіювання файлу в домашню директорію від імені root...\n");
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "sudo cp %s %s", src, dst);
    system(cmd);

    printf("3. Зміна прав доступу до файлу (тільки root):\n");
    snprintf(cmd, sizeof(cmd), "sudo chmod 600 %s", dst);
    system(cmd);

    printf("4. Спроба редагувати файл звичайним користувачем...\n");
    snprintf(cmd, sizeof(cmd), "echo 'Нова спроба запису' >> %s", dst);
    int status = system(cmd);
    if (status != 0) {
        printf("Помилка запису — імовірно, немає прав\n");
    } else {
        printf("Запис пройшов\n");
    }

    printf("5. Спроба видалити файл:\n");
    snprintf(cmd, sizeof(cmd), "rm %s", dst);
    status = system(cmd);
    if (status != 0) {
        printf("Помилка видалення — імовірно, немає прав\n");
    } else {
        printf("Файл видалено\n");
    }

    return 0;
}
