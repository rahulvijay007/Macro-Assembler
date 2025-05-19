%{
#include "y.tab.h"   
#include <string.h>
%}

%%

[ \t]+              ;               
\n                  { return NEWLINE; }

";".*               ;               


[a-zA-Z_][a-zA-Z0-9_]*:    { yylval.str = strdup(yytext); return LABEL; }


ORG                 { return ORG; }
DB                  { return DB; }
DW                  { return DW; }
MACRO               { return MACRO; }
MEND                { return MEND; }
EQU                 { return EQU; }


MOV                 { return MOV; }
MVI                 { return MVI; }
ADD                 { return ADD; }
INR                 { return INR; }
JMP                 { return JMP; }
HLT                 { return HLT; }


A|B|C|D|E|H|L       { yylval.str = strdup(yytext); return REGISTER; }


[0-9]+H             { yylval.str = strdup(yytext); return HEXNUMBER; }
[0-9]+              { yylval.str = strdup(yytext); return DECNUMBER; }


[a-zA-Z_][a-zA-Z0-9_]*     { yylval.str = strdup(yytext); return IDENTIFIER; }

.                   ;              
%%

int yywrap() { return 1; }
