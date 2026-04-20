@echo off&set jiluk=&set /a xiaosu=10
title Mathemetics Calculator 2
set sangcijg=&set "pi=3.14"
::3.1415926535897932384626433832795 圆周率31位小数
setlocal enabledelayedexpansion&set "lin=00000"
for /l %%a in (1 1 5) do set "lin=!lin!!lin!!lin!"
:kaisi
set yyd=&color 2f
echo.
echo.
echo        Mathemetics Calculator 2
echo        Copyright(C) Eisenberg Andrew Roland
echo.
echo       [1]Readme   [2]Text edit interface   [3]Mathemetics Calculator
:kaisi2
echo.&set xuanze=&set /p xuanze=   &cls
if "%xuanze%"=="3" color 2f&goto start0
if not defined xuanze color 2f&goto start0
if defined yyd if "!xuanze!"=="1" cls&goto kaisi
if "%xuanze%"=="1" (
  call :ydsuom "%~0"
  set yyd=a&echo.&echo.
  echo.      [1]Home   [2]Text edit interface   [3]Mathemetics Calculator
  goto kaisi2
)
if not "%xuanze%"=="2" cls&goto kaisi
:wbjm 文本界面
cls&color 2f
echo.&echo.  [Enter]Home
echo.&echo.  [3]Manually enter expression interface
echo.&echo.  Input path or put file in here ━━ 
echo.&set wenben=&set /p wenben= &cls&set baocun=temp.txt
if "!wenben!"=="3" cls&goto start0
if not defined wenben cls&goto kaisi
set "wenben=%wenben:"=%"
if not exist "%wenben%" echo  File does not exist！&ping/n 3 127.0>nul&goto wbjm
echo.&echo. Calculating text file %wenben:"=%, answer save in Answer.txt .
echo.&echo. Just a moment, please.&echo.
setlocal&cd.>"Answer.txt"
for /f "usebackq delims=" %%a in ("%wenben%") do (
   call :start0 "%%a" okk
   >>"Answer.txt" echo !okk!
)
start "" "Answer.txt"
exit
:start0
setlocal
if "!wenben!"=="3" set "wenben="
if defined wenben set suru=%~1&goto wenben
echo.&echo. System save number is %xsljjg%
echo.&echo.  %sangcijg%
echo.&echo.&echo.&echo. [0]Readme
echo.&echo. Input expression:
echo.&set "suru="&set /p suru= &cls
if "!suru!"=="0" (
   call :ydsuom "%~0"
   echo.&echo.    Press any key to restart.&pause>nul&cls&color 2f
   endlocal&set xsljjg=%jilu%&goto start0
)
if not defined suru endlocal&cls&set xsljjg=%jilu%&goto start0
set "suru=%suru: =%"
if "!suru:~-1!"=="+" set jiluk=a&set "bq=+"
if "!suru:~-1!"=="-" set jiluk=a&set "bq=-"
if "!suru:~-1!"=="*" set jiluk=a&set "bq=*"
if "!suru:~-1!"=="/" set jiluk=a&set "bq=/"
if "!suru:~-1!"=="." set jiluk=a&set jilu=0&set "bq=+"
if defined jiluk set suru=!suru:~0,-1!
:wenben
set "suru=%suru: =%"
if "!suru:~0,1!"=="." set "suru=0!suru!"
for %%a in (c + - / ^( [ {) do set "suru=!suru:%%a.=%?.!"
if "%suru:~-1%"=="=" set "suru=%suru:~0,-1%"
echo.&echo.Calculating  %suru% =
set xsjg=%suru% =
:::从这里开始
set "ok="
if "%suru:~0,1%"=="-" set "suru=f%suru:~1%"
call :lis1 "%suru%" ok
set "ok=!Ok:~1!"
for %%a in (c + - / ^( [ {) do set "ok=!ok:%%a-=%?!"
for /l %%a in (0 1 9) do (
  set ok=!ok:%%a^(=%?^(!
  set ok=!ok:^)%%a=^)c%%a!
  set "ok=!ok:%%a[=%?[!"
  set "ok=!ok:]%%a=]c%%a!"
  set "ok=!ok:%%a{=%?{!"
  set "ok=!ok:}%%a=}c%%a!"
)
set "ok=!ok:pi=%pi%!"
set "ok=0+!ok!+0"
call :cif "!ok!" ok
for %%g in ("()" "[]" "{}") do (
  set "kuoh=%%~g"
  call :lisxh "!ok!" ok
)
call :liscc "!ok!" ok
call :lisjj "!ok!" ok
set ok=!ok:f=-!
::完成计算
set lecs=&set "cucw="
if defined jiluk (
   set "okok=!ok!"
   set "leiji=!okok! !bq! !jilu!"
   if "!bq!"=="/" if "!jilu!"=="0" (
      set bq=*&set /a okok=1
      set "leiji=0 + !jilu!"
      set lecs=Cannot divide by zero！Cumulative storage results in the fixity.
    )
   if "!ok!"=="Cannot divide by zero！" (
      set lecs=Cannot divide by zero！Cumulative storage results in the fixity.
      set "leiji=0 + !jilu!"
      set bq=+&set /a okok=0
    )
   call :start "^(!okok!^)!bq!^(!jilu!^)" jilu
)
if defined wenben endlocal&set %~2=%xsjg% %ok%&goto :EOF
cls&set xsljjg=!jilu!  !lecs!
set sangcijg=!xsjg! !ok!   !cucw!
if defined jiluk (
  endlocal&set jilu=%jilu%&set "xsljjg=%xsljjg%"&set "sangcijg=%sangcijg%"
) else endlocal&set "sangcijg=%sangcijg%"
goto start0
goto :EOF
:lisxh 处理各种()[]{}括弧
for /f "tokens=1,2* delims=%kuoh%" %%a in ("%~1") do (
   if "%%b"=="" set %~2=!ok!&goto :EOF
   call :liscc "%%b" ok
   call :lisjj "!ok!" ok
   set "ok=!ok:-=f!"
   set "ok=%%a!ok!%%c"
   call :lisxh "!ok!" ok
)
goto :EOF
:liscc 计算连续乘除
set ph=%~1&set q=&set h=&set aa=&set n=0
set ph=!ph:c= c# !&set ph=!ph:/= /@ !
set ph=!ph:+= + !&set ph=!ph:-= - !
for /f "tokens=1* delims=c/" %%a in ("!ph!") do (
   if "%%b"=="" set %~2=!ph: =!&goto :EOF
   for %%i in (%%a) do set q=!q!!aa!&set "aa=%%i"
   for %%i in (%%b) do set /a n+=1&set "m!n!=%%i"
   for /l %%i in (3 1 !n!) do set h=!h!!m%%i!
   if "!m1!"=="#" (set m1=*) else set "m1=/"
   set "js=^(!aa:f=-!^)!m1!^(!m2:f=-!^)"
   if not "!h!"=="" set h=!h:c#=c!&set "h=!h:/@=/!"
   call :start "!js!" ph
   if "!ph!"=="Cannot divide by zero！" set q=&set "h="
   set "ph=!ph:-=f!"
   set "ph=!q!!ph:-=f!!h!"
   set "ph=!ph:/@=/!"
   call :liscc "!ph!" ph
)
set "%~2=!ph: =!"
goto :EOF
:lisjj 计算连续加减
set he=&set js=%~1
set js=!js:+= +!&set js=!js:-= -!
for %%a in (!js!) do (
   set "b=%%a"
   if defined he (
      set js=^(!he!^)!b:~0,1!^(!b:~1!^)
      set js=!js:f=-!
      call :start !js! he
    ) else set "he=%%a"
 )
set "%~2=!he:-=f!"
goto :EOF
:lis1 将*号替换为c 方便代码运行
for /f "tokens=1* delims=*" %%a in ("%~1") do (
   set "ok=!ok!c%%a"
   call :lis1 "%%b" ok
   if "%%b"=="" goto :EOF
)
set "%~2=%ok%"
goto :eof
:cif  处理次方
set aaa=&set bbb=&set aa=&set bb=&set n=0
for /f "tokens=1* delims=x" %%a in ("%~1") do (
   if "%%b"=="" set %~2=!ok!&goto :EOF
   set a=%%a&set "b=%%b"
   set a=!a:^(=^( !&set a=!a:+=+ !&set a=!a:-=- !
   set a=!a:c=c !&set a=!a:/=/ !
   for %%i in (!a!) do set aaa=!aaa!!aa!&set aa=%%i
   set b=!b:^)= ^)!&set b=!b:+= +!&set b=!b:-= -!
   set b=!b:c= c!&set b=!b:/= /!
   for %%i in (!b!) do set /a n+=1&set l!n!=%%i
   set bb=!l1!&set "ok="
   for /l %%i in (2 1 !n!) do set bbb=!bbb!!l%%i!
   for /l %%i in (1 1 !bb!) do set ok=!ok!c!aa!
   set "ok=!ok:~1!"
   if "!bb!"=="0" set "ok=1c1"
   if "!bb!"=="1" set "ok=!aa!c1"
   call :liscc "!ok!" ok
   set ok=!aaa!!ok!!bbb!
   call :cif "!ok!" ok
)
set %~2=!ok!
goto :EOF
:start 计算单一算式
setlocal
set "suru=%~1"
set yunsuanf=&set f=&set "ff="&set xs1=&set "xs2="
set "suru=%suru: =%"
if "%suru:~-1%"=="=" set "suru=%suru:~0,-1%"
if "%suru:~0,1%"=="(" set suru=%suru:~1%&set "xs1=("
if "%suru:~0,1%"=="-" (set yf=-) else set "yf="
for /f "tokens=1* delims=+-*/" %%a in ("%suru%") do (
   set num=%yf%%%a&set "str=%%b"
   (set str=!str:^(=!&set str=!str:^)=!)
)
(set num=!num:^)=!)
set "ysf=!suru:*%num%=!"
if "%ysf:~0,1%"==")" set "ysf=%ysf:~1%"
set "ysf=!ysf:~0,1!"
if not defined xs1 (set "xs1=!num!")else set "xs1=!xs1!!num!)"
set "xsysf=%ysf%"
if "!str:~0,1!"=="-" (set "xs2=(!str!)")else set "xs2=!str!"
set "xsss=!xs1! !xsysf! !xs2!"
if "!num:~0,1!"=="-" (
  if "!str:~0,1!"=="-" (set ff=) else set "ff=-"
) else if "!str:~0,1!"=="-" set "ff=-"
if "!ysf!"=="+" (
   set "yunsuanf=jia"&set "ff="
   if "!num:~0,1!"=="-" (
      set "ff=-"
      if not "!str:~0,1!"=="-" set "yunsuanf=jian"
    ) else if "!str:~0,1!"=="-" set "yunsuanf=jian"
)
if "!ysf!"=="-" (
   set "yunsuanf=jian"&set "ff="
    if "!num:~0,1!"=="-" (
      set "ff=-"&set "yunsuanf=jia"
      if "!str:~0,1!"=="-" set "yunsuanf=jian"
    ) else (if "!str:~0,1!"=="-" set yunsuanf=jia)
)
if "!ysf!"=="*" set "yunsuanf=cen"
if "!ysf!"=="/" (set "yunsuanf=cu0")
set num=!num:-=!&set "str=!str:-=!"
set /a numxw=0,strxw=0,xzw=0,xc=0,duo=0
call :pdxs %num% numz numx numxw
call :pdxs %str% strz strx strxw
if %numxw% geq %strxw% (set /a duo=numxw) else set /a duo=strxw
set /a xzw=numxw+strxw,xc=numxw-strxw&set "xc=!xc:-=!"
if !duo! neq 0 (
   set "numx=!numx:~0,%duo%!"&set "strx=!strx:~0,%duo%!"
) else set "numx="&set "strx="
::echo 第一个数 整数 %numz%   小数 %numx%   小数的位数 %numxw% 位
::echo 第一个数 整数 %strz%   小数 %strx%   小数的位数 %strxw% 位
set "she=%numz%%numx% %strz%%strx%"
if "!ysf!"=="*" set /a duo=xzw&set "she=%num:.=% %str:.=%"
call :%yunsuanf% %she% ok
if "!ysf!"=="/" goto ok
goto xs
:pdxs 给小数补0、获取小数位数。
setlocal&set /a z=0
set "var=%~1"
if "!var:~0,1!"=="." set "var=0!var!"
for /f "tokens=1* delims=." %%a in ("!var!")do (set "str1=%%a"
   if "%%b"=="" (set str2=!lin!&set z=0) else (
     set "str2=%%b"
     for /l %%i in (0 1 9) do set "str2=!str2:%%i= %%i !"
     for %%i in (!str2!) do set /a z+=1
     set "str2=!str2: =!"&set "str2=%%b!lin!"
))
Endlocal&set %~2=%str1%&set %~3=%str2%&set "%~4=%z%"&goto :EOF
:xs 处理最终结果
if "%ok:-=%"=="0" goto ok
set "ok=!ff!!ok!"&set "lin="
if "!ok:~0,1!"=="-" (
   if "!ok:~1,1!"=="-" (set "f=") else set "f=-"
) else set "f="
set "ok=!ok:-=!"
if !duo! equ 0 (goto ok) else (
   set "ok=!lin!!ok!"
   set "ok=!ok:~0,-%duo%!.!ok:~-%duo%,%duo%!"
)
:loop
if "!ok:~-1!"=="0" set ok=!ok:~0,-1!&goto loop
for /f "tokens=* delims=0" %%a in ("%ok%") do (
   if "%%a"=="" (set ok=0&goto ok) else set "ok=%%a"
)
if "!ok!"=="." set ok=0&goto ok
if "!ok:~0,1!"=="." set "ok=0!ok!"
if "!ok:~-1!"=="." set "ok=!ok:~0,-1!"
:ok
endlocal&set %~2=%f%%ok%&goto :EOF
:jia 加法函数（封装）
::计算任意位数的正整数加法
setlocal enabledelayedexpansion&set f=&set "t="
set var1=%~1&set var2=%~2&set /a j=0,n1=0,n2=0
for /l %%a in (0 1 9) do (set vard1=&set "vard2="
set var1=!var1:%%a= %%a !&set var2=!var2:%%a= %%a !)
for %%a in (!var1!)do (set/a n1+=1&set vard1=%%a !vard1!)
for %%a in (!var2!)do (set/a n2+=1&set vard2=%%a !vard2!)
(if !n1! lss !n2! (set var1=%var2%&set "var2=%var1%"
set vard1=%vard2%&set vard2=%vard1%))&set "var2=!var2: =!"
for %%a in (!vard1!) do (if "!var2!"=="" set /a var2=0
set /a a=%%a+!var2:~-1!+j&set t=!a:~-1!!t!&set "a=0!a!"
set "j=!a:~-2,1!"&set var2=!var2:~0,-1!)
if !j! neq 0 set "t=!j!!t!"
Endlocal&set %~3=%t%&goto :EOF
:jian 减法函数（封装）
::计算1000位以内的正整数减法
setlocal enabledelayedexpansion&set f=&set "lin=00000"
for /l %%a in (1 1 5) do set "lin=!lin!!lin!!lin!"
set var1=!lin!%~1&set var2=!lin!%~2&set vard1=&set/a j=0
set t=&set var1=!var1:~-1000!&set "var2=!var2:~-1000!"
if "!var1!" lss "!var2!" (set var1=%~2&set "var2=%~1"
set "f=-") else set var1=%~1&set "var2=%~2"
for /l %%a in (0 1 9) do set "var1=!var1:%%a= %%a !"
for %%a in (!var1!) do set "vard1=%%a !vard1!"
for %%a in (!vard1!) do (if "!var2!"=="" set/a var2=0
set /a a=%%a-j,b=!var2:~-1!
if !a! lss !b! (set /a a+=10,j=1)else set /a j=0
set /a w=a-b&set t=!w!!t!&set var2=!var2:~0,-1!)
for /f "tokens=* delims=0" %%a in ("!t!") do (
if "%%a"=="" (set t=0) else set "t=%%a")
Endlocal&set %~3=%f%%t%&goto :EOF
:cen 乘法函数（封装）
::计算任意位数的正整数乘法
setlocal enabledelayedexpansion
if "%~1"=="0" Endlocal&set %~3=0&goto :EOF
if "%~2"=="0" Endlocal&set %~3=0&goto :EOF
set f=&set jia=&set ji=&set /a n1=0,n2=0
set vard1=&set "vard2="&set var1=%~1&set "var2=%~2"
for /l %%a in (0 1 9) do (
set var1=!var1:%%a= %%a !&set var2=!var2:%%a= %%a !)
for %%a in (!var1!)do (set /a n1+=1&set vard1=%%a !vard1!)
for %%a in (!var2!)do (set /a n2+=1&set vard2=%%a !vard2!)
if !n1! gtr !n2! (set vard1=%vard2%&set vard2=%vard1%)
for %%a in (!vard1!) do (set "t="&set /a j=0
for %%b in (!vard2!) do (if "!jia!"=="" set /a jia=0
set /a a=%%a*%%b+j+!jia:~-1!&set "t=!a:~-1!!t!"
set a=0!a!&set j=!a:~-2,1!&set jia=!jia:~0,-1!)
set ji=!t:~-1!!ji!&(if "!j:~0,1!"=="0" (set ss=)else (
set ss=!j:~0,1!))&set jia=!ss!!t:~0,-1!)
(if not "!j:~0,1!"=="0" set t=!j:~0,1!!t!)&set "ji=!t!!ji:~1!"
Endlocal&set %~3=%ji%&goto :EOF
:cu0 500位内整数除法函数（封装）
::函数内有 cu1 cu2 cu3 cu4 四个标签，引用时需注意
setlocal enabledelayedexpansion&set "lin=00000"
for /l %%a in (1 1 5) do set "lin=!lin!!lin!!lin!"
set /a zongw=1000,cs1w=0,cs2w=0,falg=0,x=0
if "!str!"=="1" Endlocal&set %~3=?%!num!&goto :EOF
if "%~1"=="0" set sang=0&goto cu4
if "!str!"=="0" set sang=Cannot divide by zero！&goto cu4
if not defined xiaosu set /a xiaosu=10
set sang=&set ppp=&set var1=%~1&set "var2=%~2"
for /f "tokens=* delims=0" %%a in ("!var1!")do set var1=%%a
for /f "tokens=* delims=0" %%a in ("!var2!")do set var2=%%a
for /l %%a in (0 1 9)do (set "var1=!var1:%%a= %%a !"
set "var2=!var2:%%a= %%a !")
for %%a in (!var1!) do set /a cs1w+=1
for %%a in (!var2!) do set /a cs2w+=1
for /l %%a in (1 1 10) do (set t=&set cs=%~2&set/a j=0
for /l %%b in (1 1 !cs2w!) do (set /a a=%%a*!cs:~-1!+j
set t=!a:~-1!!t!&set a=0!a!&set "j=!a:~-2,1!"
set cs=!cs:~0,-1!&set cs%%a=&set "bj%%a=")
if !j! neq 0 (set cs%%a=!lin!!j!!t!&set "bj%%a=!j!!t!"
) else set cs%%a=!lin!!t!&set "bj%%a=!t!"
set "cs%%a=!cs%%a:~-%zongw%!")
set var2=!lin!!var2: =!&set "var2=!var2:~-%zongw%!"
set /a cswc=cs1w-cs2w&set "var1=!var1: =!"
if !cswc! lss 0 (set cswc=!cswc:-=!&set/a flag=1
for /l %%a in (1 1 !cswc!)do (
if %%a leq 11 set sang=0!sang!&set /a x=cswc-1
set "var1=!var1!0")
set "sang=!sang:~0,1!.!sang:~1!")
set ppp=!var1:~0,%cs2w%!&set "var1=!var1:~%cs2w%!"
if !flag! equ 1 (set /a bul=1) else set /a bul=0
goto cu2
:cu1
if not defined var1 (set "var1=0"
if not defined ppp goto cu4
if !flag! equ 0 (set sang=!sang!.&set /a flag=1))
set/a bul=1&set ppp=!ppp!!var1:~0,1!&set "var1=!var1:~1!"
:cu2
if !x! geq %xiaosu% goto cu4
set pvar1=!lin!!ppp!&set "pvar1=!pvar1:~-%zongw%!"
if "!pvar1!" lss "!var2!" (
if !bul! equ 1 (set sang=!sang!0&set /a bul=0
if !flag! equ 1 set /a x+=1)
if "!ppp:~0,1!"=="0" set "ppp="
goto cu1)
if !flag! equ 1 set /a x+=1
set /a bul=0
::计算商
for /l %%a in (1 1 10) do (
if "!cs%%a!" equ "!pvar1!" (
set "sang=!sang!%%a"&set "yu=!bj%%a!"&goto cu3)
if "!cs%%a!" gtr "!pvar1!" (set /a s=%%a-1
set "sang=!sang!!s!"&set yu=!t!&goto cu3)
set "t=!bj%%a!")
:cu3 计算差
set cjs=!ppp!&set cj1=&set m=&set/a jjj=0
for /l %%a in (0 1 9) do set "cjs=!cjs:%%a= %%a !"
for %%a in (!cjs!) do set "cj1=%%a !cj1!"
for %%a in (!cj1!) do (if "!yu!"=="" set/a yu=0
set /a a=%%a-jjj,b=!yu:~-1!
if !a! lss !b! (set /a a+=10,jjj=1)else set/a jjj=0
set /a w=a-b&set m=!w!!m!&set yu=!yu:~0,-1!)
for /f "tokens=* delims=0" %%m in ("!m!") do (
if "%%m"=="" (set m=0) else set "m=%%m")
if !m! equ 0 (
if "!var1:0=!"=="" set sang=!sang!!var1!&goto cu4
set ppp=&goto cu1) else set "ppp=!m!"
goto cu2
:cu4
if "!sang:~0,1!"=="." set "sang=0!sang!"
Endlocal&set %~3=?%%sang%&goto :EOF
:ydsuom  阅读使用说明
color 2f&set "flag3="
for /f "usebackq delims=" %%a in ("%~1")do (
   if "%%a"=="Mathemetics Calculator 2" set flag3=a
   if defined flag3 echo.&echo  %%a
)
echo.&echo.    ===============================================================
set xiansixs=  Prec: %xiaosu%[Default]
echo.&echo.  !xiansixs! You can altering it own.
echo.
echo.&echo.    P.s. Software can't judge rightly or wrongly of input format.
echo.          You must input rightly format, if you don't, answer will error.
set flag3=&goto :EOF
Mathemetics Calculator 2
1、可对1000位以内 整数、小数、负数进行 加减乘除 计算(除法 500 位)。
   1000位指需计算的数的位数不能超过1000位，包扩小数点及小数的位数。
2、可对表达式进行计算如：1+2-3*4/5
3、支持括弧号如：7+[5*(-2+3)+(1+-2)-2+8]
   运算符为  + - * / ( ) [ ] { } x =
   计算次序为 先括弧内、后括弧外、先乘除、再加减。
   括弧次序依次为：小括弧() 中括弧[] 大括弧{}
4、输入格式：
   负数的输入如：负8减负5 -8--5 或 负8加负5 -8+-5
   小数的输入如：0.5 直接输入 .5 也可以，系统自动补0。
   括弧外测的乘号可省略如：2*(5+3)可简写成 2(5+3) 或 (5+3)2
   算式后面的 = 号 可有可无 如：1+2+3= 或 1+2+3 都可以。
5、可对文本内的算式进行批量计算，文本内必须一行一个算式。
6、手动输入算式：
   算式末尾加运算符 对储存结果的值进行计算。(2+6+ 将8与存储结果的值加起来) (末尾加 / 可能出错)。
   算式末尾加点 定义储存结果的初始值。(2+6. 将存储结果的值改为8)。
7、圆周率：3.14
   圆周率默认两位小数 用 pi 表示。
   如：3*pi 等同 3*3.14	
8、次方的计算及输入：
   如：4的2次方 4x2 如：3的3次方 3x3
   也可在算式中直接输入次方如：2+(2*16x2)+8x5