#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void *ptr = NULL;
    int i = 0;

    while (i++ < 3) {
        if (!ptr)
            ptr = malloc(16);

        printf("Iteration %d, writing to memory...\n", i);
        strcpy(ptr, "Hello");  // використання пам'яті

        printf("Data: %s\n", (char*)ptr);

        free(ptr);  // пам’ять звільнено, але ptr не скинуто в NULL
        // ptr досі вказує на звільнену пам’ять
    }

    return 0;
}
