/*
[16]
Write a program that finds the min, max, and mode of a sequence of strings.
*/
//the task is the same as 15 ex.

import PPP;
using namespace std;

int main()
try {
	cout << "Type words. Terminate sequence with enter then Ctrl+Z followed by enter.\n";
	vector<string>words;

	for (string w{}; cin >> w;)
	{
		words.push_back(w);
	}

	if (words.empty())throw string{ "No words" };

	sort(words.begin(), words.end());

	string wrd = words[0]; // word
	string mode = wrd;
	unsigned count = 0;
	unsigned countMode = 0;
	vector<pair<string, unsigned>>number_counters;
	vector<string>several_modes;
	for (unsigned i = 1; i < words.size(); i++)
	{
		if (words[i] == wrd)
		{ // count occurrences of the current number
			++count;
		}
		else
		{ // now this is a different number
			number_counters.push_back({ wrd,count });
			if (count > countMode)
			{
				countMode = count; // mode is the biggest ocurrences
				mode = wrd;
			}
			count = 0; // reset count for the new number
			wrd = words[i];
		}
	}
	number_counters.push_back({ wrd,count }); // last in the sequence

	// in case the mode the last in the sequence
	if (count > countMode)
	{
		countMode = count;
		mode = wrd;
	}

	// now we look for modes with max counters
	for (const pair<string, unsigned>& n : number_counters)
	{
		if (countMode == n.second)
			several_modes.push_back(n.first);
	}

	//print
	cout << "Min is " << words[0] << ". Max is " << words[words.size() - 1]<<".\n";
	if (several_modes.size() == 1)
		cout << "Mode is " << mode << ".\n";
	else
	{
		cout << "Modes are ";
		for (const string& n : several_modes)
			cout << n << ",";
		cout << '\b' << ".\n";
	}

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