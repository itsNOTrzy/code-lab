//头文件
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <WINDOWS.H>

//宏定义
#define QIPAN 15	//棋盘大小
#define MAXHUI 5	//最大悔棋次数
#define HEI "●"	//黑子
#define BAI "○"	//白子
#define STEP 2		//光标移动步长
#define LEFT 75
#define UP 72
#define RIGHT 77 
#define DOWN 80
#define ESC 27
#define SPACE 32
#define ENTER 13

//函数声明
void map(void);		//绘制棋盘
void gotoxy(int x,int y,int color);		//移动光标
char getkey(void);		//获取键盘输入键值
void move(COORD *now,int x,int y);		//按键移动光标
void printgb(COORD now);		//打印光标
void deletegb(COORD now);		//删除光标
void printts(void);				//打印提示信息
void putdown(COORD now,int sx); //下子
int victory(); //胜利判断

//全局变量
int QP[QIPAN][QIPAN];	//棋盘数组
int	qinum;				//已经下子的总棋子数
COORD GBIAO;			//当前光标位置
COORD OLDPOS;			//上次放入棋子的坐标
COORD TISHI;			//提示信息位置
int shunxu;				//开局执棋顺序
int huihei;				//黑子悔棋次数
int huibai;				//白子悔棋次数

//主函数
int main(void) 
{
	HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
	int dx,dy,key,flag=0;				//初始化光标偏移量为0,flag 标记已经悔棋一次,不许连续悔棋
	char chtmp[256];				//胜利方字符串
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };								//隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	system("title Gobang Deluxe");	//设置标题
    system("Color 0a");
    system("mode con: cols=65 lines=21");

    printf("\n\n\n\n                          Gobang Deluxe\n"); //游戏名
    printf("         Copyright(C) Eisenberg Andrew Roland 2012-2015\n\n\n"); //申明版权
    printf("                   Press any key to continue.");

    system("pause>nul");
	system("mode con cols=63 lines=40");//设置窗口大小
	system("color a0");					//设置黑子先手
    
    
	huibai=huihei=MAXHUI;				//设置最大悔棋次数
	map();
	GBIAO.X=GBIAO.Y=QIPAN;				//初始化光标为棋盘中间
	TISHI.X=0,TISHI.Y=2*QIPAN+1;		//初始化提示位置坐标
	printgb(GBIAO);						//移动光标到中间
	printts();						//打印提示信息
	//开始游戏
	key=dx=dy=0;				//初始化光标偏移量以及键值
	while(!_kbhit())				//如果有输入
	{
		switch(key=getkey())
		{
		case LEFT:	if(GBIAO.X>1&&GBIAO.X<=2*QIPAN-1)dx=-1;	//前面 的判断为光标是否在棋盘内
			break;
		case RIGHT:	if(GBIAO.X>=1&&GBIAO.X<2*QIPAN-1)dx=1;
			break;
		case UP:	if(GBIAO.Y>1&&GBIAO.Y<=2*QIPAN-1)dy=-1;
			break;
		case DOWN:	if(GBIAO.Y>=1&&GBIAO.Y<2*QIPAN-1)dy=1;
			break;
		case SPACE:	if(QP[GBIAO.X/2][GBIAO.Y/2]==0)		//如果棋盘数组中此位置还没有被下子
					{ 
						putdown(GBIAO,shunxu);
						if(victory())					//胜利判断
						{
							sprintf(chtmp," %s 胜利!",shunxu?"黑方":"白方");
							MessageBox(hwnd,chtmp,TEXT("恭喜"),MB_OK);return 0;
						}
						shunxu=shunxu?0:1;				//交换下子顺序
						qinum++;						//总棋子总累加1
						OLDPOS.X=GBIAO.X;				//记录本次下子坐标  以防悔棋
						OLDPOS.Y=GBIAO.Y;
						if(flag)flag=0;					//如果上次是悔棋的,就将悔棋标记清除
					}
					if(qinum==QIPAN*QIPAN)				//棋盘放满也没有分出胜负
					{
						MessageBox(hwnd,TEXT("和局!"),TEXT("提示"),MB_OK);return 0;	
					}
			break;
		case ESC:	MessageBox(hwnd,TEXT("退出游戏!"),TEXT("提示"),MB_OK);return 0;
			break;
		case ENTER:	if(!flag)								//如果没有连续悔棋
					{	
						if(qinum>0&&(shunxu?huibai:huihei)) //根据当前执子顺序 判断要悔棋的是白方还是黑方,再根据其可用悔棋次数来判断是否可以执行悔棋!
						{
							sprintf(chtmp,"  %s 申请悔棋成功!",shunxu?"白方":"黑方");
							MessageBox(hwnd,chtmp,TEXT("提示"),MB_OK);	
							gotoxy(OLDPOS.X,OLDPOS.Y,0xa0);
							printf("┼");					//还原上一个棋子的位置为棋盘
							QP[OLDPOS.X/2][OLDPOS.Y/2]=0;	//还原棋盘数组内的上一个棋子
							if(shunxu)--huibai;				//如果当前顺序是黑子,那么悔棋的是白方,白方可用悔棋次数-1;
							else --huihei;
							shunxu=shunxu?0:1;				//交换下子顺序
							flag=1;
						}
						else if(qinum==0);
						else MessageBox(hwnd,TEXT("您的悔棋次数已经用完!"),TEXT("错误"),MB_OK);
					}
			break;
		default:		
			break;
		}
		if(dx!=0||dy!=0)
			move(&GBIAO,dx,dy);
		key=dx=dy=0;				//重置光标偏移量以及键值
		printts();					//打印提示信息
	}
	getchar();
	return 0;
}

