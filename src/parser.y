%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
void yyerror(const char *s) { printf("Parse error: %s\n", s); }

%}

%union {
    char* str;
}

%token <str> REGISTER
%token <str> HEXNUMBER DECNUMBER
%token <str> IDENTIFIER
%token <str> LABEL

%token MOV MVI ADD INR JMP HLT
%token ORG DB DW EQU MACRO MEND
%token NEWLINE

%%

program:
    lines
    ;

lines:
    | lines line
    ;

line:
      instruction NEWLINE
    | label_def instruction NEWLINE
    | directive NEWLINE
    | macro_def
    ;

instruction:
      MOV REGISTER ',' REGISTER
    | MVI REGISTER ',' HEXNUMBER
    | ADD REGISTER
    | INR REGISTER
    | JMP IDENTIFIER
    | HLT
    ;

label_def:
      LABEL      { /* Store label in symbol table (Pass 1) */ }
    ;

directive:
      ORG HEXNUMBER
    | DB HEXNUMBER
    | DW HEXNUMBER
    | IDENTIFIER EQU HEXNUMBER
    ;

macro_def:
      MACRO IDENTIFIER NEWLINE macro_body MEND NEWLINE
    ;

macro_body:
      | macro_body instruction NEWLINE
    ;

%%

