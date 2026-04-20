@echo off
set /a r=100,rp=r*r
for /l %%x in (-%r% 1 %r%) do (
	for /l %%y in (-%r% 1 %r%) do (
		set /a "a=rp-%%x*%%x-%%y*%%y,n+=!(a>>31)"
	)
)
set /a pi=n*1000/rp
echo 近似值为 %pi%
pause

::计算相切圆的落点
::计算正方形内所有位于相切圆的落点数量来暴力计算pi
::优点是容易理解，缺点也是级数太大导致运行慢，精确到小数点后 3 位与精确到后 4 位的计算量相差近百倍