#include <iostream>
#include <string>
using namespace std;
enum states{
	start,
	a,
	stop
};
int main()
{
	string s;
	cin >> s;
	states state = start;
	for (int i = 0; i < s.length(); ++i)
	{
		char c = s[i];
		switch (state)
		{
		case start:
			if (c == 'a')
			{
				state = a;
			}
			break;
		case a:
			if (c == 'a')
				state = a;
			else if (c == 'b')
				state = stop;
			else
				state = start;
			break;
		}
		if (state == stop)
		{
			cout << "YES";
			system("pause");
			return;
		}
	}
	cout << "NO";
	cin >> s;
}