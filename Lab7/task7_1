#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;

    // Відкриваємо pipe: запускаємо rwho | more
    fp = popen("rwho | more", "r");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    // Зчитуємо і виводимо вміст
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }

    // Закриваємо pipe
    int status = pclose(fp);
    printf("\nКоманда завершена зі статусом: %d\n", status);

    return 0;
}
