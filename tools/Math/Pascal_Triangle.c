#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>
#include <math.h>
#include <process.h>

#define ERROR 0 
#define OK 1 
#define OVERFLOW -1 
#define MAX_QUEUE 100 
  
typedef int  DataType; 
  
typedef struct
{ 
    DataType elem[MAX_QUEUE]; 
    int  front; 
    int  rear; 
} LinkQueue; 
  
int  InitQueue(LinkQueue *); 
void EnQueue(LinkQueue *,DataType); 
void DeQueue(LinkQueue *,DataType *); 
void GetFront(LinkQueue,DataType *); 
int  QueueEmpty(LinkQueue); 
void YangHuiTriangle(int  ); 
int isNum(char * s);
  
int  main(void) 
{ 
    float n;int i;
    system("title Pascal Triangle");
    printf("您可更改控制台属性的缓冲区高度，调低很可能显示错误或者闪退。\n有的数字前面会有负号，属于计算出错，忽略负号即可。\n");
    printf("请输入杨辉三角的行数:  "); 
    scanf("%f",&n);
    i=n; 
    if(n<=0) 
    { 
    printf("不能输入0或负数，行数必须是正整数"); 
    while(1);
    } 
    else if(n-i>0)
    {
    printf("不能输入小数，行数必须是正整数");
    while(1);
    }
   YangHuiTriangle(n); 
    return 0; 
} 
  
int  InitQueue(LinkQueue *Q) 
{ 
    Q->front=Q->rear=-1; 
    return 1; 
} 
  
void EnQueue(LinkQueue *Q,DataType e) 
{ 
    if((Q->rear+1)%MAX_QUEUE==Q->front) 
        exit(OVERFLOW); 
    else
    { 
        Q->rear=(Q->rear+1)%MAX_QUEUE; 
        Q->elem[Q->rear]=e; 
    } 
} 
  
void DeQueue(LinkQueue *Q,DataType *e) 
{ 
    if(QueueEmpty(*Q)) 
    { 
        printf("排列是空的！\n"); 
        while(1); 
    } 
    else
    { 
        Q->front=(Q->front+1)%MAX_QUEUE; 
        *e=Q->elem[Q->front]; 
    } 
} 
  
void GetFront(LinkQueue Q,DataType *e) 
{ 
    if(QueueEmpty(Q)) 
    { 
        printf("排列是空的！\n"); 
        while(1);
    } 
    else
        *e=Q.elem[(Q.front+1)%MAX_QUEUE]; 
} 
  
int  QueueEmpty(LinkQueue Q) 
{ 
    if(Q.front==Q.rear) 
        return 1; 
    else
        return 0; 
} 
  
void YangHuiTriangle(int  n) 
{ 
    LinkQueue Q; 
    int  i,j,k,t,s,e; 
    InitQueue(&Q); 
    for(i=0; i<n; i++) 
        printf(" "); 
    printf(" 1\n"); 
    EnQueue(&Q,1); 
    EnQueue(&Q,1); 
    for(i=1; i<n; i++) 
    { 
        for(k=0; k<n-i; k++) 
            printf(" "); 
        EnQueue(&Q,1); 
        for(j=0; j<i; j++) 
        { 
            DeQueue(&Q,&t); 
            printf(" %d",t); 
            GetFront(Q,&s); 
            e=t+s; 
            EnQueue(&Q,e); 
        } 
        EnQueue(&Q,1); 
        DeQueue(&Q,&t); 
        printf(" %d\n",t); 
    }
      printf("\nPress any key to exit.");
      system("pause>unl");
      system("start Mathemetics_Calculator.exe");
   system("del unl");
}

