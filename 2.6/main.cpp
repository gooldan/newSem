#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int inf = 1000*1000;

int src=1, stok, m, n;
int flow;
vector< vector<int> > mat(n,vector<int>(n,-1));


vector<int> bfs()
{
	queue<int> Q;
	vector<int> used;
	vector<int> way;
	used.assign(n+1, -1);
	used[src] = 1;
	Q.push(src);
	while (!Q.empty())
	{
		int t = Q.front();
		Q.pop();
		for (int i = 1; i <= n; ++i)
		{
			if (mat[t][i]>0 && used[i] == -1)
			{
				used[i] = t;
				Q.push(i);
				if (i == stok)
				{
					int p = i;
					
					while (p!=src)
					{
						way.insert(way.begin(), p);
						p = used[p];
					}
					way.insert(way.begin(), 1);
					return way;
				}
			}
		}
	}
	return way;
}


int maxFlow()
{
	vector<int> way(1);
	while (way.size() != 0)
	{
		way = bfs();
		if (way.size() == 0)
			return flow;
		int min = inf;
		for (int i = 0; i < way.size()-1; ++i)
		{
			if (mat[way[i]][way[i + 1]] < min)
			{
				min = mat[way[i]][way[i + 1]];
			}
		}
		for (int i = 0; i < way.size() - 1; ++i)
		{
			mat[way[i]][way[i + 1]] -= min;
		}
		flow += min;
	}
}
int main()
{
	cin >> n >> m;
	int c, a, b;
	mat.assign(n, vector<int>(n+1, -1));
	for (int i = 0; i < m; ++i)
	{
		cin >> a >> b >> c;
		mat[a][b] = c;
	}
	stok = n; 
	cout<<maxFlow();
	cin >> m;
}