/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "expr.y" /* yacc.c:339  */

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
typedef enum { typePrint, typeGoto, typeInput, typeRem, typeIf_NN, typeIf_NV, typeIf_VN, typeIf_VV, typeLet, typeArrLet, typeDim, typeTwoDim } nodeEnum;

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

typedef struct {
    int type;  
    char name[1024];  
    int val;  
    int idx;            
} letArrNodeType;

typedef struct {
    int type;  
    char name[1024];  
    int size;            
} dimNodeType;

typedef struct {
    int type;  
    char name[1024];  
    int row, col;            
} twodimNodeType;

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
		letArrNodeType letArr;   
		dimNodeType dim;
		twodimNodeType twodim;
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
int arr_idx = 0;
char save_var[1024];
int is_if = 0;
int gogo = 0;
int row = 0, col = 0;

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

nodeType * letArrNode(char name[1024], int val, int idx){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->type = typeLet;
	strcpy(p->letArr.name, name);
	p->letArr.val = val;
	p->letArr.idx = idx;
	return p;
}

nodeType * dimNode(char name[1024], int size){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->type = typeDim;
	strcpy(p->dim.name, name);
	p->dim.size = size;
	return p;
}

nodeType * twodimNode(char name[1024], int row, int col){
	nodeType *p = (nodeType *)malloc(sizeof(nodeType));
	p->type = typeTwoDim;
	strcpy(p->twodim.name, name);
	p->twodim.row = row;
	p->twodim.col = col;
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
						table[i].val = malloc(sizeof(L.C->let.val));
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
		case typeArrLet:
			for(i = 0;i<idx;i++){
				if(strcmp(table[i].name, L.C->letArr.name) == 0){
					exist = 1;
					if(table[i].val == NULL)	
						table[i].val = malloc(sizeof(L.C->letArr.val));
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
		case typeDim:
			for(i = 0;i<idx;i++){
				if(strcmp(table[i].name, L.C->dim.name) == 0){
					exist = 1;
					if(table[i].val == NULL)	
						table[i].val = malloc(sizeof(L.C->dim.size));
					table[i].size = sizeof(table[i].val)/4;
				} 
			}
			return NEXT_LINE;
		case typeTwoDim:
			for(i = 0;i<idx;i++){
				if(strcmp(table[i].name, L.C->twodim.name) == 0){
					exist = 1;
					if(table[i].val == NULL)	
						table[i].val = malloc(sizeof(int) * (L.C->twodim.row*L.C->twodim.col));
					table[i].size = sizeof(table[i].val)/4;
				} 
			}
			return NEXT_LINE;
		default:
			return 0;
	}
}


#line 519 "expr.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PRINT = 258,
    INPUT = 259,
    LET = 260,
    GOTO = 261,
    IF = 262,
    REM = 263,
    VAR = 264,
    NUM = 265,
    STRING = 266,
    EQUALS = 267,
    BIGGER = 268,
    LESS = 269,
    EOL = 270,
    THEN = 271,
    PLUS = 272,
    MINUS = 273,
    MUL = 274,
    DIV = 275,
    MOD = 276,
    DIM = 277,
    TWODIM = 278,
    AS = 279,
    O_BRACKET = 280,
    C_BRACKET = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 594 "expr.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   70

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  45
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  85

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   456,   456,   466,   478,   479,   480,   481,   482,   483,
     484,   484,   485,   485,   485,   488,   488,   491,   492,   492,
     495,   496,   501,   506,   506,   507,   507,   510,   511,   512,
     515,   516,   517,   520,   521,   524,   525,   528,   529,   532,
     533,   536,   537,   540,   541,   544
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PRINT", "INPUT", "LET", "GOTO", "IF",
  "REM", "VAR", "NUM", "STRING", "EQUALS", "BIGGER", "LESS", "EOL", "THEN",
  "PLUS", "MINUS", "MUL", "DIV", "MOD", "DIM", "TWODIM", "AS", "O_BRACKET",
  "C_BRACKET", "\"[\"", "\"]\"", "$accept", "program", "statement", "$@1",
  "$@2", "$@3", "let", "$@4", "let_is_arr", "$@5", "print", "input", "if",
  "$@6", "$@7", "operator_n", "operator_v", "equal_n", "equal_v",
  "bigger_n", "bigger_v", "less_n", "less_v", "goto", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283
};
# endif

