%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define NEXT_LINE INT_MAX
#define PASS_LINE INT_MIN
#define IF_EQUAL 0
#define IF_NOT_EQUAL 1
#define IF_LESS_THAN 2
#define IF_MORE_THAN 3
#define IF_LESS_EQUAL 4
#define IF_MORE_EQUAL 5

extern char* yytext;
extern int yylval;
typedef enum { typePrint, typeGoto, typeInput, typeRem, typeIf_NN, typeIf_NV, typeIf_VN, typeIf_VV, typeLet } nodeEnum;

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
    int calType;
    int left, right;   
    int go;     
} ifNode_NN_Type;

typedef struct {
    int type;
    int calType;  
    int left;
    char right[1024];  
    int go;           
} ifNode_NV_Type;

typedef struct {
    int type;  
    int calType;
    char left[1024];  
    int right;      
    int go;       
} ifNode_VN_Type;

typedef struct {
    int type;  
    int calType;
    char left[1024];        
    char right[1024];
    int go;             
} ifNode_VV_Type;

typedef struct {
    int type;  
    char name[1024];  
    int val;              
} letNodeType;

typedef struct nodeType {
    	nodeEnum type;           

    	union {
		printNodeType print;      
		gotoNodeType go;    
		inputNodeType input; 
		ifNode_NN_Type ifNode_nn;
		ifNode_NV_Type ifNode_nv;    
		ifNode_VN_Type ifNode_vn;    
		ifNode_VV_Type ifNode_vv;     
		letNodeType let;       
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
int save_yyval = 0;
char save_var[1024];
int is_if = 0;
int gogo = 0;

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

nodeType * ifNode_NN(int left, int right, int calType){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->ifNode_nn.calType = calType;
	p->type = typeIf_NN;
	p->ifNode_nn.left = left;
	p->ifNode_nn.right = right;
	return p;
}

nodeType * ifNode_NV(int left, char right[1024], int calType){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->ifNode_nv.calType = calType;
	p->type = typeIf_NV;
	p->ifNode_nv.left = left;
	strcpy(p->ifNode_nv.right, right);
	return p;
}

nodeType * ifNode_VN(char left[1024], int right, int calType){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->ifNode_vn.calType = calType;
	p->type = typeIf_VN;
	strcpy(p->ifNode_vn.left, left);
	p->ifNode_vn.right = right;
	return p;
}

nodeType * ifNode_VV(char left[1024], char right[1024], int calType){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->ifNode_vv.calType = calType;
	p->type = typeIf_VV;
	strcpy(p->ifNode_vv.left, left);
	strcpy(p->ifNode_vv.right, right);
	return p;
}

nodeType * letNode(char name[1024], int val){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->type = typeLet;
	strcpy(p->let.name, name);
	p->let.val = val;
	return p;
}

int execute(triple L){
	int i = 0;
	int exist = 0, exist_r = 0;
	int inp = 0, left = 0, right = 0;
	char right_str[1024];
	char left_str[1024];
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
		case typeIf_NN:
			left = L.C->ifNode_nn.left;
			right = L.C->ifNode_nn.right;
			if(L.C->ifNode_nn.calType == IF_EQUAL){
				if(left == right)
					return L.C->ifNode_nn.go;
				else
					return NEXT_LINE;
			}
			else if(L.C->ifNode_nn.calType == IF_LESS_THAN){
				if(left > right)
					return L.C->ifNode_nn.go;
				else
					return NEXT_LINE;
			}
			else if(L.C->ifNode_nn.calType == IF_MORE_THAN){
				if(left < right)
					return L.C->ifNode_nn.go;
				else
					return NEXT_LINE;
			}
		case typeIf_NV:
			left = L.C->ifNode_nv.left;
			strcpy(right_str, L.C->ifNode_nv.right);
			right = 0;
			for(i = 0;i<idx;i++){
				if(strcmp(table[i].name, right_str) == 0){
					exist = 1;
					right = table[i].val;
				} 
			}
			if(L.C->ifNode_nv.calType == IF_EQUAL){
				if(left == right)
					return L.C->ifNode_nv.go;
				else
					return NEXT_LINE;
			}
			else if(L.C->ifNode_nv.calType == IF_LESS_THAN){
				if(left > right)
					return L.C->ifNode_nv.go;
				else
					return NEXT_LINE;
			}
			else if(L.C->ifNode_nv.calType == IF_MORE_THAN){
				if(left < right)
					return L.C->ifNode_nv.go;
				else
					return NEXT_LINE;
			}
		case typeIf_VN:
			right = L.C->ifNode_vn.right;
			strcpy(left_str, L.C->ifNode_vn.left);
			left = 0;
			for(i = 0;i<idx;i++){
				if(strcmp(table[i].name, left_str) == 0){
					exist = 1;
					left = table[i].val;
				} 
			}
			if(L.C->ifNode_vn.calType == IF_EQUAL){
				if(left == right)
					return L.C->ifNode_vn.go;
				else
					return NEXT_LINE;
			}
			else if(L.C->ifNode_vn.calType == IF_LESS_THAN){
				if(left > right)
					return L.C->ifNode_vn.go;
				else
					return NEXT_LINE;
			}
			else if(L.C->ifNode_vn.calType == IF_MORE_THAN){
				if(left < right)
					return L.C->ifNode_vn.go;
				else
					return NEXT_LINE;
			}
		case typeIf_VV:
			right = 0;
			strcpy(left_str, L.C->ifNode_vv.left);
			strcpy(right_str, L.C->ifNode_vv.right);
			left = 0;
			exist_r = 0;
			for(i = 0;i<idx;i++){
				if(strcmp(table[i].name, left_str) == 0){
					exist = 1;
					left = table[i].val;
				} 
			}
			for(i = 0;i<idx;i++){
				if(strcmp(table[i].name, right_str) == 0){
					exist_r = 1;
					right = table[i].val;
				} 
			}
			if(L.C->ifNode_vv.calType == IF_EQUAL){
				if(left == right)
					return L.C->ifNode_vv.go;
				else
					return NEXT_LINE;
			}
			else if(L.C->ifNode_vv.calType == IF_LESS_THAN){
				if(left > right)
					return L.C->ifNode_vv.go;
				else
					return NEXT_LINE;
			}
			else if(L.C->ifNode_vv.calType == IF_MORE_THAN){
				if(left < right)
					return L.C->ifNode_vv.go;
				else
					return NEXT_LINE;
			}
		case typeLet:
			for(i = 0;i<idx;i++){
				if(strcmp(table[i].name, L.C->let.name) == 0){
					exist = 1;
					if(table[i].val == NULL)	
						table[i].val = malloc(sizeof(L.C->input.value));
					table[i].val = L.C->let.val;
					table[i].size = sizeof(L.C->let.val)/4;
				} 
			}
			if(exist == 0){
				table[idx].val = malloc(sizeof(L.C->let.val));
				table[idx].val = L.C->let.val;
				strcpy(table[idx].name, L.C->let.name);
				idx++;
			}
			return NEXT_LINE;
			
		default:
			return 0;
	}
}

%}
%token PRINT INPUT LET GOTO IF REM VAR NUM STRING EQUALS BIGGER LESS EOL THEN
%%
program: 
        NUM statement EOL {
		codes[code_idx].C = $2; 
		if(is_if == 1){
			codes[code_idx].C->ifNode_nn.go = gogo;
			codes[code_idx].C->ifNode_nv.go = gogo;
			codes[code_idx].C->ifNode_vn.go = gogo;
			codes[code_idx].C->ifNode_vv.go = gogo;
		} 
		is_if = 0; 
		code_idx++;}
	| program NUM statement EOL {
		codes[code_idx].C = $3; 
		if(is_if == 1){
			codes[code_idx].C->ifNode_nn.go = gogo;
			codes[code_idx].C->ifNode_nv.go = gogo;
			codes[code_idx].C->ifNode_vn.go = gogo;
			codes[code_idx].C->ifNode_vv.go = gogo;
		} 
		is_if = 0; 
		code_idx++;}
