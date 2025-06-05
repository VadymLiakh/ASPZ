#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>

#define LIMIT_CPU_SECONDS 2

void cpu_limit_handler(int signum) {
    fprintf(stderr, "\n Перевищено ліміт часу ЦП (%d секунд). Програма завершена.\n", LIMIT_CPU_SECONDS);
    exit(1);
}

// Перемішування масиву (алгоритм Фішера-Йєтса)
void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

void generate_lottery_numbers() {
    int pool49[49], pool36[36];

    // Заповнення масивів
    for (int i = 0; i < 49; i++) pool49[i] = i + 1;
    for (int i = 0; i < 36; i++) pool36[i] = i + 1;

    shuffle(pool49, 49);
    shuffle(pool36, 36);

    printf("Лотерея: 7 чисел з 49: ");
    for (int i = 0; i < 7; i++) printf("%d ", pool49[i]);
    printf("\n");

    printf("Лотерея: 6 чисел з 36: ");
    for (int i = 0; i < 6; i++) printf("%d ", pool36[i]);
    printf("\n");
}

int main() {
    // Обмеження часу ЦП
    struct rlimit rl;
    rl.rlim_cur = LIMIT_CPU_SECONDS;
    rl.rlim_max = LIMIT_CPU_SECONDS;
    if (setrlimit(RLIMIT_CPU, &rl) != 0) {
        perror("Не вдалося встановити обмеження часу ЦП");
        return 1;
    }

    // Обробник сигналу перевищення ліміту
    signal(SIGXCPU, cpu_limit_handler);

    srand(time(NULL));

    generate_lottery_numbers();

    // Імітуємо складну обчислювальну задачу (для перевірки ліміту)
    volatile unsigned long long dummy = 0;
    for (unsigned long long i = 0; i < 1e10; i++) {
        dummy += i;
    }

    return 0;
}
