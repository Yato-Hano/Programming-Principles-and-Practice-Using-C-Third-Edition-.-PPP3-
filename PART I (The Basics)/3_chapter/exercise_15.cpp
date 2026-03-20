/*
[15] 
In the drill, you wrote a program that, given a series of numbers, found the max and min of
that series. The number that appears the most times in a sequence is called the mode. Create
a program that finds the mode of a set of positive integers.
*/

import PPP;
using namespace std;

int main()
try {
	cout << "Type numbers. Terminate sequence with the '|' character and enter.\n";
	vector<unsigned>numbers;
	
	for (unsigned num{}; cin >> num;)
	{
		numbers.push_back(num);
	}

	if (numbers.empty())throw string{ "No numbers" };

	sort(numbers.begin(), numbers.end());

	unsigned num = numbers[0];
	unsigned mode = num;
	unsigned count = 0;
	unsigned countMode = 0;
	vector<pair<unsigned, unsigned>>number_counters;
	vector<unsigned>several_modes;
	for (unsigned i = 1; i < numbers.size(); i++)
	{
		if (numbers[i] == num)
		{ // count occurrences of the current number
			++count;
		}
		else
		{ // now this is a different number
			number_counters.push_back({ num,count });
			if (count > countMode)
			{
				countMode = count; // mode is the biggest ocurrences
				mode = num;
			}
			count = 0; // reset count for the new number
			num = numbers[i];
		}
	}
	number_counters.push_back({ num,count }); // last in the sequence

	// in case the mode the last in the sequence
	if (count > countMode) 
	{
		countMode = count; 
		mode = num;
	}

	// now we look for modes with max counters
	for (const pair<unsigned, unsigned>& n : number_counters)
	{
		if (countMode == n.second)
			several_modes.push_back(n.first);
	}

	//print
	if(several_modes.size()==1)
		cout << "Mode is "<< mode << ".\n";
	else
	{
		cout << "Modes are ";
			for(unsigned n :several_modes)
				cout << n<< ",";
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