
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *data = malloc(16);
    if (!data) return 1;
    strcpy(data, "Initial");

    // Потенційно небезпечна операція:
    data = realloc(data, 1024 * 1024 * 1024);  // 1 GB

    if (!data) {
        printf("Realloc failed!\n");
        return 1;
    }

    printf("Data: %s\n", data);
    free(data);
    return 0;
}

