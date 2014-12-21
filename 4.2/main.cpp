#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
const string alphabet = "abcdefghijklmnopqrstuvwxyz0123456789./<=*; ";
const string separators = " ;/<=\n";
const string letters = "abcdefghijklmnopqrstuvwxyz";
const string numbers = "0123456789";
enum states{
	number,
	fnumber,
	iff,
	floatt,
	relation,
	assignment,
	id,
	num,
	separator,
	commentary,
	mscommentary,
	sscommentary,
	error,
	stop,
	start
};
states getState(states state, char symb, char lastsymb)
{
	switch (state)
	{
	case start:
		if (symb == 'f')
			return floatt;
		if (symb == 'i')
			return iff;
		if (symb >= 'a' && symb <= 'z')
			return id;
		if (symb >= '0' && symb <= '9')
			return number;
		if (symb == '<')
			return relation;
		if (symb == '=')
			return assignment;
		if (symb == '/')
			return commentary;
		if (symb == ';' || symb == ' ' || symb == '\n')
			return separator;
		return error;

	case floatt:
		if (((symb == 'l') && (lastsymb == 'f')) || ((symb == 'o') && (lastsymb == 'l')) || ((symb == 'a') && (lastsymb == 'o')) || ((symb == 't') && (lastsymb == 'a')))
			return floatt;
		if (separators.find(symb) != -1)
			return stop;
		if ((symb >= 'a' && symb <= 'z') || (symb >= '0' && symb <= '9'))
			return id;
		return error;
	case iff:
		if ((symb == 'f') && (lastsymb == 'i'))
			return iff;
		if (separators.find(symb) != -1)
			return stop;
		if ((symb >= 'a' && symb <= 'z') || (symb >= '0' && symb <= '9'))
			return id;
		return error;
	case id:
		if (separators.find(symb) != -1)
			return stop;
		if ((symb >= 'a' && symb <= 'z') || (symb >= '0' && symb <= '9'))
			return id;
		return error;
	case number:
		if (symb == '.')
			return fnumber;
		if (separators.find(symb) != -1)
			return stop;
		if (symb >= '0' && symb <= '9')
			return number;
		return error;
	case fnumber:
		if (separators.find(symb) != -1)
		if (lastsymb != '.')
			return stop;
		if (symb >= '0' && symb <= '9')
			return fnumber;
		return error;
	case relation:
		if (symb == '=')
			return relation;
		return stop;
	case commentary:
		if (symb == '/')
			return sscommentary;
		if (symb == '*')
			return mscommentary;
		return error;
	}

}
vector<pair<string, string>> analyzer(string str)
{
	vector<pair<string, string>> res;
	if (str.size() == 0)
		return res;
	res.push_back(make_pair("nice", "nice"));
	states state = start;
	states curstate = start;
	string lexem;
	int i = 0;
	int line = 1;
	char lasts = '\0';
	char symb = str[0];
	while (state != stop && state != error && i < str.size())
	{
		lasts = symb;
		symb = str[i];
		switch (state)
		{
		case start:
			lexem.clear();
			state = getState(state, symb, '0');
			switch (state)
			{
			case separator:
				state = stop;
				if (symb == ';')
					res.push_back(make_pair(";", "separator"));
				else
				if (symb == '\n')
					line++;
				break;
			case assignment:
				res.push_back(make_pair("=", "assignment"));
				state = stop;
				break;
			}
			break;
		case floatt:
			state = getState(state, symb, lasts);
			switch (state)
			{
			case stop:
				if (lasts == 't')
					res.push_back(make_pair("float", "type"));
				else
					res.push_back(make_pair(lexem, "id"));
				i--;
				break;
			}
			break;
		case iff:
			state = getState(state, symb, lasts);
			switch (state)
			{
			case stop:
				if (lasts == 'f')
					res.push_back(make_pair("if", "if"));
				else
					res.push_back(make_pair(lexem, "id"));
				i--;
				break;
			}
			break;
		case id:
			state = getState(state, symb, lasts);
			switch (state)
			{
			case stop:
				res.push_back(make_pair(lexem, "id"));
				i--;
				break;
			}
			break;
		case number:
			state = getState(state, symb, lasts);
			switch (state)
			{
			case stop:
				res.push_back(make_pair(lexem, "num"));
				i--;
				break;
			}
			break;
		case fnumber:
			state = getState(state, symb, lasts);
			switch (state)
			{
			case stop:
				res.push_back(make_pair(lexem, "num"));
				i--;
				break;
			}
			break;
		case relation:
			state = getState(state, symb, lasts);
			switch (state)
			{
			case relation:
				state = stop;
				res.push_back(make_pair("<=", "relation"));
				break;
			case stop:
				res.push_back(make_pair("<", "relation"));
				break;
			}
			break;

		case commentary:
			state = getState(state, symb, lasts);
			switch (state)
			{
			case mscommentary:
				while (state != stop && state != error)
				{
					symb = str[++i];
					while (symb != '*' && i < str.size())
					{
						if (symb == '\n')
							line++;
						symb = str[++i];

					}
					if (i < str.size() - 1)
					if (str[++i] == '/')
					{
						state = stop;
					}
					else;
					else state = error;
				}
				break;
			case sscommentary:
				while (state != stop && state != error)
				{
					symb = str[++i];
					while (symb != '\n' && i < str.size())
					{
						symb = str[++i];

					}
					if (i == str.size())
						state = error;
					state = stop;
					line++;
				}
				break;
			}
			break;
		}
		lexem.push_back(symb);
		if (state == stop)
		{
			state = start;
			lexem.clear();
		}
		if (state == error)
		{
			res[0] = make_pair(error, to_string(line));
			break;
		}
		i++;
	}
	return res;
}
int main()
{
	ifstream in("in.txt");
	string s;
	char c = '1';
	c = in.get();
	while (in.good())
	{
		s += c;
		c = in.get();
	}
	vector<pair<string, string>> res = analyzer(s);
	if (res[0].first == "nice")
	for (int i = 1; i < res.size(); ++i)
		cout << res[i].first << " " << res[i].second<<endl;
	else
		cout << "An error occurred in line number " << res[0].second << ".";
	cin >> s;
}