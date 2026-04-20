#include "FlappyBird.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR iCmdLine,int iShowCmd)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	TCHAR szAppName[]=TEXT("Flappy Bird V1.0 x32");
	int errorCode;
	TCHAR errorInfomation[20];
	
	wndclass.style=CS_HREDRAW|CS_VREDRAW;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.hCursor=LoadCursor(NULL,IDC_HAND);
	wndclass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON));
	wndclass.hInstance=hInstance;
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpfnWndProc=WndProc;
	wndclass.lpszClassName=szAppName;
	wndclass.lpszMenuName=NULL;

	hInst=hInstance;

	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL,TEXT("抱歉,您的操作系统不兼容此游戏!\r\n游戏支持平台:Windows XP/Vista/7/8/8.1/10, 此游戏为32位系统版"),TEXT("警告"),MB_OK|MB_ICONERROR);
		return FALSE;
	}

	hwnd=CreateWindowEx(WS_EX_TOPMOST,szAppName,szAppName,WS_OVERLAPPED|WS_VISIBLE|WS_SYSMENU,
		GetSystemMetrics(SM_CXSCREEN)/2-320,GetSystemMetrics(SM_CYSCREEN)/2-256,
		640,512,
		NULL,NULL,hInstance,NULL);

	if(!hwnd)
	{
		errorCode=GetLastError();
		wsprintf(errorInfomation,TEXT("抱歉,游戏初始化失败!\n错误代码:%d"),errorCode);
		MessageBox(NULL,errorInfomation,TEXT("错误"),MB_OK|MB_ICONERROR);
		return FALSE;
	}

	hInst=(HINSTANCE)hInstance;

	ShowWindow(hwnd,iShowCmd);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,0,0)>0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND hwndPlayButton,hwndQuitButton;
	static HBITMAP hPlayBitmap,hQuitBitmap;
	int i,j;

	switch(iMsg)
	{
	case WM_CREATE:
		hwndPlayButton=CreateWindow(TEXT("button"),TEXT("Play"),WS_CHILD|BS_BITMAP|WS_BORDER,
			205,360,100,40,
			hwnd,(HMENU)IDPLAYBUTTON,hInst,NULL);//create the play button
		hwndQuitButton=CreateWindow(TEXT("button"),TEXT("Quit"),WS_CHILD|BS_BITMAP|WS_BORDER,
			325,360,100,40,
			hwnd,(HMENU)IDQUITBUTTON,hInst,NULL);//create the play button

		hPlayBitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_PLAY));//load the play bitmap resource
		hQuitBitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_QUIT));//load the quit bitmap resource

		SendMessage(hwndPlayButton,BM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)(HBITMAP)hPlayBitmap);//set the play button picture
		SendMessage(hwndQuitButton,BM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)(HBITMAP)hQuitBitmap);//set the quit button picture

		EnableWindow(hwndPlayButton,TRUE);
		EnableWindow(hwndQuitButton,TRUE);
		ShowWindow(hwndPlayButton,SW_SHOW);
		ShowWindow(hwndQuitButton,SW_SHOW);

		GameInfo.BestScore=0;//when login the game,set the best score as 0
		GameInfo.GameState=LOGINGAME;//set the value to indicate we r in the login interface,in this way we can set the relevant interface
		GameInfo.isDayOrNight=DAY;
		GameInfo.GameGrade=NOMEDAL;

		BirdInfo.isBirdDie=LIVE;
		BirdInfo.WhichBird=BLUEBIRD;
		GameInfo.Amination=TRUE;
		GameInfo.NewPipeTime=(int)(1000/PIPEMOVE)-2*GameInfo.GameGrade;

		SetTimer(hwnd,PIPEMOVE,PIPEMOVE,NULL);

		break;

	case WM_GAMEGETREADY://initialize the game
		EnableWindow(hwndPlayButton,FALSE);
		EnableWindow(hwndQuitButton,FALSE);
		ShowWindow(hwndPlayButton,SW_HIDE);
		ShowWindow(hwndQuitButton,SW_HIDE);

		if(LOGINGAME==GameInfo.GameState)
			KillTimer(hwnd,PIPEMOVE);

		GameInfo.GameState=GETREADYGAME;
		GameInfo.isDayOrNight=DayorNight();
		GameInfo.Amination=TRUE;
		GameInfo.GameGrade=NOMEDAL;
		GameInfo.NewPipeTime=(int)(1000/PIPEMOVE)-2*GameInfo.GameGrade;
		GameInfo.isGamePause=FALSE;
		GameInfo.Score=0;
		GameInfo.GameGrade=NOMEDAL;

		BirdInfo.WhichBird=ChooseBirdtoFly();
		BirdInfo.BirdHeight=10;
		BirdInfo.isBirdDie=LIVE;
		
		for(i=0;i<21;i++)
			for(j=0;j<21;j++)
			{
				if(20==i)
					PipeInformation[i][j]=HAVEBOX;
				else
					PipeInformation[i][j]=NOBOX;
			}

		SetTimer(hwnd,PIPEMOVE,PIPEMOVE,NULL); 
		InvalidateRect(hwnd,NULL,FALSE);
		break;
	/*case WM_KILLFOCUS:
		if(PLAYINGGAME==GameInfo.GameState&&DIE!=BirdInfo.isBirdDie)
			SetFocus(hwnd);
		break;
*/
	case WM_TIMER:
		if(TRUE==GameInfo.Amination)
			GameInfo.Amination=FALSE;
		else
			GameInfo.Amination=TRUE;
		switch(GameInfo.GameState)
		{
		case LOGINGAME:
		case GETREADYGAME:
			if(GETREADYGAME==GameInfo.GameState)
				if(GetAsyncKeyState(VK_SPACE)&0x8000)
				{
					GameInfo.GameState=PLAYINGGAME;
				}
			InvalidateRect(hwnd,NULL,FALSE);
		return 0;
		case PLAYINGGAME:
			BirdInfo.isBirdDie=isBirdDie();
			if(DIE==BirdInfo.isBirdDie)
			{
				KillTimer(hwnd,PIPEMOVE);
				PlaySound(TEXT("sfx_hit.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_NODEFAULT);
			}
			else
			{
				NewPipe();
				PipeMove();
				if(GetAsyncKeyState(VK_SPACE)&0x8000)
				{
					if(0==BirdInfo.BirdHeight)
					{
						InvalidateRect(hwnd,NULL,FALSE);
						break;
					}
					BirdInfo.BirdHeight--;
				}
				else
					BirdInfo.BirdHeight++;
			}
			InvalidateRect(hwnd,NULL,FALSE);
			break;
		}
		break;
	case WM_CHAR:
		switch(wParam)
		{
		case 'R':
		case 'r':
			if(LOGINGAME==GameInfo.GameState||DIE==BirdInfo.isBirdDie)
			{
				SendMessage(hwnd,WM_COMMAND,IDPLAYBUTTON,0);
				break;
			}
			else
				break;
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDPLAYBUTTON:
			PlaySound(TEXT("sfx_swooshing.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_NODEFAULT);
			SendMessage(hwnd,WM_GAMEGETREADY,0,0);
			break;
		case IDQUITBUTTON:
			SendMessage(hwnd,WM_CLOSE,0,0);
			break;
		}
		break;

	case WM_PAINT:
		hdc=BeginPaint(hwnd,&ps);
		switch(GameInfo.GameState)
		{
		case LOGINGAME:
			DrawLoginPic(hdc);
			break;
		case GETREADYGAME:
			DrawGetReadyPic(hdc);
			break;
		case PLAYINGGAME:
			DrawPlayingPic(hdc);
			if(DIE==BirdInfo.isBirdDie)
			{
				DrawGameOver(hdc);
				EnableWindow(hwndPlayButton,TRUE);
				EnableWindow(hwndQuitButton,TRUE);
				ShowWindow(hwndPlayButton,SW_SHOW);
				ShowWindow(hwndQuitButton,SW_SHOW);
			}
			break;
		}
		EndPaint(hwnd,&ps);
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		DeleteObject(hPlayBitmap);
		DeleteObject(hQuitBitmap);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd,iMsg,wParam,lParam);
	}
	return 0;
}

int isBirdDie(void)//detect if the bird is die,cross or live
{
	if(20==BirdInfo.BirdHeight||HAVEBOX==PipeInformation[BirdInfo.BirdHeight][4])
		return DIE;

	if(NOBOX==PipeInformation[BirdInfo.BirdHeight][4]&&HAVEBOX==PipeInformation[19][4])
	{
		GameInfo.Score++;
		PlaySound(TEXT("sfx_point.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_NODEFAULT);
		return CROSS;
	}
	else
		return LIVE;
}

BOOL NewPipe(void)//create new pipe
{
	int i,NoPipeHeight;
	time_t t;

	if(0!=GameInfo.NewPipeTime)//it is not time to create the new pipe
	{
		for(i=0;i<20;i++)
			PipeInformation[i][20]=NOBOX;
		GameInfo.NewPipeTime--;
		return FALSE;
	}
	else//create new pipe
	{
		srand((unsigned)time(&t));

		NoPipeHeight=rand()%15+1;

		for(i=1;i<19;i++)
		{
			if(NoPipeHeight==i||NoPipeHeight+1==i||NoPipeHeight+2==i||NoPipeHeight+3==i)
				PipeInformation[i][20]=NOBOX;
			else
				PipeInformation[i][20]=HAVEBOX;
		}
		PipeInformation[0][20]=PipeInformation[19][20]=HAVEBOX;//insure the top and bottom have box
		GameInfo.NewPipeTime=(int)(1000/PIPEMOVE)-2*GameInfo.GameGrade;
		return TRUE;
	}
}

void PipeMove(void)//pipes move to left
{
	int i,j;

	for(j=0;j<21;j++)
		for(i=0;i<20;i++)
		{
			if(0==j)
			{
				PipeInformation[i][j]=NOBOX;
			}
			else
			{
				PipeInformation[i][j-1]=PipeInformation[i][j];
				PipeInformation[i][j]=NOBOX;
			}
		}
}

int WhichGrade(void)//calculate the grade of the player
{
	switch((int)(GameInfo.Score/20))
	{
	case 0:
		GameInfo.GameGrade=NOMEDAL;
		break;
	case 1:
		GameInfo.GameGrade=COPPERMEDAL;
		break;
	case 2:
		GameInfo.GameGrade=SLIVERMEDAL;
		break;
	case 3:
		GameInfo.GameGrade=GOLDMEDAL;
		break;
	case 4:
	default:
		GameInfo.GameGrade=PLATIUMMEDAL;
		break;
	}

	return GameInfo.GameGrade;
}

BOOL DayorNight(void)
{
	time_t t;

	srand((unsigned)time(&t));

	return rand()%2;
};

int ChooseBirdtoFly(void)
{
	time_t t;

	srand((unsigned)time(&t));

	return rand()%3;
}

BOOL DrawLoginPic(HDC hdcWindow)//draw the pic when login
{
	HBITMAP hTempbitmap,hTitlebitmap,hBirdbitmap,hGroundbitmap,hBKbitmap;
	HDC hdcBuffer,hdcTemp;
	HBRUSH hBrushBuffer;
	TCHAR Author[25]=TEXT("Copyright(C) Eisenberg Andrew Roland");
	TCHAR Email[23]=TEXT("Contact(E-mail): 1102933738@qq.com");

	hdcBuffer=CreateCompatibleDC(hdcWindow);

	hTempbitmap=CreateCompatibleBitmap(hdcWindow,640,512);
	hBrushBuffer=(HBRUSH)GetStockObject(HOLLOW_BRUSH);
	SelectObject(hdcBuffer,hBrushBuffer);
	SelectObject(hdcBuffer,hTempbitmap);

	hdcTemp=CreateCompatibleDC(hdcWindow);
	if(DAY==GameInfo.isDayOrNight)//draw the bk pic to the buffer DC
		hBKbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BKDAY));
	else
		hBKbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BKNIGHT));
	SelectObject(hdcTemp,hBKbitmap);
	BitBlt(hdcBuffer,0,0,640,512,hdcTemp,0,0,SRCCOPY);
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);
	hTitlebitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_TITLE));//draw the title to the buffer DC
	SelectObject(hdcTemp,hTitlebitmap);
	TransparentBlt(hdcBuffer,235,150,178,48,hdcTemp,0,0,178,48,RGB(255,255,255));
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the bird to the buffer DC
	switch(BirdInfo.WhichBird)
	{
	case YELLOWBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_YELLOWBIRD));
		break;
	case BLUEBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BLUEBIRD));
		break;
	case REDBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_REDBIRD));
		break;
	}
	SelectObject(hdcTemp,hBirdbitmap);
	if(TRUE==GameInfo.Amination)
		TransparentBlt(hdcBuffer,303,250,34,24,hdcTemp,0,0,34,24,RGB(255,255,255));	
	else
		TransparentBlt(hdcBuffer,303,250,34,24,hdcTemp,0,48,34,24,RGB(255,255,255));
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the ground animation
	hGroundbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_GROUND));
	SelectObject(hdcTemp,hGroundbitmap);
	if(TRUE==GameInfo.Amination)
		StretchBlt(hdcBuffer,0,400,666,112,hdcTemp,10,0,650,112,SRCCOPY);
	else
		StretchBlt(hdcBuffer,0,400,666,112,hdcTemp,0,0,650,112,SRCCOPY);
	DeleteObject(hdcTemp);

	SetBkMode(hdcBuffer,TRANSPARENT);//draw the author information
	SetTextColor(hdcBuffer,RGB(0,124,204));
	TextOut(hdcBuffer,240,430,Author,24);
	SetTextColor(hdcBuffer,RGB(0,153,0));
	TextOut(hdcBuffer,240,450,Email,22);

	BitBlt(hdcWindow,0,0,640,512,hdcBuffer,0,0,SRCCOPY);//draw the all buffer pic to the screen

	DeleteObject(hdcBuffer);
	DeleteObject(hTitlebitmap);
	DeleteObject(hBirdbitmap);
	DeleteObject(hGroundbitmap);
	DeleteObject(hBKbitmap);
	DeleteObject(hBrushBuffer);

	return TRUE;
}

