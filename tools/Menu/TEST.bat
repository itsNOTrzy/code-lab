@echo off
menu /S 取消 /P 1 /F list.txt
cls
echo 你选中了第%errorlevel%号。
set /p s=<page
echo 在第%s%页。
pause