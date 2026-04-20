#include <stdio.h>
#include <graphics.h>




int ini(void);
int game(void);


int ini(void)
{
int x,y,a=0,b;
initgraph(384,512);
randomize();
setbkmode(TRANSPARENT);
HWND hWnd = getHWnd(); // 获得窗口句柄
SetWindowText(hWnd, TEXT("Flappy Bird V1.0 x32"));// 使用 API 函数修改窗口名称
PIMAGE loading=newimage();
getimage(loading,"依赖包\\图片\\其他\\加载.png");
putimage(0,0,loading);
delay_ms(500);
delimage(loading);
PIMAGE main_interface=newimage();
getimage(main_interface,"依赖包\\图片\\其他\\开始.png");
PIMAGE ground=newimage();
getimage(ground,"依赖包\\图片\\背景\\地.png");
PIMAGE bird_u = newimage();
PIMAGE bird_m = newimage();
PIMAGE bird_d = newimage();
getimage(bird_u, "依赖包\\图片\\鸟\\上.png");
getimage(bird_m, "依赖包\\图片\\鸟\\中.png");
getimage(bird_d, "依赖包\\图片\\鸟\\下.png");
while(1)
{
a-=2;
if(a<=0)
a=384;
putimage(0,0,main_interface);
putimage(a,448,ground);
putimage((a-384),448,ground);

b=a%128;
if(b>=0&&b<32)
putimage_withalpha(NULL,bird_m,175,220);
if(b>=32&&b<64)
putimage_withalpha(NULL,bird_u,175,216);
if(b>=64&&b<96)
putimage_withalpha(NULL,bird_m,175,220);
if(b>=96&&b<=128)
putimage_withalpha(NULL,bird_d,175,224);
setcolor(WHITE);
xyprintf(120,480,"By Steve Joe Ran in 2.26.2015"); 
if(keystate(VK_LBUTTON))
{
mousepos(&x,&y);
if(x>10&&x<170&&y>350&&y<450)
break;
}
delay_fps(77);
cleardevice();
}
delimage(main_interface);
delimage(ground);
delimage(bird_u);
delimage(bird_m);
delimage(bird_d);
}


