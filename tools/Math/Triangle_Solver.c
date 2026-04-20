#include<stdio.h>
#include<stdlib.h>
#include<math.h> //必需的头文件

int types(float x,float y,float z) //定义函数 types 用来判断三角形的类型(Types of triangle)
{
int t;
//巧妙利用勾股定律 
if(x*x+y*y==z*z) t=1; //直角 
if(x*x+y*y>z*z) t=2; //锐角
if(x*x+y*y<z*z) t=3; //钝角
return(t); //返回值t变量
}

int types2(float x,float y,float z)//定义函数 types2 用来判断三角形的另一种类型
{
int t2;
if(x==y&&x==z) t2=1; //等边
else if(x==y||x==z||y==z) t2=2; //等腰
else t2=3; //不等边
return(t2); //返回值t2变量
}

int main(void) //主函数 标准写法
{
system("title Triangle solver"); //标题
printf("\n\n      Triangle Solver\n      Copyright(C) DMU Studio(Eisenberg Andrew Roland)\n"); //版权
while(1)
{
float a,b,c,p,c1; //长度
float A,B,C; //角度
float CosA,CosB,CosC; //角度的余弦值
double s; //面积
int loop=1,Types,Types2; //三角形的类型

printf("\n       Input the lengths of sides[a b c]:  "); //输入三条边的值
scanf("%f %f %f",&a,&b,&c); //a b c

while (loop==1)
{
if((a+b)<=c||(a+c)<=b||(c+b)<=a||abs(a-b)>=c||abs(a-c)>=b||abs(c-b)>=a)
loop=1;
else
loop=0;
if(loop==1)
{
printf("\n       Error, The sum of the lengths of any two sides must be greater than or equal to the length of the remaining side！"
//错误，三角形任意两边长度之和大于另一条边的长度！
       "\n       Input the lengths of sides again[a b c]:  "); //请重新输入三条边的值
scanf("%f %f %f",&a,&b,&c); //a b c
}
}

if(a=b&&a==c) //等腰
{
A=60,B=A,C=B;
}
else if(a==b||a==c||b==c) //等边
{
CosA=(c*c+b*b-a*a)/(2*b*c);  //先求A的余弦值
A=acos(CosA); //角度A 反余弦
B=(180-A)/2; //顶角为A，底角相等。
C=B;
}
else if(a*a+b*b==c*c) //直角
{
A=90; //勾股定律 90度
CosB=(a*a+c*c-b*b)/(2*a*c); //先求B的余弦值
B=acos(CosB); //角度B 反余弦
C=90-B;
}
else //不等边
{
CosA=(c*c+b*b-a*a)/(2*b*c);  //先求A的余弦值
A=acos(CosA); //角度A 反余弦

CosB=(a*a+c*c-b*b)/(2*a*c); //先求B的余弦值
B=acos(CosB); //角度B 反余弦

C=180-A-B; //角度C
}

c1=a+b+c; //Circumference周长
p=c1/2; //1/2 Circumference半周长
s=sqrt(p*(p-a)*(p-b)*(p-c)); //Square面积

printf("\n       Square  %f\n       Circumference  %f\n       1/2 Circumference  %f\n",s,c1,p);
printf("       ∠A  %f°\n       ∠B  %f°\n       ∠C  %f°\n",A,B,C);

Types=types(a,b,c);
if(Types==1)printf("       This is a right "); //直角
if(Types==2)printf("       This is a acute "); //锐角
if(Types==3)printf("       This is a obtuse "); //钝角

Types2=types2(a,b,c);
if(Types2==1)printf("and equilateral triangle.\n"); //等边
if(Types2==2)printf("and isosceles triangle.\n"); //等腰
if(Types2==3)printf("and scalene triangle.\n"); //不等边
}
}

/*
利用a b c三条边求面积，C为周长。
S＝√￣(C÷2(C÷2—a)(C÷2—b)(C÷2—c))

余弦函数 Cosine 利用三条边求角度A B C，Cos-1为反余弦。
Cos(A)=(cc+bb—aa)÷(2bc) 再 Cos-1(Cos(A))＝A
Cos(B)=(aa+cc—bb)÷(2ac) 再 Cos-1(Cos(B))＝B
Cos(C)=(aa+bb—cc)÷(2ab) 再 Cos-1(Cos(C))＝C

勾股定理 Pythagoras theorem
xx+yy＝zz 直角
xx+yy＞zz 锐角
xx+yy＜zz 钝角

三角形基本公式
C＝a+b+c 周长
h＝S÷a 利用面积求高

三角表达式
a+b＞c a+c＞b b+c＞a  三角形任意两边长度之和大于另一条边的长度
a＝b＝c 等边
a≠b≠c 不等边
a＝b≠c a＝c≠b b＝c≠a 等腰

内角和＝180° 外角和＝360° 直角＝90° 钝角＞90° 锐角＜90°
等边三角形 三条边 三个角度(内角60° 外角300°) 均相等 (180°÷3＝60°)
等腰三角形 两条边 两个角度(底角 角度包括外角) 均相等 (180°—顶角÷2＝底角)
*/
