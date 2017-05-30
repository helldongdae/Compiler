%{
#include "flex.h"
%}
%%
[+] {return ADD;}
[-] {return SUB;}
[*] {return MUL;}
[\n\t] {return EOL;}
[0-9]* {return NUM;}
[R] {return R;}
%%
