#ifndef common_h
#define common_h
#include <stdio.h>
#include <stdlib.h>

//项的分类和内部表示

#define UNITARY       1
#define DUALITY       2
#define ISDATA        3
#define INTEGER       4
#define FLOAT         5
#define LEFT_BRACKET  6
#define RIGHT_BRACKET 7
#define MATH_FUNCTION 8
#define ISVARIABLE    9

//常量定义
#define FUNCTION_NAME_MAXLENGTH 7
#define FUNCTION_MAXLENGTH      11 //设置数学函数的数量
#define MAXSIZE                 256

//全局错误标志，值为 0 时表示没有错误
extern int  error;
//错误编号定义
#define the_name_is_too_long								1
#define can_not_identify_identifier							2
#define the_data_bit_is_too_long							3
#define the_real_number_is_illegal							4
#define illegal_compages									5
#define the_brackets_are_not_match							6
#define the_mode_operator_only_accept_integral_operands		7
#define the_divisor_can_not_be_zero							8
#define the_stack_is_null									9
#define memmory_allocation_failed							10
#define the_argument_cannot_been_explained					11
#define the_var_is_not_seen_before				        	12
#define find_some_illegal_word								13
#define find_some_illegal_alpha              				14
#define the_precision_or_mode_only_accept_integral_argument 15
#define the_prec_value_range_from_0_to_100                  16
#define the_command_is_incorrect                            17
#define connot_use_system_identify                          18

typedef union
{
	int     Integer;
	double  Real;
}_OPERAND;

typedef struct
{
	_OPERAND Data;
	int      DataSignal;
}OPERAND;

typedef struct 
{ 
	char Symbol;
	int  Priority;
	int  OperandNumber;
}OPERATOR;

typedef union 
{
	OPERAND  Operand;
	OPERATOR Operator;
}TERM;

typedef struct _NODE
{
	TERM         Term;
	int          TermSignal;
	struct _NODE *Next;
}NODE;

typedef struct
{
	char FunctionName [FUNCTION_NAME_MAXLENGTH];
	char FunctionOperator;
}FUNCTION;

typedef struct _VAR
{
	char        Name[MAXSIZE];
	OPERAND     Operand;
	struct _VAR *Next;
}VARIABLE;


extern char     VarName[];
extern char     *expString;
extern char     *Unknown;
extern char     *Command[];
extern int      prec;
extern int      infocmd;
extern int      infoarg;
extern int      ArgCounter;
extern bool     vision;
extern NODE     *ExpressionHead;
extern NODE     *ExpressionTail;
extern VARIABLE *VariableList;
extern VARIABLE *VariableListTail;
extern FUNCTION FunctionList[];


//一些公共函数
VARIABLE *NewVarNode (
	char *NewName,
	OPERAND NewOperand
	);

VARIABLE * InsertVarNode (
	VARIABLE *VariableListTail,
	VARIABLE *NewVar
	);

bool strmatch (
	const char sour[],
	const char p[]
	);
NODE *NewNode (
	TERM NewTerm,
	int NewTermSignal
	);

void DeleteNodes (
	NODE *first,
	NODE *last
	);

void DeleteList (
	NODE *head
	);

void NODEcopy (
	NODE *dest,
	NODE *sour
	);
void NODEcopyWithoutNext(
	NODE *dest,
	NODE *sour
	);
void InsertAfter (
	NODE *Target,
	NODE *s
	);
NODE *InsertEnd (
	NODE *Tail,
	NODE *s
	);

int FunctionSearch (
    FUNCTION FunctionList[],
    char     name[],
    TERM     *tempTerm
	);
bool FunctionNameSearch (
	FUNCTION FunctionList[],
	char     symbol,
	char     name[]
	);

int VariableSearch (
    VARIABLE *VariableList,
    char     name[],
    TERM     *tempTerm
	);
VARIABLE *VariableSearch (
    VARIABLE *VariableList,
    char     name[]
	);
void PrintVariable (
	void
	);

void PrintList (
	void
	);
void usage (
	void
	);
void logo (
   void
   );
void InitVvar (
	void
	);
void FreeCMD (
	void
	);
#endif
