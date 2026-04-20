#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define Esc 27
#define Tab 9

void needle(char* s,char* carriage,int start)//needle意为“用针缝”
{
int size_carriage=(int)strlen(carriage);
int i,j;
for(j=0;j<size_carriage;j++)
{
   for(i=(int)strlen(s);i>=start;i--)
    s[i+1]=s[i];
   s[i+1]=carriage[j];
   start=i+2;
} 
}
double factorial(double d)//factorial意为“阶乘”
{
return d==0?1:d*factorial(d-1);
}
void handle(char* carriage)//handle意为“处理”
{
void find_start(char*,int*);
char* save1,*save2,ch;
char op[111];
double d1,d2;
int start,i;
find_start(carriage,&start);
ch=carriage[start];
d1=strtod(carriage,&save1);//strtod是库函数，功能是将字符串carriage中出现的第一个浮点数转化为double,并将剩余字符储存在save1中
if(ch=='!')
{
   sprintf(op,"%g",factorial(d1));//springf是库函数，功能是将显示在屏幕上的内容储存在op中
   strcpy(carriage,op);
   return;
}
for(i=0;i<(int)strlen(save1);i++)//对于第一个不是'+'或'-'或数字的字符串，strtod无法作用。所以得去掉诸如"*22"字符串中的'*'
   save1[i]=save1[i+1];
d2=strtod(save1,&save2);
switch(ch)
{
   case '*':sprintf(op,"%.32g",d1*d2);break;
   case '/':sprintf(op,"%.32g",d1/d2);break;
   case '+':sprintf(op,"%.16g",d1+d2);break;
   case '-':sprintf(op,"%.16g",d1-d2);
}
strcpy(carriage,op);
}
void delete(char* s,int start,int end)//delete意为“删除”
{
int i,j;
int size=(int)strlen(s);
for(i=end;i>=start;i--)
   for(j=i;j<size;j++)
    s[j]=s[j+1];
}
void copy(char* s,char* carriage,int start,int end)//copy意为“复制”
{
int i;
for(i=0;start<=end;i++,start++)
   carriage[i]=s[start];
carriage[i]='\0'; 
}
void scissor(char* s,char* carriage,int* start)//scissor意为“用剪刀剪”
{
int sta,end;
for(sta=*start-1;(s[sta]>='0'&&s[sta]<='9')||s[sta]=='.';sta--);
if(sta!=0||s[*start]=='!') //处理式子是-2+3或-2!的特殊情况
   sta++;
if(s[*start]=='!')//'!'是单目运算符
   end=*start;
else
{
   for(end=*start+1;(s[end]>='0'&&s[end]<='9')||s[end]=='.';end++);
   if((s[end-1]=='*'||s[end-1]=='/')&&(s[end]=='+'||s[end]=='-'))//处理式子是2*-2等的特殊情况
    for(end++;(s[end]>='0'&&s[end]<='9')||s[end]=='.';end++);
   end--;
}
copy(s,carriage,sta,end);
delete(s,sta,end);
*start=sta;//记住等下针线函数needle要开始缝的地方
}
void find_start(char* s,int* start)//find_start意为“找到操作符号开始处”
{
int i;
int size=(int)strlen(s);
//由优先级决定从上而下的顺序
for(i=0;i<size;i++)
   if(s[i]=='!')
   {
    *start=i;
    return;
   }
for(i=0;i<size;i++)
   if(s[i]=='*'||s[i]=='/')
   {
    *start=i;
    return;
   }
if(s[0]=='+'||s[0]=='-')
{
   for(*start=1;(s[*start]>='0'&&s[*start]<='9')||s[*start]=='.';(*start)++);
   return;
}
for(i=0;i<size;i++)
   if(s[i]=='+'||s[i]=='-')
   {
	   *start=i;
    return;
   } 
}
int judge(char* s)//judge意为“判断”
{
int i;
int size=(int)strlen(s);
for(i=1;i<size;i++)
   if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='!')
    return 1;
return 0;  
}
void count(char* s)//count意为“计算”
{
int start,i;
char carriage[555];//carriage意为“运载体”
while(judge(s))//判断式子是否还需要进行运算
{
   for(i=0;i<(int)strlen(s);i++)//此循环作用是将式子中出现的'--'替换为'+'
   {
    for(;s[i]!='-'&&i<(int)strlen(s);i++);
    if(s[i+1]=='-')
    {
     delete(s,i,i+1);
     needle(s,"+",i);
    }

   }
   find_start(s,&start);//让下标start指向式子应该最先开始处理的运算符
   scissor(s,carriage,&start);//用剪刀scissor将start指向的运算符及相对应的操作数剪下并储存在运载体carriage上
   handle(carriage);//处理该运载体，并将运载体上运载的式子的计算结果储存在运载体上
   needle(s,carriage,start);//见函数simplify中的说明
}
}
void simplify(char* s)//simplify意为“简化”
{
char carriage[555];//carriage意为“运载体”
int start,end,i;
int size=(int)strlen(s);
while(1)
{
   for(i=0;s[i]!='('&&i<size;i++);
   if(i==size)
    break;//说明式子已不含括号
   for(end=0;s[end]!=')';end++);//使end下标指向式子中第一个出现')'的地方
   end--;
   for(start=end;s[start]!='(';start--);//寻找与上面一个')'配对的'('
   start++;
   copy(s,carriage,start,end);//将括号里的内容复制给运载体carriage
   delete(s,start-1,end+1);//删除整个括号及其里面的内容
   count(carriage);//计算运载体运载的表达式，运算结果储存在运载体上
   needle(s,carriage,start-1);//将运载体运载过来的结果用针线needle缝在刚才删除式子s括号及其内容的地方
}
}
int main()
{
int i=0;
char s[555],ch;
puts(" 本程序不对用户输入数据进行检测:");
puts(" 式子不能含有空格及其他非计算字符;");
puts(" 按任意一个键开始，按回车键显示运算结果;");
while(1)
{
   i++;
   ch=getch();
   if(Esc==ch)
    break;
   if(Tab==ch)
   {
    system("cls");//清除当前屏幕
	puts("显示运算结果后：按“Esc”键退出,按“Tab”键清除当前屏幕");
   }
   if(i==1)
   {
    system("cls");
    puts("显示运算结果后：按“Esc”键退出,按“Tab”键清除当前屏幕");
   }
   puts("————");
   gets(s);
   simplify(s);
   count(s);
   puts(s);
   //实验数据：23.243*(5!-23.123/.133+(2!-13/13.23)*(2!-.235)-((4!-20)!/2!)-32*(3!+2.23/(2*3)!))
   //其正确结果是：-5953.9401265774754346182917611489
}
puts("谢谢使用!");
getch();
return 0;
}
