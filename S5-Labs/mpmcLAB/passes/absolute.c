#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char line[100], *token;
    int addr;

    fp = fopen("program.txt", "r");
    if (!fp) return 1;

    fscanf(fp, "%s", line);
    printf("Program name: ");
    for (int i = 2; i < 8 && line[i] != '^' && line[i]; i++)
        printf("%c", line[i]);
    printf("\n");

    while (fscanf(fp, "%s", line) == 1) {
        if (line[0] == 'T') {
            token = strtok(line + 2, "^");
            addr = strtol(token, NULL, 16);
            strtok(NULL, "^");
            while ((token = strtok(NULL, "^")) != NULL) {
                for (int i = 0; token[i] && token[i+1]; i += 2) {
                    printf("%04X:\t%c%c\n", addr, token[i], token[i+1]);
                    addr++;
                }
            }
        } else if (line[0] == 'E') break;
    }

    fclose(fp);
    return 0;
}
