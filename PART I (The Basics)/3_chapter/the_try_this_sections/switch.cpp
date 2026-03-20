//try this. from  chapter 3

import PPP;
using namespace std;

int main()
try {
	constexpr double yen_per_dollar = 154.04;
	constexpr double kroner_per_dollar = 10.09;
	constexpr double pound_per_dollar = 0.76;
	const string dollar_literal = " dollars.\n";
	double value{ 0 };
	char unit{ ' ' };
	cout << "Please enter a value followed by a unit (y, k or p):\n";
	cin >> value >> unit;


	switch (unit)
	{
	case'y':
		cout << value << " yen == " << value / yen_per_dollar << dollar_literal;
		break;
	case'k':
		cout << value << "kroner == " << value / kroner_per_dollar << dollar_literal;
		break;
	case'p':
		cout << value << " pound == " << value / pound_per_dollar << dollar_literal;
		break;
	default:
		cout << "Sorry, I don't know a unit called '" << unit << "'\n";
		break;
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