#include <iostream>
#include <vector>
#include <kunh.h>
using namespace std;

vector<vector<int>> mat;
vector<vector<int>> res;
vector<vector<int>> g;
vector<int> Used, Xt, Yt, _Yt, X, Y, match, revMatch;
bool isPerfect(vector<int> match)
{
	for (int i = 0; i < match.size(); ++i)
	{
		if (match[i] == -1)
			return false;
	}
	return true;
}
/*
vector<int> newYEdges(vector<int> match, vector<int> revMatch, vector<int> Used, vector<vector<int>> g, int i)
{
	vector<int> res;
	for (int j = 0; j < g[i].size(); ++j)
	{
		if (g[i][j] != revMatch[i] && Used[g.size() + g[i][j]] == 0)
			res.push_back( g[i][j]);
	}
	return res;
}
vector<int> newXEdges(vector<int> match, vector<int> revMatch, vector<int> Used, vector<vector<int>> g, vector<int> mas)
{
	vector<int> res;
	for (int i = 0; i < mas.size();++i)
    if (match[mas[i]] != -1 && Used[g.size()+mas[i]]!=0)
		res.push_back( match[i]);
	return res;
}
*/

void dfs(int i, int part)
{
	if (part == 0)
	{
		for (int j = 0; j < g[i].size(); ++j)
		{
			if (g[i][j] != revMatch[i] && Used[g.size() + g[i][j]] == 0)
			{
				Yt.push_back(g[i][j]);
				Used[g.size() + g[i][j]] = 1;
				dfs(g[i][j], 1);
			}
		}
	}
	else
	if (part == 1)
	{
		if (match[i] != -1 && Used[match[i]] == 0)
		{
			Xt.push_back(match[i]);
			Used[match[i]] = 1;
			dfs(match[i], 0);
		}
	}
	return;
}
vector<int> reverseMatch(vector<int> match)
{
	vector<int> revM; revM.assign(match.size(), -1);
	for (int i = 0; i < match.size(); ++i)
	if (match[i] != -1)
		revM[match[i]] = i;
	return revM;
}
void main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		vector<int> t(n);
		mat.push_back(t);
		vector<int> tt(0);
		g.push_back(tt);
		for (int j = 0; j < n; ++j)
		{
			cin>>mat[i][j];

		}
	}
	int min;
	res = mat;

	for (int i = 0; i < n; ++i)
	{
		min = mat[i][0];
		for (int j = 0; j < n; ++j)
		if (min>mat[i][j])
			min = mat[i][j];
		if (min>0)
		for (int j = 0; j < n; ++j)
			mat[i][j] -= min;
	}
	for (int i = 0; i < n; ++i)
	{
		min = mat[0][i];
		for (int j = 0; j < n; ++j)
		if (min>mat[j][i])
			min = mat[j][i];
		if (min>0)
		for (int j = 0; j < n; ++j)
			mat[j][i] -= min;
	}
	while (1)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			if (mat[i][j] == 0)
				g[i].push_back(j);
		}
		Used.assign(2 * n, 0);
		match = kunh::kunh(g, n, n);
		revMatch = reverseMatch(match);
		if (isPerfect(match))
		{
			int t = 0;
			for (int i = 0; i < n; ++i)
				t += res[match[i]][i];
			cout << t;
			break;
		}
		for (int i = 0; i < match.size(); ++i)
		{
			if (match[i] == -1)
				Y.push_back(i);
			bool f = false;
			for (int j = 0; j < match.size(); ++j)
			if (match[j] == i)
			{
				f = true;
				break;
			}
			if (f == false)
				X.push_back(i);
		}
		for (int i = 0; i < X.size(); ++i)
		{
			Xt.push_back(X[i]);
			dfs(X[i], 0);
		}
		for (int i = 0; i < n; ++i)
		{
			bool f = true;
			for (int j = 0; j < Yt.size(); ++j)
			if (i == Yt[j])
				f = false;
			if (f)
				_Yt.push_back(i);
		}
		int min = 12031232;
		for (int i = 0; i < Xt.size(); ++i)
		{
			for (int j = 0; j < _Yt.size(); ++j)
			if (mat[Xt[i]][_Yt[j]] < min)
				min = mat[Xt[i]][_Yt[j]];
		}
		for (int i = 0; i < Xt.size(); ++i)
		{
			for (int j = 0; j < n; ++j)
				mat[Xt[i]][j] -= min;
		}
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < Yt.size(); ++j)
				mat[i][Yt[j]] += min;
		}
		X.clear();
		Y.clear();
		Xt.clear();
		Yt.clear();
		_Yt.clear();
		for (int i = 0; i < n; ++i)
			g[i].clear();
	}
	cin >> n;
}