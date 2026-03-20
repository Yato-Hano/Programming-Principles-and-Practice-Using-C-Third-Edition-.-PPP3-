// try this. bleep unwanted words


import PPP;
using namespace std;

void turn_vector_tolower(vector<string>& words)
{
	for (string& wd : words)
	{
		for (char& letter : wd)
			letter = tolower(letter);
	}
}


int main()
try {
	const vector<string> disliked={"broccoli","lol","bad"};
	const string replacement = { "BLEEP" };

	cout << "Type several words followed by Enter. Then Ctrl+Z and Enter: ";

	vector<string> words;
	for (string temp; cin >> temp; )
		words.push_back(temp);

	turn_vector_tolower(words);


	for (string& wd : words)
	{
		for (const string& check_word : disliked)
			if (wd == check_word) wd = replacement;
	}


	for (const string& wd : words)
		cout << wd << ' ';
	cout << "\b.\n";


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