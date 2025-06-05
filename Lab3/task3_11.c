#include <stdio.h>

int count = 0;

void recurse() {
    int dummy[100];  // Локальний масив, щоб швидше заповнити стек
    count++;
    printf("Recursion depth: %d, stack addr: %p\n", count, (void*)&dummy);
    recurse();
}

int main() {
    recurse();
    return 0;
}
