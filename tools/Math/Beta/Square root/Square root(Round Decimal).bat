@echo off
echo.
echo.
%1 set /p x=     ©³Input radicand ¡ª¡ª 
%1 mshta vbscript:createobject("wscript.shell").run("%~s0 Rem "^&round(sqr(%x%),2))(window.close)&goto :eof
echo     ©³Input radicand ¡ª¡ª %x%
echo     ©ÇSquare root of %x% ¡Ö[£½] %2 (Round to the nearest hundredth)
echo     ©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥
pause