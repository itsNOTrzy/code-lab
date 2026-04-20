#include <stdio.h>
#include <math.h>
#include "stack.h"
#include "calculate.h"
#include "common.h"
#include "math function.h"
#define OVER false


bool checkword (
	char word[]
	)
/*++
函数描述：

功能：
	检查字符的合法性

参数：
	word	- 待检查的字符串

返回值：
	字符合法返回 true ，否则返回 false
--*/
{
	int i;

	for (i = 0;word[i] != '\0';i ++) {
		if (word[i] >= 40 && word[i] <= 57 && word[i] != 44
			|| word[i] >= 65 && word[i] <= 90
			|| word[i] == 92 || word[i] == 94
			|| word[i] >= 97 && word[i] <= 122
			|| word[i] == 32 || word[i] == 9 || word[i] == 37
			) {
			continue;
		} else {
			return false;
		}
	}
	return true;
}
void SingelCalc (
	NODE *Operand,
	NODE *Operator
	)
/*++
函数描述：

功能：
	实现一元运算符的运算，并将结果存入到 Operand 中，
	且对小数位是零的浮点数，转换成整数后再保存

参数：
	Operand		- 操作数
	Operator	- 一元操作符

返回值：
	无
--*/
{
	switch (Operator->Term.Operator.Symbol) {
		case '-': //负号
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Integer = 0 - Operand->Term.Operand.Data.Integer;
			} else {
				Operand->Term.Operand.Data.Real = 0 - Operand->Term.Operand.Data.Real;
			}
			break;
		case '%': //百分号
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = Operand->Term.Operand.Data.Integer/100.0; 
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = Operand->Term.Operand.Data.Real/100.0;
			}
			break;
		case 21: //sin函数
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = sin ((double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = sin (Operand->Term.Operand.Data.Real);
			}
			break;
		case 22: //cos函数
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = cos ((double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = cos (Operand->Term.Operand.Data.Real);
			}
			break;
		case 23: //tan函数
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = tan ((double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = tan (Operand->Term.Operand.Data.Real);
			}
			break;
		case 24: //cot函数
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = 1/tan ((double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = 1/tan (Operand->Term.Operand.Data.Real);
			}
			break;
		case 25: //arcsin函数
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = asin ((double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = asin (Operand->Term.Operand.Data.Real);
			}
			break;
		case 26: //arccos函数
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = acos ((double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = acos (Operand->Term.Operand.Data.Real);
			}
			break;
		case 27: //arctan函数
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = atan ((double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = atan (Operand->Term.Operand.Data.Real);
			}
			break;
		case 28: //arccot函数
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = atan (1.0/(double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = atan (1.0/Operand->Term.Operand.Data.Real);
			}
			break;
		case 29: //ln函数
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = log ((double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = log (Operand->Term.Operand.Data.Real);
			}
			break;
		case 30: //lg函数
			if (Operand->Term.Operand.DataSignal == INTEGER) {
				Operand->Term.Operand.Data.Real = log10 ((double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = log10 (Operand->Term.Operand.Data.Real);
			}
			break;
		case 31: //10.7.2015 新增 abs绝对值函数
			if (Operand->Term.Operand.DataSignal == INTEGER) { 
				Operand->Term.Operand.Data.Real = abs ((double)Operand->Term.Operand.Data.Integer);
				Operand->Term.Operand.DataSignal = FLOAT;
			} else {
				Operand->Term.Operand.Data.Real = abs (Operand->Term.Operand.Data.Real);
			}
			break;
	}
	if (Operand->Term.Operand.DataSignal == FLOAT
		&& Operand->Term.Operand.Data.Real - (int)Operand->Term.Operand.Data.Real == 0.0) {
			Operand->Term.Operand.Data.Integer = (int)Operand->Term.Operand.Data.Real;
			Operand->Term.Operand.DataSignal = INTEGER;
	}
}


void DoubleCalc (
	NODE *Operand1,
	NODE *Operand2,
	NODE *Operator
	)
/*++
函数描述：

功能：
	实现二元运算符的运算，并将结果存入到 Operand 中,且对小数位是零的数，转换成整数后再保存

参数：
	Operand1	- 操作数 1 
	Operand2	- 操作数 2
	Operator	- 二元操作符

返回值：
	无
--*/
{
	switch (Operator->Term.Operator.Symbol) {
		case '+':
			if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == INTEGER) {
				Operand1->Term.Operand.Data.Integer = Operand1->Term.Operand.Data.Integer + Operand2->Term.Operand.Data.Integer;
			} else if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == FLOAT) {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Integer + Operand2->Term.Operand.Data.Real;
				Operand1->Term.Operand.DataSignal = FLOAT;
			} else if (Operand1->Term.Operand.DataSignal == FLOAT && Operand2->Term.Operand.DataSignal == INTEGER) {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Real + Operand2->Term.Operand.Data.Integer;
			} else {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Real + Operand2->Term.Operand.Data.Real;
			}
			break;
		case '-': //减
			if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == INTEGER) {
				Operand1->Term.Operand.Data.Integer = Operand1->Term.Operand.Data.Integer - Operand2->Term.Operand.Data.Integer;
			} else if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == FLOAT) {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Integer - Operand2->Term.Operand.Data.Real;
				Operand1->Term.Operand.DataSignal = FLOAT;
			} else if (Operand1->Term.Operand.DataSignal == FLOAT && Operand2->Term.Operand.DataSignal == INTEGER) {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Real - Operand2->Term.Operand.Data.Integer;
			} else {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Real - Operand2->Term.Operand.Data.Real;
			}
			break;
		case '*':
			if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == INTEGER) {
				Operand1->Term.Operand.Data.Integer = Operand1->Term.Operand.Data.Integer * Operand2->Term.Operand.Data.Integer;
			} else if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == FLOAT) {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Integer * Operand2->Term.Operand.Data.Real;
				Operand1->Term.Operand.DataSignal = FLOAT;
			} else if (Operand1->Term.Operand.DataSignal == FLOAT && Operand2->Term.Operand.DataSignal == INTEGER) {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Real * Operand2->Term.Operand.Data.Integer;
			} else {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Real * Operand2->Term.Operand.Data.Real;
			}
			break;
		case '/':
			if (Operand2->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.Data.Integer == 0 
				|| Operand2->Term.Operand.DataSignal == FLOAT && Operand2->Term.Operand.Data.Real == 0.0) {
					error = the_divisor_can_not_be_zero;
					return;
			}
			if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == INTEGER) {
				Operand1->Term.Operand.Data.Real = (double)Operand1->Term.Operand.Data.Integer / (double)Operand2->Term.Operand.Data.Integer;
				Operand1->Term.Operand.DataSignal = FLOAT;
			} else if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == FLOAT) {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Integer / Operand2->Term.Operand.Data.Real;
				Operand1->Term.Operand.DataSignal = FLOAT;
			} else if (Operand1->Term.Operand.DataSignal == FLOAT && Operand2->Term.Operand.DataSignal == INTEGER) {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Real / Operand2->Term.Operand.Data.Integer;
			} else {
				Operand1->Term.Operand.Data.Real = Operand1->Term.Operand.Data.Real / Operand2->Term.Operand.Data.Real;
			}
			break;
		case '\\':
			if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == INTEGER) {
				Operand1->Term.Operand.Data.Integer = Operand1->Term.Operand.Data.Integer % Operand2->Term.Operand.Data.Integer;
			} else {
				error = the_mode_operator_only_accept_integral_operands;
				return;
			}
			break;
		case '^':
			if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == INTEGER) {
				if (Operand1->Term.Operand.Data.Integer == 1 || Operand2->Term.Operand.Data.Integer >= 0) {
					Operand1->Term.Operand.Data.Integer = PlusPow (Operand1->Term.Operand.Data.Integer , Operand2->Term.Operand.Data.Integer);
				} else {
					Operand1->Term.Operand.Data.Real = MinusPow (Operand1->Term.Operand.Data.Integer , Operand2->Term.Operand.Data.Integer);
					Operand1->Term.Operand.DataSignal = FLOAT;
				}
			} else if (Operand1->Term.Operand.DataSignal == INTEGER && Operand2->Term.Operand.DataSignal == FLOAT) {
				Operand1->Term.Operand.Data.Real = pow (Operand1->Term.Operand.Data.Integer , Operand2->Term.Operand.Data.Real);
				Operand1->Term.Operand.DataSignal = FLOAT;
			} else if (Operand1->Term.Operand.DataSignal == FLOAT && Operand2->Term.Operand.DataSignal == INTEGER) {
				Operand1->Term.Operand.Data.Real = pow (Operand1->Term.Operand.Data.Real , Operand2->Term.Operand.Data.Integer);
			} else {
				Operand1->Term.Operand.Data.Real = pow (Operand1->Term.Operand.Data.Real , Operand2->Term.Operand.Data.Real);
			}
			break;
	}
	if (Operand1->Term.Operand.DataSignal == FLOAT
		&& Operand1->Term.Operand.Data.Real - (int)Operand1->Term.Operand.Data.Real == 0.0) {
			Operand1->Term.Operand.Data.Integer = (int)Operand1->Term.Operand.Data.Real;
			Operand1->Term.Operand.DataSignal = INTEGER;
	}
}

