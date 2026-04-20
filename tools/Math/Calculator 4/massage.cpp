#include "public.h"
#include "windows.h"
RUN_EVENT event_box;
void event_report(short event_type)
/*功能：记录事件类别，只记录第一次发生的事件
事件incident值被改写，就加上写保护is_write_protec*/
{
	if(event_box.is_write_protected==false)
	{
		event_box.incident=event_type;
		event_box.is_write_protected=true;
	}
}
void ini_incident()
/*功能：事件初始化*/
{
	event_box.incident=NULL;
	event_box.is_write_protected=false;
}
void massage(short event_type)
/*功能：输出事件*/
{
	switch (event_type)
	{
	case 0:printf("\n\n\n       Thanks for using, have a good time, Bye！\n\n       ");
		Sleep(500);exit(EXIT_SUCCESS);
	case 1: printf("Error[1]> [Null]Stack Underflow！\n\n");
		return;
	case 2: printf("Error[2]> [Full]Stack Overflow！\n\n");
		return;
	case 3: printf("Syntax Error[3]> Illegal words or undefined commands！\n\n");
		return;
	case 4: printf("Syntax Error[4]> Iillegal characters！\n\n");
		return;
	case 5: printf("Syntax Error[5]> Real number is illegal！\n\n");
		return;
	case 6: printf("Syntax Error[6]> Brackets aren't match！\n\n");
		return;
	case 7: printf("Syntax Error[7]> Operator between the brackets is missing！\n\n");
		return;
	case 8: printf("Math Error[8]> Divisor cannot be zero！\n\n");
		return;
	case 9: printf("Math Error[9]> Operand in tangent must not be integer multiple of 90 or half π！\n\n");
		return;
	case 10: printf("Math Error[10]> Antilogarithm must be greater than zero！\n\n");
		return;
	case 11: printf("Syntax Error[11]> Operator before the percent sign must be a number！\n\n");
		return;
	case 12: printf("Syntax Error[12]> String exceeds the length of the provisions(%d characters)！\n\n",MAXSIZE);
		return;
	case 13: printf("Syntax Error[13]> Missing a operator before the unary operator！\n\n");
		return;
	case 14: printf("Syntax Error[14]> Missing a operand before the binary operator！\n\n");
		return;
	case 15: printf("Syntax Error[15]> Missing a operand before the right brecket！\n\n");
		return;
	case 16: printf("Syntax Error[16]> Missing a operator after the right brecket！\n\n");
		return;
	case 17: printf("Syntax Error[17]> Missing a operator before the left brecket！\n\n");
		return;	
	case 18: printf("Syntax Error[18]> Just input expression...\n\n");
		return;
	case 19: printf("Syntax Error[19]> Just input element between the match beckets...\n\n");
		return;
	case 20: printf("Command> Set successfully.\n\n");
		return;
	case 21:
		return;		
	default: printf("Undefined Error[20]！\n\n");
		return;
	}
}