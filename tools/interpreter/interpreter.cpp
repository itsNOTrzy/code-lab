#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cstdlib>

static double d;

using namespace std;
int setpos(int nx,int ny);
int setstr(string name,string str);
int modecon(string c,string s);
int add(string name,string str);
int sub(string name,string str);
int mult(string name,string str);
int div(string name,string str);
int getstr(string name);
int mos(string str1,string str2);
bool isnum(const char* cstr) ;

//主函数
int main(int argc,char **argv) //设置程序入口，支持一个参数，即文件
{
	system("title Comioud For Win32");

	//临时目录获取，用于储存变量
	TCHAR buf[MAX_PATH];
	GetTempPath(MAX_PATH, buf);
    string tmpdir = buf;

	if(argc != 1) //确保参数有效
	{
		string gv;
		bool gvs=false;
		string filename=argv[1];
		system("rd /s /q %temp%\\set>nul 2>nul&md %temp%\\set>nul 2>nul");
		_load:
		ifstream infile(filename.c_str());
		string line;
		string cl;
		 while(getline(infile,line)) //逐行读取
	     {
			 if (line==":"+gv) {gvs=false;}
			 if (gvs==false) {
			//基础命令部分的解析
			 if (line=="pause")//暂停运行
			 {
			system("pause>nul");
			 continue;
			 }
		     if (line=="echo.")//回显文字
			 {
			system("echo.");
			 continue;
			 }
			  if (line=="cls")//清屏
			 {
			system("cls");
			 continue;
			 }
			 if (line=="_exit")//结束解释器
			 {
             return 0;
			 }

			 //带有参数的命令解析部分

			 istringstream f(line);
               string p;
			    while( getline(f,p,';'))
			       {
					   if(cl=="echo")// echo 的具体处理
					   {
							   cout<<p;
					   }
					   if(cl=="void")// void 的具体处理
					   {
						 
						   string fpstr=tmpdir+"\\set\\"+p+".cv";
							ifstream p(fpstr.c_str());
							string nr;
							getline(p,nr);
							
								cout<<nr;
					   }
					   if(cl=="title")// title 的具体处理
					   {
						   string s(p);
						   string comc1="title "+s;
							   system(comc1.c_str());
					   }
					   if(cl=="goto")// goto 的具体处理
					   {
						   gvs=true;
						   gv=p;
					   }
					   if(cl=="get")// goto 的具体处理
					   {
						   getstr(p);
					   }
					    if(cl=="shell")// shell 的具体处理
					   {
							   system(p.c_str());
					   }
						if(cl=="pos")// pos 的具体处理
					   {
						   
						   int cx=0;
						 int cy=0;
						   int js=0;
						    istringstream t(p);
							string p1;
			              while( getline(t,p1,' '))
						  {
							  if(js==0)
							  {
								  cx=atoi(p1.c_str());
								  js++;
							  }
							  else
							  {
								  cy=atoi(p1.c_str());
							  }
						  }
						  setpos(cx,cy);
					   }
						if(cl=="set")// set 的具体处理
					   {
						   
						   string cname="";
						 string cstr="";
						   int js=0;
						    istringstream t(p);
							string p2;
			              while( getline(t,p2,'='))
						  {
							  if(js==0)
							  {
								  cname=p2;
								  js++;
							  }
							  else
							  {
								  cstr=p2;
							  }
						  }
						  setstr(cname,cstr);
					   }

						if(cl=="add")// add 的具体处理
					   {
						   
						   string cname="";
						 string cstr="";
						   int js=0;
						    istringstream t(p);
							string p2;
			              while( getline(t,p2,' '))
						  {
							  if(js==0)
							  {
								  cname=p2;
								  js++;
							  }
							  else
							  {
								  cstr=p2;
							  }
						  }
						  add(cname,cstr);
					   }

						if(cl=="sub")// sub 的具体处理
					   {
						   
						   string cname="";
						 string cstr="";
						   int js=0;
						    istringstream t(p);
							string p2;
			              while( getline(t,p2,' '))
						  {
							  if(js==0)
							  {
								  cname=p2;
								  js++;
							  }
							  else
							  {
								  cstr=p2;
							  }
						  }
						  sub(cname,cstr);
					   }

						if(cl=="mult")// mult 的具体处理
					   {
						   
						   string cname="";
						 string cstr="";
						   int js=0;
						    istringstream t(p);
							string p2;
			              while( getline(t,p2,' '))
						  {
							  if(js==0)
							  {
								  cname=p2;
								  js++;
							  }
							  else
							  {
								  cstr=p2;
							  }
						  }
						  mult(cname,cstr);
					   }

						if(cl=="div")// div 的具体处理
					   {
						   
						   string cname="";
						 string cstr="";
						   int js=0;
						    istringstream t(p);
							string p2;
			              while( getline(t,p2,' '))
						  {
							  if(js==0)
							  {
								  cname=p2;
								  js++;
							  }
							  else
							  {
								  cstr=p2;
							  }
						  }
						  div(cname,cstr);
					   }


						if(cl=="if")// if 的具体处理
					   {
						   
						   string s1="";
						 string s2="";
						   int js=0;
						   int js1=0;
						    istringstream t(p);
							string p2;
							string s3="";
			              while( getline(t,p2,'='))
						  {
							  if(js==0)
							  {
								  s1=p2;
								  js++;
							  }
							  else
							  {
								  s2=p2;
								  istringstream t(s2);
								string p3;
								while( getline(t,p3,'$'))
								{
									if(js1==0)
							  {
								  s3=p3;
								  js1++;
							  }
							  else
							  {
								  string fpstr=tmpdir+"\\set\\"+s1+".cv";
							ifstream q(fpstr.c_str());
							string nr;
							getline(q,nr);
                           if(nr==s3) {
								   gvs=true;
								   gv=p3;
						   }
									}
								}
							  }
						  }
					   }



							if(cl=="con")// con 的具体处理
					   {
						   
						   string cols="";
						 string lines="";
						   int js=0;
						    istringstream t(p);
							string p2;
			              while( getline(t,p2,' '))
						  {
							  if(js==0)
							  {
								  cols=p2;
								  js++;
							  }
							  else
							  {
								  lines=p2;
							  }
						  }
						  modecon(cols,lines);
					   }
					   cl="";
					   if (p=="echo"){cl="echo";}// echo 的定义
					   if (p=="void"){cl="void";}// void 的定义
					   if (p=="title"){cl="title";}// title 的定义
					   if (p=="shell"){cl="shell";}// shell 的定义
					   if (p=="pos"){cl="pos";}// pos 的定义
					   if (p=="con"){cl="con";}// con 的定义
					   if (p=="set"){cl="set";}// set 的定义
					   if (p=="+"){cl="add";}// add 的定义
					   if (p=="-"){cl="sub";}// sub 的定义
					   if (p=="*"){cl="mult";}// mult 的定义
					   if (p=="/"){cl="div";}// div 的定义
					   if (p=="<"){cl="get";}// get 的定义
					   if (p=="if"){cl="if";}// if 的定义
					   if (p=="sif"){cl="sif";}// if 的定义
					   if (p=="goto"){cl="goto";}// goto 的定义

				    }
		
		 }
		 }
		 	if(gvs==true){goto _load;}
	}
	else
	{
	}
	//程序运行完毕后的提示
	system("title Comioud For Win32");
	system("cls&echo Comioud Alpha");
	if(argc == 1)
	{
		system("echo 没有提交脚本任务");
	}
	else
	{
		system("echo 脚本已经执行完毕(自然结束)");
	}
	system("pause>nul");
	return 0;
}

