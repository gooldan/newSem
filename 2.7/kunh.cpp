#include "kunh.h"

int kunh::max(int a, int b)
{
	return a < b ? b : a;
}

int kunh::min(int a, int b)
{
	return a > b ? b : a;
}

bool kunh::dfs(int v)
{
	if (used[v] == 1)
		return false;
	used[v] = 1;
	for (int i = 0; i < mat[v].size(); ++i)
	{
		int to = mat[v][i];
		if (match[to] == -1 || dfs(match[to]))
		{
			match[to] = v;
			return true;
		}
	}
	return false;

}
std::vector<int> kunh::kunh(std::vector< std::vector <int> > &_mat, int m, int n, bool spisoksmejnihvershin)
{

	mat = _mat;
	match.assign(min(m, n),-1);
	if (spisoksmejnihvershin == false)
	{
		std::vector< std::vector <int> > t;
		std::vector<int> ps;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (mat[i][j] == 1)
					ps.push_back(j);
			}
			t.push_back(ps);
			ps.clear();
		}
		mat = t;
	}
	for (int i = 0; i < m; ++i)
	{
		used.assign(max(m, n), 0);
		dfs(i);

	}

	return match;
}
