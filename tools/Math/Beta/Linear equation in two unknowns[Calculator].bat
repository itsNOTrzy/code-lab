@echo off
color 1e
:choose
cls
mode con cols=67 lines=20
title Linear equation in two unknowns[Calculator]
echo Linear equation in two unknowns[Calculator]
echo.
echo Answer on "Answer.html" and desktop of calculator.
echo If logs have got "0.x", you should checking calculation.
echo.
echo 1.Calculation  2.Check log
set /p chose=Choose(1/2):
if "%chose%"=="1" goto start
if "%chose%"=="2" goto log
cls
echo Error£¡
pause
goto choose
:start
cls
echo    a     b      c
echo 1©°a1x + b1y £½ c1©´
echo 2©¸a2x + b2y £½ c2©¼
set /p a1=a1£½
cls
echo    a     b      c
echo 1©°%a1%x + b1y £½ c1
echo 2©¸a2x + b2y £½ c2
set /p b1=b1£½
cls
echo    a     b      c
echo 1©°%a1%x + %b1%y £½ c1
echo 2©¸a2x + b2y £½ c2
set /p c1=c1£½
cls
echo    a     b      c
echo 1©°%a1%x + %b1%y £½ %c1%
echo 2©¸a2x + b2y £½ c2
set /p a2=a2£½
cls
echo    a     b      c
echo 1©°%a1%x + %b1%y £½ %c1%
echo 2©¸%a2%x + b2y £½ c2
set /p b2=b2£½
cls
echo    a     b      c
echo 1©°%a1%x + %b1%y £½ %c1%
echo 2©¸%a2%x + %b2%y £½ c2
set /p c2=c2£½
cls

echo    a     b      c
echo 1©°%a1%x + %b1%y £½ %c1%
echo 2©¸%a2%x + %b2%y £½ %c2%
set /a x1=%b1%*%c2%-%b2%*%c1%
set /a x2=%a2%*%b1%-%a1%*%b2%
set /a y1=%a1%*%c2%-%a2%*%c1%
set /a y2=%b2%*%a1%-%b1%*%a2%
set times=0 
set jd=2
set /a yus=%x1%%%x2%
set /a jg=%x1%/%x2%
set /a yusy=%y1%%%y2%
set /a jgy=%y1%/%y2%
if %yus% equ 0 goto skip
:back
cls
echo Answer is decimals.
echo How many digits after the decimal point?
echo Don't input as 2 digits after.
set /p jd=Input: 
cls
if exist Answer.html goto skip2
echo ^<html^>>>Answer.txt
echo ^<title^>>>Answer.txt
echo Answer: >>Answer.txt
echo ^</title^>>>Answer.txt
echo ^<h2^>>>Answer.txt
goto skip3
:skip2
ren Answer.html Answer.txt
cls
:skip3
echo [%date%,%time%] >>Answer.txt
echo %a1%x + %b1%y £½ %c1%, >>Answer.txt
echo %a2%x + %b2%y £½ %c2%, >>Answer.txt
echo x £½ >>Answer.txt
echo %jg% >>Answer.txt
echo . >>Answer.txt
:again
set /a yus2=%yus%*10
set /a jg2=%yus2%/%x2%
set /a yus3=%yus2%%%x2%
echo %jg2% >>Answer.txt
set /a times=%times%+1
set /a yus=%yus3%
if %times% lss %jd% goto again
echo , >>Answer.txt
echo y £½ >>Answer.txt
echo %jgy% >>Answer.txt
echo . >>Answer.txt
:againy
set /a yusy2=%yusy%*10
set /a jgy2=%yusy2%/%x2%
set /a yusy3=%yusy2%%%x2%
echo %jgy2% >>Answer.txt
set /a timesy=%timesy%+1
set /a yusy=%yusy3%
if %timesy% lss %jd% goto againy
echo ^<h2^>>>Answer.txt
ren Answer.txt Answer.html
echo    a     b      c
echo 1©°%a1%x + %b1%y £½ %c1%
echo 2©¸%a1%x + %b1%y £½ %c1%
echo Answer is decimals.
echo Check "Answer.html".
pause
goto start
:skip
if %yusy% equ 0 goto skip4
goto back
:skip4
set /a x=%x1%/%x2%
set /a y=%y1%/%y2%
echo x=%x%
echo y=%y%
if exist Answer.html goto begin
echo ^<html^>>>Answer.txt
echo ^<title^>>>Answer.txt
echo Answer: >>Answer.txt
echo ^</title^>>>Answer.txt
echo ^<h2^>>>Answer.txt
goto begin1
:begin
ren Answer.html Answer.txt
:begin1
echo [%date%,%time%] %a1%x+%b1%y=%c1%, %a2%x+%b2%y=%c2%, x=%x%, y=%y% >>Answer.txt
echo ^<h2^>>>Answer.txt
ren Answer.txt Answer.html
pause
cls
goto start
:log
if not exist Answer.html goto error
Answer.html
goto start
:error
cls
echo No log£¡
pause
cls
goto start
