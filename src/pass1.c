#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct {
    char label[32];
    int address;
} Symbol;

typedef struct {
    char name[32];
    char body[100][100];
    int line_count;
} Macro;



Symbol symbol_table[100];
int sym_count = 0;

Macro macro_table[10];
int macro_count = 0;

int location_counter = 0x0000;



int hex_to_int(char* hex) {
    int val;
    sscanf(hex, "%x", &val);
    return val;
}

void add_to_symbol_table(char* label, int addr) {
    for (int i = 0; i < sym_count; i++) {
        if (strcmp(symbol_table[i].label, label) == 0) {
            printf("Error: Duplicate label %s\n", label);
            return;
        }
    }
    strcpy(symbol_table[sym_count].label, label);
    symbol_table[sym_count].address = addr;
    sym_count++;
}

int instruction_size(char* instr) {
    if (strcmp(instr, "HLT") == 0 || strcmp(instr, "INR") == 0 || strcmp(instr, "ADD") == 0)
        return 1;
    else if (strcmp(instr, "MOV") == 0)
        return 1;
    else if (strcmp(instr, "MVI") == 0)
        return 2;
    else if (strcmp(instr, "JMP") == 0)
        return 3;
    return 1;
}

void print_symbol_table() {
    printf("\n=== Symbol Table ===\n");
    for (int i = 0; i < sym_count; i++) {
        printf("%s\t%04X\n", symbol_table[i].label, symbol_table[i].address);
    }
}



void process_line(char* line) {
    char label[32] = "", instr[32] = "", op1[32] = "", op2[32] = "";

   
    int parts = sscanf(line, "%31[^:]: %31s %31[^,], %31s", label, instr, op1, op2);
    if (parts < 1) return;

    
    if (strchr(line, ':')) {
        add_to_symbol_table(label, location_counter);
        sscanf(line + strlen(label) + 1, "%s %s , %s", instr, op1, op2); // Parse after label
    } else {
        sscanf(line, "%s %s , %s", instr, op1, op2);
    }

    
    if (strcmp(instr, "ORG") == 0) {
        location_counter = hex_to_int(op1);
    }
    else if (strcmp(instr, "DB") == 0) {
        location_counter += 1;
    }
    else if (strcmp(instr, "DW") == 0) {
        location_counter += 2;
    }
    else if (strcmp(instr, "EQU") == 0) {
        add_to_symbol_table(label, hex_to_int(op1));
    }
    else {
        location_counter += instruction_size(instr);
    }
}



int main() {
    FILE* fp = fopen("input.asm", "r");
    if (!fp) {
        printf("Error opening input.asm\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        
        line[strcspn(line, "\n")] = 0;

        
        if (line[0] == ';' || strlen(line) == 0)
            continue;

        process_line(line);
    }

    fclose(fp);
    print_symbol_table();
    return 0;
}
