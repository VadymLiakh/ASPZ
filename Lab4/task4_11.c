#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BLOCKS 10
#define BLOCK_SIZE 1024 * 1024  // 1 MB

int main() {
    void *blocks[BLOCKS];

    printf("Initial program break: %p\n", sbrk(0));

    // Виділяємо 10 блоків по 1 MB
    for (int i = 0; i < BLOCKS; i++) {
        blocks[i] = malloc(BLOCK_SIZE);
        if (!blocks[i]) {
            perror("malloc");
            return 1;
        }
        printf("Allocated block %d at: %p\n", i, blocks[i]);
    }

    printf("Program break after allocations: %p\n", sbrk(0));

    // Звільняємо кожен другий блок (парні)
    for (int i = 0; i < BLOCKS; i += 2) {
        free(blocks[i]);
        printf("Freed block %d at: %p\n", i, blocks[i]);
    }

    // Спроба виділити великий блок (5 MB)
    void *large_block = malloc(5 * BLOCK_SIZE);
    if (!large_block) {
        printf("Failed to allocate large block (5 MB)\n");
    } else {
        printf("Allocated large block at: %p\n", large_block);
        free(large_block);
    }

    printf("Program break after large malloc: %p\n", sbrk(0));

    // Звільняємо решту блоків
    for (int i = 1; i < BLOCKS; i += 2) {
        free(blocks[i]);
    }

    return 0;
}