;
statement:
	PRINT print {$$ = $2;}
	| INPUT input  {$$ = $2;}
	| IF if THEN NUM {is_if = 1; gogo = yylval; $$ = $2;}
	| REM {$$ = remNode();}
	| GOTO goto {$$ = $2;}
	| LET let {$$ = $2;}
; 
let:
	VAR {strcpy(save_var, yytext);} EQUALS NUM {$$ = letNode(save_var, yylval);}
;
print:
	STRING {$$ = printNode(yytext, 0);}
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
	NUM {save_yyval = yylval;} operator_n {$$ = $3;}
	| VAR {strcpy(save_var, yytext);} operator_v {$$ = $3;}
;
operator_n:
	EQUALS equal_n {$$ = $2;}
	| BIGGER bigger_n {$$ = $2;}
	| LESS less_n {$$ = $2;}
;
operator_v:
	EQUALS equal_v {$$ = $2;}
	| BIGGER bigger_v {$$ = $2;}
	| LESS less_v {$$ = $2;}
;
equal_n:
	NUM {$$ = ifNode_NN(save_yyval, yylval, IF_EQUAL);}
	| VAR {$$ = ifNode_NV(yytext, yylval, IF_EQUAL);}
;
equal_v:
	NUM {$$ = ifNode_VN(save_var, save_yyval, IF_EQUAL);}
	| VAR {$$ = ifNode_VV(save_var, yytext, IF_EQUAL);}
;
bigger_n:
	NUM {$$ = ifNode_NN(save_yyval, yylval, IF_MORE_THAN);}
	| VAR {$$ = ifNode_NV(yytext, yylval, IF_MORE_THAN);}
;
bigger_v:
	NUM {$$ = ifNode_VN(save_var, save_yyval, IF_MORE_THAN);}
	| VAR {$$ = ifNode_VV(save_var, yytext, IF_MORE_THAN);}
;
less_n:
	NUM {$$ = ifNode_NN(save_yyval, yylval, IF_LESS_THAN);}
	| VAR {$$ = ifNode_NV(yytext, yylval, IF_LESS_THAN);}
;
less_v:
	NUM {$$ = ifNode_VN(save_var, save_yyval, IF_LESS_THAN);}
	| VAR {$$ = ifNode_VV(save_var, yytext, IF_LESS_THAN);}
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
