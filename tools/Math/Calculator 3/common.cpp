#include <stdlib.h>
#include "common.h"

int      error = NULL; //错误null空
int      prec = 2; //小数精度
int      infocmd = 0;
int      infoarg = 0;
int      ArgCounter = 0;
char     VarName[MAXSIZE]; //变量名
char     *expString = NULL;
char     *Unknown = NULL;
char     *Command[2];
bool     vision = false;
NODE     *ExpressionHead = NULL;
NODE     *ExpressionTail = NULL;
VARIABLE *VariableList = NULL;
VARIABLE *VariableListTail = NULL;

//FUNCTION_MAXLENGTH宏定义值 函数数量 在common.h头文件中
FUNCTION FunctionList[FUNCTION_MAXLENGTH] = {
	{"sin",21},{"cos",22},{"tan",23},{"cot",24},{"arcsin",25},{"arccos",26},{"arctan",27},{"arccot",28},{"ln",29},{"lg",30},{"abs",31}
}; //函数 余切cot以前亦作ctg

bool strcopy (
	char dest[],
	char sour[],
	int n
	)
{
	int i;
	for (i = 0;i < n-1 && sour[i] != NULL;i ++) {
		dest[i] = sour[i];
	}
	if (i >= n) {
		return false;
	} else {
		dest[i] = NULL;
		return true;
	}
}



bool strcmp_a(const char str1[],const char str2[])
{
	int i=0;
	for(;str1[i] != NULL && str2[i] != NULL;i++) {
		if(str1[i] != str2[i]) {
			return false;
		}
	}
	if (str1[i] == NULL && str2[i] == NULL) {
		return true;
	} else {
		return false;
	}
}
bool strmatch (
	const char sour[],
	const char p[]
	)
/*++
函数描述：

功能：
	实现字符串(字母序列)的大小写模糊匹配

参数：
	sour	- 原字符串(字母序列)
	p	    - 要匹配的字符串(字母序列)

返回值：
	若匹配返回 true ,否则返回 false 
--*/
{
	int        i;
	for (i = 0;i < FUNCTION_NAME_MAXLENGTH && sour[i] != NULL && p[i] != NULL;i ++) {
		if ((sour[i] - p[i])%32 != 0) {
			return false;
		}
	}
	if (sour[i] == NULL && p[i] == NULL) {
		return true;
	} else {
		return false;
	}
}


VARIABLE *NewVarNode (
	char *NewName,
	OPERAND NewOperand
	)
{
	VARIABLE *tmp;
	tmp = (VARIABLE *) malloc (sizeof (VARIABLE));
	if (tmp == NULL) {
		error = memmory_allocation_failed;
		return NULL;
	}
	strcopy (tmp->Name,NewName,MAXSIZE);
	tmp->Operand = NewOperand;
	tmp->Next = NULL;
	return tmp;
}

VARIABLE *InsertVarNode (
	VARIABLE *Tail,
	VARIABLE *NewVar
	)
{
	if (Tail != NULL) {
		Tail->Next = NewVar;
		Tail = NewVar;
	}
	return Tail;
}


NODE *NewNode (
	TERM NewTerm,
	int  NewTermSignal
	)
/*++
函数描述：

功能：
	生成一个新的结点

参数：
	NewTerm         - 一个新的项
	NewTermSignal	- 一个新的项标志

返回值：
	无
--*/
{
	NODE *p;
	if ((p = (NODE *)malloc(sizeof(NODE))) != NULL) {
		p->Term = NewTerm;
		p->TermSignal = NewTermSignal;
		p->Next = NULL;
	}
	return p;
}


void DeleteNodes (
	NODE *first,
	NODE *last
	)
/*++
函数描述：

功能：
	销毁从 first 到 last 的所有结点 (不包含 first 结点)
	并将 first 结点和 last 之后的结点链接起来

参数：
	
返回值：
	无
--*/
{
	NODE *tp,*savenext;
	if (first != NULL && last != NULL) {
		tp = first->Next;
		first->Next = last->Next;
		while (tp != first->Next) {
			savenext = tp->Next;
			free (tp);
			tp = savenext;
		}
	}
}


void DeleteList (
	NODE *head
	)
/*++
函数描述：

功能：
	销毁整个链表，释放内存

参数：
	head	- 链表头指针
返回值：
	无
--*/
{
	NODE *savenext;	
	while (head!=NULL) {
		savenext=head->Next;
		free (head);
		head=savenext;
	}
}
void NODEcopy (
	NODE *dest,
	NODE *sour
	)
/*++
函数描述：

功能：
	将 sour 中的内容复制到 dest 中

参数：

返回值：
	无
--*/
{
	dest->Next = sour->Next;
	dest->Term = sour->Term;
	dest->TermSignal = sour->TermSignal;
}

void NODEcopyWithoutNext(
	NODE *dest,
	NODE *sour
	)
{
	dest->Term = sour->Term;
	dest->TermSignal = sour->TermSignal;
}

void InsertAfter (
	NODE *Target,
	NODE *s
	)
{
	if (Target != NULL) {
		s->Next = Target->Next;
		Target->Next = s;
	}
}
	
NODE *InsertEnd (
	NODE *Tail,
	NODE *s
	)
/*++
函数描述：

功能：
	在链表尾部插入一个结点

参数：
	Tail	- 链表尾结点
	s       - 要插入的结点

返回值：
	返回链表的尾结点
--*/
{
	if (Tail != NULL) {
		Tail->Next = s;
		s ->Next = NULL;
		Tail = s;
	}
	return Tail;
}


