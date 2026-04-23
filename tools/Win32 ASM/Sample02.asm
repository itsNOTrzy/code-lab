;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	Programmed by 罗云彬, bigluo@telekbird.com.cn
;	Website: http://asm.yeah.net
;	LuoYunBin's Win32 ASM page (罗云彬的编程乐园)
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	版本信息
;	罗云彬的Win32汇编教程演示程序：
;	一个最简单的Win32程序
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		.386
		.model flat, stdcall
		option casemap :none   ; case sensitive

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	Include 数据
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

include		windows.inc
include		kernel32.inc
include		user32.inc

includelib	kernel32.lib
includelib	user32.lib

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	数据段
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		.data

szCaption	db	'Win32汇编例子 - http://asm.yeah.net',0
szText		db	'Win32 Assembly , Simple and powerful!',0

;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
;	代码段
;>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		.code

start:
		invoke	MessageBox,NULL,addr szText,addr szCaption,MB_OK
		invoke	ExitProcess,NULL

		end	start
