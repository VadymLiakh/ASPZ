#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void test_access(const char *filepath) {
    printf("\nПеревірка доступу до файлу: %s\n", filepath);

    if (access(filepath, R_OK) == 0)
        printf("Можна читати\n");
    else
        printf("Читання заборонено\n");
 
    if (access(filepath, W_OK) == 0)
        printf("Можна записувати\n");
    else
        printf("Запис заборонено\n");

    if (access(filepath, X_OK) == 0)
        printf("Можна виконувати\n");
    else
        printf("Виконання заборонено\n");
}

int main() {
    const char *home = getenv("HOME");

    printf("Перегляд прав у домашньому каталозі:\n");
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ls -l %s", home);
    system(cmd);

    printf("\nПерегляд прав у /usr/bin:\n");
    system("ls -l /usr/bin | head -n 5");  // показати лише перші 5

    printf("\nПерегляд прав у /etc:\n");
    system("ls -l /etc | head -n 5");  // показати лише перші 5

    // Тест доступу до одного файлу з кожної директорії
    char test1[256], test2[] = "/usr/bin/ls", test3[] = "/etc/passwd";

    snprintf(test1, sizeof(test1), "%s/.bashrc", home);  // файл користувача
    test_access(test1);
    test_access(test2);
    test_access(test3);

    return 0;
}
