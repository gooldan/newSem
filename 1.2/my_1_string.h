#pragma once
#include <iostream>
using namespace std;
const int cMinSize = 4;
class String{
public:
	String(int size = 0, int voulme = cMinSize);
	String(const char *str);
	
	~String();
	String(const String &obj);
	String &operator=(const String &obj);
	int length();
	int capacity();
	bool isEmpty();
	void clear();
	void add(char c);
	char pop_back();
	void insert(int pos, const char *str);
	void erase(int pos, int len = 1);
	String operator + (String a);
	String operator +=(String a);
	char operator[](int ind);
	friend ostream &operator<<(ostream &stream, const String &s);
	friend istream &operator>>(istream &stream, String &s);
	bool operator==(char* s);
	bool operator!=(char* s);
	bool operator==(String s);
	bool operator!=(String s);
private:
	char *p;
	int size;
	int volume;
};
bool operator==(char *s, String s1);
bool operator!=(char *s, String s1);
int max(int a, int b);