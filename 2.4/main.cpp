#include <iostream>
#include <vector>

using namespace std;

struct edge
{
	edge(int a, int b) :target(a), k(b){};
	int target;
	int k;
};

const int MAXN = 100;
vector<edge> g[MAXN];
bool used[MAXN];
int timer, tin[MAXN], fup[MAXN];
vector<pair<int, int>> answer;
int min(int a, int b)
{
	return a < b ? a : b;
}

void dfs(int v, int p = -1)
{
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (size_t i = 0; i<g[v].size(); ++i)
	{
		int to = g[v][i].target;
		if (to == p)  continue;
		if (used[to])
			fup[v] = min(fup[v], tin[to]);
		else
		{
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] > tin[v])
			if (g[v][i].k == 1)
				answer.push_back(make_pair(v, to));
		}
	}
}

void find_bridges()
{

}

int main()
{
	int n, m, t;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		m = 0;
		cin >> m;
		for (int j = 0; j < m; ++j)
		{
			cin >> t;
			for (int p = 0; p < g[i].size(); ++p)
			if (g[i][p].target == t)
			{
				g[i][p].k++;
				continue;
			}
			g[i].push_back(edge(t, 1));
		}
	}
	timer = 0;
	for (int i = 0; i < n; ++i)
		used[i] = false;
	for (int i = 0; i < n; ++i)
	if (!used[i])
		dfs(i);
	cout << answer.size() << endl;
	for (int i = 0; i < answer.size(); ++i)
		cout << answer[i].first << " " << answer[i].second<<endl;

	cin >> n;
}