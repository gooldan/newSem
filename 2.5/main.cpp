#include <iostream>
#include <vector>

using namespace std;


void qsort(vector<pair<int, pair<int, int>>> &a, int l, int r)
{
	int x = a[l + (r - l) / 2].first;
	int i = l;
	int j = r;
	while (i <= j)
	{
		while (a[i].first < x) i++;
		while (a[j].first > x) j--;
		if (i <= j)
		{
			swap(a[i], a[j]);
			i++;
			j--;
		}
	}
	if (i < r)  qsort(a, i, r);
	if (l < j)  qsort(a, l, j);
}

int main()
{
	int n, m;
	int price, begin, end;
	cin >> n >> m;
	vector<int> treeNum(n+1); 
	vector < pair < int, pair<int, int> > > mas; // вес - вершина 1 - вершина 2

	for (int i = 0; i < n; ++i)
	{
		treeNum[i] = i;
	}
	for (int i = 0; i < m; ++i)
	{
		cin >> begin >> end >> price;
		mas.push_back(make_pair(price, make_pair(begin, end)));
	}
	qsort(mas, 0, n - 1);

	int cost = 0;
	for (int i = 0; i < m; ++i)
	{
		int begin = mas[i].second.first;
		int end = mas[i].second.second;
		int price = mas[i].first;
		if (treeNum[begin] != treeNum[end])
		{
			cost += price;
			int oldNum = treeNum[end];
			int newNum = treeNum[begin];
			for (int j = 0; j < n+1; ++j)
			if (treeNum[j] == oldNum)
				treeNum[j] = newNum;
		}
	}

	cout << cost << endl;
	cin >> n;
}