#include"stdio.h"
#include"string.h"
#define maxn 1000000
int f[maxn];
int main()
{
int i,j,c,s;
char buf[512];
float n;
int l;

system("title Factorial");
printf("\n\n\n     Factorial\n     Copyrgiht(C) Eisenberg Andrew Roland 2012¡ª2015");
printf("\n\n      Please input a number:  ");
scanf("%f",&n);
printf("\n      Calculating[Computing]......");
    
memset(f,0,sizeof(f));
f[0]=1;
for(i=2;i<=n;i++)
{
c=0;
for(j=0;j<maxn;j++)
{
s=f[j]*i+c;
f[j]=s%10;
c=s/10;
}
}
l=n; 
    if(n<0) 
    { 
        system("cls");
        printf("\n\n\n     Factorial\n     Copyrgiht(C) Eisenberg Andrew Roland 2012¡ª2015\n");
        
    printf("\n      Sorry£¡Don't input Negative.\n\n");
    printf("      Press any key to exit.\n\n");
    system("pause>nul"); 
    exit(0);
    } 
    else if(n-l>0)
    {
        system("cls");
        printf("\n\n\n     Factorial\n     Copyrgiht(C) Eisenberg Andrew Roland 2012¡ª2015\n");
        
    printf("\n      Sorry£¡Don't input Decimal or Words.\n\n");
    printf("      Press any key to exit.\n\n");
    system("pause>nul"); 
    exit(0);
    }
for(j=maxn-1;j>=0;j--)
{
if (f[j])
{
        system("cls");
        printf("\n\n\n     Factorial\n     Copyrgiht(C) Eisenberg Andrew Roland 2012¡ª2015\n\n");

printf("      %d£¡£½ ",l);
for(i=j;i>=0;i--)
{
printf("%d",f[i]);
}
printf("\n      Factorial of %d is a %d-Digit [%d Figures].\n\n",l,j+1,j+1);
printf("      Press any key to exit.\n\n");
system("pause>nul"); 
exit(0);
}
}
}
