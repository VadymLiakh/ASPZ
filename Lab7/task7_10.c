#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float random_0_1() {
    return (float)rand() / (float)RAND_MAX;
}

float random_0_n(float n) {
    return random_0_1() * n;
}

int main(int argc, char *argv[]) {
    float n = 5.0; // Значення за замовчуванням
    if (argc == 2) {
        n = atof(argv[1]);
        if (n <= 0.0) {
            fprintf(stderr, "n має бути додатним дійсним числом\n");
            return 1;
        }
    }

    srand(time(NULL)); // Унікальне початкове значення

    printf("Випадкові числа у [0.0, 1.0]:\n");
    for (int i = 0; i < 5; i++) {
        printf("  %.6f\n", random_0_1());
    }

    printf("\nВипадкові числа у [0.0, %.2f]:\n", n);
    for (int i = 0; i < 5; i++) {
        printf("  %.6f\n", random_0_n(n));
    }

    return 0;
}
