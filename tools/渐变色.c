#include <graphics.h>
#include<stdio.h>
#include<conio.h>
int main()
{
float H,S,L;
initgraph(600,600);//绘图环境800,600
H=255;//色相
S=0.5;//饱和度
L=0.3f;//亮度
for(int y=0;y<800;y++)
{
L+=0.0005f;
setcolor(HSLtoRGB(H,S,L));
line(0,y,639,y);
}


getch(); 



BeginBatchDraw();//开始批量绘图
setbkmode(TRANSPARENT);//背景是透明的。
for(int i=200; i<800; i++)
{
circle(i,100,40);//画圆
floodfill(i, 100, RGB(254, 249, 233));//填充
FlushBatchDraw();//执行未完成的绘制任务
Sleep(50);//减慢月亮移动速度

cleardevice();//用背景色清空屏幕
}
getch();
closegraph;


}

