#include<stdio.h>
#include<math.h>
#include<malloc.h>

double jisuan(char a[])
{
int i=1,j,k,m,cnt=0,t1=0,t2=0,t3=0;
    char nibo[50],zhan2[50];
double x,n,l,z=0,zhan3[50];
typedef struct
{
        double d1;

int d2;
}dd;
typedef struct
{
dd data[50];
int top;
    }zhan1;
zhan1 *shu;
shu=(zhan1 *)malloc(sizeof(zhan1));
shu->top=0;
   while(a[i]!='\0')
{
if(a[i]>='0'&&a[i]<='9')
{
   z=0;
   j=i+1;
   while(a[j]>='0'&&a[j]<='9')
   {j++;}
   j--;
   for(k=i;k<=j;k++)
   {
         z=z*10+a[k]-'0';
   }
   j=j+1;
   x=z;
       if(a[j]=='.')
   {
    l=1;
    i=j+1;
    j=i+1;
    while(a[j]>='0'&&a[j]<='9')
    {j++;}
       j--;
       for(k=i;k<=j;k++)
    {
     n=pow(0.1,l);
     l=l+1;
           x=x+n*(a[k]-'0');
    }
    i=j+1;
   }
   else i=j;
   shu->data[++shu->top].d1=x;
   shu->data[shu->top].d2=++cnt;
   nibo[++t1]='0'+shu->data[shu->top].d2;
   nibo[t1+1]='\0';
}
else if(a[i]=='(')
{
   zhan2[++t2]=a[i];
   i++;
}
else if(a[i]==')')
{
   j=t2;
   while(zhan2[j]!='(')
   {
    nibo[++t1]=zhan2[j];
    nibo[t1+1]='\0';
    j--;
   }
   t2=j-1;
   i++;
}
else if(a[i]=='+')
{
   while(t2>0&&zhan2[t2]!='(')
   {
    nibo[++t1]=zhan2[t2];
    nibo[t1+1]='\0';
    t2--;
   }
   zhan2[++t2]=a[i];
   i++;
}
else if(a[i]=='-')
{
   if(a[i-1]=='$')
   {
    a[0]='0';
    i=0;
   }
   else if(a[i-1]=='(')
   {
    a[i-1]='0';
    a[i-2]='(';
    i=i-2;
    t2--;
   }
   else
   {
       while(t2>0&&zhan2[t2]!='(')
    {
    nibo[++t1]=zhan2[t2];
    nibo[t1+1]='\0';
    t2--;
    }
       zhan2[++t2]=a[i];
       i++;
   }
}
else if(a[i]=='*'||a[i]=='/')
{
   while(zhan2[t2]=='*'||zhan2[t2]=='/'||zhan2[t2]=='^'||zhan2[t2]=='#')
   {
    nibo[++t1]=zhan2[t2];
    nibo[t1+1]='\0';
    t2--;
   }
   zhan2[++t2]=a[i];
   i++;
}
else if(a[i]=='^'||a[i]=='#')
{
   while(zhan2[t2]=='^'||zhan2[t2]=='#')
   {
    nibo[++t1]=zhan2[t2];
    nibo[t1+1]='\0';
    t2--;
   }
   zhan2[++t2]=a[i];
   i++;
}
}
while(t2>0)
{
nibo[++t1]=zhan2[t2];
nibo[t1+1]='\0';
t2--;
}

j=1;t3=0;
while(j<=t1)
{
if(nibo[j]>='0'&&nibo[j]!='^'&&nibo[j]!='#')//
{
   for(i=1;i<=shu->top;i++)
   {
    if((int)(nibo[j]-'0')==shu->data[i].d2)
    {
     m=i;
     break;
    }
   }
   zhan3[++t3]=shu->data[m].d1;
   
}
else if(nibo[j]=='+')
{
   zhan3[t3-1]=zhan3[t3-1]+zhan3[t3];
   t3--;
   
}
else if(nibo[j]=='-')
{
   zhan3[t3-1]=zhan3[t3-1]-zhan3[t3];
   t3--;
}
else if(nibo[j]=='*')
{
   zhan3[t3-1]=zhan3[t3-1]*zhan3[t3];
   t3--;
}
else if(nibo[j]=='/')
{
   zhan3[t3-1]=zhan3[t3-1]/zhan3[t3];
   t3--;
}
else if(nibo[j]=='^')
{
   zhan3[t3-1]=pow(zhan3[t3-1],zhan3[t3]);
   t3--;
}
else if(nibo[j]=='#')
{
   zhan3[t3]=sqrt(zhan3[t3]);
   t3--;
}
j++;
}

return zhan3[t3];

}

void main()   //主函数
{
system("title Mathemetics Calculator"); //设置窗口标题
printf("\n\n       Mathemetics Calculator\n       Copyright(C) Eisenberg Andrew Roland 2012—2015"); 
//显示软件名称、作者及版权
for(;;)
{
char x,a[50];
double Answer;
int i=0;
a[0]='$';
printf("\n\n       Times Table[t]  Factorial[f]\n");
printf("       Pascal Triangle[p] Exit[e][other key]\n\n");  
printf("       Please read “Readme.txt” and input expression:\n\n       ");   //显示一些信息

scanf("%c",&x);  //输入x字符变量
if(x=='t'||x=='T') system("start Times_Table.exe");   
if(x=='p'||x=='P') system("start Pascal_Triangle.exe");
if(x=='f'||x=='F') system("start Factorial.exe");
if(x=='e'||x=='E') break;           //其它选项

while(x!='\n')
{
a[++i]=x;
scanf("%c",&x);
}
a[i+1]='\0';
Answer=jisuan(a);
    printf("    ＝ %lf",Answer);   //显示答案
}
}

