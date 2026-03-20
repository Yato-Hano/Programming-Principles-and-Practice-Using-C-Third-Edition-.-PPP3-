/*
   Chapter 3. Drill.
*/

import PPP;
using namespace std;
void skip_spaces()
{
	char letter{};
	while(cin.get(letter) && letter == ' ')
	{};
	cin.putback(letter); //probably '\n'
}

void turn_string_tolower(string& word)
{

	for (char& letter : word)
		letter = tolower(letter);

}

double get_rate(const double number, const string unit)
{
	vector<pair<string,double>> cm_per_unit{ {"cm",1},{"m",100},{"in",2.54},{"ft",30.48} };
	for (const pair<string, double >& wd : cm_per_unit)
	{
		if (unit == wd.first) return number * wd.second;
	}
	throw string{ unit+" is not a unit i know." };
}

int main()
try {
	cout << "Type numbers with a unit cm, m, in or ft. Terminate sequence with the '|' character.\n";
	double number{};
	string unit;
	double smallest{ 999999 }, largest{ -999999 };
	int quantity{0};
	double sum{ 0 }; //in m
	double m_per_cm{ 0.01 };
	vector<double>lengths;//in m
	while (cin >> number)
	{
		skip_spaces();
		char letter{};
		if (cin.get(letter) &&letter=='\n') throw string{ "Type a unit please." };
		cin.putback(letter); //probably a unit letter

		cin >> unit;
		turn_string_tolower(unit);

		number = get_rate(number, unit); //to cm
		number *= m_per_cm; //to m
		lengths.push_back(number);

		if (number <= smallest)
		{
			smallest = number;
		}
		if (largest <= number)
		{
			largest = number;
		}
		sum += number;
		++quantity;

		//double difference = largest - smallest;
		//cout << "difference is: " << difference << ".\n";
		
		//if (a == b)cout << "numbers are equal.\n";
	//	else if (difference < 0.01) cout << "the numbers are almost equal.\n";
	}

	cout << smallest<< "m the smallest so far.\n"
		<< largest << "m the largest so far.\n"
		<< "quantity of numbers is " << quantity << ".\n"
		<<"sum is "<<sum<<"m.\n";

	sort(lengths.begin(), lengths.end());
	cout << "all sorted lengths in m:\n";
	for (const double& d : lengths)
		cout << d << '\n';

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