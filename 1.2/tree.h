#pragma once

class Tree{
public:
	struct Node
	{
		Node *Left, *Right,*Parent;
		int data,height;
		char c;
	};
	virtual void insert(int x) = 0;
	virtual void remove(Node *p) = 0;
	Tree();
	int getHeight(Node *p);
	Node* find(int x);
	Node* minimum(Node *p);
	Node* maximum(Node *p); 
	Node* successor(const Node *p);
	Node* predecessor(const Node *p);
	Node* getRoot()
	{
		return root;
	}
	void inOrderTraversal();
	void preOrderTraversal();
	void postOrderTraversal();
	void breadthFirstTraversal();
	Node* root;
protected:
	Node* updateHeight(Node *node);
private:
	void iOT(Node *p);
	void preOT(Node *p);
	void postOT(Node *p);
};