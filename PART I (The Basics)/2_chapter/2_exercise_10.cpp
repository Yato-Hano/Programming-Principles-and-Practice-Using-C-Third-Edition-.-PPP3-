//2 chapter. exercise 10
/*
Write a program that takes an operation followed by two operands and outputs the result. For
example:
+ 100 3.14
∗ 4 5
Read the operation into a string called operation and use an if-statement to figure out which
operation the user wants, for example, if (operation=="+"). Read the operands into variables
of type double. Implement this for operations called +, −, ∗, /, plus, minus, mul, and div with
their obvious meanings.
*/
import PPP;
using namespace std;
int main()
try {
	cout << "Type an operator followed by 2 operands, then hit enter.\n";
	string operation;
	double a{ 0 };
	double b{ 0 };
	cin >> operation >> a >> b;
	if (operation == "+" || operation=="plus") cout << a + b << '\n';
	if (operation == "-" || operation == "minus") cout << a - b << '\n';
	if (operation == "*" || operation == "mul") cout << a * b << '\n';
	if (operation == "/" || operation == "div") cout << a / b << '\n';
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