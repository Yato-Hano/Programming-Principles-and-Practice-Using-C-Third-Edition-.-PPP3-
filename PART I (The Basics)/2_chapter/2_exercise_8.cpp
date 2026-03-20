//2 chapter. exercise 8
/*
Write a program to test an integer value to determine if it is odd or even. As always, make
sure your output is clear and complete. In other words, don’t just output yes or no. Your out-
put should stand alone, like The value 4 is an even number. Hint: See the remainder (modulo)
operator in §2.4.
*/
import PPP;
using namespace std;
int main()
try {
	cout << "Type na integer number followed by enter to know enven it is or odd.\n";
	int num{ 0 };
	cin >> num;

	string property;
	if (num % 2)
		property = "odd";
	else
		property = "even";

	cout<<"The value " << num << " is an "<< property <<" number.\n";

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