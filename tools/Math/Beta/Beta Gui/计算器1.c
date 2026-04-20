#include <dos.h>   /*DOS接口函数*/
#include <math.h>   /*数学函数的定义*/
#include <conio.h>   /*屏幕操作函数*/
#include <stdio.h>   /*I/O函数*/
#include <stdlib.h>   /*库函数*/
#include <stdarg.h>   /*变量长度参数表*/
#include <graphics.h>   /*图形函数*/
#include <string.h>   /*字符串函数*/
#include <ctype.h>   /*字符操作函数*/
#include <bios.h>

/*宏代换定义*/
#define BWIDTH 50   /*按键条的宽度*/
#define BHEIGHT 30   /*按键条的高度*/
#define MAX_SCR 15
#define PI 3.141592654

/*声明函数*/
void graph(void);   /*画图形函数声明*/
void windows(void);   /*绘制窗口界面函数声明*/
void button(int x,int y,int c1,int c2,int c3,char *bt);   /*按键函数声明*/
void scr(char scr_main[MAX_SCR],int error);   /*屏显函数声明*/
int mouse_message(void);   /*鼠标信息函数声明*/
void visbilemouse(void);   /*鼠标可视化函数声明*/
void getmouse(int *x,int *y,int *key);   /*获得鼠标信息函数声明*/
void drawmouse(int *x,int *y,int *z);   /*画鼠标函数声明*/
void jd(int x,int y);   /*按钮焦点函数声明*/
void calculator(int fun_code);   /*实现计算器功能函数声明*/
void clrnum(int n0,int n1);   /*清空Num数组函数声明*/
void adv(void);   /*高级函数功能声明*/
double qiu_zhi(char *bds_start,char *bds_end);   /*求表达式值函数声明*/
long jie_cheng(long n);   /*阶乘函数声明*/

/*定义全局变量*/
int Maxcolor,Maxx,Maxy;   /*定义最大颜色数，边界*/
char Num[2][MAX_SCR]={{0},{0}};   /*定义存储数据的二维数组，分别对应双目运算的数据*/
double Memory=0;   /*定义内存存储数据*/ 
int Flag=0,Num_flag=0;   /*二维数组的第几维数和第几个数*/
char fun=0;   /*功能变量，对应双目运算*/
int Mx,My,Mkey,Mk0=-1;   /*定义鼠标的位置和按键状态，初始键值为-1*/
int jd0=-1,jd1=-1;   /*定义按键焦点，按鼠标键后返回0~29或-1*/
char function[30]={'Q','M','R','S','P','B','7','4','1','0','C','8','5','2','F','A','9','6','3','.','%','/','*','-','+','e','^','K','D','='};   /*定义按键对应的function[fun_code]*/
char Adv_ch[100]={0};   /*定义表达式数组变量*/

/*主函数*/
void main()
{
int message;   /*定义通信变量*/
graph();   /*进入图形模式*/
windows();   /*绘制窗口界面*/
visbilemouse();   /*显示鼠标*/
for (;message=mouse_message();)
     if (message!=-1) calculator(message); /*用鼠标输入数据mouse-message返回jd1到message*/
closegraph();   /*关闭图形模式*/
}   /*message，fun-code，jd1是相互联系的通信变量*/

/*进入图形模式*/
void graph(void)
{
   int   GraphDriver=DETECT,GraphMode,ErrorCode;
   initgraph( &GraphDriver, &GraphMode, "" );   /*初始化图形系统*/
   ErrorCode = graphresult();   /*读初始化结果*/
   if( ErrorCode != grOk )   /*如果初始化时出现错误*/
   {
     printf("Graphics System Error: %s\n",grapherrormsg( ErrorCode ) );   /*显示错误代码*/
     exit(1);   /*退出*/
   }
   /*读取最大颜色数,最大横纵座标*/
   Maxcolor=getmaxcolor();
   Maxx=getmaxx();
   Maxy=getmaxy();
}

