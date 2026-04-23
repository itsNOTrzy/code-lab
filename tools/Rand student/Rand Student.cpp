#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>	
#include <malloc.h>
#include <dirent.h>
#include <string.h> 

#define ABS(X) (X<0)?0:X
#define ABS2(X) (X<0)?(X*-1):X

int	  x,y,z=0; 
POINT map;											//用于存储GetcursorPos() 返回的鼠标坐标值 
DWORD res;      									//用于存储读取记录  
COORD pos;    										//用于存储鼠标当前相对窗口位置 
clock_t Time=0; 									 
INPUT_RECORD mouserec;								//创建一个输入事件结构体 mouserec
char tip_window[11][21]={"┏━━━━━■■■┓", "┆ Tip window ：  ┆","┆                ┆","┆  更换名单      ┆","┆                ┆","┆  查看名单      ┆","┆                ┆","┆                ┆","┆     ◇◇◇     ┆","┃________________┃","┗┛┗┛┗┛┗┛┗┛"};
char chakan_ui[44][41]={"┏------------------------------■■■┓","┊.                                  .┊","┊ <<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>> ┊","┊                                    ┊","┊        ■    查看名单    ■        ┊","┊                                    ┊","┊┏                                ┓┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊              ◇◇◇◇              ┊","┊                                    ┊","┊┗                                ┛┊","┊ <<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>> ┊","┊.              ------              .┊","┗┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┛",};	
char system_ui[44][41]={"┏------------------------------■■■┓","┊.                                  .┊","┊ <<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>> ┊","┊                                    ┊","┊    ■至上励合  随机抽签系统  ■    ┊","┊                                    ┊","┊┌                                ┐┊","┊                                    ┊","┊           <- 开始抽取 ->           ┊","┊                                    ┊","┊           <- 管理名单 ->           ┊","┊                                    ┊","┊           <- 关于我们 ->           ┊","┊                                    ┊","┊           <- 系统设置 ->           ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊              ◇◇◇◇              ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊└                                ┘┊","┣〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓┫","┊┏  +                          +  ┓┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊                                    ┊","┊\\                                  /┊","┊ =                                = ┊","┊ =                                = ┊","┊ =                                = ┊","┊ =                                = ┊","┊/                                  \\┊","┊                                    ┊","┊ <<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>> ┊","┊.              ------              .┊","┗┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┛",};
char tip_window2[32][37]={"┏━━━━━━━━━━━━━■■■┓","┆.  Tip window               ┗┓┆","┣------------------┛          ┗┫","┆                                ┆","┆                                ┆","┆.                               ┆","┆                                ┆","┆.                               ┆","┆                                ┆","┆.                               ┆","┆                                ┆","┆.                               ┆","┆                                ┆","┆.                               ┆","┆                                ┆","┆.                               ┆","┆                                ┆","┆.                               ┆","┆                                ┆","┆.                               ┆","┆                                ┆","┆                                ┆","┆                                ┆","┆                                ┆","┆                                ┆","┆                                ┆","┆                                ┆","┆  选择文件            跳过此步  ┆","┆                                ┆","┆            ◇◇◇◇            ┆","┃________________________________┃","┗┛┗┛┗┛┗┛┗┛┗┛┗┛┗┛┗┛",};
char setup_ui[35][35]={"┏------------------------■■■┓","┊.                            .┊","┊ <<<<<<<<<<<<<<>>>>>>>>>>>>>> ┊","┊                              ┊","┊     ■    系统设置    ■     ┊","┊                              ┊","┊┏                          ┓┊","┊                              ┊","┊                              ┊","┊ 音效：                       ┊","┊                              ┊","┊ 抽签动画款式：               ┊","┊                              ┊","┊ 抽签动画时间：               ┊","┊                              ┊","┊                              ┊","┊ 主题色选择（暂未开放）       ┊","┊                              ┊","┊                              ┊","┊                              ┊","┊                              ┊","┊                              ┊","┊                              ┊","┊                              ┊","┊                              ┊","┊                              ┊","┊                              ┊","┊                              ┊","┊           ◇◇◇◇           ┊","┊                              ┊","┊┗                          ┛┊","┊                              ┊","┊.<<<<<<<<<<<<<<>>>>>>>>>>>>>>.┊","┃______________________________┃","┗┛ ┗┛┗┛┗┛┗┛┗┛┗┛ ┗┛", };
char tip_buf[8][27]={"检测到您是第一次运行本程序","在使用本程序之前您得加入一","个您的班级学生名单以供本程","序随机抽选。              ","                          ","如需手动输入学生姓名请点击","\" 跳过此步\" 然后进入  管理","名单->更换名单选择手动输入",};

struct student_name { char stu_name[10];} *stu_p; 
struct file_name{ char name[29];} *f_name;
struct console_save{
	
	int donghuatime;
	int student_num;
	char file_path[32];
	short music_off;
	short donghuatype;

} save_data ;

void StudentList(FILE *fp,HANDLE handle_out,HANDLE handle_in,int i,FILE *save_p);

void gotoxy(int X,int Y, HANDLE handle_out) 			//【光标移动函数】 
{
		COORD pos={X,Y};
		SetConsoleCursorPosition(handle_out,pos);
}

