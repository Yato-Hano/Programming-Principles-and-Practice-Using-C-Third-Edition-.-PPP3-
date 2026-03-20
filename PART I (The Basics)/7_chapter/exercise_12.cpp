/*
[12]
Improve print_until_s() from §7.4.2. Test it. What makes a good set of test cases? Give rea-
sons. Then, write a print_until_ss() that prints until it sees a second occurrence of its quit
argument.
*/

import PPP;
using namespace std;

void print_until_s(const vector<string>& v, const string& quit)
{
	for (const string& s : v) {
		if (s == quit)
			return;
		cout << s << '\n';
	}
}
void print_until_ss(const vector<string>& v, const string& quit)
//print untill second time quit word
{
	bool seen{ false };
	for (const string& s : v) {
		if (s == quit && seen) return;
		if (s == quit) seen = true;
		cout << s << '\n';
	}
}
int main()
try {
	string quit_word{ "q" };
	cout << "Enter words: ";
	vector<string> words;
	for (string s; cin >> s;) words.push_back(s);

	print_until_ss(words, quit_word);

	system("pause");
	return 0;
}
catch (const string& surprise)
{
	cerr << surprise << '.' << endl;
	system("pause");
	return 1;
}
catch (const exception& surprise)
{
	cerr << "Exception: " << surprise.what() << '.' << endl;
	system("pause");
	return 2;
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
	return 3;
}