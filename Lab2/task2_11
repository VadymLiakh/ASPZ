#include <stdio.h>
#include <stdlib.h>

int global_var = 42; // глобальна змінна

void sample_function() {
    // порожня функція
}

int main() {
    int local_var = 123;  // локальна змінна
    void *heap_var = malloc(1); // динамічна змінна

    printf("Address of function          : %p\n", (void*)sample_function);
    printf("Address of global variable   : %p\n", (void*)&global_var);
    printf("Address of local variable    : %p\n", (void*)&local_var);
    printf("Address of heap allocation   : %p\n", heap_var);

    free(heap_var); // звільнення пам’яті

    return 0;
}
