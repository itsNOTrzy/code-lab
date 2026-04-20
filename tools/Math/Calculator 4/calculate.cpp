#include "public.h"
#include "math.h"
#define PI 3.1415926535897932385 //19位科学计数
short mode=RADIAN_MODE;
double eps = 1e-10;
double dec2rad(double dec)
/*功能：弧度制转角度制*/
{
	return PI*dec/180;
}

char precede(char t1,char t2)
/*功能：判断双目运算符的优先级别
  参数：t1前一运算符，t2当前运算符*/
{
	switch(t2)
	{
	case '+':
	case '-':
		if (t1=='('||t1==END)
			return'<';
		else
			return '>';
	case '*':
	case '/':
		if (t1=='^'||t1=='*'||t1=='/'||t1==')')
			return '>';
		else
			return '<';
	case '^':
		if(t1=='^'||t1==')')
			return '>';
		else
			return '<';
	case '(': return '<';
	case ')':
		switch(t1)
		{
		case '(':
			return '=';
		case END:
			event_report(the_breckets_do_not_match);
			return '<';
		default:
			return '>';
		}
	case END:
		switch(t1)
		{
		case END:
			return '=';	
		case '(':
			event_report(the_breckets_do_not_match);
			return '<';
		default:
			return '>';
		}
	}
}
double unary_compute(char opt,double a)
/*功能：单目运算符运算
参数：opt单目运算符，a运算数*/
{
	switch (opt)
	{
	case 19: return a;
	case 20: return 0-a;
	case 21: if(mode==DECIAML_MODE) //函数case数据和字符判断在string.cpp中
				 return sin(dec2rad(a));
		return sin(a);
	case 22: if(mode==DECIAML_MODE)
				 return cos(dec2rad(a));
		return cos(a);
	case 23: if(mode==DECIAML_MODE)
				 if(a-(int)a<eps&&(int)a%90<eps)
				{
					event_report(the_operand_in_tangent_function_must_not_be_integer_multiple_of_90_or_half_pi);
					 return 1;
				 } 
				 else
					 return tan(dec2rad(a));
			 else
				 if(2*a/PI-(int)(2*a/PI)<eps)
				{
					event_report(the_operand_in_tangent_function_must_not_be_integer_multiple_of_90_or_half_pi);
					 return 1;
				 } 
			 return tan(a);
	case 24: if(a>0)
				 return log10(a);
			event_report(the_antilogarithm_must_be_greater_than_zero);
			return 1;
	case 25: if(a>0)
				 return log(a);
			event_report(the_antilogarithm_must_be_greater_than_zero);
			return 1;
	case 26: if(a<0)//绝对值 10.10.2015新增
			 {
				 return a+2*a;
			 }
			 else
			 {
				 return a;
			 }
	default: event_report(undefined_error);
		return 1;
	}
}
double binary_compute(double a,char opt,double b)
/*功能：双目目运算符运算
  参数：opt双目运算符，a前运算数，b后运算数*/
{
	switch (opt)
	{
	case '+':
		return a+b;
	case '-':
		return a-b;
	case '*':
		return a*b;
	case '/':
		if(b)
			return a/b;
		event_report(the_divisor_can_not_be_zero);
		return 1;
	case '^':
		return pow(a,b);
	default:
		event_report(undefined_error);
		return 1;
	}
}
double calculate()//算术式的运算，详情在函数内部注释
{
	short i=0,times;
	double total=.0,a,b;
	char fore_valid_char=END,fore_operator=END,*str=unknownstring;
	bool have_been_point=false;
	ini_incident();ini_stack();input();	
	for(;str[i] != NULL;i++)
	{
		switch (type_char(str[i],true))
		{
		case NUMBER:
			if(fore_valid_char==')')
			{
				event_report(missing_a_operator_after_the_right_brecket);
				return 0;
			}
			if(str[i]=='.')//判断小数点出现次数
				if(have_been_point==false)
				{
					have_been_point=true;
					times=1;
				}
				else
				{
					event_report(the_real_number_is_illegal);
					return 0;
				}
			else
			{
				if(have_been_point==false)//整数部分累加
					total=10*total+str[i]-'0';
				else//小数部分累加
					total+=(str[i]-'0')*pow(.1,times++);
				if(type_char(str[i+1],true)!=NUMBER)
				{
					while(fore_operator>=19 && fore_operator<=25)
					{//数入栈前取出之前所有单目运算符
						total=unary_compute(fore_operator,total);
						if(event_box.incident)
							return 0;
						pop_or_get(OPERATOR,POP);
						fore_operator=(int)pop_or_get(OPERATOR,GET);
					}
					push(total,OPERAND);
					have_been_point=false;
					total=0;
				}
			}
			if(event_box.incident)//以下所有return 0都是因错误退出该函数
				return 0;
			fore_valid_char=str[i];
			break;
		case OPERATOR:
			if(fore_valid_char=='.')//若运算符前是小数点，认为数不完整
			{
				event_report(the_real_number_is_illegal);
				return 0;
			}
			switch (str[i])
			{
			case '%'://遇到百分号取出栈顶数，进行百分运算，并且%之前只能是）和数字
				if(fore_valid_char>='0'&&fore_valid_char<='9'||fore_valid_char==')')
					push(pop_or_get(OPERAND,POP)/100,OPERAND);
				else
				{
					event_report(the_operator_before_the_percent_sign_must_be_a_number);
					return 0;
				}
				break;
			case 21://sin
			case 22://cos
			case 23://tan
			case 24://lg
			case 25://ln
			case 26://abs
				if(type_char(fore_valid_char,true)==OPERATOR)//均为单目运算符，直接入栈
					push(str[i],OPERATOR);//单目运算符之前只能是运算符
				else
				{
					event_report(missing_a_operator_before_the_unary_operator);
					return 0;
				}
				fore_operator=str[i];
				break;
			case '+':
				if(fore_valid_char!=')'&&type_char(fore_valid_char,true)==OPERATOR)
				{//当+，-前是除)之外的运算符，认为是单目运算符，正号用19表示，负号用20，加减号用原ASCII码
					str[i]=19;
					push(19,OPERATOR);
					fore_operator=19;
					break;
				}//此处没有用break语句，当判定+ -的确是加减号时直接流转到default语句
			case '-':
				if(str[i]!=19&&str[i]!='+'&&fore_valid_char!=')'&&type_char(fore_valid_char,true)==OPERATOR)
					{
						str[i]=20;
						push(20,OPERATOR);
						fore_operator=20;
						break;
					}
			default://以上是单目运算符，此处开始为双目运算符
				switch(str[i])
				{
				case '('://左括号前只能是运算符，即不能是数字，不能是%,也不能是)
					if(type_char(fore_valid_char,true)==NUMBER||fore_valid_char=='%'||fore_valid_char==')')
					{
						event_report(missing_a_operator_before_the_left_brecket);
						return 0;
					}
					break;
				case ')'://右括号前一个字符不能是除%)之外的任何运算符
					if(fore_valid_char=='(')
					{
						event_report(the_element_is_null_between_the_match_beckets);
						return 0;
					}
					else if(type_char(fore_valid_char,true)==OPERATOR&&fore_valid_char!=')'&&fore_valid_char!='%')
					{
						event_report(missing_a_operand_before_the_right_brecket);
						return 0;
					}
					break;
				default:
					if(type_char(fore_valid_char,true)!=NUMBER&&fore_valid_char!=')'&&fore_valid_char!='%')
					{
						event_report(missing_a_operand_before_the_binary_operator);
						return 0;
					}
					break;
				}
			label_level_1231:			//当优先级由升序突然降低时，要把前面所有优先级高的运算完毕
				switch (precede(fore_operator,str[i]))
				{
				case '<':
					push(str[i],OPERATOR);
					fore_operator=str[i];
					break;
				case '>':
					b=pop_or_get(OPERAND,POP);
					a=pop_or_get(OPERAND,POP);
					push(binary_compute(a,(int)pop_or_get(OPERATOR,POP),b),OPERAND);
					fore_operator=(int)pop_or_get(OPERATOR,GET);
			goto label_level_1231;//C语言课老师给我了一个错觉：goto语句像小时候认为的国民党那样坏，其实不是那样
				case '='://在这里没有比goto更简洁，更直观的语句了
					if(str[i]==')')//当前运算符为)时，把(弹出栈，然后取出前一运算符
					{
						pop_or_get(OPERATOR,POP);
						fore_operator=(int)pop_or_get(OPERATOR,GET);
					}
					else//当前运算符为END时，肯定不能像)那样操作
						fore_operator=(int)pop_or_get(OPERATOR,POP);
					while(fore_operator>=19 && fore_operator<=25)//当运算符为）和END时必须把前面所有的单目运算符计算完毕
					{
						push(unary_compute(fore_operator,pop_or_get(OPERAND,POP)),OPERAND);
						pop_or_get(OPERATOR,POP);
						fore_operator=(int)pop_or_get(OPERATOR,GET);
					}
					break;
				}
			}
			if(event_box.incident)
				return 0;
			fore_valid_char=str[i];
		default:
			break;
		}
	}
	if(str[0]!=NULL&&fore_operator==END)
		return pop_or_get(OPERAND,GET);
	event_report(undefined_error);
	return 0;
}