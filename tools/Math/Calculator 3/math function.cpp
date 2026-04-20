int PlusPow (
	int x,
	int y
	)
{
	int t = 1;
	if (y == 0) {
		return 1;
	}
	for (int i = 0;i < y;i ++) {
	   t *= x;
	}
	return t;
}
double MinusPow (
	int x,
	int y
	)
{
	double t = 1;
	int m = -y;
	for (int i = 0;i < m;i ++) {
		t *= 1.0/x;
	}
	return t;
}