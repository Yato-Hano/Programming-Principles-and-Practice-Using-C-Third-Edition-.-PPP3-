/*
[9]
Write a function that given two vector<double>s price and weight computes a value (an
‘‘index’’) that is the sum of all price[i]∗weight[i]. Make sure to have weight.siz e()==price.siz e().
*/

import PPP;
using namespace std;

double index(const vector<double>& price, const vector<double>& weight)
{
	if (price.size() != weight.size()) throw exception{ "price.size() != weight.size()" };
	double ind{ 0 };
	for (size_t i = 0; i < price.size(); i++)
	{
		ind += price[i]*weight[i];
	}
	return ind;
}

int main()
try {
	cout << index(vector<double>{2.2, 3.4, 5.6}, vector<double>{2.2, 3.4, 5.6}) << '\n';
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