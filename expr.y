%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int prev = 0;
extern char* yytext;
%}
%token ADD SUB MUL NUM EOL R
%precedence '+' '-' '*'
%%
line    : expr EOL {$$ = $1; return $1; }
;
expr    : expr ADD expr {$$ = $1 + $3;}
| NUM {$$ = atoi(yytext);}
| R {$$ = prev;}
| expr MUL expr {$$ = $1 * $3;}
| expr SUB expr {$$ = $1 - $3;}
;
%%

int yyerror(char *s){
	printf("%s\n", s);
}

extern FILE *yyin;
int main()
{
  int q = 0;
  while(1){
  	prev = yyparse();	
	printf("result %d\n", prev);
  }
}
