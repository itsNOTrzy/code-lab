#include <stdio.h>
#include <math.h>

//判断输入的数据是否有效
int check(double a)
{
    if (a > 0)
        return 1;
    else
        return 0;
}

//判断三角形是否有效

int check2(double a, double b, double c)
{
    if ( ((a+b)<=c) | ((a+c)<=b) | ((c+b)<=a) )
        return 0;
    if (abs(a-b)>=c | abs(a-c)>=a | abs(c-b)>=a)
        return 0;
    else
        return 1;
}

int main(void)
{
    double area = 0;
    double s;
    double a,b,c;
    printf("请输入三角形的三边的长(a b c):");
    scanf("%lf %lf %lf", &a, &b, &c);
    if (check(a) == 1 && check(b) == 1 && check(c) ==1)
    {
        if (check2(a,b,c) == 0)
        {
            printf("您输入的不是三角形.请重新输入\n\r");
            return 0;
        }
        else if (check2(a,b,c) == 1)
        {
            s = (a+b+c) / 2;
            area = sqrt(s * (s - a) * (s - b) * (s - c));
            printf("该三角形的面积是:%g\n\r",area);
        }
    }
    else
        printf("输入有误,请重新输入.\n\r");
    system("pause");
}