char* student_file(FILE *fp,int Case)				//【文件读取函数】 当Case为1时 返回的是学生表的人数 为0 时 返回的是学生名字地址 
{	
	int i=0,k=0; 
	char *name_buf=(char *)malloc(10);
	if(fp==NULL) return "NULL";
	for(i=0;1;i++)
	{
		for(;!feof(fp) && getc(fp)!='	' ;);
		for(memset(name_buf,0,10),k=0;(name_buf[k++]=getc(fp))!='	' ;)
	 	{
	 		if(k>= 10) break;
		 	if(feof(fp))
	 		{
				rewind(fp);
				if(Case==1) return (char *)i;
				break;	
			}
	 	}
			while(ftell(fp)!=0 && getc(fp)!='\n');
		if(Case==0) break;
	}
	return name_buf;	
}

void mouserec_event(HANDLE handle_in)   				//【获取鼠标事件函数】 
{	
		x=map.x,y=map.y;
		GetCursorPos(&map);
		pos = mouserec.Event.MouseEvent.dwMousePosition;    	//获得当前鼠标位置		 
		if(GetKeyState(VK_LBUTTON)==-128 || GetKeyState(VK_LBUTTON)==-127 || x!=map.x || y!=map.y)
	    {	
			ReadConsoleInput(handle_in, &mouserec, 1, &res);  	//读取输入事件
			pos = mouserec.Event.MouseEvent.dwMousePosition;    //获得当前鼠标位置 
	    }
}


void _music(int Case)									//【播放音效函数】 
{
	if(save_data.music_off == 1)
	{	if(clock()-Time> 60 || Case == 1) 
		{
	    mciSendString(TEXT("close keydown"), NULL, 0, NULL);
	    }
		switch(Case)
		{
			case  1:mciSendString(TEXT("open sounds\\c-ad-hd.wav alias keydown"), NULL, 0, NULL);break;
			case  2:mciSendString(TEXT("open sounds\\Breaker_Switch_2.wav alias keydown"), NULL, 0, NULL);break;  
			case  3:mciSendString(TEXT("open sounds\\Latch_Slide_2.wav alias keydown"), NULL, 0, NULL);break;
			case  4:mciSendString(TEXT("open sounds\\Latch_Metal_Jingle_2.wav alias keydown"), NULL, 0, NULL);break;
			case  5:mciSendString(TEXT("open sounds\\Arcade_Beeps_A.WAV alias keydown"), NULL, 0, NULL);break;
			case  6:mciSendString(TEXT("open sounds\\Button38.wav alias keydown"), NULL, 0, NULL);break;
			case  7:mciSendString(TEXT("open sounds\\start.wav alias keydown"), NULL, 0, NULL);break;
			case  8:mciSendString(TEXT("open sounds\\Breaker_Switch_1.WAV alias keydown"), NULL, 0, NULL);break;
			case  9:mciSendString(TEXT("open sounds\\CLICK.WAV alias keydown"), NULL, 0, NULL);break;
		}
		mciSendString(TEXT("play keydown"), NULL, 0, NULL);
		Time = clock();
	}
}

void GuoDu(int caseA,int caseB,HANDLE handle_out) 		//【过渡动画函数】 
{
	int i=0,j=0,k=0;
	char buf[3]="  ";
	if(caseA == 0)for(i=0;i<4000;gotoxy(rand()%40,(i++)%44,handle_out),putchar(' '));
	else 		  for(i=0; i<=2000;i++,j=rand()%20)
				  {
						gotoxy(j*2 , i%44 ,handle_out);	
						for(k=0;k<2;k++)
						buf[k]=(caseB == 0)?chakan_ui[i%44][j*2+k]:system_ui[i%44][j*2+k];
						printf("%s",buf);
				  }
} 


void setup(HANDLE handle_out ,HANDLE handle_in)
{
	 FILE *save_p;
	 int i=0,j=0;
	 SetConsoleTextAttribute(handle_out,240);
	 for(gotoxy(3,4,handle_out);i<35;printf("%s",setup_ui[i++]),gotoxy(3,4+i,handle_out));
	 for(i=0;1;i++)
	 {
		mouserec_event(handle_in);
		gotoxy(16+(i/16%4)*2,32,handle_out);
		if((i/(32*4))%2==0) printf((i/(16*4))%2==0?"□":"◆");
		else printf("◇");
		if(pos.X>=20 && pos.X<=24 && pos.Y==13)		_music(4),SetConsoleTextAttribute(handle_out,15);
		else										SetConsoleTextAttribute(handle_out,240); 
		gotoxy(21,13,handle_out),printf("开启"); 
		if(pos.X>=25 && pos.X<=29 && pos.Y==13)		_music(4),SetConsoleTextAttribute(handle_out,15);
		else										SetConsoleTextAttribute(handle_out,240); 
		gotoxy(26,13,handle_out),printf("关闭"); 
		if(pos.X>=20 && pos.X<=23 && pos.Y==15)		_music(4),SetConsoleTextAttribute(handle_out,15);
		else										SetConsoleTextAttribute(handle_out,240); 
		gotoxy(21,15,handle_out),printf("一");
		if(pos.X>=24 && pos.X<=27 && pos.Y==15)		_music(4),SetConsoleTextAttribute(handle_out,15);
		else										SetConsoleTextAttribute(handle_out,240); 
		gotoxy(25,15,handle_out),printf("二");
		if(pos.X>=20 && pos.X<=28 && pos.Y==17)		_music(4),SetConsoleTextAttribute(handle_out,15);
		else										SetConsoleTextAttribute(handle_out,240);
		gotoxy(21,17,handle_out),printf("%d",save_data.donghuatime);
		if(pos.X>=18 && pos.X<=22 && pos.Y==30)		_music(4),SetConsoleTextAttribute(handle_out,15);
		else										SetConsoleTextAttribute(handle_out,240);
		gotoxy(18,30,handle_out),printf("返回");
		if (mouserec.EventType == MOUSE_EVENT && mouserec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			if(pos.X>=20 && pos.X<=24 && pos.Y==13)	save_data.music_off = 1 ;
		 	if(pos.X>=25 && pos.X<=29 && pos.Y==13)	save_data.music_off = 0 ;
			if(pos.X>=20 && pos.X<=23 && pos.Y==15)	save_data.donghuatype = 1;
			if(pos.X>=24 && pos.X<=27 && pos.Y==15) save_data.donghuatype = 2;
			if(pos.X>=20 && pos.X<=28 && pos.Y==17)
			{
				gotoxy(21,17,handle_out);
				scanf("%d",&save_data.donghuatime);
			}
		 	if(pos.X>=18 && pos.X<=22 && pos.Y==30)	return ; 
		 	else{
		 		save_p = fopen("./save.data","w+");
		 		fwrite(&save_data,sizeof(struct console_save),1,save_p);
		 		fclose(save_p);
		 	}
		}
	 }
}

