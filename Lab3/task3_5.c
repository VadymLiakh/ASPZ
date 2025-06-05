#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define MAX_FILE_SIZE 10240  // Наприклад, обмеження на 10 KB

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Program need two arguments\n");
        return 1;
    }

    const char *source = argv[1];
    const char *destination = argv[2];

    FILE *src = fopen(source, "rb");
    if (!src) {
        fprintf(stderr, "Cannot open file %s for reading: %s\n", source, strerror(errno));
        return 1;
    }

    FILE *dst = fopen(destination, "wb");
    if (!dst) {
        fprintf(stderr, "Cannot open file %s for writing: %s\n", destination, strerror(errno));
        fclose(src);
        return 1;
    }

    // Отримуємо обмеження на розмір файлу
    struct rlimit rl;
    if (getrlimit(RLIMIT_FSIZE, &rl) == 0 && rl.rlim_cur != RLIM_INFINITY) {
        printf("System max file size: %lu bytes\n", (unsigned long)rl.rlim_cur);
    } else {
        printf("System max file size: unlimited or unknown\n");
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    size_t totalWritten = 0;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        totalWritten += bytesRead;
        if (totalWritten > MAX_FILE_SIZE) {
            fprintf(stderr, "File size limit exceeded (%d bytes)\n", MAX_FILE_SIZE);
            fclose(src);
            fclose(dst);
            remove(destination);  // Видаляємо недоповний файл
            return 1;
        }

        size_t bytesWritten = fwrite(buffer, 1, bytesRead, dst);
        if (bytesWritten != bytesRead) {
            fprintf(stderr, "Write error: %s\n", strerror(errno));
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    printf("File copied successfully: %zu bytes\n", totalWritten);

    fclose(src);
    fclose(dst);
    return 0;
}