#define YYPACT_NINF -7

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-7)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       8,    -3,     7,     5,     6,    27,    28,    13,    -7,    30,
      31,    22,    -7,    -3,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    26,    -7,    -7,    -7,    29,
      -6,    -4,    -1,    33,    24,    32,    -7,    35,    36,    -7,
      15,    17,    19,    -7,    21,    23,    25,    -7,    -7,    16,
      34,    -7,    37,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    39,    40,    -7,    38,    -7,    41,    -7,    42,    44,
      45,    -7,    47,    43,    -7
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     7,     0,
       0,     0,     1,     0,    21,    20,     4,    22,     5,    15,
       9,    45,     8,    25,    23,     0,    10,    12,     2,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,    16,
       0,     0,     0,    26,     0,     0,     0,    24,     6,     0,
       0,    17,     0,    36,    35,    30,    40,    39,    31,    44,
      43,    32,    34,    33,    27,    38,    37,    28,    42,    41,
      29,     0,     0,    18,     0,    13,     0,    11,     0,     0,
       0,    19,     0,     0,    14
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -7,    -7,    48,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,    -7
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    11,    34,    35,    78,    20,    30,    39,    76,
      16,    18,    25,    32,    31,    47,    43,    64,    55,    67,
      58,    70,    61,    22
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       3,     4,     5,     6,     7,     8,    37,    12,    40,    41,
      42,    44,    45,    46,    14,    17,    15,    13,     1,     9,
      10,    38,    23,    24,    53,    54,    56,    57,    59,    60,
      62,    63,    65,    66,    68,    69,    19,    28,    21,    26,
      27,    71,    33,    48,    36,    51,    52,     0,    49,    74,
      75,     0,     0,    79,    81,     0,    50,    83,     0,    72,
       0,    29,     0,     0,    77,    73,     0,     0,    80,    84,
      82
};