void open_file_list(HANDLE handle_out,HANDLE handle_in,FILE *save_p)  // 【获取文件目录 && 打开文件 函数】 
{
	int i,len=0,j=0,k=0;
	DIR *dir;
	struct dirent *s;
	FILE *fp;
	
	dir=opendir("./");
	_music(1),Sleep(50),GuoDu(0,0,handle_out),GuoDu(1,0,handle_out);
	for(gotoxy(0,0,handle_out),i=0;i<44;printf("%s",chakan_ui[i]),i++);
	gotoxy(16,4,handle_out),printf("选择文件");
	gotoxy(0,7,handle_out),printf("%s","┊│ [FILE LIST] 软件目录下：         ┊┊│___________________________       ┊");
	for(len=0;(s=readdir(dir))!=NULL;len++);
	f_name=(struct file_name *)malloc(len*sizeof(struct file_name));
	rewinddir(dir);
	for (i=0;(s=readdir(dir))!=NULL;i++)  
	{  
		if(strlen(s->d_name)<=28)strcpy((f_name+i)->name,s->d_name);
		else{	  
		for(j=0;j<=28;f_name[i].name[j]=s->d_name[j],j++);
		f_name[i].name[27] = '.',f_name[i].name[28] = '.';} 
	}
	for(j=0,i=0,z=pos.Y;1;i++,j=ABS(j))
	{
	mouserec_event(handle_in);
	if(i==0 || (pos.X>=31 && pos.X<=38))
	for(k=j;k<=j+28;gotoxy(3,k-j+9,handle_out),printf("%-28s|",(k<len)?(f_name+k)->name:"                            "),k++);
	else 			Sleep(20); 
	gotoxy(32,20,handle_out),printf(" %3.f%%",((float)((k>=len)?len:k)/len)*100);
	if(pos.X>=31 && pos.X<=38 && pos.Y==10)		_music(4),SetConsoleTextAttribute(handle_out,15);
	else										SetConsoleTextAttribute(handle_out,240); 
	gotoxy(32,10,handle_out),printf(" BACK  "); 
	if(pos.X>=31 && pos.X<=38 && pos.Y==14)		j--,_music(4),SetConsoleTextAttribute(handle_out,15);
	else										SetConsoleTextAttribute(handle_out,240); 
	gotoxy(32,14,handle_out),printf(" UP    ");
	if(pos.X>=31 && pos.X<=38 && pos.Y==16)		j+=(j<len-29)?1:0,_music(4),SetConsoleTextAttribute(handle_out,15);
	else										SetConsoleTextAttribute(handle_out,240); 
	gotoxy(32,16,handle_out),printf(" DOWN  ");
	if(pos.X>=3 && pos.X<=30 && pos.Y>=9 && ((len-j>=28)?37:pos.Y<len-j+9))
	{
	gotoxy(3,pos.Y,handle_out) ,printf("%-28s",(f_name+j+pos.Y-9)->name);
	if(z != pos.Y)	SetConsoleTextAttribute(handle_out,15),gotoxy(3,z,handle_out),printf("%-28s",(f_name+j+z-9)->name);
	z=pos.Y;
	}
	SetConsoleTextAttribute(handle_out,rand()%16);
	gotoxy(2+i%30,0,handle_out),putchar('-');
	gotoxy(36-(i%18)*2,43,handle_out),printf("┉");
	SetConsoleTextAttribute(handle_out,15);
	if(3+i%34<10 || 3+i%34>=30)
	{
	gotoxy(3+i%34,41,handle_out),printf((i/54%3==0)?"-":" ");
	gotoxy(36-i%34,42,handle_out),printf((i/54%3==0)?"-":" ");
	}
		if (mouserec.EventType == MOUSE_EVENT)   
        {
			if(pos.X>=32 && pos.X<=38 && pos.Y==10 && mouserec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				_music(1),GuoDu(0,0,handle_out),GuoDu(1,1,handle_out),pos.X=0,pos.Y=0,z=0;
				return ;
			}
			if(pos.X>=3 && pos.X<=30 && pos.Y>=9 && ((len-j>=28)?37:pos.Y<len-j+9) &&  mouserec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
			{
				if(strchr((f_name+j+pos.Y-9)->name,'.') == NULL || j+pos.Y-9 == 0 || j+pos.Y-9 == 1)	gotoxy(16,pos.Y,handle_out),printf("|该目标不合法|"),Sleep(1000); 
				else if(strstr((f_name+j+pos.Y-9)->name,"txt")==NULL && strstr((f_name+j+pos.Y-9)->name,"TXT")==NULL && strstr((f_name+j+pos.Y-9)->name,"Txt")==NULL && strstr((f_name+j+pos.Y-9)->name,"TXt")==NULL && strstr((f_name+j+pos.Y-9)->name,"TxT")==NULL && strstr((f_name+j+pos.Y-9)->name,"tXt")==NULL) gotoxy(10,pos.Y,handle_out),printf("|只能打开txt类型文件|"),Sleep(1000);
				else{ 
				sprintf(save_data.file_path,"./%s",(f_name+j+pos.Y-9)->name),_music(8);
				fp=fopen(save_data.file_path,"r+"),save_data.student_num=(int)student_file(fp,1);
				save_p=fopen("./save.data","w+");
			 	fwrite(&save_data,sizeof(struct console_save),1,save_p),fclose(save_p);
			 	MessageBox(NULL,TEXT("\ncont>> 已加载你所选择的文件请确保该文件可行!\n\n如果打开文件后程序出现异常可通过请到本程序目录下删除文件save.data来重置本程序\n\n          请按确认键继续...\n"),TEXT(" 提示："),MB_OK),z=0;
				return ; 
				}
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 



int main(int argc, char *argv[])
{
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄 
	HANDLE handle_in  = GetStdHandle(STD_INPUT_HANDLE);	//获取标准输入句柄 
	CONSOLE_SCREEN_BUFFER_INFO bInfo; 					//窗定义一个口缓冲区信息结构体 
	GetConsoleScreenBufferInfo(handle_out, &bInfo ); 	//获取窗口缓冲区信息
	COORD cdBufferSize = {40, 46};
	SMALL_RECT rc = {0, 0, 40, 46};						//设置窗口大小 
 	SetConsoleScreenBufferSize(handle_out, cdBufferSize);   	// 重新设置缓冲区大小     
    SetConsoleWindowInfo(handle_out, 1, &rc);    				// 重置窗口大小
    CONSOLE_CURSOR_INFO cci = {1, 0};					//
    SetConsoleCursorInfo(handle_out, &cci); 			//隐藏光标
    SetConsoleTitle("■    至上励合  随机抽签系统     ■");
    
    
	int i=0,k=1,color[3]={8,7,15};
	char input_buf[40]="A",*name_buf=NULL;
	FILE *save_p=NULL,*fp=NULL;
	
	save_p=fopen("./save.data","r+");
	if(!save_p)											//如果程序为第一次运行 则执行下列动画 
	{	
 		save_data.donghuatime = 1000,save_data.music_off = 1,save_data.donghuatype = 1;
 		for(i=0;i<16;SetConsoleTextAttribute(handle_out,240),gotoxy(0,0,handle_out),printf("如果显示异常,\n请更改您的控制台缓冲区和窗口大小\n缓冲区大小设置为：高 46 宽 40 \n窗口大小同上"),i++,Sleep(300));
		for(i=0,SetConsoleTextAttribute(handle_out,255);i<=45;printf("                                        "),i++);
		for(i=0,_music(9),SetConsoleTextAttribute(handle_out,15),gotoxy(1,4,handle_out);i<32;i++)
		{
			for(k=0;k<=i;gotoxy(1,k+4,handle_out),printf("%s","                                    "),k++);
			for(k=0,SetConsoleTextAttribute(handle_out,136);k<i;gotoxy(37,k+5,handle_out),printf("  "),k++);
			for(k=0;k<=36;gotoxy(k+2,i+5,handle_out),putchar(' '),k++);
			SetConsoleTextAttribute(handle_out,15);
			(i == 0)? Sleep(400):Sleep(10);
		}
		for(Sleep(200),i=0;i<32*18;i++)
		for(gotoxy((i%18)*2+1,i/2%32+4,handle_out),k=0;k<2;printf("%c",tip_window2[i/2%32][(i%18)*2+k]),k++);
		for(i=0;i<8;i++,_music(i==8?2:7))
		for(k=0;k<3;SetConsoleTextAttribute(handle_out,color[k]),gotoxy(6,i*2+9,handle_out),printf("%s",tip_buf[i]),k++,Sleep(200));
		for(i=0;1;i++)
		{
			mouserec_event(handle_in);
			SetConsoleTextAttribute(handle_out,240);
			if(pos.Y == 31 && pos.X >=5 && pos.X <=11)	_music(6),SetConsoleTextAttribute(handle_out,15);
			else 											SetConsoleTextAttribute(handle_out,240);
			gotoxy(5,31,handle_out),printf("选择文件");
			if(pos.Y == 31 && pos.X >=25 && pos.X <=31)	_music(6),SetConsoleTextAttribute(handle_out,15);
			else 											SetConsoleTextAttribute(handle_out,240);
			gotoxy(25,31,handle_out),printf("跳过此步");
			if(GetKeyState(VK_LBUTTON)==-128 || GetKeyState(VK_LBUTTON)==-127) //我用另一个函数来实现了检测鼠标左键触发事件
	 		if(pos.Y == 31 && pos.X >=25 && pos.X <=31) break;
		 	else if((pos.Y == 31 && pos.X >=5 && pos.X <=11))
		 	{
		 		SetConsoleTextAttribute(handle_out,15),open_file_list(handle_out,handle_in,save_p);
				break ;
		 	}
		}
		Sleep(100),_music(8);
		for(i=0;i<=32*37;gotoxy(i%37+1,i%32+4,handle_out),putchar(' '),i++)
		if(i%37==0)Sleep(10); 
		gotoxy(0,0,handle_out);
	}
	else fread(&save_data,sizeof(struct console_save),1,save_p);
	
	fp=fopen(save_data.file_path,"r+"); 
	if(fp!=NULL) save_data.student_num=(int)student_file(fp,1);
	if(!fp && save_p!=NULL)
	{
		sprintf(input_buf,"Error ：文件 %s 丢失 ;");
		MessageBox(NULL,TEXT(input_buf),TEXT("Error：文件丢失"),MB_OK);
		open_file_list(handle_out,handle_in,save_p);
	} 
	
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
    //开始动画部分
    
	SetConsoleTextAttribute(handle_out,15);
	for(i=0;i<40*45;i++,putchar(' ')); 
	printf(".           ._________________.         ");Sleep(40); 
	printf  ("            | _______________ | ");Sleep(30);
	printf("\n            |┃             ┃| ");Sleep(20);
	printf("\n            |┃             ┃| ");Sleep(20);
	printf("\n            |┃             ┃| ");Sleep(20);
	printf("\n            |┃             ┃| ");Sleep(20);
	printf("\n            |┃_____________┃| ");Sleep(20);
	printf("\n            !_________________! ");Sleep(20);
	printf("\n               ._[_______]_. ");Sleep(10);
	printf("\n           .___|___________|___."); Sleep(10);
	printf("\n           |::: ____           | ");Sleep(10);
	printf("\n       ┏━|    ~~~~ [CD-ROM]  | ");Sleep(10);
	printf("\n∷ ━━┛  !___________________! \n"); 
	for( i=-30;i < 99; i++,Sleep(20))
	{ 
		if(i<=0)	printf("\n");
		else
		{	
			if(i==1)
			{
				gotoxy(0,41,handle_out),printf("∷━━━━━━━━━━━━━━━━━━━ \n Loading ");
				PlaySound("sounds\\start(2).wav", NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
			}
			gotoxy(15+(i%13),3+(i%5),handle_out),putwchar(' ');
        	SetConsoleTextAttribute(handle_out,i+rand()%256);
 			if(i > 67)	gotoxy(i%58-1,43,handle_out),printf(">");
 			if(i == 68)	PlaySound ("sounds\\Load_run.wav", NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
		}
	}
	PlaySound("sounds\\c-ad-hd.wav", NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
	Sleep(1000);
	PlaySound("sounds\\NULL_music.wav", NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //菜单部分	

while("死循环")
{ 	
	SetConsoleTextAttribute(handle_out,15);
	for(i=0;i<=43;Sleep(30-i/2),printf("%s",system_ui[i++]));
	putchar('\n');
	gotoxy(0,0,handle_out);
	for(i=0;i<44;printf("%s",system_ui[i++]));
	for(i=0,GetCursorPos(&map);1;gotoxy(2+(i++)%30,0,handle_out),putchar('-'),Sleep(10))
	{   
		SetConsoleTextAttribute(handle_out,15);
        if(z==0)	mouserec_event(handle_in);
        else		
		{  
      		if(i<=z+9)
			for(gotoxy(0,0,handle_out),k=0;k<10;printf("%s",system_ui[k++]));  
			StudentList(fp,handle_out,handle_in,i,save_p);
			if(z==0)
  			{
				gotoxy(0,0,handle_out);
    		 	for(i=0;i<44;printf("%s",system_ui[i++]));
  			}
        }
		gotoxy(36,0,handle_out);
		if(pos.X==36 && pos.Y==0)	printf("Ⅹ");
		else						printf("■");
		if(kbhit()) 
		{ 	
			gotoxy(12,22,handle_out);
			gets(input_buf);
		}
	 	if(pos.Y != 8 && pos.Y != 10 && pos.Y != 12 && pos.Y != 14 && pos.X>=13 && pos.X<=26 && z==0) 
		if(i%2==0)gotoxy(0,7,handle_out),printf("%s","┊                                    ┊┊           <- 开始抽取 ->           ┊┊                                    ┊┊           <- 管理名单 ->           ┊┊                                    ┊┊           <- 关于我们 ->           ┊┊                                    ┊┊           <- 系统设置 ->           ┊┊                                    ┊");
		
		if(pos.X>=13 && pos.X<=26) 
		{	
			SetConsoleTextAttribute(handle_out,rand()%16); 	
			if(((k<0)?(k*-1):k)!=pos.Y)
			mciSendString(TEXT("close keydown"), NULL, 0, NULL),k=pos.Y;	
			if(pos.Y==8 || pos.Y==10 || pos.Y==12 || pos.Y==14)
			{	
				if(z==0 || (3+i%34<10 || 3+i%34>=30)) gotoxy(3+i%34,pos.Y-1,handle_out), printf((i/54%3==0)?"-":" ");
    			gotoxy(36-i%34,pos.Y+1,handle_out),printf((i/54%3==0)?"-":" ");
				if(k>=0)
				{	
					if(z==0)	mciSendString(TEXT("open sounds\\Latch_Slide_2.wav alias keydown"), NULL, 0, NULL);   
					else 		mciSendString(TEXT("open sounds\\Button38.wav alias keydown"), NULL, 0, NULL);
					mciSendString(TEXT("play keydown"), NULL, 0, NULL),k*=-1;
					if(z==0)	i=0+rand()%20;
 				}
				if(z==0)
				{
					gotoxy(16+(i%4)*2,20,handle_out);
					if(i/8%2==0) printf("◆");
					else printf("◇");
					switch(pos.Y)
  					{	
						case  8:gotoxy(12,  8,handle_out);printf((i/4%2==0)?"<-  开始抽取  ->":" <- 开始抽取 -> ");break; 
						case 10:gotoxy(12, 10,handle_out);printf((i/4%2==0)?"<-  管理名单  ->":" <- 管理名单 -> ");break;
						case 12:gotoxy(12, 12,handle_out);printf((i/4%2==0)?"<-  关于我们  ->":" <- 关于我们 -> ");break;
						case 14:gotoxy(12, 14,handle_out);printf((i/4%2==0)?"<-  系统设置  ->":" <- 系统设置 -> ");break;
					} 
				}
			}
		}
		else	SetConsoleTextAttribute(handle_out,rand()%16);
		if(pos.X>=16 && pos.X<=22 && pos.Y==20)
		gotoxy(pos.X,pos.Y,handle_out),printf((i/100%2==0)?"◇":"□");		
		if(pos.X>=2 && pos.X<=37 && pos.Y>=26 && pos.Y<=40)
		gotoxy(pos.X,pos.Y,handle_out),printf("+");
		 
		//  ↓ 判断鼠标事件 做出反应 
		if (mouserec.EventType == MOUSE_EVENT && z==0)    //如果当前为鼠标事件  
        {  
   			gotoxy(pos.X, pos.Y,handle_out); 
            if (mouserec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)  //单击鼠标左键  
            {  	
            	if(pos.X==36 && pos.Y==0)	exit(0);
            	if(pos.X>=13 && pos.X<=26 && pos.Y>=8 && pos.Y<=14)
           		{	
           			if(pos.X>=13 && pos.X<=26 && pos.Y==8)	
			   		{
	   					_music(2);
					   	break;
			   		}
					switch(pos.Y)
  					{
						case 10:_music(2),z=i+1,mouserec.EventType = 0;break;
						case 12:_music(2),MessageBox(NULL,TEXT("\n	制作：Mr.Monster联芯\n	该程序编写于：2015.8.24\n\n\n	这应该会是我高中时代的最终(最佳)作\n\n	Le Vent se lève  Li faut tenter de vivre. 让我怎能不爱！！\n\n	我的c语言讨论群：454059384 / QQ:1347004358\n\n	谢鸣：感谢WWW.ZIXUE7.COM的c 语言自学教程   \n"),TEXT(" 关于我们 "),MB_OK);break;
						case 14:{_music(2),setup(handle_out,handle_in);
						for(gotoxy(0,0,handle_out),i=0;i<44;printf("%s",system_ui[i++]));
						Sleep(100),_music(8),Sleep(400); 
						};break;
  					}
           		}
           		else	printf("%s",input_buf);  
       		} 
            if (mouserec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)  putchar(' ');//单击鼠标右键       
            if (mouserec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)  						   //双击清除屏幕 
            {
            	_music(4),SetConsoleTextAttribute(handle_out,15);
            	gotoxy(0,0,handle_out);
            	for(i=0;i<44;printf("%s",system_ui[i++]));
            }
        }  
		if(i%4==0)	gotoxy(9+(rand()%3)*8,27+i%14,handle_out),printf("%s",student_file(fp,0)); 
		gotoxy(36-(i%18)*2,43,handle_out),printf("┉");
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	//抽签部分		 
	SetConsoleTextAttribute(handle_out,15);
	gotoxy(0, 44,handle_out),printf("\n┍------------------------------------┑");
	for(i=0;++i<45;printf(" [%02d].          \n",i),Sleep(20));
	printf("┕------------------------------------┙\n");
	for(rewind(fp),GetCursorPos(&map),i=0;++i;Sleep(ABS(30-i/5)),srand(time(NULL)))
	{
		name_buf=student_file(fp,0);
		SetConsoleTextAttribute(handle_out,i%16);
		if(save_data.donghuatype == 1)	gotoxy((i%2==0)?i%30:28-i%28, 45,handle_out);
		else 							gotoxy((i%2==0)?i%30:28-i%28, 44,handle_out);
		printf("  [%02d]. %-10s \t\t     \n\n",i%(save_data.student_num),name_buf);
		if(i%(save_data.student_num)!=0 && i>=save_data.donghuatime && rand()%(save_data.student_num)==i%(save_data.student_num) || i==0)
		{	
			SetConsoleTextAttribute(handle_out,15);
			gotoxy(0,43,handle_out),printf("┕------------------------------------┙\a\n\n\n\n"); 	 
			for(k=0;1;k++)
			{	
				mouserec_event(handle_in);   //判断当前指针位置
				if(GetKeyState(VK_LBUTTON)==-128 || GetKeyState(VK_LBUTTON)==-127) //我用另一个函数来实现了检测鼠标左键触发事件 
				{	
					_music(4);
					if(pos.X>=0 && pos.X <=10 && pos.Y==0)	i=-1;
					break;
				} 
				if(pos.X>=0 && pos.X <=10 && pos.Y==0) 
				_music(4),SetConsoleTextAttribute(handle_out,240);
				gotoxy(0,0,handle_out),printf(" <-- BACK                               ");
				SetConsoleTextAttribute(handle_out,15);
				gotoxy(3,42,handle_out),printf("选中[%02d]:\t     ┃",i%66);
				SetConsoleTextAttribute(handle_out,(k/400%2==0)?15:240),printf("%s",name_buf); 
				SetConsoleTextAttribute(handle_out,15),					printf("┃");
			}
			rewind(fp);
			if(i!=-1)  printf("\n┍------------------------------------┑\n",i=0); 
		}
	}
	gotoxy(0,44,handle_out);
}

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ”管理名单“ 部分 
void StudentList(FILE *fp,HANDLE handle_out,HANDLE handle_in,int i,FILE *save_p)
{
	int len=0,j=0,k=0,color[3]={8,7,15};
	DIR *dir;
	char *input_buf;
	struct dirent *s;
	FILE *p; 
	
	if(i==z+10) i--;
	if(i>z+10) i=11,z=2;
	gotoxy(19-(i-z),i-z,handle_out),printf("%s",tip_window);
	for(k=1;k<=(i-z)+1;gotoxy(19-(i-z),(i-z)+k,handle_out),printf("%s",tip_window[k++])); 
	if(i%4==0) Sleep(10);
	if(i>=z+9)	
	{		
		mouserec_event(handle_in); 
		if(pos.X >=14 && pos.X<=26 && (pos.Y == 12 || pos.Y == 14 ))
		{
			gotoxy(12,pos.Y,handle_out),printf((pos.Y == 12)?"      更换名单  ":"      查看名单  ┆");
			if(mouserec.EventType == MOUSE_EVENT && mouserec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{		
				if(pos.Y == 14)	// 查看名单 部分 
				{
					_music(1),Sleep(50),GuoDu(0,0,handle_out),GuoDu(1,0,handle_out);
					gotoxy(0,0,handle_out);
					for(k=0;k<44;printf("%s",chakan_ui[k++]));
					rewind(fp);
					len=(int)student_file(fp,1);
					stu_p=(struct student_name *)malloc(len*sizeof(struct student_name));
					for(i=0;i<len;strcpy(stu_p[i].stu_name,student_file(fp,0)),i++); 
					for(i=0;1;i++,j=ABS(j))
					{
						mouserec_event(handle_in);
						if(i==0 || (pos.X>=31 && pos.X<=38))
						for(k=j;k<=j+28;gotoxy(8,k-j+8,handle_out),printf((k<=len)?"[%03d]. %-10s":"                    ",(k++)+1,stu_p[k].stu_name));
						else 			Sleep(20);
						gotoxy(31,20,handle_out),printf(" %3.f%%  ",((float)((k>=len)?len:k)/len)*100);
						if(pos.X>=31 && pos.X<=38 && pos.Y==10)		_music(4),SetConsoleTextAttribute(handle_out,15);
						else										SetConsoleTextAttribute(handle_out,240); 
						gotoxy(31,10,handle_out),printf(" BACK  "); 
						if(pos.X>=31 && pos.X<=38 && pos.Y==14)		j--,_music(4),Sleep(30),SetConsoleTextAttribute(handle_out,15);
						else										SetConsoleTextAttribute(handle_out,240); 
						gotoxy(31,14,handle_out),printf(" UP    ");
						if(pos.X>=31 && pos.X<=38 && pos.Y==16)		j+=(j<len-29)?1:0,_music(4),Sleep(30),SetConsoleTextAttribute(handle_out,15);
						else										SetConsoleTextAttribute(handle_out,240); 
						gotoxy(31,16,handle_out),printf(" DOWN  ");
						if(pos.X>=31 && pos.X<=38 && pos.Y==18)	
						{
							SetConsoleTextAttribute(handle_out,15);
							if(GetKeyState(VK_LBUTTON)==-128 || GetKeyState(VK_LBUTTON)==-127)
							ReadConsoleInput(handle_in, &mouserec, 1, &res),_music(4),j+=(j>=len-28)?-j:28;
							Sleep(60);
						}
						else									SetConsoleTextAttribute(handle_out,240); 
						gotoxy(31,18,handle_out),printf(" AUTO  "); 
						SetConsoleTextAttribute(handle_out,rand()%16);
						gotoxy(2+i%30,0,handle_out),putchar('-');
						gotoxy(36-(i%18)*2,43,handle_out),printf("┉");
						SetConsoleTextAttribute(handle_out,15);
						if(3+i%34<10 || 3+i%34>=30)
 						{
							gotoxy(3+i%34,41,handle_out),printf((i/54%3==0)?"-":" ");
    						gotoxy(36-i%34,42,handle_out),printf((i/54%3==0)?"-":" ");
  						} 
  						if(mouserec.EventType == MOUSE_EVENT && mouserec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
						if(pos.X>=31 && pos.X<=38 && pos.Y==10)
						{
							_music(1),GuoDu(0,0,handle_out),GuoDu(1,1,handle_out),pos.X=0,pos.Y=0,z=0;
							return ;
						}
					}
				}
				else{/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						_music(2),SetConsoleTextAttribute(handle_out,15);
						for(i=0;i<10;i++)
						{
							for(gotoxy(0,0,handle_out),k=0;k<10;printf("%s",system_ui[k++]));
							gotoxy(19-i,i,handle_out),printf("%s",tip_window),Sleep(20);
							for(k=1;k<=i+1;gotoxy(19-i,i+k,handle_out),printf("%s",tip_window[k++])); 
							gotoxy(19-i,i+k,handle_out),printf("%s",tip_window[11]);
						}gotoxy(10,10,handle_out),printf("┆ 请选择一项：   ┆");
						for(i=0;1;mouserec_event(handle_in),i++)
						{	
							if(i/10%2==0 || ((pos.Y == 12 || pos.Y == 14) && pos.X>=10 && pos.X<=20))
							{
								if(i/10%2==1) _music(6);
								gotoxy(12,12,handle_out),printf((pos.Y == 12 && i>10)?"      读取文件  ":"  读取文件      ");
								gotoxy(12,14,handle_out),printf((pos.Y == 14 && i>10)?"      手动输入  ":"  手动输入      ");
								if(i==0)	Sleep(200);
							}
							if(GetKeyState(VK_LBUTTON)==-128 || GetKeyState(VK_LBUTTON)==-127) //我用另一个函数来实现了检测鼠标左键触发事件
						 	{	
						 		if(pos.Y == 12 && pos.X>=10 && pos.X<=20 )
							 	{
								 	open_file_list(handle_out,handle_in,save_p),fclose(fp),fp= fopen (save_data.file_path,"r+");
									return ;
							 	}
							 	if(pos.Y == 14 && pos.X>=10 && pos.X<=20 )
							 	{
								 	for(_music(1),GuoDu(0,0,handle_out),GuoDu(1,0,handle_out),gotoxy(0,0,handle_out),i=0;i<44;printf("%s",chakan_ui[i++]));
								 	gotoxy(16,4,handle_out),printf("手动输入");
								 	stu_p = (struct student_name *)  malloc (sizeof(struct student_name)*1000); 
								 	input_buf = (char *) malloc (14);
					 			 	for(i=0,len=0,j=0;1;i++,j=ABS(j))
									{
										mouserec_event(handle_in);
										gotoxy(16+(i/16%4)*2,38,handle_out);
										if((i/(32*4))%2==0) printf((i/(16*4))%2==0?"□":"◆");
										else printf("◇");
										if(i%4==0)
										for(k=(len>26)?j:0;(len>26)?k<j+26:k<len;k++)
										{ 
											gotoxy(8,(len>26)?k-j+9:35-len+k,handle_out);
											printf("[%3d].%-10s",k,stu_p[k].stu_name);
										}
										if(pos.X>=31 && pos.X<=38 && pos.Y==22)		_music(4),SetConsoleTextAttribute(handle_out,15);
										else										SetConsoleTextAttribute(handle_out,240); 
										gotoxy(31,22,handle_out),printf(" BACK  "); 
										if(pos.X>=31 && pos.X<=38 && pos.Y==26)		j--,_music(4),Sleep(40),SetConsoleTextAttribute(handle_out,15);
										else										SetConsoleTextAttribute(handle_out,240); 
										gotoxy(31,26,handle_out),printf(" UP    ");
										if(pos.X>=31 && pos.X<=38 && pos.Y==28)		j+=(j<len-26)?1:0,_music(4),Sleep(40),SetConsoleTextAttribute(handle_out,15);
										else										SetConsoleTextAttribute(handle_out,240); 
										gotoxy(31,28,handle_out),printf(" DOWN  ");
										if(pos.X>=31 && pos.X<=38 && pos.Y==32)		_music(4),Sleep(40),SetConsoleTextAttribute(handle_out,15);
										else										SetConsoleTextAttribute(handle_out,240); 
										gotoxy(31,32,handle_out),printf(" 保存  ");
										SetConsoleTextAttribute(handle_out,rand()%16);
										gotoxy(2+i%30,0,handle_out),putchar('-');
										gotoxy(36-(i%18)*2,43,handle_out),printf("┉");
										if(kbhit())
										{
											SetConsoleTextAttribute(handle_out,15);
											gotoxy(10,36,handle_out),SetConsoleTextAttribute(handle_out,15); 
											fgets(stu_p[len].stu_name,10,stdin);
											for(k=0;k<10;k++)
											if(stu_p[len].stu_name[k] == '\n')	stu_p[len].stu_name[k] = '\0';
											len++,j+=(len>26)?1:0;
										}
								 		SetConsoleTextAttribute(handle_out,15);
										if(i<3) gotoxy(6,7,handle_out),SetConsoleTextAttribute(handle_out,color[i]),printf("请输入学生姓名 最多输入1000名"),Sleep(200);
										gotoxy(4,36,handle_out),printf("输入：          ");
										if(mouserec.EventType == MOUSE_EVENT && mouserec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
										{ 
											if(pos.X>=31 && pos.X<=38 && pos.Y==22)
											{
												_music(1),free(stu_p),GuoDu(0,0,handle_out),GuoDu(1,1,handle_out),pos.X=0,pos.Y=0,z=0;
												return ;
											}
											if(pos.X>=31 && pos.X<=38 && pos.Y==32)
											{
												Sleep(100),_music(2);
												p=fopen("./studentlist.dll","w+"); 
												save_p = fopen("./save.data","w+");
												save_data.student_num = len-1; 
												memset(save_data.file_path,0,32);
												strcpy(save_data.file_path,"./studentlist.dll");
												for(k=0;k<len;sprintf(input_buf,"	%s	\n",stu_p[k++].stu_name),fputs(input_buf,p));
												fwrite(&save_data,sizeof(struct console_save),1,save_p);
												fclose(p),fclose(save_p),fclose(fp);
												MessageBox(NULL,TEXT("保存成功\n\n已保存到程序目录下\n文件：studentlist.dll里\n\n按确认返回"),TEXT("  保存成功 "),MB_OK);
												fp=fopen("./studentlist.dll","r+");
											} 
										} 
									}
									 
							 	}
								if(!((pos.Y == 12 || pos.Y == 14) && pos.X>=10 && pos.X<=20))
								{
									_music(4),z=0;
									return ;
								}
						 	} 
						}
					} 
			}
		}
		else 
		{	
			if(GetKeyState(VK_LBUTTON)==-128 || GetKeyState(VK_LBUTTON)==-127)
			_music(4),Sleep(200),z=0,free(stu_p),SetConsoleTextAttribute(handle_out,15);
			return ;
		}
	}
	if(pos.Y == 10) pos.Y==12,pos.X=20;
} 
