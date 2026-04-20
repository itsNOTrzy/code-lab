#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;const char Tab=0x9;
const int DIGIT=1;double fun(double x,char op[],int *iop)
{
while(op[*iop-1]<32) //本行使得函数嵌套调用时不必加括号
// 如 arc sin(sin(1.234)) 只需键入arc sin sin 1.234<Enter>
switch(op[*iop-1])
{
case 7: x=sin(x); (*iop)--;break;
case 8: x=cos(x); (*iop)--;break;
case 9: x=tan(x); (*iop)--;break;
case 10: x=sqrt(x); (*iop)--;break;
case 11: x=asin(x); (*iop)--;break;
case 12: x=acos(x); (*iop)--;break;
case 13: x=atan(x); (*iop)--;break;
case 14: x=log10(x);(*iop)--;break;
case 15: x=log(x); (*iop)--;break;
case 16: x=exp(x); (*iop)--;break;
}
return x;
}

double calc(char *expr,char **addr)
{
static deep; //递归深度
static char *fname[]={ "sin","cos","tan","sqrt",
"arcsin","arccos","arctan","lg","ln","exp",NULL};
double ST[10]={0.0}; //数字栈
char op[10]={'+'}; //运算符栈
char c,*rexp,*pp,*pf;
int ist=1,iop=1,last;
if(!deep)
{
pp=pf=expr;
do
{
c = *pp++;
if(c!=' '&& c!=Tab)
*pf++ = c;
}
while(c!='\0');
}
pp=expr;
if((c=*pp)=='-'||c=='+')
{
op[0] = c;
pp++;
}
last = !DIGIT;
while((c=*pp)!='\0')
{
if(c=='(')//左圆括弧
{
deep++;
ST[ist++]=calc(++pp,addr);
deep--;
ST[ist-1]=fun(ST[ist-1],op,&iop);
pp = *addr;
last = DIGIT;
if(*pp == '('||isalpha(*pp) && strnicmp(pp,"Pi",2))
{ //目的是：当右圆括弧的
op[iop++]='*'; //右恻为左圆括弧或函数
last = !DIGIT; //名字时，默认其为乘法
c = op[--iop]; 
goto operate ; 
}
}
else if(c==')')//右圆括弧
{
pp++;
break;
}
else if(isalpha(c))
{
if(!strnicmp(pp,"Pi",2))
{
	if(last==DIGIT){cout<< "Cannot input parenthesis besides π" <<endl;exit(1);} //左边
ST[ist++]=3.14159265358979323846;
ST[ist-1]=fun(ST[ist-1],op,&iop);
pp += 2;
last = DIGIT;
if(!strnicmp(pp,"Pi",2)){cout<< "Cannot input π besides π" <<endl;exit(2);}
if(*pp=='('){cout<< "Cannot input parenthesis besides π" <<endl;exit(3);} //右边
}
else 
{ 
for(int i=0; (pf=fname[i])!=NULL; i++)
if(!strnicmp(pp,pf,strlen(pf)))break;
if(pf!=NULL)
{
op[iop++] = 07+i;
pp += strlen(pf);
}
else {cout<< "Unknown function" <<endl;exit(4);}
}
}
else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='^')
{
char cc;
if(last != DIGIT){cout<< "Operational characters can't be side by side" <<endl;exit(5);}
pp++;
if(c=='+'||c=='-') 
{
do
{
cc = op[--iop];
--ist;
switch(cc)
{
case '+': ST[ist-1] += ST[ist];break;
case '-': ST[ist-1] -= ST[ist];break;
case '*': ST[ist-1] *= ST[ist];break;
case '/': ST[ist-1] /= ST[ist];break;
case '^': ST[ist-1] = pow(ST[ist-1],ST[ist]);break;
}
}
while(iop);
op[iop++] = c;
}
else if(c=='*'||c=='/')
{
operate: cc = op[iop-1];
if(cc=='+'||cc=='-')
{
op[iop++] = c;
}
else
{
--ist;
op[iop-1] = c;
switch(cc)
{
case '*': ST[ist-1] *= ST[ist];break;
case '/': ST[ist-1] /= ST[ist];break;
case '^': ST[ist-1] = pow(ST[ist-1],ST[ist]);break;
}
}
}
else
{
cc = op[iop-1];
if(cc=='^'){cout<< "Cannot be used in conjunction with two exponentiation signs" <<endl;exit(6);}
op[iop++] = c;
}
last = !DIGIT;
}
else
{
if(last == DIGIT){cout<< "Too many parameters" <<endl;exit(7);}
ST[ist++]=strtod(pp,&rexp);
ST[ist-1]=fun(ST[ist-1],op,&iop);
if(pp == rexp){cout<< "Illegal characters" <<endl;exit(8);}
pp = rexp; 
last = DIGIT;
if(*pp == '('||isalpha(*pp))
{
op[iop++]='*';
last = !DIGIT;
c = op[--iop]; 
goto operate ; 
}
}
}
*addr=pp;
if(iop>=ist){cout<< "Expression is incorrect" <<endl;exit(9);}
while(iop)
{
--ist;
switch(op[--iop])
{
case '+': ST[ist-1] += ST[ist];break;
case '-': ST[ist-1] -= ST[ist];break;
case '*': ST[ist-1] *= ST[ist];break;
case '/': ST[ist-1] /= ST[ist];break;
case '^': ST[ist-1] = pow(ST[ist-1],ST[ist]);break;
}
}
return ST[0];
}


int main()//主函数
{
char s[128],*end;
system("title Mathemetics Calculator"); //设置窗口标题
cout << "\n\n       Mathemetics Calculator\n       Copyright(C) Eisenberg Andrew Roland 2012—2015\n\n";
while(1)
{
A:
cout << "       Input expression:\n\n       ";
cin.getline(s,128);
cout <<"    ＝ ";
cout << setprecision(17) << calc(s,&end) << endl;
	system("start Mathemetics_Calculator.exe");
}
}