/*绘制窗口界面*/
void windows(void)
{
int i,j;
char btext[30][6]={"QUIT"," MC"," MR"," MS"," M+"," \033 "," 7 "," 4 "," 1 "," 0 "," C "," 8 "," 5 "," 2 ","+/-","ADV"," 9 "," 6 "," 3 "," . "," % "," / "," * "," - "," + ","EXP","X^Y","y\0373X","1/X"," = "};/*定义各键的显示符号*/
int ctext[30]={RED,GREEN,GREEN,GREEN,GREEN,RED,BLUE,BLUE,BLUE,BLUE,RED,BLUE,BLUE,BLUE,BLUE,RED,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,BLUE,RED};   /*定义各键的显示颜色*/
setbkcolor(WHITE);   /*定义背景色*/
setcolor(BLUE);   /*设定蓝色模式*/
rectangle(10,10,Maxx-10,Maxy-10);   /*画计算器边框*/
line(10,300,400,300);
line(400,10,400,300);
bar(150,0,245,20);
outtextxy(160,7,"Calculator");
for (i=0;i<=5;i+=1)
     for (j=0;j<=4;j+=1)
         button(25+i*(BWIDTH+10),100+j*(BHEIGHT+10),WHITE,ctext,ctext,btext);   /*画按键的矩形条*/
scr(Num[Flag],0);
}

/*绘制按钮*/
void button(int x,int y,int c1,int c2,int c3,char *bt)
{ 
setfillstyle(SOLID_FILL,c1);   /*用c1颜色填充*/
bar(x,y,x+BWIDTH,y+BHEIGHT);   /*画按键的条形图*/
setcolor(c2);   /*设置c2颜色模式*/
rectangle(x,y,x+BWIDTH,y+BHEIGHT);   /*画矩形框*/
setcolor(c3);   /*设置c3颜色模式*/
outtextxy(x+13,y+13,bt);   /*字符输出定位函数*/
}

/*计算器屏幕显示*/
void scr(char scr_main[MAX_SCR],int error)
{
char memory_s[20];   /*定义内存数组来存储内存数据*/
bar(25,25,375,75);   /*画屏显的条形图*/
setcolor(BLUE);   /*设置蓝色模式*/
rectangle(25,25,375,75);   /*画屏显的边框*/
setcolor(GREEN);   /*设置绿色模式*/
settextstyle(0,0,3);   /*改变字符大小方向函数*/
if (error) {strcpy(scr_main,"error"); setcolor(RED); Flag=0; Num_flag=0; clrnum(0,1); }
outtextxy(30,50,scr_main);   /*字符输出定位函数scr_main中存储的是主屏数据*/
setcolor(RED);   /*设置红色模式*/
settextstyle(0,0,2);   /*改变字符大小方向函数*/
sprintf(memory_s,"M[%f]",Memory);   /*将Memory拷贝到memory-s中再按"M[0.000000]"格式化输出*/
outtextxy(30,30,memory_s);   /*字符输出定位函数，内存显示*/
}

/*鼠标*/
void visbilemouse()/*显示鼠标*/
{ 
union REGS inregs,outregs;
inregs.x.ax=0x01; /*显示鼠标*/ 
int86(0x33,&inregs,&outregs);   /*通用软中断库函数*/ 
}
/*鼠标消息*/
int mouse_message()
{
drawmouse(&Mx,&My,&Mkey);   /*调用画鼠标函数*/
for (;Mk0==Mkey;)
     {
       getmouse(&Mx,&My,&Mkey);   /*调用获得鼠标函数*/
     }
if (Mk0==1)
     {Mk0=-1;return jd1;}
if (Mk0==2)
     {Mk0=-1;return jd1;}
}
/*获取鼠标位置和按键,key=1是左键,key=2是右键*/ 
void getmouse(int *x,int *y,int *key)
{ 
union REGS inregs,outregs; 
inregs.x.ax=3; /*获取鼠标位置和状态也可以用3*/ 
int86(0x33,&inregs,&outregs); /*中断调用*/ 
*x=outregs.x.cx; /*cx寄存器中存的是横坐标*/ 
*y=outregs.x.dx; /*dx寄存器中存的是列坐标*/ 
*key=outregs.x.bx; /*bx寄存器是按键状态*/ 
}
/*按键后,返回当前鼠标的x,y和按键状态,直到按键后才返回*/ 
void drawmouse(int *x,int *y,int *z) /*画鼠标是利用将一个空矩形存入内存中,然后再在该空矩形中画鼠标形状*/ 
{
int a=0,b=0,c=0,a_old=0,b_old=0; /*a,b的值可以随便*/ 
int *ball; /*定义指向内存的存储图形的指针*/ 
ball=malloc(imagesize(a,b,a+20,b+20)); /*返回矩形的大小*/ 
getimage(a,b,a+20,b+20,ball); /*第一次将图形(一个空矩形)存入到内存中,内存中存入的是一个空矩形*/ 
while(c==0) /*直到按键后才返回,不按键一直循环*/ 
{ 
getmouse(&a,&b,&c); /*a,为横坐标,b,为列坐标,c为按键状态*/
if(a<0) a=0; /*保证鼠标左边不出界*/
if(b<0) b=0; /*保证上面不出界*/
if(a>Maxx-20) a=Maxx-20; /*保证右边不出界*/
if(b>Maxy-20) b=Maxy-20; /*保证下边不出界*/
if(a!=a_old || b!=b_old) /*当鼠标移动时*/
{ 
putimage(a_old,b_old,ball,0); /*在a_old,b_old输出图形,用来擦掉原来的鼠标*/ 
jd(a,b);
getimage(a,b,a+20,b+20,ball); /*这条语句是将目前鼠标所在位置的图形存贮到ball里面试着看着有无这条语句的区别*/ 
/*不需要在获取了*/ 
setcolor(BLUE); 
setlinestyle(0,0,1); 
line(a,b,a+15,b+15/2); 
line(a,b,a+15/2,b+15); 
line(a+15/2,b+15,a+10,b+25/2); 
line(a+15,b+15/2,a+25/2,b+10);
line(a+10,b+25/2,a+15,b+35/2);
line(a+25/2,b+10,a+35/2,b+15);
line(a+15,b+35/2,a+35/2,b+15);/*画鼠标*/ 
} 
a_old=a;b_old=b; 
} /*while()结束*/ 
Mk0=c;
*x=a;*y=b;*z=c; /*返回按键后鼠标的位置*/ 
putimage(a,b,ball,0); /*将鼠标擦掉,因为存在ball里面的是一个背景为缺省状态下的一个空矩形*/ 
free(ball); 
}