BOOL DrawGetReadyPic(HDC hdcWindow)
{
	HBITMAP hGetReadyTextbitmap,hGetReadyHintbitmap,hBirdbitmap,hGroundbitmap,hBufferbitmap,hBKbitmap;
	HDC hdcTemp,hdcBuffer;
	HBRUSH hBufferbrush;
	TCHAR Hints[]=TEXT("空格键指挥小鸟向上飞");

	hdcBuffer=CreateCompatibleDC(hdcWindow);
	hBufferbitmap=CreateCompatibleBitmap(hdcWindow,640,512);
	hBufferbrush=(HBRUSH)GetStockObject(HOLLOW_BRUSH);
	SelectObject(hdcBuffer,hBufferbitmap);
	SelectObject(hdcBuffer,hBufferbrush);
	
	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the bk pic to the buffer DC
	if(DAY==GameInfo.isDayOrNight)
		hBKbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BKDAY));
	else
		hBKbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BKNIGHT));
	SelectObject(hdcTemp,hBKbitmap);
	BitBlt(hdcBuffer,0,0,640,512,hdcTemp,0,0,SRCCOPY);
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the get ready text to the buffer DC
	hGetReadyTextbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_GETREADY));
	SelectObject(hdcTemp,hGetReadyTextbitmap);
	TransparentBlt(hdcBuffer,228,100,184,50,hdcTemp,0,0,184,50,RGB(255,255,255));
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the get ready hint to the buffer DC
	hGetReadyHintbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_GETREADYTEXT));
	SelectObject(hdcTemp,hGetReadyHintbitmap);
	TransparentBlt(hdcBuffer,265,159,110,97,hdcTemp,0,0,110,97,RGB(255,255,255));
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the bird to the buffer DC
	switch(BirdInfo.WhichBird)
	{
	case YELLOWBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_YELLOWBIRD));
		break;
	case BLUEBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BLUEBIRD));
		break;
	case REDBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_REDBIRD));
		break;
	}
	SelectObject(hdcTemp,hBirdbitmap);
	if(TRUE==GameInfo.Amination)
		TransparentBlt(hdcBuffer,128,200,34,24,hdcTemp,0,0,34,24,RGB(255,255,255));	
	else
		TransparentBlt(hdcBuffer,128,200,34,24,hdcTemp,0,48,34,24,RGB(255,255,255));
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the ground animation
	hGroundbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_GROUND));
	SelectObject(hdcTemp,hGroundbitmap);
	if(TRUE==GameInfo.Amination)
		StretchBlt(hdcBuffer,0,400,666,112,hdcTemp,10,0,650,112,SRCCOPY);
	else
		StretchBlt(hdcBuffer,0,400,666,112,hdcTemp,0,0,650,112,SRCCOPY);
	DeleteObject(hdcTemp);

	SetBkMode(hdcBuffer,TRANSPARENT);//draw the hints information
	SetTextColor(hdcBuffer,RGB(255,255,255));
	TextOut(hdcBuffer,200,430,Hints,15);

	BitBlt(hdcWindow,0,0,640,512,hdcBuffer,0,0,SRCCOPY);//draw the all buffer pic to the screen

	DeleteObject(hBirdbitmap);
	DeleteObject(hGetReadyHintbitmap);
	DeleteObject(hGetReadyTextbitmap);
	DeleteObject(hGroundbitmap);
	DeleteObject(hBKbitmap);
	DeleteObject(hBufferbrush);
	DeleteObject(hBufferbitmap);
	DeleteObject(hdcBuffer);

	return TRUE;
}

