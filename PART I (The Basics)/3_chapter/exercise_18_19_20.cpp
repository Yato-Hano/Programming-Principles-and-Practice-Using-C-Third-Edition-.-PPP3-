/*
[18] 
Write a program where you first enter a set of name-and-value pairs, such as Joe 17 and Bar-
bara 22. For each pair, add the name to a vector called names and the number to a vector
called scores (in corresponding positions, so that if names[7]=="Joe" then scores[7]==17).
Terminate input with NoName 0. Check that each name is unique and terminate with an error
message if a name is entered twice. Write out all the (name,score) pairs, one per line.
[19]
Modify the program from the previous exercise so that once you have entered the name-and-
value pairs, you ask for values: In a loop, when you enter a name, the program will output the
corresponding score or name not found.
[20]
Modify the program from the previous exercise so that once you have entered the name-and-
value pairs, you ask for names: In a loop, when you enter a value, the program will output all
the names with that score or score not found.
*/

import PPP;
using namespace std;
bool name_check(vector<string>names, string nm)
{
	for (string s : names)if (nm == s)return true;
	return false;
}



void print_pairs(vector<string>names, vector<int>scores)
{
	for (int i = 0; i < names.size(); ++i)
	{
		cout << names[i] << ' ' << scores[i] << '\n';
	}
}


string get_pair_by_name(vector<string>names, vector<int>scores, string n)
{
	for (int i = 0; i < names.size(); ++i)
	{
		if (names[i] == n)
			return string{ names[i]+" " + to_string(scores[i])};
	}
	return "name not found";
}

string get_pairs_by_score(vector<string>names, vector<int>scores, int n)
{
	string answer;
	for (int i = 0; i < names.size(); ++i)
	{
		if (scores[i] == n)
			answer+= string{ names[i] + " " + to_string(scores[i]) + "\n" };
	}
	if (answer.empty())
		return "score not found";
	return answer;
}
int main()
try {
	vector<string>names;
	vector<int>scores;
	cout << "Enter name and score pairs, terminate input with NoName 0.\n";
	int sc{};
	for (string word; cin >> word>> sc;)
	{
		if (word == "NoName" && sc == 0)
			break;

		if (name_check(names, word))
		{
			throw string{ word + " name was intered twice" };
		}
		else {
			names.push_back(word);
			scores.push_back(sc);
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
			cout << get_pair_by_name(names, scores, word) << '\n';
		}
		break;
	case 's':

		cout << "Type a score you have entered before: ";

		while (cin >> sc)
		{
			cout << get_pairs_by_score(names, scores, sc) << '\n';
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