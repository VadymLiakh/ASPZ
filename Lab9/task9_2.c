#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Отримання вмісту /etc/shadow через sudo...\n");

    int status = system("sudo cat /etc/shadow");

    if (status == -1) {
        perror("Помилка при виконанні команди");
        return 1;
    } else {
        printf("\nКоманда виконана з кодом %d\n", WEXITSTATUS(status));
    }

    return 0;
}
