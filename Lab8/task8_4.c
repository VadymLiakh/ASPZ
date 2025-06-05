#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Дитячий процес
        printf("Child process: pid = %d\n", getpid());
    } else {
        // Батьківський процес
        printf("Parent process: child pid = %d, my pid = %d\n", pid, getpid());
    }

    return 0;
}
