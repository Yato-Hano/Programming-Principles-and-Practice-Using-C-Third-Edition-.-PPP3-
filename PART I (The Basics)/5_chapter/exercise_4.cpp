/*
[4]
Define a class Name_value that holds a string and a value. Rework exercise 20 in Chapter 3
to use a vector<Name_value> instead of two vectors.

*/
import PPP;
using namespace std;

class Name_value
{
public:
	Name_value(string n, int val)
		:name{ n }, value{ val } {
	}

	string name;
	int value{0};
};



bool name_check(vector<Name_value>names, Name_value nm)
{
	for (Name_value s : names)if (nm.name == s.name)return true;
	return false;
}



void print_pairs(vector<Name_value>names)
{
	for (int i = 0; i < names.size(); ++i)
	{
		cout << names[i].name << ' ' << names[i].value << '\n';
	}
}


string get_pair_by_name(vector<Name_value>names, Name_value n)
{
	for (int i = 0; i < names.size(); ++i)
	{
		if (names[i].name == n.name)
			return string{ names[i].name+' '+to_string(names[i].value)};
	}
	return string{ "name not found" };
}

string get_pairs_by_score(vector<Name_value>names, Name_value n)
{
	string answer;
	for (int i = 0; i < names.size(); ++i)
	{
		if (names[i].value == n.value)
			answer += string{ names[i].name + " " + to_string(names[i].value) + "\n" };
	}
	if (answer.empty())
		return "score not found";
	return answer;
}
int main()
try {
	vector<Name_value>names;
	cout << "Enter name and score pairs, terminate input with NoName 0.\n";
	int sc{};
	for (string word; cin >> word >> sc;)
	{
		if (word == "NoName" && sc == 0)
			break;

		if (name_check(names, { word,0 }))
		{
			throw string{ word + " name was intered twice" };
		}
		else {
			names.push_back({ word,sc });
		}
	}
	cout << "n for finding by name, s for finding by score: ";

	char choice{};
	cin >> choice;
	switch (choice)
	{
	case 'n':

		cout << "Type a name you have entered before: ";

		for (string word; cin >> word;)
		{
			cout << get_pair_by_name(names, { word,0 }) << '\n';
		}
		break;
	case 's':

		cout << "Type a score you have entered before: ";

		while (cin >> sc)
		{
			cout << get_pairs_by_score(names, { "",sc }) << '\n';
		}
		break;
	default:
		cerr << choice << " is not the choice i know.\n";
		break;
	}


	//print_pairs(names, scores);

	system("pause");
	return 0;
}
catch (const string& surprise)
{
	cerr << surprise << '.' << endl;
	system("pause");
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
}