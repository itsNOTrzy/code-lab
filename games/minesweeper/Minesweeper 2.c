#include <stdio.h>
#include <graphics.h>//用来绘图
#include <stdlib.h>//使用取随机数函数rand(),srand()从而实现真正意义上的随机
#include <time.h>//用到time()
void put_graph(void);//声明游戏进行的界面函数
void sign_1(int x, int y);//声明用来标识雷的绘图符号函数
void sign_2(int x, int y);//声明用来标识非雷的绘图符号函数
void sign_3(int * count, int x, int y);//声明用来标识雷个数的函数
void information(void);//声明作者信息函数
int start(void);//声明游戏开始界面函数

int main()
{
        double num[10][10];//该数组的下标跟鼠标坐标信息相联系，值为随机分配0到1的值
        int BOOL[10][10];//用来标识方框是否已经被点击
        int i, j, X, Y;//X,Y用来跟鼠标信息坐标发生关系
        int flag;
        flag = start();//调用游戏开始界面函数
        if(flag)
        {
                time_t first, second;
                first = time(NULL); 
                srand((unsigned) time(NULL));//播种子
            for(i = 0; i < 10; ++i)//用来给num[10][10]数组分配随机值
                        for(j = 0; j < 10; ++j)
                        {
                                num[j] = rand()/double(RAND_MAX);//因为rand()函数返回值为int型，而声明的数组是double型，此处用个强制转换
                        }
                        for(i = 0; i < 10; ++i)//用来初始BOOL[10][10]
                                for(j = 0; j < 10; ++j)
                                        BOOL[j] = 1;
            put_graph();//调用游戏进行的界面函数
            information();//调用作者信息函数
            MOUSEMSG m;//声明m的类型，MOUSEMSG 是一个结构体类型
            while (1)//用来重复执行以下操作（不断获取鼠标信息）
                {        
                        int X1,X3,X4,X5,X6,X8,Y1,Y2,Y3,Y6,Y7,Y8;
                    int count = 0;//用来计数非雷周围的雷数
                    m = GetMouseMsg();//获取鼠标信息
                    if(m.uMsg == WM_LBUTTONUP && m.x > 0 && m.x < 500 && m.y > 0 && m.y < 500)
                        {
                                X = m.x / 50;//鼠标的x坐标跟数组的下标关系
                        Y = m.y / 50;//鼠标的y坐标跟数组的下标关系
                            X1 = X-1;//以下是得到非雷周围的坐标信息
                        Y1 = Y-1;
                        Y2 = Y-1;
                        X3 = X+1;
                        Y3 = Y-1;
                        X4 = X-1;
                        X5 = X+1;
                        X6 = X-1;
                        Y6 = Y+1;
                        Y7 = Y+1;
                        X8 = X+1;
                        Y8 = Y+1;
                        int num_X[8] = {X1, X, X3, X4, X5, X6, X, X8};//用非雷周围的位置坐标跟数组相联系
                        int num_Y[8] = {Y1, Y2, Y3, Y, Y, Y6, Y7, Y8};//用非雷周围的位置坐标跟数组相联系
                            if(BOOL[X][Y])
                                        if(num[X][Y] >= 0.8)//num[X][Y] >= 0.8 表示雷
                                        {
                                                char str_1[] = "您的游戏总共";//1
                                                char str_2[] = "用时为：";//2
                                                char str_time[10], str_3[] = "秒";//3
                                                for(i = 0; i < 10; ++i)
                                                        for(j = 0; j < 10; ++j)
                                                        {
                                                                if(num[j] >= 0.8)
                                                                {
                                                                        sign_1(i*50, j*50);
                                                                }
                                                            BOOL[j] = 0;
                                                        }
                                                second = time(NULL);//4这1-11是用来统计用户玩游戏进行的时间并显示
                                                settextcolor(LIGHTGREEN);//5
                            settextstyle(25, 15, _T("宋体"));//6
                                                outtextxy(510,100,str_1);//7
                                                outtextxy(540,130,str_2);//8
                                                sprintf(str_time, "%d", int(difftime(second,first)));//9
                                                outtextxy(565,160,str_time);//10
                                                outtextxy(595,160,str_3);//11
                                        }
                                    else//num[X][Y] < 0.8 表示非雷
                                        {
                                            for(i = 0; i < 8; ++i)
                                                {
                                                        if(num_X >= 0 && num_X <= 9 && num_Y >= 0 && num_Y <= 9)
                                                                if(num[num_X][num_Y] >= 0.8)
                                                                        count++;
                                        }
                                        if(0 == count)
                                        {
                                                sign_3(&count, X*50+3, Y*50+2);//调用用来标识雷个数的函数
                                                BOOL[X][Y] = 0;
                                                for(i = 0; i < 8; ++i)
                                                {
                                                        if(BOOL[num_X][num_Y])
                                                        {
                                                                if(num_X >= 0 && num_X <= 9 && num_Y >= 0 && num_Y <= 9)
                                                                {
                                                                        sign_2(num_X*50,num_Y*50);//调用用来标识非雷的绘图符号函数
                                                                        BOOL[num_X][num_Y] = 0;
                                                                }
                                                        }
                                                }
                                        }
                                        else
                                        {
                                                sign_3(&count, X*50+3, Y*50+2);//调用用来标识雷个数的函数
                                                BOOL[X][Y] = 0;
                                        }
                                }
                        }
                }
        }
        else
        {
                closegraph();
                exit(EXIT_FAILURE);
        }
        return 0;
}
void put_graph(void)//定义游戏开始的界面函数
{
        initgraph(700, 500);//取窗口的大小
        line(0, 50, 500, 50);
        line(0, 100, 500, 100);
        line(0, 150, 500, 150);
        line(0, 200, 500, 200);
        line(0, 250, 500, 250);
        line(0, 300, 500, 300);
        line(0, 350, 500, 350);
        line(0, 400, 500, 400);
        line(0, 450, 500, 450);
        line(50, 0, 50, 500);
        line(100, 0, 100, 500);
        line(150, 0, 150, 500);
        line(200, 0, 200, 500);
        line(250, 0, 250, 500);
        line(300, 0, 300, 500);
        line(350, 0, 350, 500);
        line(400, 0, 400, 500);
        line(450, 0, 450, 500);
        line(500, 0, 500, 500);
}
void sign_1(int x, int y)//定义标识雷的绘图符号函数
{
        setcolor(RED);//用此函数改变绘图的颜色
    line(x, y, x+50, y+50);//绘出X的符号，用于标识地雷
    line(x+50, y, x, y+50);
}
void sign_2(int x, int y)//定义标识非雷的绘图符号函数
{
        setcolor(RED);
        line(x, y+25, x+25, y+50);//绘出对号，用于标识不是地雷
        line(x+25, y+50, x+50, y);
}
void information(void)//定义作者信息函数
{
        char name[] = "Copyright(C) Eisenberg Andrew Roland";
        char QQ[] = "QQ: 1102933738";
        settextcolor(LIGHTGREEN);
        outtextxy(550, 460, name);
        outtextxy(540, 480, QQ);
}
void sign_3(int * count, int x, int y)
{ 
        char str[5];
        settextcolor(LIGHTGREEN);
        settextstyle(45, 45, _T("宋体"));
        sprintf(str, "%d", *count);
        outtextxy(x, y, str);
}
int start(void)//定义游戏开始界面函数
{
        initgraph(250,320);
        IMAGE img_star;
        loadimage(&img_star,"开始.jpg");
        putimage(20,60,&img_star);
        IMAGE img_end;
        loadimage(&img_end,"结束.jpg");
        putimage(20,180,&img_end);
        MOUSEMSG n;
        while(1)
        { 
                n = GetMouseMsg();
                if(n.uMsg == WM_LBUTTONUP && n.x > 20 && n.x < 220 && n.y > 60 && n.y < 127)
                {
                        return 1;
                        break;
                }
                else if(n.uMsg == WM_LBUTTONUP && n.x > 20 && n.x < 220 && n.y > 180 && n.y < 247)
                {
                        return 0;
                        break;
                }
                else 
                        continue;
        }
}
