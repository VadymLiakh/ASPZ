#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    size_t size = (size_t)1 << 63; // 8 ексабайт

    void *ptr = malloc(size);
    if (ptr == NULL) {
        printf("Не вдалося виділити %lu байт\n", size);
    } else {
        printf("Успішно виділено пам'ять: %p\n", ptr);
        free(ptr);
    }

    return 0;
}