void FixList (
	NODE *Left,
	NODE *Right,
	NODE *data
	)
{
	DeleteNodes (Left,Right);
	NODEcopyWithoutNext (Left,data);
}


void CalcUnit (
	NODE *expHead,
	NODE *expEnd
	)
/*++
函数描述：

功能：
	实现仅含一对括号的表达式的计算，并，将结果保存到 expHead 中

参数：
	expHead		- 表达式头节点（也是左括号)
	expEnd		- 表达式尾节点 (也是右括号)

返回值：
	无
--*/
{
	bool FirstTerm = true;
	NODE *ActivedPointer = expHead;
	NODE *Operator = NULL;
	NODE *Operand1 = NULL,*Operand2 = NULL;

	PushOperator (ActivedPointer);
	ActivedPointer = ActivedPointer->Next;

	while (ActivedPointer != expEnd->Next) {
		//识别负号，由于负号只出现在表达式的表头
		if (ActivedPointer->TermSignal == DUALITY && ActivedPointer->Term.Operator.Symbol == '-' && FirstTerm == true) {
			ActivedPointer->Term.Operator.OperandNumber = 1;
			ActivedPointer->Term.Operator.Priority = 3;
			ActivedPointer->TermSignal = UNITARY;
			PushOperator (ActivedPointer);
			ActivedPointer = ActivedPointer->Next;
		}
		if (FirstTerm == true) {
			FirstTerm = false;
		}

		if (ActivedPointer->TermSignal == ISDATA 
			|| ActivedPointer->TermSignal == ISVARIABLE) {
			PushOperand (ActivedPointer);
			ActivedPointer = ActivedPointer->Next;
		} else {
			if (ActivedPointer->Term.Operator.Priority < OperatorHead->Term.Operator.Priority) {
				PushOperator (ActivedPointer);
				ActivedPointer = ActivedPointer->Next;
			} else if (ActivedPointer->Term.Operator.Priority > OperatorHead->Term.Operator.Priority
				|| ActivedPointer->Term.Operator.Priority == OperatorHead->Term.Operator.Priority 
				&& ActivedPointer->Term.Operator.Symbol != '^'
				&& ActivedPointer->TermSignal != MATH_FUNCTION
				&& ActivedPointer->TermSignal != RIGHT_BRACKET) {					
				Operator = PopOperator ();
				Operand2 = PopOperand ();
				if (Operator->Term.Operator.OperandNumber == 2) {
					Operand1 = PopOperand ();
					DoubleCalc (Operand1,Operand2,Operator);
					PushOperand (Operand1);
				} else {
					SingelCalc (Operand2,Operator);
					PushOperand (Operand2);
				}
			} else {
				PushOperator (ActivedPointer);
				ActivedPointer = ActivedPointer->Next;
			}
		}
	}
	if (OperandHead->Term.Operand.DataSignal == FLOAT
		&& OperandHead->Term.Operand.Data.Real - (int)OperandHead->Term.Operand.Data.Real == 0.0) {
			OperandHead->Term.Operand.Data.Integer = (int)OperandHead->Term.Operand.Data.Real;
			OperandHead->Term.Operand.DataSignal = INTEGER;
	}
	FixList (expHead,expEnd,OperandHead);
	ClearStack ();
}

