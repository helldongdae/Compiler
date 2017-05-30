bison expr.y
lex flex.l
gcc lex.yy.c expr.tab.c -ll 
./a.out
