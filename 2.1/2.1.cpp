#include <iostream>
#include <list>
using namespace std;
const int maxN = 20 + 1;
struct point{
	int x;
	int y;
};

int n;
int board[maxN][maxN] = { 0 };
void print(int board[maxN][maxN], int dx[], int dy[],int steps,int fx,int fy)
{
	if (steps == 0) return;
	for (int i = 0; i < 8; ++i)
		if (fx + dx[i] <= n && fx + dx[i]>0 && fy + dy[i] <= n && fy + dy[i]>0 && board[fx + dx[i]][fy + dy[i]] == steps - 1)
		{
			fx += dx[i];
			fy += dy[i];
		}
	print(board, dx, dy, steps-1, fx, fy);
	cout << fx << " " << fy << endl;
}
int main()
{
	int dx[8] = { 2, 2, 1, -1, -2, -2, -1, 1 };
	int dy[8] = { -1, 1, 2, 2, 1, -1, -2,-2 };
	
	cin >> n;
	point place, target;
	for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j)
	{
		board[i][j] = -1;
	}
	int sx, sy, fx, fy;
	//cin >> place.x >> place.y >> target.x >> target.y;
	cin >> sx >> sy >> fx >> fy;
	board[sx][sy] = 0;
	list <point>l;
	place.x = sx;
	place.y = sy;
	l.push_front(place);
	int x = sx; int y = sy;
	int step = 0;
	int newl=1;
	do{
		int oldl = newl;
		newl = 0;
		do
		{
			x = l.back().x;
			y = l.back().y;
			for (int i = 0; i < 8; ++i)
			if (x + dx[i]<=n && x + dx[i]>0 && y + dy[i]<=n && y + dy[i]>0 && board[x + dx[i]][y + dy[i]] == -1)
			{
				board[x + dx[i]][y + dy[i]] = step+1;
				point *a = new point;
				a->x = x + dx[i];
				a->y = y + dy[i];
				l.push_front(*a);
				newl++;
			}
			oldl--;
			l.pop_back();
		} while (oldl > 0);
		step++;
	} while (board[fx][fy] == -1);
	cout << board[fx][fy] << endl << endl;
	int steps = board[fx][fy];
	print(board, dx, dy, steps,fx,fy);
	cout << fx << " " << fy << endl;
	cin >> n;
}