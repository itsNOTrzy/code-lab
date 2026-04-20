#include "common.h"
#include "Input.h"
#include "Output.h"
#include "calculate.h"

//主体
int main (void)
{
	logo ();       //版权
	InitVvar ();   //后台设置常数变量
	while (true) {
		Input ();  //输入与命令解释
		Output (); //输出与命令执行    
	}
	return 0;
}