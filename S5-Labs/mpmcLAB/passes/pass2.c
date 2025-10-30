#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *intermediate, *optab, *symtab, *programFile;
    char label[20], opcode[20], operand[20], code[20], mnemonic[20];
    char symbol[20], address[20], line[100], objcode[20];
    char progName[20] = "", textRecord[2000] = "";
    int loc, startAddr = 0, progLen = 0, firstTextAddr = -1, textLen = 0;

    intermediate = fopen("intermediate.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "r");
    programFile = fopen("program.txt", "w");
    
    if (!intermediate || !optab || !symtab || !programFile) {
        printf("Error opening files.\n");
        return 1;
    }

    fgets(line, sizeof(line), intermediate);
    sscanf(line, "%X %s %s %s", &loc, label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        startAddr = (int)strtol(operand, NULL, 16);
        strcpy(progName, label);
        fgets(line, sizeof(line), intermediate);
    }

    int lastAddr = startAddr, tmpAddr;
    char tmpLabel[20], tmpOpcode[20], tmpOperand[20];
    while (fgets(line, sizeof(line), intermediate)) {
        sscanf(line, "%X %s %s %s", &tmpAddr, tmpLabel, tmpOpcode, tmpOperand);
        lastAddr = tmpAddr;
    }
    progLen = lastAddr - startAddr;

    fseek(intermediate, 0, SEEK_SET);
    fgets(line, sizeof(line), intermediate);
    sscanf(line, "%X %s %s %s", &loc, label, opcode, operand);
    if (strcmp(opcode, "START") == 0) fgets(line, sizeof(line), intermediate);

    fprintf(programFile, "H^%-6s^%06X^%06X\n", progName, startAddr, progLen);

    while (!feof(intermediate)) {
        sscanf(line, "%X %s %s %s", &loc, label, opcode, operand);
        if (firstTextAddr == -1) firstTextAddr = loc;
        if (strcmp(opcode, "END") == 0) break;

        int found = 0;
        rewind(optab);
        while (fscanf(optab, "%s %s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                rewind(symtab);
                int symFound = 0;
                while (fscanf(symtab, "%s %s", symbol, address) != EOF) {
                    if (strcmp(operand, symbol) == 0) {
                        sprintf(objcode, "%s%s", mnemonic, address);
                        symFound = 1;
                        break;
                    }
                }
                if (!symFound) sprintf(objcode, "%s0000", mnemonic);
                found = 1;
                break;
            }
        }

        if (found) {
            sprintf(textRecord + strlen(textRecord), "^%s", objcode);
            textLen += 3;
        } 
        else if (strcmp(opcode, "WORD") == 0) {
            sprintf(objcode, "%06X", atoi(operand));
            sprintf(textRecord + strlen(textRecord), "^%s", objcode);
            textLen += 3;
        } 
        else if (strcmp(opcode, "BYTE") == 0) {
            char hex[20] = "";
            if (operand[0] == 'C') {
                for (int i = 2; operand[i] != '\''; i++) {
                    char temp[5];
                    sprintf(temp, "%02X", operand[i]);
                    strcat(hex, temp);
                }
            } else if (operand[0] == 'X') {
                for (int i = 2; operand[i] != '\''; i++) {
                    char temp[2] = {operand[i], '\0'};
                    strcat(hex, temp);
                }
            }
            sprintf(objcode, "%s", hex);
            sprintf(textRecord + strlen(textRecord), "^%s", objcode);
            textLen += strlen(hex) / 2;
        }

        fgets(line, sizeof(line), intermediate);
    }

    fprintf(programFile, "T^%06X^%02X%s\n", firstTextAddr, textLen, textRecord);
    fprintf(programFile, "E^%06X\n", startAddr);

    fclose(intermediate);
    fclose(optab);
    fclose(symtab);
    fclose(programFile);
    printf("Pass 2 complete.\n");
    return 0;
}
