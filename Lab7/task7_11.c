#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMANDS 1000
#define MAX_LENGTH 128

typedef struct {
    char command[MAX_LENGTH];
    int count;
} Command;

int find_command(Command cmds[], int size, const char *cmd) {
    for (int i = 0; i < size; i++) {
        if (strcmp(cmds[i].command, cmd) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    FILE *fp;
    char line[256];
    char cmd[MAX_LENGTH];
    Command cmds[MAX_COMMANDS];
    int total = 0;

    fp = popen("history", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    while (fgets(line, sizeof(line), fp)) {
        // Пропустити номер і дістати перше слово
        if (sscanf(line, "%*d %127s", cmd) == 1) {
            int idx = find_command(cmds, total, cmd);
            if (idx >= 0) {
                cmds[idx].count++;
            } else if (total < MAX_COMMANDS) {
                strncpy(cmds[total].command, cmd, MAX_LENGTH);
                cmds[total].count = 1;
                total++;
            }
        }
    }

    pclose(fp);

    // Знайти мінімальне використання
    int min = cmds[0].count;
    for (int i = 1; i < total; i++) {
        if (cmds[i].count < min) {
            min = cmds[i].count;
        }
    }

    printf("Найменш використовувані команди (використані %d раз):\n", min);
    for (int i = 0; i < total; i++) {
        if (cmds[i].count == min) {
            printf("  %s\n", cmds[i].command);
        }
    }

    return 0;
}
