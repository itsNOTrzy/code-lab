#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "conio2.h"

char argv_[1000][80];
int argc_;
char FileName[100];
int only=0;
char only_[76];
int startp=1;

void putsm(char * str)
{
	int l=(int)((80-strlen(str))/2);
	gotoxy(1,(int)wherey);
	int i;
	for (i=1;i<=l;i++)
		putchar(' ');
	printf(str);
	for (i=l+strlen(str)+1;i<=80;i++)
		putchar(' ');
}

int check(int nu,char * st[])
{
	int _i=0;
	int __i;
	int _n_;
	while (_i<=nu-1)
	{
		_i++;
		if (st[_i][0]!='/') break;
		if (st[_i][1]=='?')
		{
			puts("显示一个分页菜单，鼠标点击进行翻页、选择。返回其编号并将当前页码写入文件page中。\nby Heptagon196\n用法一:menu [/S] [string] [/A] [int] /C int int int int string string ……\n前四个1至15的整数分别表示选中部分前景、后景及未选中部分的前景、后景，每个数字可以为以下任何值之一:\n\n    0 = 黑色       8 = 灰色\n    1 = 蓝色       9 = 淡蓝色\n    2 = 绿色       10 = 淡绿色\n    3 = 湖蓝色     11 = 淡浅绿色\n    4 = 红色       12 = 淡红色\n    5 = 紫色       13 = 淡紫色\n    6 = 黄色       14 = 淡黄色\n    7 = 白色       15 = 亮白色\n/S	将下一个参数作为菜单每一页均存在的一个选项(该选项返回0)\n/P	将下一个参数作为起始页码\n用法二:menu [/S] [string] [/A] [int] /F [FILENAME]从文件中读取参数，具体内容同用法一。(不加/C)\n");
			return 1;
		}
		if ((st[_i][1]=='S')||(st[_i][1]=='s'))
		{
			only=1;
			_i++;
			sprintf(only_,"%s",st[_i]);
			continue;
		}
		if ((st[_i][1]=='P')||(st[_i][1]=='p'))
		{
			_i++;
			startp=atoi(st[_i]);
			continue;
		}
		
		if ((st[_i][1]=='C')||(st[_i][1]=='c'))
		{
			_n_=1;
			for (__i=_i+1;__i<=nu-1;__i++)
			{
				sprintf(argv_[_n_],"%s",st[__i]);
				_n_++;
			}
			argc_=nu-_i;
			return 0;
		}
		if ((st[_i][1]=='F')||(st[_i][1]=='f'))
		{
			sprintf(FileName,"%s",st[_i+1]);
			return 2;
		}
	}
	return 1;
}

int main(int argc,char * argv[])
{
	system("mode con cols=80 lines=28");
	int chk;
	if ((chk=check(argc,argv))==1) return 0;
	if (chk==2)
	{
	FILE * fp_;
	fp_=fopen(FileName,"r");
	int n_=0;
	char ch_;
	int i_;
	for (i_=1;i_<=1000;i_++)
	{
	while (((ch_=fgetc(fp_))!=' ')&&(ch_!=EOF))
	{
		argv_[i_][n_]=ch_;
		n_++;
	}
	if (ch_==EOF) break;
	n_=0;
	}
	argc_=i_+1;
	fclose(fp_);
	}
	hidecursor();
	HWND hConsole = FindWindow("ConsoleWindowClass", NULL);
	INPUT_RECORD rec;
	DWORD evk;
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	FILE * fp;
	int n=startp;
	int i;
	system("cls");
	int tc1=atoi(argv_[1]);
	int tb1=atoi(argv_[2]);
	int tc2=atoi(argv_[3]);
	int tb2=atoi(argv_[4]);
	char ch;
	int page=(int)(argc_-5)/23+1;
	if (argc_-page*23+18==0)
		page--;
	if (n>page) n=1;
	SetConsoleMode(hIn, ENABLE_MOUSE_INPUT);
	while (1)
	{
		B:
		color(tc2,tb2);
		gotoxy(1,1);
		for (i=1;i<=23;i++)
			if ((n-1)*23+i+4>argc_-1)
				putsm("");
			else
				putsm(argv_[(n-1)*23+i+4]);
		if (only)
		{
			gotoxy(1,25);
			putsm(only_);
		}
		gotoxy(1,1);
		color(tc1,tb1);
		putsm(argv_[(n-1)*23+5]);
		gotoxy(1,24);
		char preport[10];
		sprintf(preport,"%02d  /  %02d",n,page);
		putsm(preport);
		for (i=1;i<=23;i++)
		{
			gotoxy(1,i);
			puts("  ");
			gotoxy(79,i);
			puts("  ");
		}
		gotoxy(1,12);
		putchar('<');
		gotoxy(2,11);
		putchar('/');
		gotoxy(2,13);
		putchar('\\');
		gotoxy(80,12);
		putchar('>');
		gotoxy(79,11);
		putchar('\\');
		gotoxy(79,13);
		putchar('/');
		int line=1;
		int line2;
		color(tc1,tb1);
		A:
		while (1)
		{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hConsole, &pt);
		ReadConsoleInput(hIn, &rec, 1, &evk);
  		if (rec.EventType == MOUSE_EVENT && rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //鼠标左键
			if ((pt.x/8+1>2)&&(pt.x/8+1<79))
			{
				system("mode con cols=80 lines=25");
				unhidecursor();	
				char last[20];
				sprintf(last,"(echo %d)>page",n);
				system(last);
  				return (line==25)?0:(n-1)*23+line;
			}
			else
				if (pt.x/8+1<=2)
				{
					if ((n==page)&&(n==1)) goto A;
					n--;
					if (!n)
						n=page;
					goto B;
				}
				else
				{
					if ((n==page)&&(n==1)) goto A;
					n++;
					if (n==page+1)
						n=1;
					goto B;
				}
		line2=line;
		line=(int)(pt.y/16+1);
		if ((((n==page)&&(line>=argc_+19-page*23))||(line>=24))&&((line!=25)||(!only)))
			line=(n==page)?argc_+18-page*23:23;
		if (line<=0)
			line=1;
		if (line==line2) continue;
		gotoxy(1,line2);
		color(tc2,tb2);
		if (line2==25)
		putsm(only_);
		else
		putsm(argv_[(n-1)*23+line2+4]);
		color(tc1,tb1);
		if (line2!=25)
		{
			gotoxy(1,line2);
			puts("  ");
			gotoxy(79,line2);
			puts("  ");
			if (line2==12)
			{
				gotoxy(1,12);
				putchar('<');
				gotoxy(80,12);
				putchar('>');
			}
			if (line2==11)
			{
				gotoxy(2,11);
				putchar('/');
				gotoxy(79,11);
				putchar('\\');
			}
			if (line2==13)
			{
				gotoxy(2,13);
				putchar('\\');
				gotoxy(79,13);
				putchar('/');
			}
		}
		gotoxy(1,line);
		if (line==25)
		putsm(only_);
		else
		putsm(argv_[(n-1)*23+line+4]);
		if (line==12)
		{
			gotoxy(1,12);
			putchar('<');
			gotoxy(80,12);
			putchar('>');
		}
		if (line==11)
		{
			gotoxy(2,11);
			putchar('/');
			gotoxy(79,11);
			putchar('\\');
		}
		if (line==13)
		{
			gotoxy(2,13);
			putchar('\\');
			gotoxy(79,13);
			putchar('/');
		}
		}
	}
	return 0;
}
