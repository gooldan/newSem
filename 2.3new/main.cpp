#include <iostream>
#include <vector>
using namespace std;
bool used[1000];
int part[1000];
vector <int > g[100];

bool dfs(int s, int pr)
{
	if (!used[s])
	{
		used[s] = 1;
		part[s] = !part[pr];
	}
	else
	{
		if (part[s] == part[pr])
			return false;
		return true;
	}
	for (int i = 0; i < g[s].size(); i++)
	{
		int to = g[s][i];
		if (!dfs(to, s))
			return false;
	}
	return true;
}

int main()
{
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++)
	{
		int t, t1;
		cin >> t >> t1;
		g[t - 1].push_back(t1 - 1);
		g[t1 - 1].push_back(t - 1);
	}

	for (int i = 0; i < n; i++)
	{
		if (!used[i])
		if (!dfs(i, i))
		{
			cout << "NO";
			return 0;
		}
	}

	cout << "YES" << endl;

	for (int i = 0; i < n; i++)
	if (part[i])
		cout << i + 1 << " ";
	return 0;
}