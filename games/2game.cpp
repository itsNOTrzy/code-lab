#include <iostream>
#include "pthread.h"
#include "stdio.h"
#include "termios.h"
#include "unistd.h"
using namespace std;

int mygetch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int n=1;int p,t,ret1,ret2;
int i,j=0;bool bud=false;
int x=11,y=4;int a,b;
char c;
pthread_t id1,id2;
void game();
void prepare();
void mfire();
void show();
void* thread1(void*);
void* thread2(void*);
char map[12][12];
void prepare(){
for(i=0;i<12;i++){
  for(j=0;j<12;j++){
map[i][j]=' ';}}
map[x][y]='*';map[x][y-1]='*';
map[x][y+1]='*';
cout<<"\033[H\033[2]";
show();
}

void show(){
for(i=0;i<12;i++){
for(j=0;j<12;j++){
cout<<map[i][j];
fflush(stdout);
}cout<<endl;
fflush(stdout);
}
}

void fire(){
a=x-1;b=y;
for(a=x-1;a>=0;a--)
{map[a][b]='#';
printf("\033[H\033[2]");
show();
map[a][b]=' ';
usleep(600);  }
}

void game(){
c=mygetch();
if(c=='w'){p=-1;t=0;}
if(c=='s'){p=1;t=0;}
if(c=='a'){p=0;t=-1;}
if(c=='d'){p=0;t=1;}
if(c=='k'){fire();p=0;t=0;}
if(x+p+1>12){p=0;t=0;bud=true;}
if(x+p<0){p=0;t=0;bud=true;}
if(y+t+2>12){p=0;t=0;bud=true;}
if(y+t-1<0){p=0;t=0;bud=true;}
if(!bud){map[x][y]=' ';
       map[x][y-1]=' ';
     map[x][y+1]=' ';
  x+=p;y+=t;
p=0;t=0;
 map[x][y]='*';map[x][y-1]='*';
map[x][y+1]='*';
printf("\033[H\033[2]");
show();
  }
  bud=false;}

void mwnd(){
int q=0,t=0;bool gg=false;
while(1){
sleep(2);
for(t=4;t<8;t++){
for(i=0;i<12;i++){
if(map[i][t]==' '||map[i][t]=='*'){}
else {goto loop;}
if(i==11&&t==7){q=0;}
}}
loop:
for(t=4;t<8;t++){map[q][t]='@';}
q++;
for(i=4;i<8;i++){
if(map[11][i]=='@'){
pthread_cancel(id1);
cout<<endl<<"GAMEOVER";
break;gg=true;}}
if(gg){break;}
cout<<"\033[H\033[2]";show();
}
}
void* thread1(void*){
while(1){game();}
}
void* thread2(void*){
mwnd();
}

int main(){
ret1=pthread_create(&id1,NULL,thread1,NULL);
ret2=pthread_create(&id2,NULL,thread2,NULL);
if(ret1!=0||ret2!=0){
printf("error\n");
exit (1);}
prepare();
pthread_join(id1,NULL);
pthread_join(id2,NULL);
return 0;}