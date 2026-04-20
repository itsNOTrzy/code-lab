#include "public.h"
extern short mode;
char unknownstring[MAXSIZE+2];
bool isblank (char c)
/*	功能：判断一个字符是否为空白字符
	参数：c	- 要判断的字符
	返回值：如果是返回 true 否则返回 false	*/
{
	if (c >= 7 && c <= 10 || c == 13 || c == 32) {
		return true;
	} else {
		return false;
	}
}
int type_char(char c,bool is_reform)
/*	功能：检测字符类型
	参数：c要判断的字符，is_reform是否进行了sin，cos等运算符的替换
	返回值：字符类型*/
{
	if(c>='0' && c<='9'|| c=='.')		//包含操作数字符：0~9 .
		return NUMBER;
	if (c>=40 &&c<=47 && c!=',' && c!='.' ||c=='^'||c=='%'||c==END)   //包含操作符字符：( ) * + - / ^
		return OPERATOR;
	if(is_reform==true &&(c>=19 &&c<=25))//除0~9和已定义运算符外，其余部分ascII码值作为自定义运算符
		return OPERATOR;						//正号+19,负号- 20,sin 21,cos 22,tan 23,lg 24,ln 25
	if (c>='A'&&c<='Z'||c>='a'&&c<='z')				  //所有大小写字母
		return ALPHA_CHAR;
	return OTHER_CHAR;
}
bool validity_check(char *str,bool is_reform)
/*  功能：字符合法性检测
	参数：str字符串指针，is_reform同上，reform之前允许英文字母存在，reform之后不允许
	返回值：如果是返回 true 否则返回 false
*/
{
	int i=0;
	if(is_reform == false)
		while (str[i]!=NULL)
		{
			if(str[i]>='A'&&str[i]<='Z')//把所有的变为小写
				str[i]+=32;
			if (type_char(str[i],false) == OTHER_CHAR)
				return false;
			i++;
		}
	else
		while (str[i]!=NULL)
		{
			if (type_char(str[i],true) == ALPHA_CHAR)
				return false;
			i++;
		}
	return true;
}
void recognize_command(char *str)//命令识别，识别命令后，将字串设为空，防止其他函数进行误操作
{	
	if(str[0]=='q'&&str[1]=='u'&&str[2]=='i'&&str[3]=='t'&&str[4]==END)
	{	massage(NULL);str[0]=NULL;return; }
	if(str[0]=='d'&&str[1]=='e'&&str[2]=='c'&&str[3]==END)
	{	mode=DECIAML_MODE;event_report(set_successfully_explicit);str[0]=NULL;return; }
	if(str[0]=='r'&&str[1]=='a'&&str[2]=='d'&&str[3]==END)
	{	mode=RADIAN_MODE;event_report(set_successfully_explicit);str[0]=NULL;return; }	
	if(str[0]=='c'&&str[1]=='l'&&str[2]=='s'&&str[3]==END)
	{ str[0]=NULL; event_report(set_successfully_implicit);system("cls");logo();}
}
void string_reform(char *str)
{//进行sin，cos等运算符的替换,reform之前允许英文字母存在，reform之后不允许
	int i;
	if(validity_check(str,false)==false)
	{	
		event_report(found_some_illegal_characters);//非法字符
		str[0]=NULL;
	}
	if(str[0]!=NULL) //calculate.cpp中含有函数具体作用
		for(i=0;str[i+2]!=END;i++)
		{	
			if(str[i]=='s'&&str[i+1]=='i'&&str[i+2]=='n')
			{
				str[i++]=21;str[i++]=' ';str[i]=' ';
				continue;
			}
			if(str[i]=='c'&&str[i+1]=='o'&&str[i+2]=='s')
			{
				str[i++]=22;str[i++]=' ';str[i]=' ';
				continue;
			}
			if(str[i]=='t'&&str[i+1]=='a'&&str[i+2]=='n')
			{
				str[i++]=23;str[i++]=' ';str[i]=' ';
				continue;
			}
			if(str[i]=='l'&&str[i+1]=='g')
			{
				str[i++]=24;str[i]=' ';
				continue;
			}
			if(str[i]=='l'&&str[i+1]=='n')
			{
				str[i++]=25;str[i]=' ';
				continue;
			}
			if(str[i]=='a'&&str[i+1]=='b'&&str[i+2]=='s') //绝对值 10.10.2015新增
			{
				str[i++]=26;str[i++]=' ';str[i]=' ';
				continue;
			}
		}
	if(validity_check(str,true)==false)
	{
		event_report(found_some_illegal_words_or_undefined_commands);//非法字符
		str[0]=NULL;
	}
}
void input()    //输入表达式，储存非空白字符
{
	int i=0;char c;
	while((c=getchar()) != '\n')
	{
		if(i==MAXSIZE)
		{
			event_report(the_string_exceeds_the_length_of_the_provisions);
			unknownstring[0]=NULL;
			return;
		}
		if(isblank(c) == false)
			unknownstring[i++]=c;
	}
	if(i)
	{
		unknownstring[i]=END;
		unknownstring[i+1]=NULL;
		recognize_command(unknownstring);
		string_reform(unknownstring);
	}
	else
		event_report(the_expression_is_null);
}