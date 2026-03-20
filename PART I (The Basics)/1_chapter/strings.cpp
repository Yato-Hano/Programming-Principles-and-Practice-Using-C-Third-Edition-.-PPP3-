//  testing the string operators

import std;
import PPP;
using namespace std;

int main()
// read and compare names
{
	cout << "Please enter two names\n";
	string first;
	string second;
	cin >> first >> second;
	// read two str ings
	if (first == second)
		cout << "that's the same name twice\n";
	if (first < second)
		cout << first << " is alphabetically before " << second << '\n';
	if (first > second)
		cout << first << " is alphabetically after " << second << '\n';
	system("pause");
	return 0;

}