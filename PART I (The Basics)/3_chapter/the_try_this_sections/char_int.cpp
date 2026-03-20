//char list

import PPP;
using namespace std;

int main()
try {
	char simbol{ -128 };
	while (simbol != 127)
	{

		cout << simbol <<'\t' << int(simbol )<< "\n";
		++simbol;
	}
	cout << simbol << '\t' << int(simbol) << "\n";



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