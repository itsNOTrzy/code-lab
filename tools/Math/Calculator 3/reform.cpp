#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "common.h"
#include "reform.h"

/**************************************************************\
*函数：isnumber
*
*功能：判断一个字符是否为数字包括小数点 '.'
*
*返回：如果是数字返回 true 否则返回 false
\**************************************************************/
bool isnumber (
	char c
	)
{
	if (c=='.' || c>= '0' && c<='9') {
		return true;
	} else {
		return false;
	}
}

/**************************************************************\
*函数：isoperator
*
*功能：判断一个字符是否为操作符，不含数学函数
*
*返回：如果是数字返回 true 否则返回 false
\**************************************************************/
bool isoperator (
	char c
	)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '\\' || c == '%' || c == '^') {
		return true;
	} else {
		return false;
	}
}

/**************************************************************\
*函数：convert
*
*功能：将数字串转换为等值的整数实数
*
*返回：返回对应的项标识号
\**************************************************************/
int convert (
	char DataString[],
	TERM *dest
	)
{
	int    i;
	int    signal = NULL;
	int    PointCount = 0;
	int    intTotal = 0;
	double floTotal = 0.0;
	double weight = 0.1;

	for (i = 0;i<MAXSIZE && DataString[i] != NULL;i ++) {
		if (DataString[i] == '.') {
			PointCount ++;
			if (PointCount > 1) {
				error = the_real_number_is_illegal;
				return NULL;
			}
			
		} else {
			if (PointCount == 0) {
				intTotal = intTotal*10+(DataString[i]-'0');
			} else if (PointCount == 1) {
				floTotal += weight*(DataString[i]-'0');
				weight = weight*0.1;
			} 
		}
	}
	if (PointCount == 0) {
		dest->Operand.DataSignal = INTEGER;
		dest->Operand.Data.Integer = intTotal;
	} else {
		dest->Operand.DataSignal = FLOAT;
		dest->Operand.Data.Real = intTotal + floTotal;
	}
	return ISDATA;
}
	    
/**************************************************************\
*函数：reform
*
*功能：将表达式字符串格式化为项串
*
*返回：返回项串的头指针
*
*注：将所有的 '-' 都当作减号
\**************************************************************/
void reform (
			  char expString[]
			  )
{
	int  i = 0,j = 0;
	int  tempSignal = LEFT_BRACKET;
	TERM tempTerm;
	NODE *tempNode;
    
	if (error != NULL) {
		return;
	}
	
	tempTerm.Operator.Symbol = '(';
	tempTerm.Operator.OperandNumber = 0;
	tempTerm.Operator.Priority = 6;
	ExpressionHead = NewNode (tempTerm,tempSignal);       //加入头结点
	ExpressionTail = ExpressionHead;
    
	for (i = 0;expString[i] != NULL;i ++) {
		j = 0;
		if (isalpha (expString[i])) {              //获得标识符
			VarName[j ++] = expString[i];
			while (isalpha(expString[++ i])) {
				if (j == MAXSIZE - 1) {
					error = the_name_is_too_long;
					return;
				}
				VarName[j ++] = expString[i];
			}
			i --;    //将下标返回到第一个非字母字符的前面以便主循环继续从其开始扫描
			VarName[j] = NULL;
			if ((tempSignal = FunctionSearch (FunctionList,VarName,&tempTerm)) == NULL &&
				(tempSignal = VariableSearch (VariableList,VarName,&tempTerm)) == NULL) {
				error = can_not_identify_identifier;
				return;
			}
		} else if (isoperator (expString[i])) {             //获得操作符
			tempTerm.Operator.Symbol = expString[i];
			if (expString[i] == '%') {
				tempSignal = UNITARY;
				tempTerm.Operator.OperandNumber = 1;
				tempTerm.Operator.Priority = 0;
			} else {
				tempSignal = DUALITY;
				tempTerm.Operator.OperandNumber = 2;
				if (expString[i] == '^') {
					tempTerm.Operator.Priority = 2;
				} else if (expString[i] == '*' || expString[i] == '/' || expString[i] == '\\') {
					tempTerm.Operator.Priority = 4;
				} else {
					tempTerm.Operator.Priority = 5;
				}
			}
		} else if (isnumber(expString[i])) {                //获得操作数
			VarName[j ++] = expString[i];
			while (isnumber (expString[++ i])) {
				if (j == MAXSIZE - 1) {
					error = the_data_bit_is_too_long;
					return;
				}
				VarName[j ++] = expString[i];
 			}
			i --;     //将下标返回到第一个非数字字符的前面以便主循环继续从其开始扫描
			VarName[j] = NULL;
			tempSignal = convert (VarName,&tempTerm);
			if (error != NULL) {
				return;
			}
		} else if (expString[i] == '(') {
			tempTerm.Operator.Symbol = expString[i];
			tempTerm.Operator.Priority = 6;
			tempTerm.Operator.OperandNumber = 0;
			tempSignal = LEFT_BRACKET;
		} else if (expString[i] == ')') {		
			tempTerm.Operator.Symbol = expString[i];
			tempTerm.Operator.Priority = 6;
			tempTerm.Operator.OperandNumber = 0;
			tempSignal = RIGHT_BRACKET;
		} else {
			continue;
		}
		tempNode = NewNode (tempTerm,tempSignal);
		ExpressionTail = InsertEnd (ExpressionTail,tempNode);
	}
	tempSignal = RIGHT_BRACKET;
	tempTerm.Operator.Symbol = ')';
	tempTerm.Operator.OperandNumber = 0;
	tempTerm.Operator.Priority = 6;
	tempNode = NewNode (tempTerm,tempSignal);      
	ExpressionTail = InsertEnd (ExpressionTail,tempNode);                     //加入尾结点
}

