/*
[11] 
Write a program that writes out the first N values of the Fibonacci series, that is, the series
that starts with 1 1 2 3 5 8 13 21 34. The next number of the series is the sum of the two pre-
vious ones. Find the largest Fibonacci number that fits in an int.
*/

import PPP;
using namespace std;
#include <cstdint>


int main()
try {
	int N{};
	cout << "Enter N for Fibonacci series: ";

	if (cin >> N && 0<N) 
	{
	}
	else
		throw string{ "Bad input" };
	

	int t1 = 0, t2 = 1, next_Term = 0;

	std::cout << "Fibonacci Series: ";

	for (int i = 1; i <= N; ++i) {
		if (i == 1) {
			cout << t1 << ", ";
		}else
		if (i == 2) {
			cout << t2 << ", ";
		}
		else {
			next_Term = t1 + t2;
			t1 = t2;
			t2 = next_Term;

			cout << next_Term << ", ";
		}
	}
	cout << "\b\b.\n";

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