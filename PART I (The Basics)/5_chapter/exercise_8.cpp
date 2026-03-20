/*
[8]
A permutation is an ordered subset of a set. For example, say you wanted to pick a combina-
tion to a vault. There are 60 possible numbers, and you need three different numbers for the
combination. There are P(60, 3) permutations for the combination, where P is defined by the
formula P(a, b) = (a!) / ((a − b)!) where ! is used as a suffix factorial operator. For example,
4! is 4∗3∗2∗1.
Combinations are similar to permutations, except that the order of the objects doesn’t
matter. For example, if you were making a ‘‘banana split’’ sundae and wished to use three
different flavors of ice cream out of five that you had, you probably wouldn’t care if you put
a scoop of vanilla at the beginning or the end or the serving dish. The formula for combina-
tions is C(a, b) = (P(a, b)) / (b!)
Design a program that asks users for two numbers, asks them whether they want to calcu-
late permutations or combinations, and prints out the result. This will have sev eral parts. Do
an analysis of the above requirements. Write exactly what the program will have to do.
Then, go into the design phase. Write pseudo code for the program and break it into sub-
components. This program should have error checking. Make sure that all erroneous inputs
will generate good error messages.
*/

import PPP;
using namespace std;

unsigned int fatcorial(const unsigned int n)
{
	unsigned int result{ 1 };
	for (unsigned int i = 1; i <= n; ++i)
	{
		result *= i;
	}
	return result;
}

unsigned int permutations(unsigned int a, unsigned int b)
{
	if (a < 1 || b < 1) throw string{ "not positive argument" };
	if (a < b) throw string{ "subset is greater than set" };
	return fatcorial(a) / fatcorial(a - b);
}


unsigned int combinations(unsigned int a, unsigned int b)
{
	if (a < 1 || b < 1) throw string{ "not positive argument" };
	if (a < b) throw string{ "subset is greater than set" };
	return permutations(a,b) / fatcorial(b);
}
int main()
try {
	cout << "Permutation and Combination.\n"
		<< "Enter set and subset numbers: ";
	int a, b;
	cin >> a >> b;
	if (!cin) throw string{ "bad input" };
	if (a < 1 || b < 1) throw string{ "not positive argument" };
	if(a<b) throw string{ "subset is greater than set" };

	cout << "Permutation 'p', Combination 'c': ";
	char choice{};
	cin >> choice;
	switch (choice)
	{
	case 'p':
		cout << "There are " << permutations(a, b) << " permutations.\n";
		break;
	case 'c':
		cout << "There are " << combinations(a, b) << " combinations.\n";
		break;
	default:
		throw string{ "not 'p' or 'c'" };
		break;
	}



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