//2 chapter. exercise 9
/*
Write a program that converts spelled-out numbers such as ‘‘zero’’ and ‘‘two’’ into digits,
such as 0 and 2. When the user inputs a number, the program should print out the corre-
sponding digit. Do it for the values 0, 1, 2, 3, and 4 and write out not a number I know if the
user enters something that doesn’t correspond, such as stupid computer!.
*/
import PPP;
using namespace std;
int main()
try {
	cout << "Enter a word with a number meaning.\n";
	vector<pair<string, int>>word_pairs{ {"zero",0},{"one",1} ,{"two",2} ,{"three",3},{"four",4} }; //we could do this without pairs, but here we go
	string word;
	while (cin >> word)
	{
		for (char& letter : word) letter = tolower(letter);

		for (const pair<string, int>& combination : word_pairs)
			if (combination.first == word) {
				cout << combination.second << '\n';
				break;
			}
			else
				if (combination.second == 4) 
					cout << "Not a number I know.\n";
	}

	system("pause");
	return 0;

}
catch (const string& surprise)
{
	cerr << surprise << endl;
	system("pause");

}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");

}