//标准光标移动函数
int setpos(int nx,int ny)
{
	DWORD dwMode, dwOldMode;	/* 原来的模式与新模式 */
	DWORD dwRead;	/* 已经读取的输入事件数 */
	int mouse_pos; /* 用于返回鼠标位置 */
	UINT count;		/* 用于循环控制 */
	INPUT_RECORD ir[128];	/* 控制台输入记录 */
	CONSOLE_CURSOR_INFO cci, cciOld;	/* 鼠标相关的设置 */
	COORD co;	/* 鼠标移动时更新坐标 */
	HANDLE hStdIn = NULL, hStdOut = NULL; /* 标准输入输出句柄  */

		HANDLE hOut;
		COORD pos= {nx,ny};
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hOut, pos);
		return 0;
}

//以字符方式写入变量
int setstr(string name,string str)//字符型变量写入
{
	string action="echo ^"+str+">%temp%\\set\\^"+name+".cv";
	system(action.c_str());
	return 0;
}

//接受控制台输入到变量
 int getstr(string name)
{
	char st[4096];
    cin>>st;
	string nrp;
	nrp=st;
	string action="echo ^"+nrp+">%temp%\\set\\^"+name+".cv";
	system(action.c_str());
	return 0;
}


//加减乘除
int add(string name,string str)//变量加
{
		TCHAR buf[MAX_PATH];
	GetTempPath(MAX_PATH, buf);
    string tmpdir = buf;
		string fpstr=tmpdir+"\\set\\"+name+".cv";
	ifstream q(fpstr.c_str());
	string nr;
	getline(q,nr);
	if(isnum(str.c_str())==true)
	{
		double a=atof(nr.c_str());
	d=a+atof(str.c_str());
	}
	else
	{
	string fpstr=tmpdir+"\\set\\"+str+".cv";
	ifstream q(fpstr.c_str());
	string nb;
	getline(q,nb);
	double a=atof(nr.c_str());
	double b=atof(nb.c_str());
	d=a+b;
	}
	double c=d;
	stringstream ss;
string ns;
ss<<c;
ss>>ns;
	string action="echo ^"+ns+">%temp%\\set\\^"+name+".cv";
	system(action.c_str());
	return 0;
}