void gotoxy(int x,int y,int color)						//移动光标
{
	static HANDLE hOut;  	
	static COORD position;      //坐标	
	position.X = x*2;
	position.Y = y;	
	hOut==NULL?(hOut = GetStdHandle(STD_OUTPUT_HANDLE)):hOut;  
	SetConsoleCursorPosition(hOut, position);            
	SetConsoleTextAttribute(hOut, (WORD)color);
}

char getkey(void)											//取键盘按键值
{
	char ch1,ch2;
	ch1=getch();
	if(ch1==ESC||ch1==SPACE||ch1==ENTER)
		return ch1;
	else if(ch1==-32)
	{
		ch2=getch();
		return ch2;
	}
	else return 0;
}

void map(void)
{
	int i,j;
	for(i=0;i<=QIPAN*2;++i)
	{	
		for(j=0;j<=QIPAN*2;++j)
		{
			if(0==j||QIPAN*2==j)printf("  ");
			else if(1==i||QIPAN*2-1==i)
			{
				if(1==i)
				{
					if(1==j)printf("┏");
					else if(QIPAN*2-1==j)printf("┓");
					else if(j%2)printf("┯");
					else printf("━");
				}
				else
				{
					if(1==j)printf("┗");
					else if(QIPAN*2-1==j)printf("┛");
					else if(j%2)printf("┷");
					else printf("━");
				}				
			}
			else if(i>1&&i<QIPAN*2-1)
			{	
				if(i%2)
				{	
					if(1==j)printf("┠");
					else if(QIPAN*2-1==j)printf("┨");
					else if(j%2)printf("┼");
					else printf("—");
				}
				else
				{
					if(1==j||QIPAN*2-1==j)printf("┃");	
					else if(j%2)printf("│");
					else printf("  ");
				}
			}
		}
		printf("\n");
	}
	printf("\n\n\n\n    ←↑↓→ 方向键控制光标, 空格键下子\n"
		   "    Enter 悔棋（每局双方各有%2d 次悔棋机会）\n"
		   "    Esc 退出游戏\n",MAXHUI);
}

void move(COORD *now,int x,int y)			//按键移动光标
{	
	deletegb(*now);
	(*now).X+=2*x;
	(*now).Y+=2*y;
	printgb(*now);	
}

void printgb(COORD now)						//打印光标
{
	gotoxy(now.X-1,now.Y-1,0xa0);
	printf("┏");
	gotoxy(now.X-1,now.Y+1,0xa0);
	printf("┗");
	gotoxy(now.X+1,now.Y-1,0xa0);
	printf("┓");
	gotoxy(now.X+1,now.Y+1,0xa0);
	printf("┛");
	gotoxy(now.X,now.Y,0xa0);
}

void deletegb(COORD now)					//删除光标
{
	gotoxy(now.X-1,now.Y-1,0xa0);
	printf("  ");
	gotoxy(now.X-1,now.Y+1,0xa0);
	printf("  ");
	gotoxy(now.X+1,now.Y-1,0xa0);
	printf("  ");
	gotoxy(now.X+1,now.Y+1,0xa0);
	printf("  ");
	gotoxy(now.X,now.Y,0xa0);
}

void printts(void)							//打印提示信息
{
	gotoxy(TISHI.X,TISHI.Y,0xa0);
	printf(	"    黑棋还剩余%2d 次悔棋机会\n"
            "    白棋还剩余%2d 次悔棋机会\n"
			"    请%s下子！\n\n\n"
			,huihei,huibai,shunxu?"黑棋":"白棋");
	gotoxy(GBIAO.X,GBIAO.Y,0xa0);
}

void putdown(COORD now,int sx)			//空格下子
{
	gotoxy(now.X,now.Y,0xa0);
	printf("%s",sx?HEI:BAI);		//打印黑或白棋子
	QP[now.X/2][now.Y/2]=sx?1:2;	//记录棋盘数组 黑色为1,白色为2
}

int victory()		//判断是否胜利
{	
	int i,j,num;
	int x=GBIAO.X/2;			//取出当前光标对应在棋盘数组中的位置
	int y=GBIAO.Y/2;
	int tmp=QP[x][y];			//取出当然位置黑白棋状态 黑 为1, 白为2;
	i=x,j=y,num=0;				//横向向右				第一种横向
	while(i>=1&&i<=QIPAN&&tmp==QP[i][j]){++num;++i;}
	i=x,j=y;					//横向向左
	while(i>=1&&i<=QIPAN&&tmp==QP[i][j]){++num;--i;} if(num>=6)return 1;
	i=x,j=y,num=0;				//纵向向下				第二种纵向
	while(j>=1&&j<=QIPAN&&tmp==QP[i][j]){++num;++j;}
	i=x,j=y;					//纵向向上
	while(j>=1&&j<=QIPAN&&tmp==QP[i][j]){++num;--j;} if(num>=6)return 1;
	i=x,j=y,num=0;				//左斜向向下			第三种左斜
	while(j>=1&&j<=QIPAN&&tmp==QP[i][j]){++num;++i;++j;}
	i=x,j=y;					//左斜向向上
	while(j>=1&&j<=QIPAN&&tmp==QP[i][j]){++num;--i;--j;} if(num>=6)return 1;
	i=x,j=y,num=0;				//右斜向向下			第四种右斜
	while(j>=1&&j<=QIPAN&&tmp==QP[i][j]){++num;--i;++j;}
	i=x,j=y;					//右斜向向上
	while(j>=1&&j<=QIPAN&&tmp==QP[i][j]){++num;++i;--j;} if(num>=6)return 1;
	return 0;
}
