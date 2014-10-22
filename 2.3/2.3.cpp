#include <iostream>

using namespace std;
bool table1[101] = { 0 };
bool table2[101] = { 0 };
int alreadySat(int guest){
	if (table1[guest] == true) return 1;
	else
	if (table2[guest] == true) return 2;
	else return 0;
}
int main(){
	
	int n, m;
	bool YES = true;
	cin >> n >> m;
	for (int i = 0; i < m; ++i){
		int guest1, guest2;
		cin >> guest1 >> guest2;
		int num1 = alreadySat(guest1);
		int num2 = alreadySat(guest2);
		if (num1 == 0 && num2 == 0){
			table1[guest1] = true;
			table2[guest2] = true;
		}
		else
		if (num1 != 0 && num2 == 0)
			if (num1 == 1)
				table2[guest2] = true;
			else
				table1[guest2] = true;
		else
		if (num1 == 0 && num2 != 0)
			if (num2 == 1)
					table2[guest1] = true;
			else
				table1[guest1] = true;
		else
		if (num1 == num2){
			cout << "NO";
			YES = false;
		}
	}
	if (YES)
		for (int i = 0; i < 101; ++i){
			if (table1[i] == true)
				cout << i << " ";
		}

	cin >> n;
}