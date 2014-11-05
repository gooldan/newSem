#pragma once
#include "tree.h"
class BSTree :public Tree{
public:

	BSTree();
	BSTree(int n, char c);
	void insert(int x);
	void remove(Node *p);
	friend BSTree *merge(BSTree *&a, BSTree *&b);
	~BSTree();
private:
	void postOD(Node *p);
	BSTree &operator=(const BSTree &b) {}
	BSTree(const BSTree &b) {}

};
BSTree *merge(BSTree *&a, BSTree *&b);