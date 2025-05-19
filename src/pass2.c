#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char label[32];
    int address;
} Symbol;

Symbol symbol_table[100];
int sym_count = 0;

int hex_to_int(char* hex) {
    int val;
    sscanf(hex, "%x", &val);
    return val;
}

int get_address_for_label(const char* label) {
    for (int i = 0; i < sym_count; i++) {
        if (strcmp(symbol_table[i].label, label) == 0)
            return symbol_table[i].address;
    }
    return -1;
}

char* generate_machine_code(char* instr, char* op1, char* op2) {
    static char output[32];
    output[0] = '\0';

    if (strcmp(instr, "MVI") == 0) {
        if (strcmp(op1, "A") == 0) sprintf(output, "3E %s", op2);
        else if (strcmp(op1, "B") == 0) sprintf(output, "06 %s", op2);
        else if (strcmp(op1, "C") == 0) sprintf(output, "0E %s", op2);
        else if (strcmp(op1, "D") == 0) sprintf(output, "16 %s", op2);
        else if (strcmp(op1, "E") == 0) sprintf(output, "1E %s", op2);
        else if (strcmp(op1, "H") == 0) sprintf(output, "26 %s", op2);
        else if (strcmp(op1, "L") == 0) sprintf(output, "2E %s", op2);
        else sprintf(output, "?? %s", op2);
    }
    else if (strcmp(instr, "MOV") == 0) {
        if (strcmp(op1, "A") == 0 && strcmp(op2, "B") == 0) sprintf(output, "78");
        else if (strcmp(op1, "A") == 0 && strcmp(op2, "C") == 0) sprintf(output, "79");
        else if (strcmp(op1, "B") == 0 && strcmp(op2, "C") == 0) sprintf(output, "41");
        else sprintf(output, "??");
    }
    else if (strcmp(instr, "ADD") == 0) {
        if (strcmp(op1, "B") == 0) sprintf(output, "80");
        else if (strcmp(op1, "C") == 0) sprintf(output, "81");
        else sprintf(output, "??");
    }
    else if (strcmp(instr, "INR") == 0) {
        if (strcmp(op1, "A") == 0) sprintf(output, "3C");
        else if (strcmp(op1, "B") == 0) sprintf(output, "04");
        else if (strcmp(op1, "C") == 0) sprintf(output, "0C");
        else sprintf(output, "??");
    }
    else if (strcmp(instr, "JMP") == 0) {
        int addr = get_address_for_label(op1);
        if (addr == -1) sprintf(output, "?? ?? ??");
        else sprintf(output, "C3 %02X %02X", addr & 0xFF, (addr >> 8) & 0xFF);
    }
    else if (strcmp(instr, "HLT") == 0) {
        sprintf(output, "76");
    }
    else if (strcmp(instr, "DB") == 0) {
        sprintf(output, "%s", op1);
    }
    else if (strcmp(instr, "DW") == 0) {
        int val = hex_to_int(op1);
        sprintf(output, "%02X %02X", val & 0xFF, (val >> 8) & 0xFF);
    }
    else {
        sprintf(output, "--");
    }

    return output;
}

void load_symbol_table() {
    FILE* fp = fopen("symbol_table.txt", "r");
    if (!fp) {
        printf("Error loading symbol table\n");
        exit(1);
    }

    char label[32];
    int addr;
    while (fscanf(fp, "%31s %x", label, &addr) == 2) {
        strcpy(symbol_table[sym_count].label, label);
        symbol_table[sym_count].address = addr;
        sym_count++;
    }
    fclose(fp);
}

void process_line(char* line, int* location_counter) {
    char label[32] = "", instr[32] = "", op1[32] = "", op2[32] = "";
    label[0] = instr[0] = op1[0] = op2[0] = '\0';

    if (strchr(line, ':')) {
        sscanf(line, "%31[^:]: %31s %31[^,], %31s", label, instr, op1, op2);
        if (op2[0] == '\0') sscanf(line, "%31[^:]: %31s %31s", label, instr, op1);
    } else {
        sscanf(line, "%31s %31[^,], %31s", instr, op1, op2);
        if (op2[0] == '\0') sscanf(line, "%31s %31s", instr, op1);
        if (op1[0] == '\0') sscanf(line, "%31s", instr);
    }

    if (strcmp(instr, "JMP") == 0) {
        printf("%04X: %s\n", *location_counter, generate_machine_code(instr, op1, NULL));
        *location_counter += 3;
    }
    else if (strcmp(instr, "MVI") == 0) {
        printf("%04X: %s\n", *location_counter, generate_machine_code(instr, op1, op2));
        *location_counter += 2;
    }
    else if (strcmp(instr, "MOV") == 0 || strcmp(instr, "ADD") == 0 || strcmp(instr, "INR") == 0 || strcmp(instr, "HLT") == 0) {
        printf("%04X: %s\n", *location_counter, generate_machine_code(instr, op1, op2));
        *location_counter += 1;
    }
    else if (strcmp(instr, "DB") == 0) {
        printf("%04X: %s\n", *location_counter, generate_machine_code(instr, op1, NULL));
        *location_counter += 1;
    }
    else if (strcmp(instr, "DW") == 0) {
        printf("%04X: %s\n", *location_counter, generate_machine_code(instr, op1, NULL));
        *location_counter += 2;
    }
    else if (strcmp(instr, "ORG") == 0) {
        *location_counter = hex_to_int(op1);
    }
}

int main() {
    FILE* fp = fopen("input.asm", "r");
    if (!fp) {
        printf("Error opening input.asm\n");
        return 1;
    }

    load_symbol_table();

    int location_counter = 0;
    char line[256];

    printf("\n=== Pass 2 Output ===\n");
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        if (line[0] == ';' || strlen(line) == 0)
            continue;
        process_line(line, &location_counter);
    }

    fclose(fp);
    return 0;
}
