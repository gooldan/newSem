#include <iostream>
#include "my_1_string.h"
#include "BSTree.h"
#include <vector>
#include <set>

using namespace std;
String ss;
int huffman = 0;
int min(int a, int b)
{
	return a < b ? a : b;
}
void pot(Tree::Node *p)
{
	if (p == nullptr)
		return;
	if (p->Left != nullptr)
		ss.add('1');
	pot(p->Left);
	if (p->Right == nullptr && p->Left == nullptr)
	{
		cout << p->c << " " << ss << endl;
		huffman += ss.length()*p->data;
	}
	if (p->Right != nullptr)
		ss.add('0');
	pot(p->Right);
	ss.pop_back();
}

int main()
{
	String s;
	cin >> s;
	int n, length;
	length = s.length();
	multiset<char> charset;
	vector<pair<char, int>> vec;
	for (int i = 0; i < length; ++i)
	{
		int count = charset.count(s[i]);
		if (count == 0)
		{
			pair<char, int> t(s[i], 1);
			vec.push_back(t);
		}
		else
		{
			int t = 0;
			while (vec[t].second != count)
				t++;
			int j = t;
			while (vec[j].first != s[i])
				j++;
			swap(vec[t], vec[j]);
			vec[t].second += 1;
		}
		charset.insert(s[i]);
	}
	vector<BSTree*> mas;
	for (int i = 0; i < vec.size(); ++i)
	{
		BSTree *t = new BSTree(vec[i].second, vec[i].first);
		mas.push_back(t);
	}
	int size = vec.size();
	while (size>1)
	{
		int min1 = size - 1;
		int min2 = size - 2;
		for (int i = size - 2; i >= 0; --i)
		if (mas[i]->root->data < mas[min1]->root->data)
		{
			min2 = min1;
			min1 = i;
		}
		else
		if (mas[i]->root->data < mas[min2]->root->data)
		{
			min2 = i;
		}
		mas.insert(mas.begin() + min(min1, min2), merge(mas[min1], mas[min2]));
		mas.erase(mas.begin() + min(min1, min2) + 1);
		mas.erase(mas.begin() + max(min1, min2));
		size--;
	}
	pot(mas[0]->root);
	cout << "COMP COEFF IS:   " << length*(floor(log2(vec.size()) - 1e-3)+1)/huffman << endl;
	delete *mas.begin();
	system("pause");	
}