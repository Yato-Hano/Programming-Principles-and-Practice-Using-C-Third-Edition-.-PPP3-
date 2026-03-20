/*
[10]
Write a function maxv() that returns the largest element of a vector argument.
[11] 
Write a function that finds the smallest and the largest element of a vector argument and also
computes the mean and the median. Do not use global variables. Either return a struct con-
taining the results or pass them back through reference arguments. Which of the two ways of
returning several result values do you prefer and why?
*/

import PPP;
using namespace std;
auto maxv(const auto& numbers)
{
	if (numbers.size() == 0) throw string{ "maxv: No data" };
	auto max{ numbers[0]};
	for (const auto& d : numbers)
	{
		if (max < d)max = d;
	}
	return max;

}
class Specification
{
public:
	Specification(vector<double>);
	double min{ 0 };
	double max{ 0 };
	double mean{ 0 };//average
	double median{ 0 };// number in the middle

};
Specification::Specification(vector<double> values) // not passing-by-referenñe because we sort
{
	if (values.size() == 0) throw string{ "No data" };

	double sum = 0;
	for (const double& x : values)
		sum += x;
	//cout << "Average temperature: " << sum / values.size() << '\n';
	mean = sum / values.size();

	sort(values.begin(), values.end());

	max = values[values.size() - 1];
	min = values[0];

	size_t index{ values.size() / 2 };
	//cout << "index: " << index << '\n';
	if (values.size() % 2)
	{//odd size
		median = values[index]; //exactly in the middle
	}
	else { //even size. 
		median = values[index];
		median += values[index - 1];
		median /= 2.0; //mean of 2 numbers in the middle
	}
//	cout << "Median temperature: " << median << '\n';
}
int main()
try {
	cout << "Type values: ";
	vector<double> temps;// temperatures
	for (double temp; cin >> temp; )
		temps.push_back(temp);

	cout << "maxv: " << maxv(temps) << '\n';

	Specification s{ temps };
	cout << "Min: " << s.min << '\n'
		<< "Max: " << s.max << '\n'
		<< "Mean: " << s.mean << '\n'
		<< "Median: " << s.median << '\n';

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