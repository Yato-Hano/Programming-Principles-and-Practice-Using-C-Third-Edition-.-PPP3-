/*
[13]
Write a function that takes a vector<string> argument and returns a vector<int> containing the
number of characters in each string. Also find the longest and the shortest string and the lexi-
cographically first and last string. How many separate functions would you use for these
tasks? Why?
*/

import PPP;
using namespace std;

vector<int> numb_of_chars(const vector<string>& words)
{
	vector<int> char_numbs;
	for (const string&s:words )
	{
		char_numbs.push_back(s.size());
	}
	return char_numbs;
}
string longest_(const vector<string>& words)
{
	if (words.empty()) return {  };

	int longest_size{-1 };
	string longest_word;

	for (const string& s : words)
	{
		if (longest_size < int(s.size())) {
			longest_word = s;
			longest_size = s.size();
		}
	}
	return longest_word;
}

string shortest_(const vector<string>& words)
{
	if (words.empty()) return {  };

	int shortest_size= words[0].size() ;
	string shortest_word{ words[0] };

	for (const string& s : words)
	{
		if (shortest_size > s.size()) {
			shortest_word = s;
			shortest_size = s.size();
		}
	}
	return shortest_word;
}
pair<string, string> first_last(vector<string> words)
{
	if (words.empty()) return {  };
	sort(words.begin(), words.end());

	return { words[0],words[words.size() - 1] };
}

void print_(const string& label ,const auto& numbers)
{
	cout << label << '\n';
	for (size_t i = 0; i < numbers.size(); i++)
	{
		cout << numbers[i] << '\n';
	}
}


int main()
try {
	vector<string> words{"asda", "cta","dcsxa"};

	pair<string, string> fl = first_last(words);
	cout << "Lexicographically first: " << fl.first << '\n'
		<< "Lexicographically last: " << fl.second << '\n';

	cout << "Shortest word: " << shortest_(words) << '\n'
		<< "Longest word: " << longest_(words) << '\n';

	vector<int> char_numbs = numb_of_chars(words);
	print_(string{ "Number of characters:" }, char_numbs);

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