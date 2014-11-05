#include "BSTree.h"
#include <iostream>
BSTree::~BSTree()
{
	postOD(root);
}
BSTree::BSTree()
{
	root = nullptr;
}
BSTree::BSTree(int n,char c)
{
	Node *roo = new Node();
	roo->data = n;
	roo->height = 0;
	roo->Left = nullptr;
	roo->Right = nullptr;
	roo->Parent = nullptr;
	roo->c = c;
	root = roo;
}
void BSTree::postOD(Node *p)
{
	if (p != nullptr)
	{
		postOD(p->Left);
		postOD(p->Right);
		delete p;
	}
}
void BSTree::insert(int x)
{
	if (find(x) != nullptr)
		return;
	Node *p = new Node;
	p->Left = nullptr;
	p->Right = nullptr;
	p->data = x;
	p->height = 0;
	if (!root)
	{
		p->height = 0;
		p->Parent = nullptr;
		root = p;
		return;
	}
	Node *t = root;
	Node *pt = nullptr;
	while (t)
	{
		pt = t;
		t = x > t->data ? t->Right : t->Left;
	}
	if (x > pt->data)
		pt->Right = p;
	else
		pt->Left = p;
	p->Parent = pt;
	while (p)
		p = updateHeight(p->Parent);
}
void BSTree::remove(Node *p)
{
	if (!p)
		return;
	Node *temp = nullptr;
	Node *tempChild = nullptr;
	temp = p->Right ? minimum(p->Right) : p;
	tempChild = temp->Right ? temp->Right : temp->Left;
	if (temp == root)
		root = NULL;
	if (tempChild)
	{
		if (!temp->Parent)
			root = tempChild;
		tempChild->Parent = temp->Parent;
	}
	if (temp->Parent)
	{
		if (temp->Parent->Left == temp)
			temp->Parent->Left = tempChild;
		else
			temp->Parent->Right = tempChild;
	}
	p->data = temp->data;
	temp->Left = nullptr;
	temp->Right =nullptr;
	while (temp)
		temp = updateHeight(temp)->Parent;
	delete temp;
	return;
}
BSTree *merge(BSTree *&a, BSTree *&b)
{
	typedef Tree::Node Node;
	BSTree *res=new BSTree;
	Node *roo = new Node();
	res->root = roo;
	res->root->Left = a->root;
	res->root->Right = b->root;
	res->root->data = a->root->data + b->root->data;
	res->root->height = 0;
	res->root->Parent = nullptr;
	res->root->c = '\0';
	return res;
}