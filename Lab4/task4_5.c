#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t init_size = 1024;
    size_t huge_size = (size_t)-1; // Дуже велике значення - realloc гарантовано провалиться

    void *ptr = malloc(init_size);
    if (!ptr) {
        perror("malloc");
        return 1;
    }

    printf("Початкова пам’ять виділена: %p\n", ptr);

    void *tmp = realloc(ptr, huge_size);
    if (!tmp) {
        // realloc не вдалося — ptr ще дійсний
        printf("realloc() не вдалося виділити %zu байт\n", huge_size);
        printf("Старий блок памʼяті досі дійсний: %p\n", ptr);
        free(ptr);
    } else {
        printf("realloc успішний, нова адреса: %p\n", tmp);
        free(tmp);
    }

    return 0;
}
