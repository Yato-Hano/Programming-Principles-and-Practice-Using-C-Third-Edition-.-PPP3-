//2 chapter. exercise 6 and 7

/*
[6]
Write a program that prompts the user to enter three integer values, and then outputs the val-
ues in numerical sequence separated by commas. So, if the user enters the values 10 4 6, the
output should be 4, 6, 10. If two values are the same, they should just be ordered together.
So, the input 4 5 4 should give 4, 4, 5.
[7]
Do exercise 6, but with three string values. So, if the user enters the values Steinbeck, Hem-
ingway, Fitzg erald, the output should be Fitzg erald, Hemingway, Steinbeck.
*/

import PPP;
using namespace std;
int main()
try {
	cout << "Type 3 words followed by enter to sort them.\n";
	vector<string>sequence;
	for (string number{ 0 }; sequence.size() != 3 && cin >> number  ; sequence.push_back(number));

	sort(sequence.begin(), sequence.end());

	for (const string& num : sequence)
		cout << num << ",";
	cout <<"\b.\n";

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