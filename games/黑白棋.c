//咱们熟悉的头文件君
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <WINDOWS.H>   //注意大小写


//用#define函数宏定义
#define QIPAN 9    //棋盘大小
#define HEI "●"   //黑子
#define BAI "○"   //白子
#define STEP 2      //光标移动步长
#define LEFT 75   //  方向键 ←
#define UP 72   //方向键 →
#define RIGHT 77     //方向键 ↑
#define DOWN 80    //方向键   ↓
#define ESC 27    //Esc 退出键
#define SPACE 32    //Space 空格键
#define ENTER 13   //Enter 确认键(回车或换行)




int QP[QIPAN][QIPAN];   //棋盘数组
COORD GBIAO;   //当前光标位置
COORD TISHI;   //提示信息位置
int shunxu;  //开局执棋顺序
int hei;  //黑棋数目
int bai;   //白棋数目
int qinum=5;   //棋子的总数




void putdown(COORD now,int sx)   //空格下子
{
int i,j;
hei=bai=0;   //将黑棋和白棋数目重新置为0
void gotoxy(int x,int y,int color);
gotoxy(now.X,now.Y,0xa0);
printf("%s",sx==1?HEI:BAI);   //打印黑或白棋子
QP[now.X/2][now.Y/2]=sx==1?1:2;   //记录棋盘数组 黑色为1,白色为2
for(i=0;i<QIPAN;i++)   //计算棋盘变化后的黑棋和白棋数目
for(j=0;j<QIPAN;j++)
{
if(QP[i][j]==1)
hei++;
else if(QP[i][j]==2)
bai++;
}
}


void map(void)    //画棋盘（规格8×8＝64）
{
int i,j;
for(i=0;i<=QIPAN*2;++i)
{
for(j=0;j<=QIPAN*2;++j)
{
if(0==j||QIPAN*2==j)printf(" ");
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
else printf(" ");
}
}
}
printf("\n");
}
printf("\n\n\n  ←↑↓→ 方向键控制光标\n"
"  Space 空格键下子\n"
"  Enter键  交换下棋顺序\n"
"  Esc  退出游戏\n");
//提前打印中间位置的4颗棋子，黑白交错相间
GBIAO.X=QIPAN-1;
GBIAO.Y=QIPAN+1;
putdown(GBIAO,1);
GBIAO.Y-=2;
putdown(GBIAO,2);
GBIAO.X+=2;
putdown(GBIAO,1);
GBIAO.Y+=2;
putdown(GBIAO,2);
}


void gotoxy(int x,int y,int color) //移动光标
{
static HANDLE hOut; 
static COORD position;  //坐标
position.X = x*2;
position.Y = y;
hOut==NULL?(hOut = GetStdHandle(STD_OUTPUT_HANDLE)):hOut; 
SetConsoleCursorPosition(hOut, position); 
SetConsoleTextAttribute(hOut, (WORD)color);
}


void printgb(COORD now)  //打印光标
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