int game(void)
{
int bird_h=250;
int shijian=0;
int a=0,b=0,c=0,point=0;
int v=0;
FILE *fp;
int point_jilu;
int x,y;
struct zhangai
{
int x;
int h;
}zhuzi[3];
PIMAGE bk=newimage();
PIMAGE bird_up=newimage();
PIMAGE bird_middle=newimage();
PIMAGE bird_down=newimage();
PIMAGE ground=newimage();
PIMAGE course_up=newimage();
PIMAGE course_down=newimage();
PIMAGE course_middle=newimage();
PIMAGE zhuzi_z=newimage();
PIMAGE zhuzi_f=newimage();
PIMAGE gameover=newimage();
PIMAGE jifenpai=newimage();
PIMAGE again=newimage();
PIMAGE paihangbang=newimage();
PIMAGE tong=newimage();
PIMAGE yin=newimage();
PIMAGE gold=newimage();
PIMAGE bai=newimage(); 
getimage(bird_up, "依赖包\\图片\\鸟\\上.png");
getimage(bird_middle, "依赖包\\图片\\鸟\\中.png");
getimage(bird_down, "依赖包\\图片\\鸟\\下.png");
getimage(ground,"依赖包\\图片\\背景\\地.png");
getimage(zhuzi_z,"依赖包\\图片\\柱子\\正.png");
getimage(zhuzi_f,"依赖包\\图片\\柱子\\反.png");
getimage(gameover,"依赖包\\图片\\其他\\gameover.png");
getimage(jifenpai,"依赖包\\图片\\其他\\记分牌.png");
getimage(again,"依赖包\\图片\\其他\\重来.png");
getimage(paihangbang,"依赖包\\图片\\其他\\排行榜.png");
getimage(tong,"依赖包\\图片\\奖牌\\铜牌.png");
getimage(yin,"依赖包\\图片\\奖牌\\银牌.png");
getimage(gold,"依赖包\\图片\\奖牌\\金牌.png");
getimage(bai,"依赖包\\图片\\奖牌\\白金牌.png");
while(1)
{
if(random(3)==0)
{
getimage(bk,"依赖包\\图片\\背景\\黑夜.png");
getimage(course_up,"依赖包\\图片\\引导\\晚上\\上.png");
getimage(course_middle,"依赖包\\图片\\引导\\晚上\\中.png");
getimage(course_down,"依赖包\\图片\\引导\\晚上\\下.png");
}
else
{
getimage(bk,"依赖包\\图片\\背景\\白天.png");
getimage(course_up,"依赖包\\图片\\引导\\白天\\上.png");
getimage(course_middle,"依赖包\\图片\\引导\\白天\\中.png");
getimage(course_down,"依赖包\\图片\\引导\\白天\\下.png");
}
shijian=0;
while(1)//引导界面 
{
shijian+=1;
a=shijian%64;
if(a>=0&&a<16)
putimage(0,0,course_up);
if(a>=16&&a<32)
putimage(0,0,course_middle);
if(a>=32&&a<48)
putimage(0,0,course_down);
if(a>=48&&a<64)
putimage(0,0,course_middle);
a=shijian%192;
a*=-2;
putimage(a,448,ground);
putimage((a+384),448,ground);
delay_fps(77);
cleardevice();
if(shijian>=30&&keystate(VK_LBUTTON))
break;
}
//初始化 
shijian=0;
bird_h=250;
point=0;
zhuzi[0].x=700;
zhuzi[1].x=940;
zhuzi[2].x=1180;
a=0;
b=0;
c=0;
while(1)//游戏界面 
{
shijian+=1;
cleardevice();
/************检 测用户操作并执行 ******************/
if((shijian-b)>1&&keystate(VK_LBUTTON))
{
v=-180;
b=shijian;
}
/***************计算高度************************/ 
v+=9.8;
bird_h+=((v*1.9)/77);
/***************柱子的移动**********************/
for(c=0;c<3;c++)
{
zhuzi[c].x-=2;
if(zhuzi[c].x<=-70)
zhuzi[c].x=650;
if(zhuzi[c].x==512)
{
zhuzi[c].h=(random(200))+200;
}
}

/***************计算分数************************/
for(c=0;c<3;c++)
{
if(zhuzi[c].x==100)
point++;
}

/***************显示图像************************/
//显示背景 
putimage(0,0,bk);

//显示柱子
for(c=0;c<3;c++)
{
putimage_withalpha(NULL,zhuzi_z,zhuzi[c].x,zhuzi[c].h);
putimage_withalpha(NULL,zhuzi_f,zhuzi[c].x,(zhuzi[c].h-400));
}
//显示地面 
a=shijian%192;
a*=-2;
putimage(a,448,ground);
putimage((a+384),448,ground);

//显示鸟 
a=shijian%16;
if(a>=0&&a<4)
putimage_withalpha(NULL,bird_middle,100,bird_h);
if(a>=4&&a<8)
putimage_withalpha(NULL,bird_up,100,bird_h);
if(a>=8&&a<12)
putimage_withalpha(NULL,bird_middle,100,bird_h);
if(a>=12&&a<16)
putimage_withalpha(NULL,bird_down,100,bird_h);





/****************判断碰撞***********************/
if(zhuzi[0].x>=30&&zhuzi[0].x<=145&&(zhuzi[0].h<(bird_h+32)||(zhuzi[0].h-150)>bird_h))
break;
if(zhuzi[1].x>=30&&zhuzi[1].x<=145&&(zhuzi[1].h<(bird_h+32)||(zhuzi[1].h-150)>bird_h))
break;
if(zhuzi[2].x>=30&&zhuzi[2].x<=145&&(zhuzi[2].h<(bird_h+32)||(zhuzi[2].h-150)>bird_h))
break;
if(bird_h>415)
break;
/*******************显示分数**********************/
setcolor(WHITE);
setfont(-50,0,"幼圆");
xyprintf(180,40,"%d",point);

delay_fps(77);
}


putimage_withalpha(NULL,gameover,55,60);
putimage_withalpha(NULL,jifenpai,35,150);
putimage_withalpha(NULL,again,35,350);
putimage_withalpha(NULL,paihangbang,200,350);
if(point>=10&&point<20)
putimage(67,200,tong);
if(point>=20&&point<30)
putimage(67,200,yin);
if(point>=30&&point<40)
putimage(67,200,gold);
if(point>=40)
putimage(67,200,bai);
setfont(-25,0,"幼圆");
xyprintf(270,195,"%d",point);
fp=fopen("依赖包\\记录.txt","r");
fscanf(fp,"%d",&point_jilu);
fclose(fp);
if(point>point_jilu)
point_jilu=point;
fp=fopen("依赖包\\记录.txt","w");
fprintf(fp,"%d",point_jilu);
fclose(fp);
xyprintf(270,260,"%d",point_jilu);
a=1;
while(a)
{
if(keystate(VK_LBUTTON))
{
mousepos(&x,&y);
if(x>10&&x<170&&y>350&&y<450)
a=0;
}
delay_fps(60);
}
}
delimage(bird_up);
delimage(bird_middle);
delimage(bird_down);

}


int WinMain(void)
{
ini();
game();
closegraph();
return 0;
}
