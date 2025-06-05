#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 65536  // 64KB

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Робимо pipe неблокуючим
    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

    char *buffer = malloc(BUF_SIZE);
    if (!buffer) {
        perror("malloc");
        return 1;
    }
    memset(buffer, 'A', BUF_SIZE);

    ssize_t count = write(pipefd[1], buffer, BUF_SIZE);
    if (count == -1) {
        perror("write");
    } else if (count < BUF_SIZE) {
        printf("Частковий запис: тільки %zd з %d байтів записано\n", count, BUF_SIZE);
    } else {
        printf("Успішно записано всі %d байтів\n", BUF_SIZE);
    }

    free(buffer);
    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
