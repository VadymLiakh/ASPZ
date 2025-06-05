#include <stdio.h>

void functionB() {
    printf("Inside function B\n");
}

void functionA() {
    printf("Inside function A\n");
    functionB();
    printf("Back in function A\n");
}

int main() {
    printf("Start of main\n");
    functionA();
    printf("End of main\n");
    return 0;
}
