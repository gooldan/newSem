#include <vector>
#include <iostream>
#include <deque>
using namespace std;
const int inf = 1000 * 1000;
int n, m;
vector<vector<pair<int, int>>>  mat;
vector < vector< pair< pair< int, int >, int> > > g;
vector<vector<int>> f;
bool levitt(vector<int> &way)
{

	int v1 = 1;
	vector<int> d(n, inf);
	d[v1] = 0;
	vector<int> id(n);
	deque<int> q;
	q.push_back(v1);
	vector<int> p(n, -1);
	while (!q.empty())
	{
		int v = q.front();
		q.pop_front();
		id[v] = 1;
		for (int i = 0; i<g[v].size(); ++i)
		{
			int to = g[v][i].second, cost = g[v][i].first.first;
			if ((d[to] > d[v] + cost) && (f[v][i] < g[v][i].first.second))
			{
				d[to] = d[v] + cost;
				if (id[to] == 0)
					q.push_back(to);
				else if (id[to] == 1)
					q.push_front(to);
				p[to] = v;
				id[to] = 1;
			}
		}
	}
	way = p;
	if (way[n - 1] == -1)
		return false;
	return true;
}

int minn(int v, int &min, vector<int> &way)
{
	if (v == 1)
		return min;
	if (mat[way[v]][v].second < min)
		min = mat[way[v]][v].second;
	minn( way[v],min,way);
}
void subs(int v, int &min,vector<int> &way)
{
	if (v == -1)
		return;
	if (way[v]>0)
	{
		mat[way[v]][v].second -= min;
		mat[v][way[v]].second += min;
		f[way[v]][v] -= min;
		f[v][way[v]] += min;
		for (int i = 0; i < g[way[v]].size(); ++i)
		{
			if (g[way[v]][i].second == v)
				g[way[v]][i].first.second -= min;
			if (g[way[v]][i].first.first < 0)
				g[way[v]][i].first.second += min;
		}
	}
	subs(way[v], min, way);
}
int main()
{
	cin >> n >> m;
	m++;
	n++;
	for (int i = 0; i <= m; ++i)
	{
		vector<pair<int, int>> t(n);
		mat.push_back(t);
		vector <pair<pair<int, int >, int>> p;
		g.push_back(p);
		vector<int> y;
		y.assign(n, 0);
		f.push_back(y);
	}
	for (int i = 0; i < m-1; ++i)
	{
		int cost, capacity, a, b;
		cin >> a >> b >> capacity >> cost;
		mat[a][b].first = cost;
		mat[a][b].second = capacity;
		mat[b][a].first = -cost;
		mat[b][a].second = 0;
		g[a].push_back(make_pair(make_pair(cost, capacity), b));
		g[b].push_back(make_pair(make_pair(-cost, 0), a));
	}
	int res = 0;
	vector<int> way; 
	while (levitt(way))
	{
		int min = inf;
		res+= minn(n-1, min, way);
		subs(n - 1, min, way);
	}
	int ccc = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (f[i][j]>0)
				ccc+=mat[i][j].first*f[j][i];
		}
	}
	cout << res << " " << ccc;
	cin >> n;
}