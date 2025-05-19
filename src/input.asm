ORG 4000H                 ; Starting address

; Macro Definitions
MACRO INCR_AND_ADD        ; increment A, copy to B, add C
    INR A
    MOV B, A
    ADD C
MEND

MACRO LOAD_IMM reg, val   ; Load immediate val to reg
    MVI reg, val
MEND

MACRO CLEAR_REG reg       ; Clear register (move 0)
    MVI reg, 00H
MEND

; Start of Program
START:
    LOAD_IMM A, 0AH       ; A = 10
    LOAD_IMM B, 05H       ; B = 5
    LOAD_IMM C, 03H       ; C = 3
    CLEAR_REG D           ; D = 0
    CLEAR_REG E           ; E = 0
    CLEAR_REG H           ; H = 0
    CLEAR_REG L           ; L = 0

MAIN_LOOP:
    INCR_AND_ADD          ; Macro expands to 3 instructions
    MOV E, A
    JMP CHECK_COND

DATA_BLOCK:
    DB 0FFH, 0ABH, 0CDH, 0EFH, 0A1H, 0B2H, 0C3H, 0D4H
    DW 1234H, 5678H, 9ABCH, DEF0H

CHECK_COND:
    MOV H, E
    MVI L, 1AH
    ; Simulated comparison, no real CMP instruction
    JMP CONDITIONAL_JUMP

    NOP
    NOP
    NOP

CONDITIONAL_JUMP:
    ; Pseudo conditional jump
    JMP LOOP2

LOOP2:
    INR B
    INR C
    JMP MAIN_LOOP

; Data segment with lots of bytes and words to test symbol table and literal pools
DATA_SEG:
    DB 01H, 02H, 03H, 04H, 05H, 06H, 07H, 08H, 09H, 0AH
    DB 0BH, 0CH, 0DH, 0EH, 0FH, 10H, 11H, 12H, 13H, 14H
    DW 5678H, 9ABCH, CDEFH, 1234H, 4321H, 6789H

; More complex branching to test symbol resolution
LABEL1:
    MVI A, 0FFH
    ADD B
    JMP LABEL3

LABEL2:
    MOV C, A
    JMP LABEL1

LABEL3:
    HLT

; End of program
