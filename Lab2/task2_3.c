#include <stdio.h>

int global_counter = 0;  // Глобальна змінна

void inspect_stack() {
    char temp_buffer[10000];  // Великий локальний масив
    printf("Stack memory location (large buffer): %p\n", (void*)temp_buffer);
}

int main() {
    int stack_marker = 42;
    int another_local = 7;

    printf("Approximate top of stack: %p\n", (void*)&stack_marker);
    printf("Location of global variable: %p\n", (void*)&global_counter);
    printf("Location of another local variable: %p\n", (void*)&another_local);

    inspect_stack();

    return 0;
}
