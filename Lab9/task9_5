#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *filename = "/tmp/tempfile.txt";
    FILE *file;

    printf("1. Створення файлу звичайним користувачем...\n");
    file = fopen(filename, "w");
    if (!file) {
        perror("fopen");
        return 1;
    }
    fprintf(file, "Це тестовий файл.\n");
    fclose(file);

    printf("2. Зміна власника файлу на root (потрібен sudo)...\n");
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "sudo chown root %s", filename);
    system(cmd);

    printf("3. Встановлення прав доступу 600 (тільки root)...\n");
    snprintf(cmd, sizeof(cmd), "sudo chmod 600 %s", filename);
    system(cmd);

    printf("4. Перевірка читання...\n");
    file = fopen(filename, "r");
    if (!file) {
        perror("Читання заборонено");
    } else {
        printf("Успішне читання\n");
        fclose(file);
    }

    printf("5. Перевірка запису...\n");
    file = fopen(filename, "a");
    if (!file) {
        perror("Запис заборонено");
    } else {
        fprintf(file, "Спроба додати запис.\n");
        printf("Успішний запис\n");
        fclose(file);
    }

    printf("6. Очистка: видалення файлу...\n");
    snprintf(cmd, sizeof(cmd), "sudo rm -f %s", filename);
    system(cmd);

    return 0;
}
