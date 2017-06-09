%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NEXT_LINE INT_MAX

extern char* yytext;
typedef enum { typePrint, typeGoto, typeInput, typeRem, typeIf } nodeEnum;

typedef struct var{
	char name[1024];
	int size;
	int *val;
} var;

typedef struct {
    int type;
    char str[1024];               
} printNodeType;

typedef struct {
    int dst;               
} gotoNodeType;

typedef struct {
    int value;  
    char name[1024];             
} inputNodeType;

typedef struct {
    int type;  
    char left[1024];   
    char right[1024]; 
    int left_val;   
    int right_val;           
} ifNodeType;

typedef struct nodeType {
    	nodeEnum type;           

    	union {
		printNodeType print;      
		gotoNodeType go;    
		inputNodeType input; 
		ifNodeType ifNode;        
    	};
} nodeType;

typedef struct triple{
	int n; // Line #
	nodeType *C; // Point to AST
	char s[1024]; // Line of the code
} triple;

var table[100];
triple codes[1000];
int code_idx = 0;
int idx = 0;
int compare1 = 0;
int compare2 = 0;
int compare_result = 0;

nodeType * printNode(char str[1024], int p_type){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->print.type = p_type;
	p->type = typePrint; 
	strcpy(p->print.str, str);
	return p;
}

nodeType * gotoNode(int dst){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->type = typeGoto;
	p->go.dst = dst;
	return p;
}

nodeType * inputNode(char name[1024]){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->type = typeInput;
	strcpy(p->input.name, name);
	return p;
}

nodeType * remNode(){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->type = typeRem;
	return p;
}

nodeType * ifNode(int type, int left_i, int right_i, char left[1024], char right[1024]){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));

	p->type = typeIf;
	p->ifNode.type = type;
	return p;
}

int execute(triple L){
	int i = 0;
	int exist = 0;
	int inp = 0;
	switch(L.C->type){
		case typePrint:
			if(L.C->print.type == 1){
				for(i = 0;i<idx;i++){
					if(strcmp(table[i].name, L.C->print.str) == 0){
						exist = 1;	
						printf("%d\n", table[i].val);
					}
				}
				if(exist == 0){
					printf("ERROR: VARIABLE DOES NOT EXIST\n");
					return 0;
				}
			}
			else
				printf("%s\n", L.C->print.str);
			return NEXT_LINE;
		case typeGoto:
			return L.C->go.dst;
		case typeInput:
			scanf("%d", &inp);
			L.C->input.value = inp;
			for(i = 0;i<idx;i++){
				if(strcmp(table[i].name, L.C->input.name) == 0){
					exist = 1;
					if(table[i].val == NULL)	
						table[i].val = malloc(sizeof(L.C->input.value));
					table[i].val = L.C->input.value;
					table[i].size = sizeof(L.C->input.value)/4;
				} 
			}
			if(exist == 0){
				table[idx].val = malloc(sizeof(L.C->input.value));
				table[idx].val = L.C->input.value;
				strcpy(table[idx].name, L.C->input.name);
				idx++;
			}
			return NEXT_LINE;
		case typeRem:
			return NEXT_LINE;
		default:
			return 0;
	}
}

%}
%token PRINT INPUT LET GOTO IF REM VAR NUM STRING EQUALS BIGGER LESS EOL THEN
%%
program: 
        NUM statement EOL {codes[code_idx].C = $2; code_idx++; printf("%d\n", $2);}
	| program NUM statement EOL {codes[code_idx].C = $3; code_idx++;}
;
statement:
	PRINT print {$$ = $2;}
	| INPUT input  {$$ = $2;}
	| IF if THEN {codes[code_idx].C = $2; code_idx++;} statement {$$ = $5; printf("%d\n", $$);}
	| REM {$$ = remNode();}
	| GOTO goto {$$ = $2;}
; 
print:
	STRING {$$ = printNode(yytext, 0); printf("%d\n", $$);}
	| VAR {
		$$ = printNode(yytext, 1);
	}
;
input:
	VAR {
		$$ = inputNode(yytext);
	}
;
if:
	NUM EQUALS NUM{ $$ = ifNode(0, $1, $3, "", ""); }
; 
goto:
	NUM { $$ = gotoNode(atoi(yytext)); }
;
%%

int yyerror(char *s){
	printf("%s\n", s);
}

extern FILE *yyin;
int main()
{
	// char array to save the command
	char command[1024];
	// pointer to the file
	FILE *fp = fopen("code.f", "r");
	char *line = NULL;
	size_t len = 0;
	// parse and get line number and the code.
	while(getline(&line, &len, fp) != -1){
		strcpy(codes[code_idx].s, line);
		char *token = strtok(line, " ");
		codes[code_idx].n = atoi(token);
		code_idx++;
	}
	fclose(fp);
	code_idx = 0;
	// create AST
	yyin = fopen("code.f", "r");
  	while(1){
		int a = yyparse();
		if(a == 0)
			break;
  	}
	fclose(yyin);
	// Driver function	
	while(1){
		scanf("%s", command);
		if(strcmp(command, "LIST") == 0){
			// Print out every single codes
			int i = 0;
			for(i = 0;i<code_idx;i++){
				printf("%s", codes[i].s);
			}
		}
		else if(strcmp(command, "RUN") == 0){
			int i = 0;
			while(1){
				if(i == code_idx)
					break;
				int nxt = execute(codes[i]);
				if(nxt == 0)
					break;
				if(nxt == NEXT_LINE){
					i++;
				}
				else{
					int j = 0;
					for(j = 0;j<code_idx;j++){
						if(codes[j].n == nxt){
							i = j;
							break;
						}
					}
				}
			}		
		}
		else if(strcmp(command, "CHECK") == 0){
			int i = 0;			
			for(i = 0;i<code_idx;i++){
				printf("%d %d %s", codes[i].n, codes[i].C->type, codes[i].s);
			}
		}	
		else if(strcmp(command, "QUIT") == 0){
			return 0;
		}
		else{
			printf("Invalid command\n");
		}
	}
}
