/*
[6]
Write a program that performs as a very simple calculator. Your calculator should be able to
handle the four basic math operations – add, subtract, multiply, and divide – on two input val-
ues. Your program should prompt the user to enter three arguments: two double values and a
character to represent an operation. If the entry arguments are 35.6, 24.1, and '+', the program
output should be The sum of 35.6 and 24.1 is 59.7. In Chapter 5 and Chapter 6, we look at a
much more sophisticated simple calculator.
*/

import PPP;
using namespace std;

int main()
try {
	cout << "Type two floating point numbers followed by +, -, * or /. Then hit enter.\n";
	double a{}, b{}, result{};
	char oprtr{ ' ' };//operator
	string operation_name;

	while (cin >> a >> b >> oprtr)
	{
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
			oprtr=0;
			break;
		}
		
		if(oprtr)
			cout << "The " << operation_name << " of " << a << " and " << b << " is " << result<<'\n';
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