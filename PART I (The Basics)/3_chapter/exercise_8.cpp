/*
[8]
Modify the ‘‘mini calculator’’ from exercise 6 to accept (just) single-digit numbers written as
either digits or spelled out.
*/

import PPP;
using namespace std;



void turn_string_tolower(string& word)
{

	for (char& letter : word)
		letter = char(tolower(letter));

}

int word_to_digit( const string& word)
{
	vector<pair<string, string>>number_literals{ {"zero","0"},
		{"one","1" },{"two","2" },{"three", "3" }, {"four", "4" },
		{"five", "5" },{"six", "6" },{"seven", "7" },
		{"eight", "8" },{"nine", "9" } };

	
	for (int index{ 0 }; index!= number_literals.size(); ++index)
	{
		if (number_literals[index].first == word|| number_literals[index].second==word)
			return index;
	}
	throw string{ word+" is not a word i know" };
}


int main()
try {

	cout << "Type two single-digit numbers either spelled out or literals followed by +, -, * or /. Then hit enter.\n";
	int a{}, b{}, result{};//for calculation
	string val1, val2;//from input
	char oprtr{ ' ' };//operator
	string operation_name;//for output

	while (cin >> val1 >> val2 >> oprtr)
	{
		turn_string_tolower(val1);
		turn_string_tolower(val2);

		a = word_to_digit(val1);
		b = word_to_digit(val2);

		switch (oprtr)
		{
		case'+':
			result = a + b;
			operation_name = "sum";
			break;
		case'-':
			result = a - b;
			operation_name = "difference";
			break;
		case'*':
			result = a * b;
			operation_name = "product";
			break;
		case'/':
			result = a / b;
			operation_name = "quotient";
			break;
		default:
			cout << oprtr << " is not operation i know.\n";
			oprtr = 0;
			break;
		}

		if (oprtr)
			cout << "The " << operation_name << " of " << val1 << " and " << val2 << " is " << result << '\n';
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