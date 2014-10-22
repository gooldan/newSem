#include <iostream>
#include <vector>
using namespace std;
const int MaxInt = 1000000;
const int maxN = 100;

int a[maxN][maxN], distance_[maxN], path[maxN];
bool visited[maxN];
void pathView(int s, int f)
{
	if (s != f)
	{
		pathView(s, path[f]);
		cout << f + 1 << " ";
	}
}
void dijkstra(int n,int s, int f)
{
	int index, min;
	
	for (int i = 0; i < n; ++i)
	{
		distance_[i] = MaxInt; 
		visited[i] = false;
		path[i] = i;
	}
	distance_[s] = 0;
	for (int i = 0; i < n; ++i)
	{
		min = MaxInt;
		for (int j = 0; j < n; ++j)
		{
			if (!visited[j] && distance_[j] < min)
			{
				min = distance_[j];
				index = j;
			}
		}
		if (min == MaxInt)
			break;
		visited[index] = true;
		for (int j = 0; j < n; j++)
			if ((a[index][j] != -1) && (distance_[index] + a[index][j] < distance_[j]))
			{
				distance_[j] = distance_[index] + a[index][j];
				path[j] = index;
			}
	}
	if (distance_[f - 1] == MaxInt)
	{
		cout << "-1";
		return;
	}
	cout << distance_[f-1]<< endl<<s+1<<" ";
	
	pathView(s, f-1);
}

int main()
{
	int n,s,f;
	cin >> n>>s>>f;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> a[i][j];
		}
	}
	dijkstra(n, s-1, f);
	cin >> n;
}