BOOL DrawPlayingPic(HDC hdcWindow)
{
	HDC hdcBuffer,hdcTemp;
	HBITMAP hBufferbitmap,hBirdbitmap,hBoxbitmap,hGroundbitmap,hBKbitmap;
	HBRUSH hBufferbrush;
	int i,j;
	TCHAR Score[5000];

	hBufferbitmap=CreateCompatibleBitmap(hdcWindow,640,512);
	hdcBuffer=CreateCompatibleDC(hdcWindow);
	hBufferbrush=(HBRUSH)GetStockObject(HOLLOW_BRUSH);
	SelectObject(hdcBuffer,hBufferbitmap);
	SelectObject(hdcBuffer,hBufferbrush);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the bk pic to the buffer DC
	if(DAY==GameInfo.isDayOrNight)
		hBKbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BKDAY));
	else
		hBKbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BKNIGHT));
	SelectObject(hdcTemp,hBKbitmap);
	BitBlt(hdcBuffer,0,0,640,512,hdcTemp,0,0,SRCCOPY);
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the bird to the buffer DC
	switch(BirdInfo.WhichBird)
	{
	case YELLOWBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_YELLOWBIRD));
		break;
	case BLUEBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BLUEBIRD));
		break;
	case REDBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_REDBIRD));
		break;
	}
	SelectObject(hdcTemp,hBirdbitmap);
	if(TRUE==GameInfo.Amination)
		TransparentBlt(hdcBuffer,128,20*BirdInfo.BirdHeight,32,20,hdcTemp,0,0,34,24,RGB(255,255,255));
	else
		TransparentBlt(hdcBuffer,128,20*BirdInfo.BirdHeight,32,20,hdcTemp,0,48,34,24,RGB(255,255,255));
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the ground animation to the buffer DC
	hGroundbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_GROUND));
	SelectObject(hdcTemp,hGroundbitmap);
	if(TRUE==GameInfo.Amination)
		StretchBlt(hdcBuffer,0,400,666,112,hdcTemp,10,0,650,112,SRCCOPY);
	else
		StretchBlt(hdcBuffer,0,400,666,112,hdcTemp,0,0,650,112,SRCCOPY);
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the box to the buffer DC
	hBoxbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BOX));
	SelectObject(hdcTemp,hBoxbitmap);
	for(j=0;j<20;j++)
		for(i=0;i<20;i++)
		{
			if(HAVEBOX==PipeInformation[i][j])
			{
				BitBlt(hdcBuffer,32*j,20*i,32,20,hdcTemp,0,0,SRCCOPY);
			}
		}
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the bird to the buffer DC
	switch(BirdInfo.WhichBird)
	{
	case YELLOWBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_YELLOWBIRD));
		break;
	case BLUEBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BLUEBIRD));
		break;
	case REDBIRD:
		hBirdbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_REDBIRD));
		break;
	}
	SelectObject(hdcTemp,hBirdbitmap);
	if(TRUE==GameInfo.Amination)
		TransparentBlt(hdcBuffer,128,20*BirdInfo.BirdHeight,32,20,hdcTemp,0,0,34,24,RGB(255,255,255));
	else
		TransparentBlt(hdcBuffer,128,20*BirdInfo.BirdHeight,32,20,hdcTemp,0,48,34,24,RGB(255,255,255));
	DeleteObject(hdcTemp);

	hdcTemp=CreateCompatibleDC(hdcWindow);//draw the score to the buffer DC
	SetBkMode(hdcBuffer,TRANSPARENT);
	wsprintf(Score,TEXT("%d"),GameInfo.Score);
	TextOut(hdcBuffer,320,100,Score,lstrlen(Score));
	DeleteObject(hdcTemp);

	BitBlt(hdcWindow,0,0,640,512,hdcBuffer,0,0,SRCCOPY);//draw the all buffer pic to the screen

	DeleteObject(hBKbitmap);
	DeleteObject(hBirdbitmap);
	DeleteObject(hGroundbitmap);
	DeleteObject(hBoxbitmap);
	DeleteObject(hBufferbrush);
	DeleteObject(hdcBuffer);
	DeleteObject(hBufferbitmap);

	return TRUE;
}

