#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *data = malloc(16);
    if (!data) return 1;
    strcpy(data, "Initial");

    char *tmp = realloc(data, 1024 * 1024 * 1024);  // 1 GB
    if (!tmp) {
        printf("Realloc failed, old data preserved: %s\n", data);
        free(data);
        return 1;
    }

    data = tmp;
    printf("Data: %s\n", data);
    free(data);
    return 0;
}
