#include <windows.h>
#include <time.h>
#include "resource.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
#pragma  comment(lib,"msimg32.lib")

#define WM_GAMEGETREADY WM_USER+1//define the message when the game get ready will send

//define the game state
#define LOGINGAME    1
#define GETREADYGAME 2
#define PLAYINGGAME  3

//define the five kind of medals
#define NOMEDAL      1
#define COPPERMEDAL  2
#define SLIVERMEDAL  3
#define GOLDMEDAL    4
#define PLATIUMMEDAL 5

//define the pipe information on the screen
#define HAVEBOX 1
#define NOBOX 0

//define the bird is die or cross the pipe
#define DIE 0
#define LIVE 2
#define CROSS 1

//define the space time(milliseconds) the pipe move and meanwhile it is the timer ID
#define PIPEMOVE 40

//define the id about the play and quit buttons
#define IDPLAYBUTTON 1
#define IDQUITBUTTON 2

//define which bird be chose
#define YELLOWBIRD 0
#define BLUEBIRD   1
#define REDBIRD    2

//define choose the day or night picture
#define DAY 1
#define NIGHT 0

struct{
	UINT Score;
	UINT BestScore;
	UINT GameState;//the game is login,get ready or playing
	UINT GameGrade;
	int NewPipeTime;
	BOOL isDayOrNight;
	BOOL Amination;
}GameInfo;//the structure information about the game

struct{
	UINT BirdHeight;
	int isBirdDie;
	UINT WhichBird;
}BirdInfo;//the structure information about the bird

BOOL PipeInformation[21][21];//the array show the location on the screen have the pipe or not
HINSTANCE hInst;//the program instances

BOOL NewPipe(void);//create new pipe
int WhichGrade(void);//calculate the grade of the player
void PipeMove(void);//pipes move to left
int isBirdDie(void);//detect if the bird is die,cross or live
BOOL DayorNight(void);//random choose the bkground pic is day or night
int ChooseBirdtoFly(void);//rand choose what kind of bird to play
BOOL DrawPlayingPic(HDC hdcWindow);//draw the Playing amination
BOOL DrawGetReadyPic(HDC hdcWindow);//draw the Get ready amination
BOOL DrawLoginPic(HDC hdcWindow);//draw the pic when login
BOOL DrawGameOver(HDC hdcWindow);//draw the game over amination and score board