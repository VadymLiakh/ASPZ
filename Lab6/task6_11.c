#include <stdio.h>
#include <stdlib.h>

int main() {
    // 1. Витік пам’яті (не звільнено)
    int *leak = malloc(100 * sizeof(int));
    leak[0] = 123;

    // 2. Неініціалізована змінна
    int x;
    if (x > 0) {  // UB: використання x до ініціалізації
        printf("x is positive\n");
    }

    // 3. Пам'ять виділена, але втрачена (заміна покажчика)
    char *lost = malloc(50);
    lost = malloc(20);  // старий блок втрачено

    return 0;
}