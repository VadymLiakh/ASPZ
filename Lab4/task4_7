#include <stdlib.h>
#include <stdio.h>

struct sbar {
    int id;
    char name[32];
};

int main() {
    struct sbar *ptr, *newptr;

    // calloc - просто для початкового виділення
    ptr = calloc(1000, sizeof(struct sbar));
    if (!ptr) {
        perror("calloc");
        return 1;
    }

    // Використання reallocarray
    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (!newptr) {
        perror("reallocarray");
        free(ptr);  // важливо звільнити, якщо reallocarray провалився
        return 1;
    }

    ptr = newptr;

    free(ptr);
    return 0;
}