void printQP(COORD now,int temp)  //补全棋盘
{
if(temp==LEFT)
{
if(now.X==14&&now.Y>2&&now.Y<16)
{
gotoxy(now.X+3,now.Y-1,0xa0);
printf("┨");
gotoxy(now.X+3,now.Y+1,0xa0);
printf("┨");
}
else if(now.Y==2&&now.X<14)
{
gotoxy(now.X+3,now.Y-1,0xa0);
printf("┯");
gotoxy(now.X+3,now.Y+1,0xa0);
printf("┼");
}
else if(now.Y==16&&now.X<14)
{
gotoxy(now.X+3,now.Y+1,0xa0);
printf("┷");
gotoxy(now.X+3,now.Y-1,0xa0);
printf("┼");
}
else if(now.X==14&&now.Y==2)
{
gotoxy(now.X+3,now.Y-1,0xa0);
printf("┓");
gotoxy(now.X+3,now.Y+1,0xa0);
printf("┨");
}
else if(now.X==14&&now.Y==16)
{
gotoxy(now.X+3,now.Y+1,0xa0);
printf("┛");
gotoxy(now.X+3,now.Y-1,0xa0);
printf("┨");
}
else
{
gotoxy(now.X+3,now.Y+1,0xa0);
printf("┼");
gotoxy(now.X+3,now.Y-1,0xa0);
printf("┼");
}
}
else if(temp==RIGHT)
{
if(now.X==4&&now.Y>2&&now.Y<16)
{
gotoxy(now.X-3,now.Y-1,0xa0);
printf("┠");
gotoxy(now.X-3,now.Y+1,0xa0);
printf("┠");
}
else if(now.Y==2&&now.X>4)
{
gotoxy(now.X-3,now.Y-1,0xa0);
printf("┯");
gotoxy(now.X-3,now.Y+1,0xa0);
printf("┼");
}
else if(now.Y==16&&now.X>4)
{
gotoxy(now.X-3,now.Y+1,0xa0);
printf("┷");
gotoxy(now.X-3,now.Y-1,0xa0);
printf("┼");
}
else if(now.X==4&&now.Y==2)
{
gotoxy(now.X-3,now.Y-1,0xa0);
printf("┏");
gotoxy(now.X-3,now.Y+1,0xa0);
printf("┠");
}
else if(now.X==4&&now.Y==16)
{
gotoxy(now.X-3,now.Y-1,0xa0);
printf("┠");
gotoxy(now.X-3,now.Y+1,0xa0);
printf("┗");
}
else
{
gotoxy(now.X-3,now.Y-1,0xa0);
printf("┼");
gotoxy(now.X-3,now.Y+1,0xa0);
printf("┼");
}
}
else if(temp==UP)
{
if(now.Y==14&&now.X>2&&now.X<16)
{
gotoxy(now.X-1,now.Y+3,0xa0);
printf("┷");
gotoxy(now.X+1,now.Y+3,0xa0);
printf("┷");
}
else if(now.X==2&&now.Y<14)
{
gotoxy(now.X-1,now.Y+3,0xa0);
printf("┠");
gotoxy(now.X+1,now.Y+3,0xa0);
printf("┼");
}
else if(now.X==16&&now.Y<14)
{
gotoxy(now.X+1,now.Y+3,0xa0);
printf("┨");
gotoxy(now.X-1,now.Y+3,0xa0);
printf("┼");
}
else if(now.X==2&&now.Y==14)
{
gotoxy(now.X+1,now.Y+3,0xa0);
printf("┷");
gotoxy(now.X-1,now.Y+3,0xa0);
printf("┗");
}
else if(now.X==16&&now.Y==14)
{
gotoxy(now.X-1,now.Y+3,0xa0);
printf("┷");
gotoxy(now.X+1,now.Y+3,0xa0);
printf("┛");
}
else
{
gotoxy(now.X-1,now.Y+3,0xa0);
printf("┼");
gotoxy(now.X+1,now.Y+3,0xa0);
printf("┼");
}
}
else if(temp==DOWN)
{
if(now.Y==4&&now.X>2&&now.X<16)
{
gotoxy(now.X-1,now.Y-3,0xa0);
printf("┯");
gotoxy(now.X+1,now.Y-3,0xa0);
printf("┯");
}
else if(now.X==2&&now.Y>4)
{
gotoxy(now.X-1,now.Y-3,0xa0);
printf("┠");
gotoxy(now.X+1,now.Y-3,0xa0);
printf("┼");
}
else if(now.X==16&&now.Y>4)
{
gotoxy(now.X+1,now.Y-3,0xa0);
printf("┨");
gotoxy(now.X-1,now.Y-3,0xa0);
printf("┼");
}
else if(now.X==2&&now.Y==4)
{
gotoxy(now.X-1,now.Y-3,0xa0);
printf("┏");
gotoxy(now.X+1,now.Y-3,0xa0);
printf("┯");
}
else if(now.X==16&&now.Y==4)
{
gotoxy(now.X-1,now.Y-3,0xa0);
printf("┯");
gotoxy(now.X+1,now.Y-3,0xa0);
printf("┓");
}
else
{
gotoxy(now.X-1,now.Y-3,0xa0);
printf("┼");
gotoxy(now.X+1,now.Y-3,0xa0);
printf("┼");
}
}
}


void deletegb(COORD now)  //删除光标
{
gotoxy(now.X-1,now.Y-1,0xa0);
printf(" ");
gotoxy(now.X-1,now.Y+1,0xa0);
printf(" ");
gotoxy(now.X+1,now.Y-1,0xa0);
printf(" ");
gotoxy(now.X+1,now.Y+1,0xa0);
printf(" ");
gotoxy(now.X,now.Y,0xa0);
}


void move(COORD *now,int x,int y)  //按键移动光标
{
deletegb(*now);
(*now).X+=2*x;
(*now).Y+=2*y;
printgb(*now);
}