int FunctionSearch (
	FUNCTION FunctionList[],
	char     name[],
	TERM     *tempTerm
	)
/*++
函数描述：

功能：数学函数查找，查找sin cos 等数学函数

参数：
	FunctionList	- 数学函数列表
	name            - 要查询的函数名
	tempTerm        - 保存询到的函数内部表示

返回：函数的内部表示数字
--*/
{
	int i;
	for (i = 0;i < FUNCTION_MAXLENGTH;i ++) {
		if (strmatch (FunctionList[i].FunctionName,name)) {
			tempTerm->Operator.Symbol = FunctionList[i].FunctionOperator;
			tempTerm->Operator.Priority = 1;
			tempTerm->Operator.OperandNumber = 1;
			return MATH_FUNCTION;
		}
	}
	return NULL;
}

bool FunctionNameSearch (
	FUNCTION FunctionList[],
	char     symbol,
	char     name[]
	)
{
	int i;
	for (i = 0;i < FUNCTION_MAXLENGTH;i ++) {
		if (symbol == FunctionList[i].FunctionOperator) {
			strcopy (name,FunctionList[i].FunctionName,FUNCTION_NAME_MAXLENGTH);
			return true;
		}
	}
	return false;
}


int VariableSearch (
	VARIABLE *VariableList,
	char     name[],
	TERM     *tempTerm
	)
/*++
函数描述：

功能：查找自定义变量，获取变量中保存的值

参数：
	VariableList	- 自定义变量列表
	name            - 要查询的变量名
	tempTerm        - 保存查询到的自定义变量的值

返回：函数的内部表示数字
--*/
{
	VARIABLE *p = NULL;
	for (p = VariableList;p != NULL;p = p->Next) {
		if (strmatch (p->Name,name)) {
			tempTerm->Operand = p->Operand;
			return ISVARIABLE;
		}
	}
	return NULL;
}

VARIABLE *VariableSearch (
    VARIABLE *VariableList,
    char     name[]
	)
/*++
函数描述：

功能：查找自定义变量，获取变量中保存的值

参数：
	VariableList	- 自定义变量列表
	name            - 要查询的变量名

返回值：
	找到的变量的地址
--*/
{
	VARIABLE *p = NULL;
	for (p = VariableList;p != NULL;p = p->Next) {
		if (strcmp_a (p->Name,name)) {
			return p;
		}
	}
	return NULL;
}

void PrintVariable (
	void
	)
{
	VARIABLE *p =NULL;
	for (p = VariableList;p != NULL;p = p->Next) {
		printf ("%s:",p->Name);
		if (p->Operand.DataSignal == FLOAT) {
			printf ("%f\n",p->Operand.Data.Real);
		} else {
			printf ("%d\n",p->Operand.Data.Integer);
		}
	}
}

void PrintList (
	void
	)
/*++
函数描述：

功能：
	输出链表中有意义的内容

参数：
	Head	- 链表的表头指针

返回值：
	无
--*/
{
	NODE *p;
	if (error != NULL || vision == false) {
		return;
	}
	for (p = ExpressionHead;p != NULL;p = p->Next) {
		if (p == ExpressionHead || p == ExpressionTail) {
			continue;
		}
		if (p->TermSignal == ISDATA || p->TermSignal == ISVARIABLE) {
			if (p->Term.Operand.DataSignal == INTEGER) {
				printf ("%d",p->Term.Operand.Data.Integer);
			} else {
				printf ("%f",p->Term.Operand.Data.Real);
			} 
		} else if (p->TermSignal == MATH_FUNCTION){
			char mathfunctionname[FUNCTION_NAME_MAXLENGTH];
			FunctionNameSearch (FunctionList,p->Term.Operator.Symbol,mathfunctionname);
			printf ("%s",mathfunctionname);
		} else {
			printf ("%c",p->Term.Operator.Symbol);
		}
		putchar (' ');
	}
}

void usage (
	void
	)
{
	printf ("\n"); //帮助
	printf ("  Set Environment variables and Custom variables.\n");
	printf ("    set [prec｜Custom variable name] [Expression]\n\n");
	printf ("  View Environment variables and Custom variables.\n");
	printf ("   view [prec｜Custom variable name｜all]\n\n");
	printf ("  help(View help), exit(Exit)\n\n");

}

void logo (
	void
	)
{
	//Logo界面
	printf ("\n\n       Mathemetics Calculator 3\n");
	printf ("       Copyright(C) Eisenberg Andrew Roland\n\n");
}

void InitVvar (
	void
	)
{
	VARIABLE *tmp;
	OPERAND  NewOperand;
	NewOperand.DataSignal = FLOAT;
	NewOperand.Data.Real = 3.1415926535897932385; //19位科学计数
	VariableList = NewVarNode ("pi",NewOperand); //圆周率
	if (VariableList == NULL) {
		error = memmory_allocation_failed;
		return;
	}
	VariableListTail = VariableList;
	NewOperand.Data.Real = 2.7182818284590452354; //19位科学计数
	tmp = NewVarNode ("e",NewOperand); //自然常数 lim(1+1/n)^n  n→∞
	if (VariableList == NULL) {
		error = memmory_allocation_failed;
		return;
	}
	VariableListTail = InsertVarNode (VariableListTail,tmp);
}

void FreeCMD (
	void
	)
{
	int i;
	for (i = 0;i < 2;i ++) {
		if (Command[i] != NULL) {
			free (Command[i]);
			Command[i] = NULL;
		}
	}
}

