/*
[8]
Write a program that reads and stores a series of integers and then computes the sum of the
first N integers. First ask for N, then read the values into a vector, then calculate the sum of
the first N values. For example:
Please enter the number of values you want to sum: 3
Please enter some integers (press ’|’ to stop): 12 23 13 24 15 |
The sum of the first 3 numbers ( 12 23 13 ) is 48
Handle all inputs. For example, make sure to give an error message if the user asks for a sum
of more numbers than there are in the vector.
[9]
Modify the program from the previous exercise to write out an error if the result cannot be
represented as an int.
[10]
Modify the program from the previous exercise to use double instead of int. Also, make a
vector of doubles containing the N-1 differences between adjacent values and write out that
vector of differences.
*/

import PPP;
using namespace std;
//#include <stdckdint.h>
#include <limits.h>


void print_numbers(const vector<double>& numbers, const double& N)
{
	PPP::expect([&] {return 0 < N; }, "Not positive argument");
	PPP::expect([&] {return N <= numbers.size(); }, "print_numbers() Too few numbers " + to_string(numbers.size()));

	for (int num{}; num< N;++num)
		cout << numbers[num ]<< ' ';
	cout << '\b';
}

int add_overflow_check(int a,int b)
{
	if ((INT_MAX - b) < a) {
		throw string{ "int overflow detected" };
	}
	else  return a + b;
}
double get_sum(const vector<double>& numbers, const double& N)
{
	PPP::expect([&] {return 0 < N; }, "Not positive argument");
	PPP::expect([&] {return N <= numbers.size(); }, "get_sum() Too few numbers " + to_string(numbers.size()));
	double sum{0};
	for (int num{0}; num < N; ++num)
	{
		//if (ckd_add(&sum, sum, numbers[num])) throw string{"Overflow detected"};
		//sum = add_overflow_check(sum, numbers[num]); 
		sum += numbers[num];
	}
	return sum;
}

vector<double> make_differences(const vector<double>& numbers, const double& N)
{
	PPP::expect([&] {return 0 < N; }, "Not positive argument");
	PPP::expect([&] {return N <= numbers.size(); }, "make_differences() Too few numbers " + to_string(numbers.size()));

	vector<double> differences;
	for (int num{ 1 }; num < N; ++num)
	{
		differences.push_back(abs(numbers[num]- numbers[num-1]));
	}
	return differences;
}

int main()
try {
	int N{};//N numbers to sum
	vector<double> numbers;

	cout << "Please enter the number of values you want to sum: ";
	cin >> N;

	cout << "Please enter some integers (press | to stop): ";
	for (double num{}; cin >> num;) numbers.push_back(num);

	cout << "The sum of the first " << N << " numbers ( ";
	print_numbers(numbers, N);
	cout << " ) is " << get_sum(numbers, N) <<'\n';

	cout << "Differences are ( " ;
	vector<double> differences = make_differences(numbers, N);
	print_numbers(differences, differences.size());
	cout << " )\n";

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