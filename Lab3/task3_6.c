#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

#define STACK_LIMIT_BYTES 32768  // 32 KB — маленький стек, щоб швидше досягти межі

int depth = 0;

void recursive_function() {
    char buffer[1024];  // займаємо пам’ять на стеку
    depth++;
    printf("Recursion depth: %d | Stack address: %p\n", depth, (void*)&buffer);
    recursive_function();  // рекурсія
}

int main() {
    struct rlimit rl;

    // Встановлюємо ліміт на стек
    rl.rlim_cur = STACK_LIMIT_BYTES;
    rl.rlim_max = STACK_LIMIT_BYTES;
    if (setrlimit(RLIMIT_STACK, &rl) != 0) {
        perror("Не вдалося встановити обмеження стеку");
        return 1;
    }

    printf("Максимальний розмір стеку обмежено до %lu байт\n", (unsigned long)rl.rlim_cur);
    printf("Запускаємо рекурсію...\n");

    recursive_function();  // запуск

    return 0;
}
