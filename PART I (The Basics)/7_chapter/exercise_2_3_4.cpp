/*
[2]
Write a function print() that prints a vector of ints to cout. Giv e it two arguments: a string for
‘‘labeling’’ the output and a vector.
[3]
Create a vector of Fibonacci numbers and print them using the function from exercise 2. To
create the vector, write a function, fibonacci(x,y,v,n), where integers x and y are ints, v is an
empty vector<int>, and n is the number of elements to put into v; v[0] will be x and v[1] will be
y. A Fibonacci number is one that is part of a sequence where each element is the sum of the
two previous ones. For example, starting with 1 and 2, we get 1, 2, 3, 5, 8, 13, 21, ... . Your
fibonacci() function should make such a sequence starting with its x and y arguments.
[4]
An int can hold integers only up to a maximum number. Find an approximation of that maxi-
mum number by using fibonacci().
*/

import PPP;
using namespace std;

void print_(const string& label,const vector<int>&numbers)
{
	cout << label << ": ";
	for ( int l:numbers)
		cout << l << ", ";
	cout << "\b\b.\n";
}

vector<int> fibonacci(int t1, int t2, vector<int>& numbers, int N)
{
	if (t2<t1)
		throw string{ "fibonacci: t1 > t2" };
	if (t1<0||t2<0||N<0)
		throw string{ "fibonacci: not positive argument" };
	if(!numbers.empty()) 
		throw string{ "fibonacci: not empty vector" };

	//int t1 = 0, t2 = 1;
	int	next_Term = 0;

	for (int i = 1; i <= N; ++i) {
		if (i == 1) {
			numbers.push_back(t1);
		}
		else
			if (i == 2) {
				numbers.push_back(t2);
			}
			else {
				next_Term = t1 + t2;
				t1 = t2;
				t2 = next_Term;

				numbers.push_back(next_Term);
			}
	}
	return numbers;
}
int main()
try {
	int t1, t2, N;
	while(true)
		try {
			cout << "Enter t1 t2 and N for Fibonacci Series: ";
			if (!(cin >> t1 >> t2 >> N))throw exception{ "bad input" };
			vector<int> fibonacci_numbers;
			fibonacci(t1, t2, fibonacci_numbers, N);
			print_("Fibonacci Series: ", fibonacci_numbers);
		}
		catch (const string& surprise)
		{
			cerr << surprise << '.' << endl;
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