void printts(void)  //打印提示信息
{
gotoxy(TISHI.X,TISHI.Y,0xa0);
printf("  当前黑白棋比分:  %d : %d\n"
"  请 %s 下子!\n\n"
,hei,bai,shunxu==1?"黑棋":"白棋");
gotoxy(GBIAO.X,GBIAO.Y,0xa0);
}


char getkey(void)  //取键盘按键值
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


int victory()   //判断胜利
{

int i,j;
hei=bai=0;   //重新计算黑棋白棋数目
for(i=0;i<QIPAN;i++)
for(j=0;j<QIPAN;j++)
{
if(QP[i][j]==1)
hei++;
else if(QP[i][j]==2)
bai++;
}
if(qinum==64||hei==0&&bai!=0||bai==0&&hei!=0)
return hei>bai?1:2;
else if(qinum==64&&hei==bai)  //平局
return 3;
else 
return 0;
}

void change_color(int i,int j,int n,int sx)  //每次下子后改变棋盘的黑棋白棋颜色
{
int x,y,l,m;
l=i;
m=j;
x=GBIAO.X/2;
y=GBIAO.Y/2;
//改变落子成功后8个方向的棋子颜色，重新将光标移动到落子位置
switch(n)
{
case 0:while(i<x){i++;putdown(GBIAO,sx);GBIAO.X-=2;}
GBIAO.X=GBIAO.X+(x-l)*2;
break;
case 1:while(i>x){i--;putdown(GBIAO,sx);GBIAO.X+=2;}
GBIAO.X=GBIAO.X-(l-x)*2;
break;
case 2:while(j<y){j++;putdown(GBIAO,sx);GBIAO.Y-=2;}
GBIAO.Y=GBIAO.Y+(y-m)*2;
break;
case 3:while(j>y){j--;putdown(GBIAO,sx);GBIAO.Y+=2;}
GBIAO.Y=GBIAO.Y-(m-y)*2;
break;
case 4:while(i>x&&j>y){i--;j--;putdown(GBIAO,sx);GBIAO.X+=2;GBIAO.Y+=2;}
GBIAO.X=GBIAO.X-(l-x)*2;GBIAO.Y=GBIAO.Y-(m-y)*2;
break;
case 5:while(i<x&&j<y){i++;j++;putdown(GBIAO,sx);GBIAO.X-=2;GBIAO.Y-=2;}
GBIAO.X=GBIAO.X+(x-l)*2;GBIAO.Y=GBIAO.Y+(y-m)*2;
break;
case 6:while(i>x&&j<y){i--;j++;putdown(GBIAO,sx);GBIAO.X+=2;GBIAO.Y-=2;}
GBIAO.X=GBIAO.X-(l-x)*2;GBIAO.Y=GBIAO.Y+(y-m)*2;
break;
case 7:while(i<x&&j>y){i++;j--;putdown(GBIAO,sx);GBIAO.X-=2;GBIAO.Y+=2;}
GBIAO.X=GBIAO.X+(x-l)*2;GBIAO.Y=GBIAO.Y-(m-y)*2;
break;
}
}