bool LocateInner (
	NODE *expHead,
	NODE **InnerLeft,
	NODE **InnerRight
	)
{
	NODE *p;
	for (p = expHead;p != NULL; p = p->Next) {
		if (p->TermSignal != ISDATA && p->TermSignal != ISVARIABLE) {
			if (p->Term.Operator.Symbol == '(') {
				*InnerLeft = p;
			} else if (p->Term.Operator.Symbol == ')') {
				*InnerRight = p;
				return true;
			}
		}
	}

	return false;
}


void Calculate (
	NODE *expHead
	)
/*++
函数描述：

功能：
	计算给定的格式化后的表达式,并将结果保存到头节点 expHead 中

参数：
	expHead    - 格式化后的表达式的头节点指针

返回值：
	表达式节点指针
--*/
{
	NODE *Left = NULL,*Right = NULL;

	if (error != NULL) {
		return;
	}
	while (LocateInner (expHead,&Left,&Right) != OVER) {
		CalcUnit (Left,Right);	
	}
}

void Calculator (
	void
	)
{
	if (expString[0] == NULL || error != NULL) {
		vision = false;
		return;
	}
	if (!checkword (expString)) {
		error = find_some_illegal_alpha;
		return;
	}
	reformer (expString);
	PrintList ();
	Calculate (ExpressionHead);
}