BOOL DrawGameOver(HDC hdcWindow)
{
	HDC hdcBuffer,hdcTemp1,hdcTemp2;
	HBITMAP hTempbitmap,hBirdDownbitmap,hGameOverbitmap,hScoreBoardbitmap,hMedalsbitmap,hBoxbitmap,hNewBestScorebitmap;
	UINT i,birdheight;
	RECT rcScoreText;
	TCHAR buffer[200],Hints[17]=TEXT("快捷操作: 按 r或R 重新开始");

	hdcBuffer=CreateCompatibleDC(hdcWindow);//to store the screen sate of when the bird die
	hTempbitmap=CreateCompatibleBitmap(hdcWindow,640,512);
	SelectObject(hdcBuffer,hTempbitmap);
	BitBlt(hdcBuffer,0,0,640,512,hdcWindow,0,0,SRCCOPY);

	SetBkMode(hdcBuffer,TRANSPARENT);//draw the hints information
	SetTextColor(hdcBuffer,RGB(255,255,255));
	TextOut(hdcBuffer,220,430,Hints,16);

	if(20!=BirdInfo.BirdHeight)//if the bird is not die on the ground,stick a box to cover the bird pic
	{
		hdcTemp2=CreateCompatibleDC(hdcWindow);
		hBoxbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BOX));
		SelectObject(hdcTemp2,hBoxbitmap);
		BitBlt(hdcBuffer,128,BirdInfo.BirdHeight*20,32,20,hdcTemp2,0,0,SRCCOPY);
		DeleteObject(hdcTemp2);
	}

	hdcTemp2=CreateCompatibleDC(hdcWindow);//the animation of bird die
	hBirdDownbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BIRDFLYDOWN));
	SelectObject(hdcTemp2,hBirdDownbitmap);
	birdheight=BirdInfo.BirdHeight;
	for(i=0;i<(21-BirdInfo.BirdHeight);i++)
	{
		BitBlt(hdcWindow,0,0,640,512,hdcBuffer,0,0,SRCCOPY);
		switch(BirdInfo.WhichBird)
		{
		case YELLOWBIRD:
			TransparentBlt(hdcWindow,130,birdheight*20-2,32,40,hdcTemp2,0,0,24,34,RGB(0,0,0));
			break;
		case BLUEBIRD:
			TransparentBlt(hdcWindow,130,birdheight*20-2,32,40,hdcTemp2,0,34,24,34,RGB(0,0,0));
			break;
		case REDBIRD:
			TransparentBlt(hdcWindow,130,birdheight*20-2,32,40,hdcTemp2,0,68,24,34,RGB(0,0,0));
			break;
		}
		birdheight++;
		Sleep(50);
	}
	DeleteObject(hdcTemp2);

	hdcTemp2=CreateCompatibleDC(hdcWindow);//draw the game over text
	hGameOverbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_GAMEOVER));
	SelectObject(hdcTemp2,hGameOverbitmap);
	TransparentBlt(hdcWindow,224,60,192,42,hdcTemp2,0,0,192,42,RGB(255,255,255));
	DeleteObject(hdcTemp2);
	Sleep(10);

	hdcTemp2=CreateCompatibleDC(hdcWindow);//draw the score board 
	hScoreBoardbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_SCOREBORAD));
	SelectObject(hdcTemp2,hScoreBoardbitmap);
	BitBlt(hdcTemp2,0,0,230,100,hdcTemp2,0,0,SRCCOPY);

	SetBkMode(hdcTemp2,TRANSPARENT);//draw the player score
	SetTextColor(hdcTemp2,RGB(0,0,204));
	rcScoreText.top=32;
	rcScoreText.left=160;
	rcScoreText.right=217;
	rcScoreText.bottom=100;
	wsprintf(buffer,TEXT("%d"),GameInfo.Score);
	DrawText(hdcTemp2,buffer,lstrlen(buffer),&rcScoreText,DT_RIGHT|DT_SINGLELINE|DT_CENTER);
	rcScoreText.top+=38;
	rcScoreText.bottom+=38;
	if(GameInfo.Score>GameInfo.BestScore)//if the player have a new best score,show the "new" text in the scoreboard
	{
		hdcTemp1=CreateCompatibleDC(hdcWindow);
		hNewBestScorebitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_NEWBESTSCORE));
		SelectObject(hdcTemp1,hNewBestScorebitmap);
		DeleteObject(hNewBestScorebitmap);
		TransparentBlt(hdcTemp2,84,40,32,14,hdcTemp1,0,0,32,14,RGB(255,255,255));
		GameInfo.BestScore=GameInfo.Score;
		DeleteObject(hdcTemp1);
	};
	wsprintf(buffer,TEXT("%d"),GameInfo.BestScore);
	DrawText(hdcTemp2,buffer,lstrlen(buffer),&rcScoreText,DT_RIGHT|DT_SINGLELINE|DT_CENTER);//draw the best score

	TransparentBlt(hdcWindow,205,125,230,100,hdcTemp2,0,0,230,100,RGB(255,255,255));//draw the score board to the screen
	DeleteObject(hdcTemp2);
	Sleep(10);

	hdcTemp2=CreateCompatibleDC(hdcWindow);//draw the medals
	hMedalsbitmap=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_MEDALS));
	SelectObject(hdcTemp2,hMedalsbitmap);
	DeleteObject(hMedalsbitmap);
	WhichGrade();
	switch(GameInfo.GameGrade)
	{
	case NOMEDAL:
		break;
	case COPPERMEDAL:
		TransparentBlt(hdcWindow,230,160,44,44,hdcTemp2,0,132,44,44,RGB(255,255,255));
		break;
	case SLIVERMEDAL:
		TransparentBlt(hdcWindow,230,160,44,44,hdcTemp2,0,88,44,44,RGB(255,255,255));
		break;
	case GOLDMEDAL:
		TransparentBlt(hdcWindow,230,160,44,44,hdcTemp2,0,44,44,44,RGB(255,255,255));
		break;
	case PLATIUMMEDAL:
		TransparentBlt(hdcWindow,230,160,44,44,hdcTemp2,0,0,44,44,RGB(255,255,255));
		break;
	}
	DeleteObject(hdcTemp2);

	DeleteObject(hdcBuffer);
	DeleteObject(hBirdDownbitmap);
	DeleteObject(hGameOverbitmap);
	DeleteObject(hScoreBoardbitmap);
	DeleteObject(hTempbitmap);
	DeleteObject(hNewBestScorebitmap);

	return TRUE;
}
