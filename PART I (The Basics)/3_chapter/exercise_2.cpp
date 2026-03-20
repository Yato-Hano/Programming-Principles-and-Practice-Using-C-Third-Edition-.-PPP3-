/*
[2]
Write a program that reads a string from input and then, for each character read, prints out
the character and its integer value on a line.
*/

import PPP;
using namespace std;

int main()
try {

	for (string word; cin >> word;)
	{
		for (const char& letter : word)
			cout << letter << ' ' << int(letter) << '\n';
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