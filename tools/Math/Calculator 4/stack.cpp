#include "public.h"
char operators[MAXSIZE/10];   //运算符栈
double operands[MAXSIZE/10];  //操作数栈
short  top[2];        //运算符栈顶标识
void push(double x,short type_data)
/*	功能：运算符和运算数都按照double型入栈，通过type_data区分
	参数：x入栈元素，type_data数据类型	*/
{
	if(top[type_data]==MAXSIZE-1)
		event_report(the_stack_is_full);
	else
	{
		if(type_data ==OPERATOR)
			operators[++top[OPERATOR]]=(char)x;
		else
			operands[++top[OPERAND]]=x;
	}
}
double pop_or_get(short type_data,short type_operation)
/*	功能：运算符或运算数的取出或者出栈
	参数：数据类型和操作类型
	返回值：返回double型，在调用函数时可能要进行强制类型转换*/
{
	if(top[type_data]==-1)
		event_report(the_stack_is_null);
	else
	{
		if(type_operation == POP)
			return type_data == OPERAND?operands[top[type_data]--]:operators[top[type_data]--];
		return type_data == OPERAND?operands[top[type_data]]:operators[top[type_data]];
	}
	return 0;
 }
void ini_stack() //初始化栈
{
	top[OPERAND]=-1;
	top[OPERATOR]=-1;
	push(END,OPERATOR);
}