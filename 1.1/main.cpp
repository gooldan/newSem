#include <iostream>
#include <cstdlib>


struct dot{
	double x;
	double y;
	int n;
};
using namespace std;
double mod(dot a, dot b)
{
	return (abs(a.n - b.n) < 2) ? 0 : sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int main()
{
	double sol[100][100] = { 0 };
	dot dots[100];
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> dots[i].x >> dots[i].y;
		dots[i].n = i;
	}
	for (int l = 2; l <= n; ++l)
	for (int i = 1; i < n - l + 1; ++i)
	{
		int j = i + l - 1;
		sol[i][j] = 10000000;
		for (int k = i; k < j; ++k)
		{
			double temp = sol[i][k] + sol[k + 1][j] + mod(dots[i - 1], dots[k]) + mod(dots[k], dots[j]);
			if (temp < sol[i][j])
				sol[i][j] = temp;
		}
	}
	cout << sol[1][n - 1];
	cin >> n;
}