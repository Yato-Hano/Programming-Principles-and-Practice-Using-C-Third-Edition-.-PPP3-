//chapter 2. exercise 4 and 5
/*
 Write a program that prompts the user to enter two integer values. Store these values in int
variables named val1 and val2. Write your program to determine the smaller, larger, sum, dif-
ference, product, and ratio of these values and report them to the user.
[5]
Modify the program above to ask the user to enter floating-point values and store them in
double variables.
*/

import PPP;
using namespace std;
int main()
try {
	cout << "Enter an integer number followed by enter: ";
	double val1 {0};
	cin >> val1;
	cout << "Enter another integer number followed by enter: ";
	double val2  { 0 };
	cin >> val2;
	double devisor= gcd(int(val1), int(val2)) ;// gcd() works for integers only
	double smaller{ 0 };
	double larger{ 0 };
	if (val2 < val1)
	{
		smaller = val2;
		larger = val1;
	}
	else if (val1 < val2)
	{
		smaller = val1;
		larger = val2;
	}
	if (val1 == val2)
		cout << "numbers are equal: " << val1 << " == " << val2 << '\n';
	else
		cout << "smaller == " << smaller << '\n'
		<< "larger == " << larger << '\n';

	cout << "sum == " << val1+ val2 << '\n'
		<< "difference == " << larger - smaller << '\n'
		<< "product == " << val1 * val2 << '\n'
		<<"gcd == " << devisor << '\n'
		<< "ratio == " << val1/ devisor <<':' << val2 / devisor << '\n';

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