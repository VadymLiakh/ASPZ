#include <stdio.h>
#include <time.h>

// Приклад фрагмента коду — затримка через обчислення
void example_code() {
    volatile long long sum = 0;
    for (long long i = 0; i < 100000000; i++) {
        sum += i;
    }
}

int main() {
    struct timespec start, end;
    long elapsed_ms;

    // Запис часу початку
    clock_gettime(CLOCK_MONOTONIC, &start);

    // === Вимірюваний фрагмент коду ===
    example_code();
    // =================================

    // Запис часу завершення
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Обчислення часу у мілісекундах
    elapsed_ms = (end.tv_sec - start.tv_sec) * 1000;
    elapsed_ms += (end.tv_nsec - start.tv_nsec) / 1000000;

    printf("Час виконання: %ld мс\n", elapsed_ms);

    return 0;
}
