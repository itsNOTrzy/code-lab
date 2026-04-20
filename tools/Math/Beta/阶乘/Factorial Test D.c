#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define  MAXCHAR 50000

char * MUL(char *ch1 , char *ch2 , char *ch3)
{
// ch3 = ch1*ch2;
 int i , j , len1 = strlen (ch1) , len2 = strlen (ch2) , len3 , tmp , num1[MAXCHAR] , num2[MAXCHAR] , num3[MAXCHAR];
 memset (num1 , 0 , sizeof(num1)); 
 memset (num2 , 0 , sizeof(num2)); 
 memset (num3 , 0 , sizeof(num3));
 for (i=len1-1;i>=0;i--) num1[len1-1-i] = ch1[i] - 48; for (i=len2-1;i>=0;i--) num2[len2-1-i] = ch2[i] - 48;
 for (i=0;i<len1;i++)
 {
  tmp = 0;
  for (j=0;j<len2;j++)
  {
   num3[i+j] += num1[i]*num2[j] + tmp; 
   tmp = 0;
   if (num3[i+j] >= 10) { tmp = num3[i+j]/10; num3[i+j] %= 10; }
  }
  while (tmp != 0) { num3[i+j] += tmp; tmp = num3[i+j]/10; j ++; }
 }
 len3 = len1+len2;
 while (len3 > 1 && num3[len3-1] == 0) len3 --; 
 for (i=0;i<len3;i++) ch3[len3-1-i] = num3[i] + 48;
 ch3[len3] = '\0';
 return ch3;
}

int main()
{
int i;
char fac[MAXCHAR];
char ch1[MAXCHAR], ch2[MAXCHAR],ch3[MAXCHAR],cc[MAXCHAR];
char * jw(char *ch,int i);
char *cm;

system("title Factorial Faster");
printf("\n\n\n     Factorial\n     Copyrgiht(C) Eisenberg Andrew Roland 2012¡ª2015");

while(1)
{
printf("\n\n\n      Please input a number:  ");
scanf("%s",ch1);
printf("\n      Calculating [Computing]......\n");

for(i=0;i<strlen(ch1);i++)
{
ch2[i]=ch1[i];
cc[i]='0';
}

cc[strlen(cc)-1]='1';

while(strcmp(ch2,cc)!=0)
{
strcpy(ch2,jw(ch2,1));
strcpy(ch1,MUL(ch1,ch2,ch3));
}

printf("\n   £½ %s\n",ch1);
    
}
}

char *jw(char *ch,int i)
{
if(ch[strlen(ch)-i]!='0')
{
ch[strlen(ch)-i]--;
}
else
{
ch[strlen(ch)-i]='9';
jw(ch,i+1);
}
return ch;
}
