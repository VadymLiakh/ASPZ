#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "test_bytes.bin";
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];

    // Створення файлу з тестовими даними
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open (write)");
        return 1;
    }
    write(fd, data, sizeof(data));
    close(fd);

    // Відкриваємо знову для читання
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open (read)");
        return 1;
    }

    // Переміщення на позицію 3
    lseek(fd, 3, SEEK_SET);

    // Читання 4 байтів
    ssize_t bytes_read = read(fd, buffer, 4);
    if (bytes_read != 4) {
        perror("read");
        return 1;
    }

    printf("Прочитані байти: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}
