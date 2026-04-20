#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    char b[100];
    while(1)
    {
    printf("\n\n    Input a Decimal System Number:  ");
scanf("%d",&a);
itoa(a,b,2);
printf("\n    %d £½ Hexadecimal of %x",a,a);
printf("\n    %d £½ Hexadecimal of %o",a,a); 
printf("\n    %d £½ Binary System of %s",a,b); 
    }
}
