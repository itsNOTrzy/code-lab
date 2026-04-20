#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#define R 4 /*球半径*/
struct box
{ int x;
int y;
int color;
}a[6][14];
int Keystate;
int MouseExist;
int MouseButton;
int MouseX;
int MouseY=400;
int dx=1,dy=1; /*计算球的反弹角度等数据*/
int sizex=18,sizey=10; /*整个框架的宽度和长度*/
void draw(int x,int y) 
/* x, y为左上角坐标sizex,sizey为长和宽*/
{
int sizx=sizex-1;
int sizy=sizey-1;
setcolor(15);/*这里最好用白色*/
line(x,y,x+sizx-1,y);
line(x,y+1,x+sizx-2,y+1);
line(x,y,x,y+sizy-1);
line(x+1,y,x+1,y+sizy-2);
setcolor(8);/*这里最好用深灰色*/
line(x+1,y+sizy,x+sizx,y+sizy);
line(x+2,y+sizy-1,x+sizx,y+sizy-1);
line(x+sizx-1,y+1,x+sizx-1,y+sizy);
line(x+sizx,y+2,x+sizx,y+sizy);
setcolor(7);/*这里最好用灰色*/
putpixel(x,y+sizy,3);
putpixel(x+1,y+sizy-1,3);
putpixel(x+sizx,y,3);
putpixel(x+sizx-1,y+1,3);
setfillstyle(1, 7);/*这里最好用灰色,设置填充模式*/
bar(x+2,y+2,x+sizx-2,y+sizy-2);
}
void picture() /*画框架*/
{ int i,j;
setcolor(15);
rectangle(99,49,413,451);
for(i=0;i<6;i++)
for(j=0;j<14;j++)
{ a[i][j].color=0;
a[i][j].x=104+j*22;
a[i][j].y=54+i*14;
draw(104+j*22,54+i*14);
}
sizex=50,sizey=5;
}
/*鼠标光标显示*/
void MouseOn(int x,int y)
{
draw(x,y);
}
/*隐藏鼠标光标*/
void MouseOff()
{
int x,y;
x=MouseX;
y=MouseY;
setfillstyle(1,0);
bar(x,y,x+sizex,y+sizey);
}
/*鼠标是否加载
MouseExist:1=加载
0=未加载
MouseButton:鼠标按键数目 */
void MouseLoad()
{
_AX=0x00;
geninterrupt(0x33);
MouseExist=_AX;
MouseButton=_BX;
}
/*鼠标状态值初始化*/
void MouseReset()
{
_AX=0x00;
geninterrupt(0x33);
}
/*设置挡板左右边界
lx:左边界
gx:右边界 */
void MouseSetX(int lx,int rx)
{
_CX=lx;
_DX=rx;
_AX=0x07;
geninterrupt(0x33);
}
/*设置挡板上下边界
uy:上边界
dy:下边界 */
void MouseSetY(int uy,int dy)
{
_CX=uy;
_DX=dy;
_AX=0x08;
geninterrupt(0x33);
}
/*设置挡板位置
x:横向坐标
y:纵向坐标 */
void MouseSetXY(int x,int y)
{
_CX=x;
_DX=y;
_AX=0x04;
geninterrupt(0x33);
}
/*设置鼠标灵敏度(挡板左右移动速度)(缺省值:vx=8,vy=1)值越大速度越慢 */
void MouseSpeed(int vx,int vy)
{
_CX=vx;
_DX=vy;
_AX=0x0f;
geninterrupt(0x33);
}
/*获取挡板位置*/
void MouseGetXY()
{
_AX=0x03;
geninterrupt(0x33);
MouseX=_CX;
MouseY=_DX;
}
void MouseStatus()/*鼠标按键情况*/
{
int x;
int status;
status=0;/*默认鼠标没有移动*/
x=MouseX;
if(x==MouseX&&status==0) /*如果鼠标没有移动*/
{
MouseGetXY();
if(MouseX!=x)
if(MouseX+50<413)
status=1;
}
if(status) /*移动情况下才重新显示光标*/
{
setfillstyle(1,0);
bar(x,MouseY,x+sizex,MouseY+sizey);
MouseOn(MouseX,MouseY); /*新位置显示*/
}
}
void Move()
{int ballX; /*球的圆心*/
int ballY=MouseY-R;
int i,j,t=0;
randomize();
while(ballX=random(409))
if(ballX>=105 && ballX<=408)
break;
while(kbhit)
{
MouseStatus();
if(ballY<=(58-R)) /*碰撞砖块则反弹*/
dy*=(-1);
if(ballX>=(413-R)||ballX<=(108-R)) /*碰撞框架边缘则反弹*/
dx*=(-1);
setcolor(YELLOW);
circle(ballX+=dx,ballY-=dy,R-1);
delay(2500);
setcolor(0);
circle(ballX,ballY,R-1);
for(i=0;i<6;i++)
for(j=0;j<14;j++) /*判断是否撞击框架*/
if(t<84&&a[i][j].color==0 && ballX>=a[i][j].x &&
ballX<=a[i][j].x+18
&& ballY>=a[i][j].y && ballY<=a[i][j].y+10)
{t++;
dy*=(-1);
a[i][j].color=1;
setfillstyle(1,0);
bar(a[i][j].x,a[i][j].y,a[i][j].x+18,a[i][j].y+10);
}
if(ballX==MouseX||ballX==MouseX-1||
ballX==MouseX-2&&ballX==(MouseX+50+2)||
ballX==(MouseX+50+1)||ballX==(MouseX+50)) /*碰撞挡板则反弹*/
if(ballY>=(MouseY-R))
{ dx*=(-1);
dy*=(-1); /*原路返回*/
}
if(ballX>MouseX && ballX<(MouseX+50)) /*碰撞挡板则反弹*/
if(ballY>=(MouseY-R))
dy*=(-1);
if(t==84) /*如果获胜*/
{ sleep(1);
cleardevice();
setcolor(RED);
settextstyle(0,0,4);
outtextxy(100,200,"You Win");sleep(1); /*显示获胜信息*/
break;
}
if(ballY>MouseY)   /*如果失败或退出游戏*/
{ sleep(1);
cleardevice();
setcolor(RED);
settextstyle(0,0,6);
setcolor(7);
outtextxy(103, 203, "GAME OVER");
setcolor(RED);
outtextxy(100, 200, "GAME OVER");
sleep(7); /*显示"游戏结束"信息*/
break;
}
}
}
void main()
{int gd=DETECT,gm;
initgraph(&gd,&gm,"c:\\tc");
picture();
MouseSetX(100,362); /*设置挡板移动的范围*/
MouseSetY(MouseY,MouseY); /*挡板只能左右移动*/
MouseSetXY(150,MouseY); /*挡板的初始位置*/
MouseOn(MouseX,MouseY); /*第一次显示光标(挡板)*/
Move();
closegraph();
}