/*按钮焦点*/
void jd(int x,int y)
{
int i;
jd1=(y-95)/(BHEIGHT+10)+(x-20)/(BWIDTH+10)*5;   /*确定鼠标具体在哪个键上，得到编号来对应键*/
if (jd0==jd1) return;   /*编号未变即鼠标未移位，返回*/
if (!((x>20&&x<380) && (y>95&&y<295))) jd1=-1;   /*超出边界，编号为-1*/
if (jd0!=-1)
     {setcolor(WHITE);
     setlinestyle(0,0,3);
     rectangle(jd0/5*(BWIDTH+10)+20,jd0%5*(BHEIGHT+10)+95,jd0/5*(BWIDTH+10)+30+BWIDTH,jd0%5*(BHEIGHT+10)+105+BHEIGHT);
     }   /*将上次突出显示的黄色擦除*/ 
if (jd1!=-1)
     {setcolor(YELLOW);
     setlinestyle(0,0,3);
     rectangle((x-20)/(BWIDTH+10)*(BWIDTH+10)+20,(y-95)/(BHEIGHT+10)*(BHEIGHT+10)+95,(x-20)/(BWIDTH+10)*(BWIDTH+10)+30+BWIDTH,(y-95)/(BHEIGHT+10)*(BHEIGHT+10)+105+BHEIGHT);
     }   /*突出显示鼠标所在键为黄色*/
jd0=jd1;   /*将上次的鼠标位置赋予jd0，以用于鼠标位置变化的判断和突出显示黄色的擦除*/
}