bool LicitCompages (NODE *a,NODE *b)
{
	switch (a->TermSignal) {
		case ISDATA:
			if (b->TermSignal == ISDATA) {
				return false;
			} else {
				return true;
			}
		case ISVARIABLE:
			if (b->TermSignal == ISDATA || b->TermSignal == ISVARIABLE) {
				return false;
			} else {
				return true;
			}
		case UNITARY://只表示 '%'
			if (b->TermSignal == UNITARY) {
				return false;
			} else {
				return true;
			}
		case DUALITY://包含负号 '-'
			if (b->TermSignal == DUALITY || b->TermSignal == RIGHT_BRACKET) {
				return false;
			} else {
				return true;
			}
		case MATH_FUNCTION:
			if (b->TermSignal == RIGHT_BRACKET || b->TermSignal == UNITARY || b->TermSignal == DUALITY) {
				return false;
			} else {
				return true;
			}
		case LEFT_BRACKET:
			if (b->TermSignal == RIGHT_BRACKET || b->TermSignal == UNITARY || (b->TermSignal == DUALITY && b->Term.Operator.Symbol != '-')) {
				return false;
			} else {
				return true;
			}
		case RIGHT_BRACKET:	
			if (b->TermSignal == ISDATA || b->TermSignal == ISVARIABLE || b->TermSignal == MATH_FUNCTION) {
				return false;
			} else {
				return true;
			}
		default:
			return false;
			
	}
}

void SyntaxCheck (
	NODE *expHead
	)
{
	int  BracketCounter = 0;
	NODE *a,*b;
	if (error != NULL) {
		return;
	}

	for (a = expHead,b = a->Next;b != NULL;a = b,b = b->Next) {
		if (a->TermSignal == LEFT_BRACKET) {
			BracketCounter ++;
		} else if (a->TermSignal == RIGHT_BRACKET) {
			BracketCounter --;
		}
		if (! LicitCompages (a,b)) {
			error = illegal_compages;
			return;
		}
	}
	BracketCounter --;
	if (BracketCounter != 0) {
		error = the_brackets_are_not_match;
		return;
	}
}

void expAnalyse (
	NODE *expHead
	)
{
	NODE *a;
	NODE *b;
	NODE *tempNode;
	TERM tempTerm;
	int  Signal = DUALITY;
	if (error != NULL) {
		return;
	}
	tempTerm.Operator.Symbol = '*';
	tempTerm.Operator.OperandNumber = 2;
	tempTerm.Operator.Priority = 4;

	for (a = expHead,b = a->Next;b != NULL; a = b,b = b->Next) {
		switch (a->TermSignal) {
			case ISDATA:
			case UNITARY:
				if ((b->TermSignal == ISVARIABLE || b->TermSignal == MATH_FUNCTION || b->TermSignal == LEFT_BRACKET)) {
					tempNode = NewNode (tempTerm,Signal);
					InsertAfter (a,tempNode);
					break;
				}
			case ISVARIABLE:
				if ((b->TermSignal == MATH_FUNCTION || b->TermSignal == LEFT_BRACKET)) {
					tempNode = NewNode (tempTerm,Signal);
					InsertAfter (a,tempNode);
					break;
				}
			case RIGHT_BRACKET:
				if ((b->TermSignal == MATH_FUNCTION || b->TermSignal == LEFT_BRACKET)) {
					tempNode = NewNode (tempTerm,Signal);
					InsertAfter (a,tempNode);
					break;
				}
		}
	}
}


void reformer (
	char expString[]
	)
{
	reform (expString);
	SyntaxCheck (ExpressionHead);
	expAnalyse (ExpressionHead);
}