int check_color(int sx)  //检查落子是否符合规则，为真改变棋子颜色
{
int i,j,flag[8];  //记录可能的8个方向的情况
int x=GBIAO.X/2;  //取出当前光标对应在棋盘数组中的位置
int y=GBIAO.Y/2;
int tmp=QP[x][y];  //取出当然位置黑白棋状态 黑 为1, 白为2;
i=x,j=y;
if(QP[x-1][y]!=sx&&QP[x-1][y]!=0)
for(;i>0;i--)
{
if(QP[i-1][j]==0)
{
flag[0]=0;
break;
}
else if(QP[i-1][j]==sx)
{
flag[0]=1;
change_color(i-1,j,0,sx);
break;
}
}
i=x,j=y;
if(QP[x+1][y]!=sx&&QP[x+1][y]!=0)
for(;i<QIPAN;i++)
{
if(QP[i+1][j]==0)
{
flag[1]=0;
break;
}
else if(QP[i+1][j]==sx)
{
flag[1]=1;
change_color(i+1,j,1,sx);
break;
}
}
i=x,j=y;
if(QP[x][y-1]!=sx&&QP[x][y-1]!=0)
for(;j>0;j--)
{
if(QP[i][j-1]==0)
{
flag[2]=0;
break;
}
else if(QP[i][j-1]==sx)
{
flag[2]=1;
change_color(i,j-1,2,sx);
break;
}
}
i=x,j=y;
if(QP[x][y+1]!=sx&&QP[x][y+1]!=0)
for(;j<QIPAN;j++)
{
if(QP[i][j+1]==0)
{
flag[3]=0;
break;
}
else if(QP[i][j+1]==sx)
{
flag[3]=1;
change_color(i,j+1,3,sx);
break;
}
}
i=x,j=y;
if(QP[x+1][y+1]!=sx&&QP[x+1][y+1]!=0)
for(;j<QIPAN,i<QIPAN;j++,i++)
{
if(QP[i+1][j+1]==0)
{
flag[4]=0;
break;
}
else if(QP[i+1][j+1]==sx)
{
flag[4]=1;
change_color(i+1,j+1,4,sx);
break;
}
}
i=x,j=y;
if(QP[x-1][y-1]!=sx&&QP[x-1][y-1]!=0)
for(;j>0,i>0;j--,i--)
{
if(QP[i-1][j-1]==0)
{
flag[5]=0;
break;
}
else if(QP[i-1][j-1]==sx)
{
flag[5]=1;
change_color(i-1,j-1,5,sx);
break;
}
}
i=x,j=y;
if(QP[x+1][y-1]!=sx&&QP[x+1][y-1]!=0)
for(;j>0,i<QIPAN;j--,i++)
{
if(QP[i+1][j-1]==0)
{
flag[6]=0;
break;
}
else if(QP[i+1][j-1]==sx)
{
flag[6]=1;
change_color(i+1,j-1,6,sx);
break;
}
}
i=x,j=y;
if(QP[x-1][y+1]!=sx&&QP[x-1][y+1]!=0)
for(;j<QIPAN,i>0;j++,i--)
{
if(QP[i-1][j+1]==0)
{
flag[7]=0;
break;
}
else if(QP[i-1][j+1]==sx)
{
flag[7]=1;
change_color(i-1,j+1,7,sx);
break;
}
}
if(flag[0]==1||flag[1]==1||flag[2]==1||flag[3]==1||flag[4]==1||flag[5]==1||flag[6]==1||flag[7]==1)
return 1;
else 
return 0;
}
int main()
{
HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
int dx,dy,key;   //初始化光标偏移量
CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };   //隐藏光标
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
system("title 黑白棋 —— By Eisenberg Andrew Roland");   //设置标题
system("mode con cols=63 lines=40");   //设置窗口大小
system("color A0");  //设置颜色
shunxu=1;  //设置黑子先手
char chtmp[256];  //胜利方字符串
map();
GBIAO.X=GBIAO.Y=QIPAN-1;  //初始化光标为棋盘中间
TISHI.X=0,TISHI.Y=2*QIPAN+1;  //初始化提示位置坐标
printgb(GBIAO);  //移动光标到中间
printts();  //打印提示信息
//开始游戏
key=dx=dy=0;  //初始化光标偏移量以及键值
while(!_kbhit())  //如果有输入
{
switch(key=getkey())
{
case LEFT:if(GBIAO.X>2&&GBIAO.X<=2*QIPAN-2)dx=-1;  //前面 的判断为光标是否在棋盘内
break;
case RIGHT:if(GBIAO.X>=2&&GBIAO.X<2*QIPAN-2)dx=1;
break;
case UP:if(GBIAO.Y>2&&GBIAO.Y<=2*QIPAN-2)dy=-1;
break;
case DOWN:if(GBIAO.Y>=2&&GBIAO.Y<2*QIPAN-2)dy=1;
break;
case SPACE:if(QP[GBIAO.X/2][GBIAO.Y/2]==0&&check_color(shunxu)==1)  //如果棋盘数组中此位置还没有被下子
{
putdown(GBIAO,shunxu);
if(victory())  //胜利判断
{
printts();
sprintf(chtmp," %s胜利!",victory()==1?"黑方":"白方");
MessageBox(hwnd,chtmp,TEXT("恭喜"),MB_OK);return 0;
if(victory()==3)//平局
MessageBox(hwnd,TEXT("和局！"),TEXT("提示"),MB_OK);return 0;
}
qinum++;
shunxu=shunxu==1?2:1;  //交换下子顺序

}
break;
case ENTER: shunxu=shunxu==1?2:1;  //交换下子顺序
break;
case ESC:MessageBox(hwnd,TEXT("退出游戏！"),TEXT("提示"),MB_OK);return 0;
break;
}
if(dx!=0||dy!=0)
move(&GBIAO,dx,dy);
printQP(GBIAO,key);
printgb(GBIAO);
key=dx=dy=0;  //重置光标偏移量以及键值
printts();  //打印提示信息


}
return 0;
}
