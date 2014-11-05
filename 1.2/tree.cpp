#include "tree.h"
#include <iostream>
#include <queue>
int Max(int a, int b)
{
	return a > b ? a : b;
}
int Tree::getHeight(Node *p)
{
	if (p == nullptr) return -1;
	return p->height;
}
Tree::Node* Tree::find(int x)
{
	if (root == nullptr)
		return nullptr;
	bool f = true;
	Node *t = root;
	while (t->data != x)
	{
		if (t->data < x)
			t = t->Right;
		else
			t = t->Left;
		if (t == nullptr)
		{
			f = false;
			break;
		}
	}
	return f ? t : nullptr;
}

Tree::Node* Tree::minimum(Node *p)
{
	if (p == nullptr) return p;
	else
	{
		bool f = false;
		Node *t = p;
		while (t->Left != nullptr)
			t = t->Left;
		return t;
	}
}
Tree::Node* Tree::maximum(Node *p)
{
	if (p == nullptr) return p;
	else
	{
		bool f = false;
		Node *t = p;
		while (t->Right != nullptr)
			t = t->Right;
		return t;
	}
}
Tree::Tree()
{
	root = 0;
}
Tree::Node* Tree::successor(const Node *p)
{
	if (maximum(root) == p)
		return nullptr;
	if (p->Right != nullptr)
		return minimum(p->Right);
	while (p->Parent->Left != p)
		p = p->Parent;

	return p->Parent;
}
Tree::Node* Tree::predecessor(const Node *p)
{
	if (minimum(root) == p)
		return nullptr;
	if (p->Left != nullptr)
		return maximum(p->Left);
	while (p->Parent->Right != p)
		p = p->Parent;

	return p->Parent;
}
void Tree::inOrderTraversal()
{
	iOT(root);
	std::cout << std::endl;
}
void Tree::preOrderTraversal()
{
	preOT(root);
	std::cout << std::endl;
}
void Tree::postOrderTraversal()
{
	postOT(root);
	std::cout << std::endl;
}
void Tree::iOT(Node *p)
{
	if (p != nullptr)
	{
		iOT(p->Left);
		std::cout<<(char)p->data<<" ";
		iOT(p->Right);
	}
}
void Tree::preOT(Node *p)
{
	if (p != nullptr)
	{
		std::cout << p->data << " ";
		preOT(p->Left);
		preOT(p->Right);
	}
}void Tree::postOT(Node *p)
{
	if (p != nullptr)
	{
		postOT(p->Left);
		postOT(p->Right);
		std::cout << p->data << " ";
	}
}
void Tree::breadthFirstTraversal()
{
	if (!root)
		return;
	std::queue<Node*> a;
	a.push(root);
	while (!a.empty()) 
	{
		Node *curr = a.front();
		a.pop();
		std::cout<<curr->data<<" ";
		if (curr->Left)
			a.push(curr->Left);
		if (curr->Right)
			a.push(curr->Right);
	}
	std::cout << std::endl;

}
Tree::Node *Tree::updateHeight(Tree::Node *node)
{
	if (node)
		node->height = Max(getHeight(node->Left), getHeight(node->Right)) + 1;
	return node;
}