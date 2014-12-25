#pragma once
#include <iostream>
#include <vector>
namespace kunh{

	std::vector<int> used;
	std::vector< std::vector<int> > mat;
	std::vector<int> match;
	__declspec(dllexport)	int max(int a, int b);
	__declspec(dllexport)	int min(int a, int b);
	__declspec(dllexport)	bool dfs(int v);
	__declspec(dllexport)	std::vector<int> kunh(std::vector< std::vector <int> > &mat, int m, int n, bool spisoksmejnihvershin=1);

}
