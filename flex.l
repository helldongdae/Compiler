%{
#include "flex.h"
#include <stdlib.h>
extern int yylval;
%}
%%
"PRINT" 				{return PRINT;}
"INPUT" 				{return INPUT;}
"LET"					{return LET;}
"GOTO" 					{return GOTO;}
"IF"					{return IF;}
"REM"[^\n]* 				{return REM;}
"THEN" 					{return THEN;}
"<<EOF>>"				{return EOF;}
[=]					{return EQUALS;}
[<]					{return BIGGER;}
[>]					{return LESS;}
[a-zA-Z][a-zA-Z_0-9]* 			{return VAR;}
[-]*[0-9]+					{yylval = atoi(yytext); return NUM;}
["][^\n]*["]			{return STRING;}
[\n\t]					{return EOL;}
[ ]					{;}
.					{;}
%%
