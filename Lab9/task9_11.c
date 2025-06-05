#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Реальний UID: %d\n", getuid());
    printf("Ефективний UID: %d\n", geteuid());
    printf("Виконання системної команди id:\n");
    system("id");
    return 0;
}
