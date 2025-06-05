#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("realloc(NULL, 100):\n");
    void *p1 = realloc(NULL, 100);
    if (p1) {
        printf("Виділено памʼять: %p\n", p1);
        free(p1);
    } else {
        printf("realloc(NULL, 100) повернув NULL\n");
    }

    printf("\nmalloc + realloc(ptr, 0):\n");
    void *p2 = malloc(50);
    if (!p2) {
        perror("malloc");
        return 1;
    }
    printf("Початковий блок: %p\n", p2);

    void *p3 = realloc(p2, 0);
    if (p3 == NULL) {
        printf("realloc(ptr, 0) повернув NULL — памʼять звільнено.\n");
    } else {
        // Не гарантується стандартом, але можливо
        printf("realloc(ptr, 0) повернув не NULL: %p\n", p3);
        free(p3);
    }

    return 0;
}
