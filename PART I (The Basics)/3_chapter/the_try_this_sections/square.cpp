// (start a variable result at 0 and add x to it x times)

import PPP;
using namespace std;

int square_(int x)
{
	int result{ 0 };

	for (int i = 0; i != x; ++i){
		result += x;
	}
	return result;
}


int main()
try 
{

	for (int i = 0; i != 100; ++i) {
		cout << "Square of " << i<<" is " << square_(i) << ".\n";
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