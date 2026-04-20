#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "calculate.h"
#include "common.h"
#include "Input.h"
#define  BASESIZE  64
#define  STEP      1024
#define  NORMAL    0
#define  NO_BLANK  1
#define  ONE_BLANK 2
#define  CMDNUMBER 4
#define  ENVNUMBER 2

char *COMMAND[] = {"set","view","help","exit","clear"}; //主要命令
//10.7.2015新增clear清屏命令，其功能在output.cpp中
char *ARGUMENT[] = {"prec","all"}; //主要变量

bool isblank (
	char c
	)
/*++
函数描述：

功能：判断一个字符是否为空白字符

参数：
	c	- 要判断的字符

返回值：
	如果是返回 true 否则返回 false
--*/
{
	if (c >= 7 && c <= 10 || c == 13 || c == 32) {
		return true;
	} else {
		return false;
	}
}

char *getline (
	int mode
	)
/*++
函数描述：

功能：从键盘输入任意(理论上)长度的字符串

参数：
	mode	- 工作模式

返回值：动态数组的头指针
--*/
{
	int  c;
	int  i;
	int  times = 1;
	int  switchstat = 0;
	int  BlankCounter = 0;
	char *UnknownString = NULL;
	char *tmp = NULL;
	UnknownString = (char *)malloc (STEP*sizeof(char));
	if (UnknownString == NULL) {
		error = memmory_allocation_failed;
		return NULL;
	}
	for (i = 0;(c=getchar()) != '\n';) {
		if (i == times*STEP - 1) {
			times ++;
			tmp = (char *) realloc (UnknownString,times*STEP*sizeof(char));
			if (tmp == NULL) {			
				error = memmory_allocation_failed;
                return NULL;
            } else {
				UnknownString = tmp;
			}
		}
		switch (mode) {
			case NORMAL:
				UnknownString[i ++] = c;
				break;
			case NO_BLANK:
				if (!isblank(c)) {
					UnknownString[i ++] = c;
				} else {
					continue;
				}
				break;
			case ONE_BLANK:
				if (!isblank(c)) {
					switchstat = 1;
					UnknownString[i ++] = c;
					BlankCounter = 0;
				} else {
					if (switchstat != 1) {
						continue;
					}
					BlankCounter ++;
					if (BlankCounter == 1) {
						UnknownString[i ++] = c;
					}
				}
				break;
		}
		
	}
	UnknownString[i] = NULL;
	return UnknownString;
}

void getarg (
	void
	)
{
	int i = 0;
	int j = 0;
	int times = 1;
	char *p = NULL;
	char *t = NULL;
	do {
		for (; isblank (Unknown[i]);i ++);
		for (j = 0,times = 1,p = NULL;Unknown[i] !=NULL && !isblank(Unknown[i]);i ++,j ++) {
			if (j % (times*BASESIZE - 1) == 0) {
				t = (char *)realloc (p,times*BASESIZE);
				if (t == NULL) {
					error = memmory_allocation_failed;
					return;
				} else {
					p = t;
				}
			}
			if (p != NULL) {
				p[j] = Unknown[i];
			}
		}
		if (p != NULL) {
			p[j] = NULL;
		}
		Command[ArgCounter] = p;
	} while (Command[ArgCounter] != NULL && (++ArgCounter) < 2);
	for (; isblank (Unknown[i]);i ++);
	expString = &Unknown[i];
	if (expString[0] != NULL) {
		ArgCounter ++;
	}
}

void CmdExplain (
	char *cmd)
{
	int i;
	getarg ();
	if (ArgCounter == 0) {
		return;
	}
	for (i = 0;i < CMDNUMBER;i ++) {
		if (strmatch (COMMAND[i],Command[0])) {
			infocmd = i + 1;
			vision = false;
			break;
		}
	}
	if (infocmd == 0) {
		vision = true;
		ArgCounter = 1;
		expString = Unknown;
		return;
	}
	if (ArgCounter == 1) {
		return;
	}
	for (i = 0;i < ENVNUMBER;i ++) {
		if (strmatch (ARGUMENT[i],Command[1])) {
			infoarg = i + 1;
			break;
		}
	}
	for (i = 0;i < CMDNUMBER;i ++) {
		if (strmatch (COMMAND[i],Command[1])) {
			error = connot_use_system_identify;
			return;
		}
	}
}


void Input (
	void
	)
{
	printf ("Calculate> ");
	Unknown = getline (ONE_BLANK);
	if (Unknown == NULL) {
		error = memmory_allocation_failed;
		return;
	}
 	CmdExplain (Unknown);
}