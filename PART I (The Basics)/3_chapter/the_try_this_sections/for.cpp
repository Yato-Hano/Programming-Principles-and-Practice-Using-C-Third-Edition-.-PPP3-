//char list

import PPP;
using namespace std;

int main()
try {
	
	for (int simbol{ -128 }; simbol != 128;++simbol)
		cout << simbol << '\t' << char(simbol) << "\n";
		
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