/*实现计算器功能*/
void calculator(int fun_code)
{
int i,error=0;
int dot_num=0,e_num=0;
int len=0;
char temp_s[20]={0};
for (i=0;Num[Flag];i++) { dot_num+=Num[Flag]=='.'?1:0; e_num+=Num[Flag]=='e'?1:0; len++;}
Num_flag=len;
for (i=Num_flag;i<MAX_SCR;i++) Num[Flag]=0;
switch(function[fun_code])
{case '1':
case '2':
case '3':
case '4':
case '5':
case '6':
case '7':
case '8':
case '9': if (Num_flag<MAX_SCR-1) Num[Flag][Num_flag++]=function[fun_code]; break;
case '0': if (Num_flag<MAX_SCR-1 && (atof(Num[Flag])!=0 || Num[Flag][0]=='.'))
               Num[Flag][Num_flag++]=function[fun_code]; break;
case '.': if (Num_flag<MAX_SCR-1 && dot_num==0) Num[Flag][Num_flag++]=function[fun_code]; dot_num++; break;
case 'e': if (Num_flag<MAX_SCR-1 && e_num==0) Num[Flag][Num_flag++]=function[fun_code]; e_num++; break;
case 'F':
           if (Num[Flag][0]=='-')
               {for (i=0;i<MAX_SCR-1;i++) Num[Flag]=Num[Flag];}/*左移一位*/
           else if (Num_flag<MAX_SCR-1)
               {for (i=MAX_SCR-2;i>0;i--) Num[Flag]=Num[Flag]; Num[Flag][0]='-';}/*右移一位*/
           break;
case '+':
case '-':
case '*':
case '/':
case '%':
case '^':
case 'K': Flag=1; Num_flag=0; fun=function[fun_code]; clrnum(Flag,Flag); break;
case 'B': if (Num_flag>0) Num[Flag][--Num_flag]=0; break;
case 'A': closegraph();adv(); break;
case 'C': Flag=0; Num_flag=0; clrnum(0,1); break;
case 'M': Memory=0; break;
case 'R': clrnum(Flag,Flag); gcvt(Memory,10,temp_s);strcpy(Num[Flag],temp_s); break;
case 'S': Memory=atof(Num[Flag]); break;
case 'P': Memory+=atof(Num[Flag]); break;
case 'D': if (atof(Num[Flag]))
               gcvt(1/atof(Num[Flag]),10,Num[Flag]);
           else
               error=1;
           break;
case '=': Flag=0; Num_flag=0;
           switch(fun)
                 {case '+': gcvt(atof(Num[0])+atof(Num[1]),10,Num[0]); break;
                   case '-': gcvt(atof(Num[0])-atof(Num[1]),10,Num[0]); break;
                   case '*': gcvt(atof(Num[0])*atof(Num[1]),10,Num[0]); break;
                   case '/': if (atof(Num[1]))
                               gcvt(atof(Num[0])/atof(Num[1]),10,Num[0]);
                             else error=1;
                             break;
                   case '%': gcvt((long)atof(Num[0])%(long)atof(Num[1]),10,Num[0]); break;
                   case '^': gcvt(pow(atof(Num[0]),atof(Num[1])),10,Num[0]); break;
                   case 'K': if (atof(Num[1]))
                               gcvt(pow(atof(Num[0]),1/atof(Num[1])),10,Num[0]);
                             else error=1;
                             break;
                 }
           break;
}
scr(Num[Flag],error);
}
/*清空Num数组*/
void clrnum(int n0,int n1)
{
int i;
for (i=0;i<MAX_SCR;i++) Num[n0]=Num[n1]=0;
}
/*高级功能*/
void adv()
{
char *i;
printf("For example:\n[1+(2-3)]*4/{5%6}+1e3+sin(pi/4)-arctan(1)*4+3^4+5!+ln2.718-log(2+3)|(10^3)\nInput esc to quit\n");
for (;1;)
{
   printf("Please input:\n");
   gets(Adv_ch);
   if (!strcmp(Adv_ch,"quit") || !strcmp(Adv_ch,"esc")) exit(0);
   for (i=Adv_ch;i<Adv_ch+strlen(Adv_ch);i++)
{
       if (*i=='[' || *i=='{') *i='(';
       if (*i==']' || *i=='}') *i=')';
       }
   printf("=%f\n",qiu_zhi(Adv_ch,Adv_ch+strlen(Adv_ch)-1));
}
}
/*求表达式的值*/
double qiu_zhi(char *bds_start,char *bds_end)
{
char *now;
char temp[100]={0};
int kuo_hao=0,i=0;
for (now=bds_start+1;now<=bds_end;now++)
     {if (*now=='+' || *now=='-' || *now=='*' || *now=='/' || *now=='%') i++;
       if (*now=='^' || *now=='!' || *now=='s' || *now=='c' || *now=='t' || *now=='l' || *now=='g' || *now=='n') i++;
     }
if (!i)
     {
     now=bds_start;
     for (;now<=bds_end;now++) temp[now-bds_start]=*now;
     if (temp[0]=='p' && temp[1]=='i') return PI;
     return (atof(temp));
     }
for (now=bds_end;now>=bds_start;now--)
     {
       kuo_hao+=(*now==')'?1:0); kuo_hao-=(*now=='('?1:0);
       if (*now=='+' && kuo_hao==0) return(qiu_zhi(bds_start,now-1)+qiu_zhi(now+1,bds_end));
       if (*now=='-' && kuo_hao==0) return(qiu_zhi(bds_start,now-1)-qiu_zhi(now+1,bds_end));
     }
for (now=bds_end;now>=bds_start;now--)
     {
       kuo_hao+=(*now==')'?1:0); kuo_hao-=(*now=='('?1:0);
       if (*now=='*' && kuo_hao==0) return(qiu_zhi(bds_start,now-1)*qiu_zhi(now+1,bds_end));
       if (*now=='/' && kuo_hao==0) return(qiu_zhi(bds_start,now-1)/qiu_zhi(now+1,bds_end));
       if (*now=='%' && kuo_hao==0) return((long)qiu_zhi(bds_start,now-1)%(long)qiu_zhi(now+1,bds_end));
}
for (now=bds_end;now>=bds_start;now--)
     {
       kuo_hao+=(*now==')'?1:0); kuo_hao-=(*now=='('?1:0);
       if (*(now-3)=='a' && *(now-2)=='r' && *(now-1)=='c' && *now=='s' && *(now+1)=='i' && *(now+2)=='n' && kuo_hao==0)
           return(asin(qiu_zhi(now+3,bds_end)));
       if (*(now-3)=='a' && *(now-2)=='r' && *(now-1)=='c' && *now=='c' && *(now+1)=='o' && *(now+2)=='s' && kuo_hao==0)
           return(acos(qiu_zhi(now+3,bds_end)));
       if (*(now-3)=='a' && *(now-2)=='r' && *(now-1)=='c' && *now=='t' && *(now+1)=='a' && *(now+2)=='n' && kuo_hao==0)
           return(atan(qiu_zhi(now+3,bds_end)));
       if (*(now-3)=='a' && *(now-2)=='r' && *(now-1)=='c' && *now=='c' && *(now+1)=='s' && *(now+2)=='c' && kuo_hao==0)
           return(asin(1/qiu_zhi(now+3,bds_end)));
       if (*(now-3)=='a' && *(now-2)=='r' && *(now-1)=='c' && *now=='s' && *(now+1)=='e' && *(now+2)=='c' && kuo_hao==0)
           return(acos(1/qiu_zhi(now+3,bds_end)));
       if (*(now-3)=='a' && *(now-2)=='r' && *(now-1)=='c' && *now=='c' && *(now+1)=='o' && *(now+2)=='t' && kuo_hao==0)
           return(atan(1/qiu_zhi(now+3,bds_end)));
       if (*now=='s' && *(now+1)=='i' && *(now+2)=='n' && kuo_hao==0) return(sin(qiu_zhi(now+3,bds_end)));
       if (*now=='c' && *(now+1)=='o' && *(now+2)=='s' && kuo_hao==0) return(cos(qiu_zhi(now+3,bds_end)));
       if (*now=='t' && *(now+1)=='a' && *(now+2)=='n' && kuo_hao==0) return(tan(qiu_zhi(now+3,bds_end)));
       if (*now=='c' && *(now+1)=='s' && *(now+2)=='c' && kuo_hao==0) return(1/sin(qiu_zhi(now+3,bds_end)));
       if (*now=='s' && *(now+1)=='e' && *(now+2)=='c' && kuo_hao==0) return(1/cos(qiu_zhi(now+3,bds_end)));
       if (*now=='c' && *(now+1)=='o' && *(now+2)=='t' && kuo_hao==0) return(1/tan(qiu_zhi(now+3,bds_end)));
     }
for (now=bds_end;now>=bds_start;now--)
     {
       char *x;
       kuo_hao+=(*now==')'?1:0); kuo_hao-=(*now=='('?1:0);
       if (*now=='l' && *(now+1)=='n' && kuo_hao==0) return(log(qiu_zhi(now+2,bds_end)));
       if (*now=='|' && kuo_hao==0)
         {x=now;
           for (;x>=bds_start;x--)
               if (*x=='l' && *(x+1)=='o' && *(x+2)=='g') break;
           return(log10(qiu_zhi(now+1,bds_end))/log10(qiu_zhi(x+3,now-1)));
         }
     }
for (now=bds_end;now>=bds_start;now--)
{
       kuo_hao+=(*now==')'?1:0); kuo_hao-=(*now=='('?1:0);
       if (*now=='^' && kuo_hao==0) return(pow(qiu_zhi(bds_start,now-1),qiu_zhi(now+1,bds_end)));
       if (*now=='!' && kuo_hao==0) return(jie_cheng((long)qiu_zhi(bds_start,now-1)));
     }
if (*bds_start=='(' && *bds_end==')') return qiu_zhi(bds_start+1,bds_end-1);
printf("error");
}
/*计算阶乘*/
long jie_cheng(long n)
{
long jc=n;
for (n--;n>0;n--) jc*=n;
return jc;
}
