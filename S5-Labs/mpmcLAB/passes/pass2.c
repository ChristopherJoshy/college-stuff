#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Variables for storing intermediate file fields
    char label[20], opcode[20], operand[20];
    char code[20], value[20], sym[20], addr[20];
    char obj_code[20], t_record[80] = "", prog_name[20];

    // Location counters and lengths
    int loc, start_addr = 0, length = 0, last_addr = 0;
    int t_start_addr = 0, t_len = 0;

    // Open files
    FILE *inter = fopen("intermediate.txt", "r");  // Intermediate file from Pass 1
    FILE *optab = fopen("optab.txt", "r");         // Opcode table
    FILE *symtab = fopen("symtab.txt", "r");       // Symbol table
    FILE *prog = fopen("program.txt", "w");        // Output object program

    if (!inter || !optab || !symtab || !prog) {
        printf("Error: Could not open files.\n");
        return 1;
    }

    // Read first line from intermediate file
    fscanf(inter, "%X %s %s %s", &loc, label, opcode, operand);

    // If program has START directive, get starting address
    if (strcmp(opcode, "START") == 0) {
        start_addr = (int)strtol(operand, NULL, 16); // Convert hex string to integer
        strcpy(prog_name, label);                     // Store program name
    }

    // Calculate program length by reading till end
    while (fscanf(inter, "%X %s %s %s", &last_addr, label, opcode, operand) != EOF);
    length = last_addr - start_addr;
    rewind(inter);  // Go back to beginning to process instructions

    // Skip START line if present
    fscanf(inter, "%X %s %s %s", &loc, label, opcode, operand);
    if (strcmp(opcode, "START") == 0)
        fscanf(inter, "%X %s %s %s", &loc, label, opcode, operand);

    // Write Header record: H^ProgramName^StartAddress^Length
    fprintf(prog, "H^%-6s^%06X^%06X\n", prog_name, start_addr, length);

    t_start_addr = loc;  // Initialize text record start address

    // Process each instruction until END
    while (strcmp(opcode, "END") != 0) {
        strcpy(obj_code, "");  // Clear object code for each line

        // Search opcode in OPTAB
        rewind(optab);
        int found_opcode = 0;
        while (fscanf(optab, "%s %s", code, value) != EOF) {
            if (strcmp(opcode, code) == 0) {
                found_opcode = 1;
                // If operand is not '**', find its address in SYMTAB
                if (strcmp(operand, "**") != 0) {
                    rewind(symtab);
                    int found_sym = 0;
                    while (fscanf(symtab, "%s %s", sym, addr) != EOF) {
                        if (strcmp(operand, sym) == 0) {
                            sprintf(obj_code, "%s%s", value, addr); // Combine opcode + address
                            found_sym = 1;
                            break;
                        }
                    }
                    if (!found_sym) sprintf(obj_code, "%s0000", value); // Undefined symbol
                } else sprintf(obj_code, "%s0000", value); // Operand is '**'
                break;
            }
        }

        // Handle WORD and BYTE directives
        if (!found_opcode) {
            if (strcmp(opcode, "WORD") == 0)  // Convert decimal to 6-digit hex
                sprintf(obj_code, "%06X", atoi(operand));
            else if (strcmp(opcode, "BYTE") == 0) {
                char temp[20] = "";
                if (operand[0] == 'C') {       // Character constant
                    for (int i = 2; operand[i] != '\''; i++)
                        sprintf(temp + strlen(temp), "%02X", operand[i]);
                } else {                        // Hex constant (X'F1')
                    for (int i = 2; operand[i] != '\''; i++)
                        sprintf(temp + strlen(temp), "%c", operand[i]);
                }
                strcpy(obj_code, temp);
            }
        }

        // Add object code to text record
        if (strlen(obj_code) > 0) {
            // If text record exceeds 30 bytes (60 hex digits), write it and start new
            if (t_len + strlen(obj_code) > 60) {
                fprintf(prog, "T^%06X^%02X%s\n", t_start_addr, t_len / 2, t_record);
                strcpy(t_record, "");
                t_len = 0;
                t_start_addr = loc;
            }
            strcat(t_record, "^");
            strcat(t_record, obj_code);
            t_len += strlen(obj_code);
        } 
        // If RESW or RESB, write current text record and reset
        else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0) {
            if (t_len > 0) {
                fprintf(prog, "T^%06X^%02X%s\n", t_start_addr, t_len / 2, t_record);
                strcpy(t_record, "");
                t_len = 0;
            }
            t_start_addr = 0;  // Reset text record start
        }

        // Read next line from intermediate file
        fscanf(inter, "%X %s %s %s", &loc, label, opcode, operand);
        if (t_start_addr == 0) t_start_addr = loc;  // Set start if reset
    }//end of while

    // Write remaining text record if any
    if (t_len > 0)
        fprintf(prog, "T^%06X^%02X%s\n", t_start_addr, t_len / 2, t_record);

    // Write End record: E^StartAddress
    fprintf(prog, "E^%06X\n", start_addr);

    printf("PASS 2 completed successfully.\n");

    // Close all files
    fclose(inter);
    fclose(optab);
    fclose(symtab);
    fclose(prog);
    return 0;
}

