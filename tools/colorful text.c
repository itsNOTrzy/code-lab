#include <stdio.h>    
#include <stdlib.h>    
#include <Windows.h>    
#include <conio.h>    

BOOL FillConsoleOutputAttribute(    // 填充字符属性    
HANDLE hConsoleOutput,              // 句柄    
WORD wAttribute,                    // 文本属性    
DWORD nLength,                      // 个数    
COORD dwWriteCoord,                 // 开始位置    
LPDWORD lpNumberOfAttrsWritten      // 返回填充的个数    
);    
BOOL FillConsoleOutputCharacter(    // 填充指定数据的字符    
HANDLE hConsoleOutput,              // 句柄    
TCHAR cCharacter,                   // 字符    
DWORD nLength,                      // 字符个数    
COORD dwWriteCoord,                 // 起始位置    
LPDWORD lpNumberOfCharsWritten      // 已写个数    
);    
BOOL WriteConsoleOutputCharacter(   // 在指定位置处插入指定数量的字符    
HANDLE hConsoleOutput,              // 句柄    
LPCTSTR lpCharacter,                // 字符串    
DWORD nLength,                      // 字符个数    
COORD dwWriteCoord,                 // 起始位置    
LPDWORD lpNumberOfCharsWritten      // 已写个数    
);

typedef struct _SMALL_RECT  //表示矩形区域的结构体    
{    
  SHORT Left;       //左边界    
  SHORT Top;        //上边界    
  SHORT Right;      //右边界    
  SHORT Bottom;     //下边界    
} SMALL_RECT;    
/*   
微软官方的说法是   
Left    区域的左上顶点的X坐标   
Top     区域的左上顶点的Y坐标   
Right   区域的右下顶点的X坐标   
Bottom  区域的右下顶点的Y坐标   
*/

int main()    
{    
    char *str = "Hello World!";     //定义输出信息    
    int len = strlen(str), i;    
    WORD shadow = BACKGROUND_INTENSITY;     //阴影属性    
    WORD text = BACKGROUND_GREEN | BACKGROUND_INTENSITY;    //文本属性    
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄    
    CONSOLE_SCREEN_BUFFER_INFO csbi;    //定义窗口缓冲区信息结构体    
    GetConsoleScreenBufferInfo(handle_out, &csbi);  //获得窗口缓冲区信息    
    SMALL_RECT rc;      //定义一个文本框输出区域    
    COORD posText;      //定义文本框的起始坐标    
    COORD posShadow;    //定义阴影框的起始坐标    
    //确定区域的边界    
    rc.Top = 8;     //上边界    
    rc.Bottom = rc.Top + 4;     //下边界    
    rc.Left = (csbi.dwSize.X - len) / 2 - 2;    //左边界，为了让输出的字符串居中    
    rc.Right = rc.Left + len + 4;   //右边界    
    //确定文本框起始坐标    
    posText.X = rc.Left;    
    posText.Y = rc.Top;    
    //确定阴影框的起始坐标    
    posShadow.X = posText.X + 1;    
    posShadow.Y = posText.Y + 1;    
    for (i=0; i<5; ++i)     //先输出阴影框    
    {    
        FillConsoleOutputAttribute(handle_out, shadow, len + 4, posShadow, NULL);    
        posShadow.Y++;    
    }    
    for (i=0; i<5; ++i)     //在输出文本框，其中与阴影框重合的部分会被覆盖掉    
    {    
        FillConsoleOutputAttribute(handle_out, text, len + 4, posText, NULL);    
        posText.Y++;    
    }    
    //设置文本输出处的坐标    
    posText.X = rc.Left + 2;    
    posText.Y = rc.Top + 2;    
    WriteConsoleOutputCharacter(handle_out, str, len, posText, NULL);   //输出字符串    
    SetConsoleTextAttribute(handle_out, csbi.wAttributes);   // 恢复原来的属性    
    CloseHandle(handle_out);    
    return 0;    
}
