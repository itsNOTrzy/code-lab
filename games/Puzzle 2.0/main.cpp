
// 加载头文件
#include "../Include/picture.h"

/* it学习网收集 http://www.itstudy8.net */

int main()
{
	GameFrame gameframe;												// 建立游戏框架
	Picture picture;													// 建立图片框架
	gameframe.DrawBackground();											// 绘制背景
	gameframe.StartMenu();												// 绘制开始信息
	
	while (1)
	{
		picture.Run();													// 运行控制函数
		Sleep(10);														// 适当增加延时, 节约 CPU
	}
	getch();
	return 0;
}
