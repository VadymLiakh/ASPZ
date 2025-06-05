#include <stdio.h>
#include <stdlib.h>

int main() {
    int xa = 1024 * 1024;
    int xb = 4096;

    int num = xa * xb;  // можлива переповнена змінна
    printf("xa: %d, xb: %d, num (xa*xb): %d\n", xa, xb, num);

    void *ptr = malloc(num);
    if (ptr == NULL) {
        printf("malloc() не виділив пам'ять (імовірно, через переповнення або ліміт).\n");
    } else {
        printf("malloc() виділив пам'ять за адресою: %p\n", ptr);
        free(ptr);
    }

    return 0;
}
