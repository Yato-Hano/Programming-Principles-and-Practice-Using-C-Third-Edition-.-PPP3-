//chapter 2 exercise 2. miles to kilometers

import PPP;
using namespace std;
int main()
try {
	
	cout << "This program converts from miles to kilometers.\n";
	double miles{ 0 };
	cout <<"Please, enter miles here: ";
	while (cin >> miles)
	{
		cout << miles << " miles == " << miles * 1.609 << " kilometers.\n";
		cout << "Please, enter miles here: ";
	}
	
	
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