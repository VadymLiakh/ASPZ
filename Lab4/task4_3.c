#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(0);

    if (ptr == NULL) {
        printf("malloc(0) повернув NULL\n");
    } else {
        printf("malloc(0) повернув ненульовий вказівник: %p\n", ptr);
        free(ptr); // Це дозволено, навіть якщо malloc(0)
    }

    return 0;
}