int sub(string name,string str)//变量减
{
		TCHAR buf[MAX_PATH];
	GetTempPath(MAX_PATH, buf);
    string tmpdir = buf;
		string fpstr=tmpdir+"\\set\\"+name+".cv";
	ifstream q(fpstr.c_str());
	string nr;
	getline(q,nr);
	if(isnum(str.c_str())==true)
	{
		double a=atof(nr.c_str());
	d=a-atof(str.c_str());
	}
	else
	{
		string fpstr=tmpdir+"\\set\\"+str+".cv";
	ifstream q(fpstr.c_str());
	string nb;
	getline(q,nb);
	double a=atof(nr.c_str());
	double b=atof(nb.c_str());
	d=a-b;
	}
	double c=d;
	stringstream ss;
string ns;
ss<<c;
ss>>ns;
	string action="echo ^"+ns+">%temp%\\set\\^"+name+".cv";
	system(action.c_str());
	return 0;
}

int mult(string name,string str)//变量乘
{
		TCHAR buf[MAX_PATH];
	GetTempPath(MAX_PATH, buf);
    string tmpdir = buf;
	string fpstr=tmpdir+"\\set\\"+name+".cv";
	ifstream q(fpstr.c_str());
	string nr;
	getline(q,nr);
	if(isnum(str.c_str())==true)
	{
		double a=atof(nr.c_str());
	d=a*atof(str.c_str());
	}
	else
	{
		string fpstr=tmpdir+"\\set\\"+str+".cv";
	ifstream q(fpstr.c_str());
	string nb;
	getline(q,nb);
	double a=atof(nr.c_str());
	double b=atof(nb.c_str());
	d=a*b;
	}
	double c=d;
	stringstream ss;
string ns;
ss<<c;
ss>>ns;
	string action="echo ^"+ns+">%temp%\\set\\^"+name+".cv";
	system(action.c_str());
	return 0;
}

int div(string name,string str)//变量除
{
		TCHAR buf[MAX_PATH];
	GetTempPath(MAX_PATH, buf);
    string tmpdir = buf;
	string fpstr=tmpdir+"\\set\\"+name+".cv";
	ifstream q(fpstr.c_str());
	string nr;
	getline(q,nr);
	if(isnum(str.c_str())==true)
	{
		double a=atof(nr.c_str());
	d=a/atof(str.c_str());
	}
	else
	{
		string fpstr=tmpdir+"\\set\\"+str+".cv";
	ifstream q(fpstr.c_str());
	string nb;
	getline(q,nb);
	double a=atof(nr.c_str());
	double b=atof(nb.c_str());
	d=a/b;
	}
	double c=d;
	stringstream ss;
string ns;
ss<<c;
ss>>ns;
	string action="echo ^"+ns+">%temp%\\set\\^"+name+".cv";
	system(action.c_str());
	return 0;
}

//修改控制台大小
int modecon(string c,string s)
{
	string action="mode con:cols="+c+" lines="+s;
	system(action.c_str());
	return 0;
}

//判断是否纯数字
bool isnum(const char* cstr)  
{  
    if (NULL == cstr || cstr[0] == 0)  
    {  
        return false;  
    }  
  
    int len = strlen(cstr);  
    int pos = 0;  
    if (cstr[0] == '-' || cstr[0] == '+')  
    {  
        if (len <= 1)   
        {  
            return false;  
        }  
          
        pos++;          
    }  
      
    while (pos < len)  
    {  
        if (cstr[pos] < '0' || cstr[pos] > '9')  
        {  
            return false;  
        }  
        pos++;  
    }  
  
    return true;  
}  