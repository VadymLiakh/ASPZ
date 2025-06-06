#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Помилка при створенні процесу
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Дочірній процес: виконується ls -l
        execlp("ls", "ls", "-l", NULL);

        // Якщо execlp завершилась невдачею
        perror("execlp failed");
        exit(1);
    } else {
        // Батьківський процес: чекає завершення дитини
        wait(NULL);
        printf("Child process has finished executing 'ls -l'\n");
    }

    return 0;
}
