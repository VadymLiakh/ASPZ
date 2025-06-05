#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define LOG_FUNC_LOCATION(func, ptr) \
    printf(">> Функція: %-18s | Адреса локальної змінної: %p\n", func, ptr)

void deep_sleep() {
    int status = 42;
    LOG_FUNC_LOCATION(__func__, &status);
    printf("+++ Очікування сигналу через pause() +++\n\n");
    pause(); // процес засне, очікуючи сигнал
}

void level_three() {
    int stack_marker = 33;
    LOG_FUNC_LOCATION(__func__, &stack_marker);
    deep_sleep();
}

void level_two() {
    int something = 22;
    LOG_FUNC_LOCATION(__func__, &something);
    level_three();
}

int main(int argc, char *argv[]) {
    int marker = 11;
    LOG_FUNC_LOCATION(__func__, &marker);
    level_two();
    return EXIT_SUCCESS;
}
