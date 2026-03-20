/*
[14]
Read (day-of-the-week,value) pairs from standard input. For example:
Tuesday 23 Friday 56 Tuesday −3 Thursday 99
Collect all the values for each day of the week in a vector<int>. Write out the values of the
seven day-of-the-week vectors. Print out the sum of the values in each vector. Ignore illegal
days of the week, such as Funday, but accept common synonyms such as Mon and monday.
Write out the number of rejected values.
*/

import PPP;
using namespace std;

constexpr int sun{ 0 }, mon{ 1 }, tue{ 2 }, wed{ 3 }, thu{ 4 }, fri{ 5 }, sat{ 6 };
constexpr int rejected{ -1 };

double get_sum(const vector<int>& numbers)
{
	double sum{ 0 };
	for (int n{ 0 }; n < numbers.size(); ++n)
	{
		//if (ckd_add(&sum, sum, numbers[num])) throw string{"Overflow detected"};
		sum +=numbers[n]; 
	}
	return sum;
}

void to_lower(string& word)
{
	for (char& letter : word)
	{
		letter = tolower(letter);
	}
}

int get_day_index(string day)
{
	to_lower(day);
	if ( day == "sun" || day == "sunday")return sun;
	if (day == "mon" || day == "monday")return mon;
	if ( day == "tue" || day == "tuesday")return tue;
	if ( day == "wed" || day == "wednesday")return wed;
	if (day == "thu" || day == "thursday")return thu;
	if ( day == "fri" || day == "friday")return fri;
	if ( day == "sat" || day == "saturday")return sat;

	return rejected;
}

int main()
try {
	string day; int value{ 0 };
	int rejected_sum{ 0 };
	vector<int>sun_values;
	vector<int>mon_values;
	vector<int>tue_values;
	vector<int>wed_values;
	vector<int>thu_values;
	vector<int>fri_values;
	vector<int>sat_values;

	while (true) 
	{
		cout << "Enter day-of-the-week name and value then press enter. End wih Ctrl+Z: ";
		
		if (!(cin >> day >> value)) break;

		switch (get_day_index(day))
		{
		case sun:
			sun_values.push_back(value);
			break;
		case mon:
			mon_values.push_back(value);
			break;
		case tue:
			tue_values.push_back(value);
			break;
		case wed:
			wed_values.push_back(value);
			break;
		case thu:
			thu_values.push_back(value);
			break;
		case fri:
			fri_values.push_back(value);
			break;
		case sat:
			sat_values.push_back(value);
			break;
		case rejected:
			++rejected_sum;
			break;
		default:
			throw string{ "day switch error" };
			break;
		}
	}
	cout << "sunday sum: " << get_sum(sun_values) << '\n'
		<< "monday sum: " << get_sum(mon_values) << '\n'
		<< "tuesday sum: " << get_sum(tue_values) << '\n'
		<< "wednesday sum: " << get_sum(wed_values) << '\n'
		<< "thursday sum: " << get_sum(thu_values) << '\n'
		<< "friday sum: " << get_sum(fri_values) << '\n'
		<< "saturday sum: " << get_sum(sat_values) << '\n'
		<< "values rejected: " << rejected_sum << '\n';

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