static const yytype_int8 yycheck[] =
{
       3,     4,     5,     6,     7,     8,    12,     0,    12,    13,
      14,    12,    13,    14,     9,     9,    11,    10,    10,    22,
      23,    27,     9,    10,     9,    10,     9,    10,     9,    10,
       9,    10,     9,    10,     9,    10,     9,    15,    10,     9,
       9,    25,    16,    10,    15,    10,    10,    -1,    24,    10,
      10,    -1,    -1,    12,    10,    -1,    24,    10,    -1,    25,
      -1,    13,    -1,    -1,    26,    28,    -1,    -1,    26,    26,
      25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    30,     3,     4,     5,     6,     7,     8,    22,
      23,    31,     0,    10,     9,    11,    39,     9,    40,     9,
      35,    10,    52,     9,    10,    41,     9,     9,    15,    31,
      36,    43,    42,    16,    32,    33,    15,    12,    27,    37,
      12,    13,    14,    45,    12,    13,    14,    44,    10,    24,
      24,    10,    10,     9,    10,    47,     9,    10,    49,     9,
      10,    51,     9,    10,    46,     9,    10,    48,     9,    10,
      50,    25,    25,    28,    10,    10,    38,    26,    34,    12,
      26,    10,    25,    10,    26
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    29,    30,    30,    31,    31,    31,    31,    31,    31,
      32,    31,    33,    34,    31,    36,    35,    37,    38,    37,
      39,    39,    40,    42,    41,    43,    41,    44,    44,    44,
      45,    45,    45,    46,    46,    47,    47,    48,    48,    49,
      49,    50,    50,    51,    51,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     4,     2,     2,     4,     1,     2,     2,
       0,     7,     0,     0,    11,     0,     3,     2,     0,     6,
       1,     1,     1,     0,     3,     0,     3,     2,     2,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 456 "expr.y" /* yacc.c:1646  */
    {
		codes[code_idx].C = (yyvsp[-1]); 
		if(is_if == 1){
			codes[code_idx].C->ifNode_nn.go = gogo;
			codes[code_idx].C->ifNode_nv.go = gogo;
			codes[code_idx].C->ifNode_vn.go = gogo;
			codes[code_idx].C->ifNode_vv.go = gogo;
		} 
		is_if = 0; 
		code_idx++;}
#line 1732 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 466 "expr.y" /* yacc.c:1646  */
    {
		codes[code_idx].C = (yyvsp[-1]); 
		if(is_if == 1){
			codes[code_idx].C->ifNode_nn.go = gogo;
			codes[code_idx].C->ifNode_nv.go = gogo;
			codes[code_idx].C->ifNode_vn.go = gogo;
			codes[code_idx].C->ifNode_vv.go = gogo;
		} 
		is_if = 0; 
		code_idx++;}
#line 1747 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 478 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1753 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 479 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1759 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 480 "expr.y" /* yacc.c:1646  */
    {is_if = 1; gogo = yylval; (yyval) = (yyvsp[-2]);}
#line 1765 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 481 "expr.y" /* yacc.c:1646  */
    {(yyval) = remNode();}
#line 1771 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 482 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1777 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 483 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1783 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 484 "expr.y" /* yacc.c:1646  */
    {strcpy(save_var, yytext);}
#line 1789 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 484 "expr.y" /* yacc.c:1646  */
    {(yyval) = dimNode(save_var, yylval);}
#line 1795 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 485 "expr.y" /* yacc.c:1646  */
    {strcpy(save_var, yytext);}
#line 1801 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 485 "expr.y" /* yacc.c:1646  */
    {row = yylval;}
#line 1807 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 485 "expr.y" /* yacc.c:1646  */
    {(yyval) = twodimNode(save_var, row, yylval);}
#line 1813 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 488 "expr.y" /* yacc.c:1646  */
    {strcpy(save_var, yytext);}
#line 1819 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 488 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1825 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 491 "expr.y" /* yacc.c:1646  */
    {(yyval) = letNode(save_var, yylval);}
#line 1831 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 492 "expr.y" /* yacc.c:1646  */
    {arr_idx = yylval;}
#line 1837 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 492 "expr.y" /* yacc.c:1646  */
    {(yyval) = letArrNode(save_var, yylval, arr_idx);}
#line 1843 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 495 "expr.y" /* yacc.c:1646  */
    {(yyval) = printNode(yytext, 0);}
#line 1849 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 496 "expr.y" /* yacc.c:1646  */
    {
		(yyval) = printNode(yytext, 1);
	}
#line 1857 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 501 "expr.y" /* yacc.c:1646  */
    {
		(yyval) = inputNode(yytext);
	}
#line 1865 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 506 "expr.y" /* yacc.c:1646  */
    {save_yyval = yylval;}
#line 1871 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 506 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1877 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 507 "expr.y" /* yacc.c:1646  */
    {strcpy(save_var, yytext);}
#line 1883 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 507 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1889 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 510 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1895 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 511 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1901 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 512 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1907 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 515 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1913 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 516 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1919 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 517 "expr.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1925 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 520 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_NN(save_yyval, yylval, IF_EQUAL);}
#line 1931 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 521 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_NV(yytext, yylval, IF_EQUAL);}
#line 1937 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 524 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_VN(save_var, save_yyval, IF_EQUAL);}
#line 1943 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 525 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_VV(save_var, yytext, IF_EQUAL);}
#line 1949 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 528 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_NN(save_yyval, yylval, IF_MORE_THAN);}
#line 1955 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 529 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_NV(yytext, yylval, IF_MORE_THAN);}
#line 1961 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 532 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_VN(save_var, save_yyval, IF_MORE_THAN);}
#line 1967 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 533 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_VV(save_var, yytext, IF_MORE_THAN);}
#line 1973 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 536 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_NN(save_yyval, yylval, IF_LESS_THAN);}
#line 1979 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 537 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_NV(yytext, yylval, IF_LESS_THAN);}
#line 1985 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 540 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_VN(save_var, save_yyval, IF_LESS_THAN);}
#line 1991 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 541 "expr.y" /* yacc.c:1646  */
    {(yyval) = ifNode_VV(save_var, yytext, IF_LESS_THAN);}
#line 1997 "expr.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 544 "expr.y" /* yacc.c:1646  */
    { (yyval) = gotoNode(atoi(yytext)); }
#line 2003 "expr.tab.c" /* yacc.c:1646  */
    break;


#line 2007 "expr.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 546 "expr.y" /* yacc.c:1906  */


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
