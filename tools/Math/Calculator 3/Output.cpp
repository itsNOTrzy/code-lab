#include <ctype.h>
#include "common.h"
#include "calculate.h"
void PrintResult (
	NODE *Result
	)
{
	char format[10];
	char c = '%';
	if (error != NULL || vision == false) {
		return;
	}
	sprintf (format,"%c.%df\n",c,prec); //小数输出
	
	printf ("＝ ");//等号
	if (Result->Term.Operand.DataSignal == INTEGER) {
		printf ("%d\n",Result->Term.Operand.Data.Integer);//Answer答案
	} else {
		printf (format,Result->Term.Operand.Data.Real);
	}
	putchar ('\n');
}

void PrintError (
	void
	)
{
	if(error==3||error==4||error==8)
	{
		printf ("Math Error[%d]: ",error); //数学错误
	}
	else if(error==2||error==5||error==6)
	{
		printf ("Syntax Error[%d]: ",error); //语法错误
	}
	else
	{
		printf ("Error[%d]: ",error); //其它错误
	}
	switch (error) {
		case the_name_is_too_long:
			printf ("Variable name is too long.\n"); //变量名过长
			break;
		case can_not_identify_identifier:
			printf ("Cannot identify \"%s\"\n",VarName); //无法识别标识符
			break;
		case the_data_bit_is_too_long:
			printf ("Data bit is too long.\n"); //数据过于庞大，数位过长
			break;
		case the_real_number_is_illegal:
			printf ("Real number is illegal.\n"); //非法实数
			break;
		case illegal_compages:
			printf ("Illegal compages.\n"); //非法表达式，语法错误
			break;
		case the_brackets_are_not_match:
			printf ("Brackets are not match.\n"); //括号不匹配
			break;
		case the_mode_operator_only_accept_integral_operands:
			printf ("Mode operator only accept integral operands.\n"); //只能对整数求余数，模式操作只接受整型操作数。
			break;
		case the_divisor_can_not_be_zero:
			printf ("Cannot divide by zero.\n"); //不能被零除
			break;
		case the_stack_is_null:
			printf ("Stack is null."); //堆栈为空，错误
			break;
		case memmory_allocation_failed:
			printf ("Memory allocation failed.\n"); //计算机内存过小，内存分配失败
			break;
		case the_argument_cannot_been_explained:
			printf ("Argument cannot been explained.\n"); //论证无法解析
			break;
		case find_some_illegal_word:
			printf ("Variable name must in English.\n"); //变量名为西文字符
			break;
		case the_precision_or_mode_only_accept_integral_argument:
			printf ("Precision or mode only accept integral argument.");//全局变量值只能是0-100的整数，精度或模式只接受积分参数。
			break;
		case the_command_is_incorrect:
			printf ("Command is incorrect.\n");//命令不正确，缺少参数等等原因
			break;
		case the_var_is_not_seen_before:
			printf ("\"%s\" isn't seen before.\n",Command[1]); //从未见过的变量名
			break;
		case find_some_illegal_alpha:
			printf ("Illegal ERROR！\n"); //有些东西无法识别
			break;
		case the_prec_value_range_from_0_to_100:
			printf ("Precision value's range from 0 to 100.\n"); //小数点精度必须为0-100的整数
			break;
		case connot_use_system_identify:
			printf ("Cannot use system identify.\n");//程序本身所用的名字，无法使用系统识别
		default:
			break;
	}
	putchar ('\n');
}

void CmdExecute (
	void
	)
{
	if (error != NULL) {
		return;
	}
	switch (ArgCounter) {
		case 0:
			return;
		case 1: //主要命令 数组在input.cpp中
			if (infocmd == 0) {
				Calculator (); //无命令则计算
				return;
			} else if (infocmd == 1 || infocmd == 2) {
				error = the_command_is_incorrect;  //如果set和view缺少参数就报错
				return;
			} else if (infocmd == 3) { //help不需要参数
				usage (); //显示common.cpp中的帮助
				return;
			} else if (infocmd == 4) { //exit不需要参数
				exit (0);
			}
			  else if (infocmd == 5) { //10.7.2015新增clear清屏
				system("cls");
				logo();
				return;
			}
		case 2: //view参数功能
			if (infocmd != 2 ) {
				error = the_command_is_incorrect;
				return;
			} else {
				if (infoarg == 1) { //参数为prec
					printf ("Precision value: %d\n\n",prec); //显示精度
					return;
				} else if (infoarg == 2) { //参数为all
					printf ("Precision value: %d\n",prec); //显示精度
					PrintVariable (); //输出变量即其它常数
					putchar ('\n');
					return;
				} else {
					VARIABLE *tmp;
					for (int i = 0;Command[1][i] != NULL;i ++) {
						if (!isalpha (Command[1][i])) {
							error = find_some_illegal_word;
							return;
						}
					}
					if (tmp = VariableSearch (VariableList,Command[1])) {
						printf ("%s: ",Command[1]);//显示常数
						if (tmp->Operand.DataSignal == FLOAT) {
							printf ("%f\n",tmp->Operand.Data.Real);
						} else {
							printf ("%d\n",tmp->Operand.Data.Integer);
						}
					} else {
						error = the_var_is_not_seen_before; //参数出错
						return;
					}
					return;
				}
			}
		case 3: //set参数功能
			if (infocmd != 1) {
				error = the_command_is_incorrect;
				return;
			} else {
				Calculator ();
				if (error != NULL) {
					return;
				}			
				if (infoarg == 1) {
					if (ExpressionHead->Term.Operand.DataSignal == FLOAT) {
						error = the_precision_or_mode_only_accept_integral_argument;
						return;
					}
					if (ExpressionHead->Term.Operand.Data.Integer > 100 || ExpressionHead->Term.Operand.Data.Integer < 0) {
						error = the_prec_value_range_from_0_to_100;
						return;
					} //小数精度
					prec = ExpressionHead->Term.Operand.Data.Integer;
					printf ("Precision value set successfully.\n\n"); //精度值设置
					return;
				} else if (infoarg == 2) {
					error = the_command_is_incorrect;
					return;
				} else {
					VARIABLE *tmp;
					for (int i = 0;Command[1][i] != NULL;i ++) {
						if (!isalpha (Command[1][i])) {
							error = find_some_illegal_word;
							return;
						}
					}
					if (tmp = VariableSearch (VariableList,Command[1])) {
						tmp->Operand = ExpressionHead->Term.Operand;
						printf ("Set！\n\n");//命令成功执行
						return;
					}
					tmp = NewVarNode (Command[1],ExpressionHead->Term.Operand);
					VariableListTail = InsertVarNode (VariableListTail,tmp);
					printf ("Set！\n\n");//命令成功执行
				}
			}
	}
}
void Output (
	 void
	 )
{
	CmdExecute ();
	if (error != NULL) {
		PrintError ();
		error = NULL;
		vision = false;
	}
	PrintResult (ExpressionHead);
	ArgCounter = 0;
	infoarg = 0;
	infocmd = 0;
	vision = false;
	DeleteList (ExpressionHead);
	ExpressionHead = NULL;
	FreeCMD ();
	free (Unknown);
}