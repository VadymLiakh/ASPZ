#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define LINES_PER_PAGE 20
#define MAX_LINE 1024

void wait_for_key() {
    printf("--Press any key to continue--");
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);              // зберегти налаштування термінала
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);            // вимкнути буферизацію й відлуння
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);     // застосувати нові налаштування
    getchar();                                   // очікування натискання клавіші
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);     // відновити налаштування
    printf("\n");
}

void display_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror(filename);
        return;
    }

    printf("===== %s =====\n", filename);

    char line[MAX_LINE];
    int line_count = 0;

    while (fgets(line, sizeof(line), fp)) {
        fputs(line, stdout);
        line_count++;

        if (line_count >= LINES_PER_PAGE) {
            wait_for_key();
            line_count = 0;
        }
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2] ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        display_file(argv[i]);
    }

    return 0;
}
