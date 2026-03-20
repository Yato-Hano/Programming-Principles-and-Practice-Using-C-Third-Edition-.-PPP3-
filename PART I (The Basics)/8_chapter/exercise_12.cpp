/*
[12] 
Change the representation of a Date to be the number of days since January 1, 1970 (known
as day 0), represented as a long int (that is, an int that can hold much larger integers than plain
int), and re-implement the Date member functions from §8.4.2. Be sure to reject dates out-
side the range we can represent that way (feel free to reject days before day 0, i.e., no nega-
tive days).
*/

import PPP;
using namespace std;

namespace Chrono
{
	class Date {
	public:
		Date(long long int days=0) :d{ days } {
			if (days<0) throw exception{ "Not valid date" };
		}
		auto add_day(int n);
		auto get_days()const { return d; }
	private:
		long long int d{ 0 };
	};
	auto Date::add_day(int n)
	{
		if (n < 0)throw exception{ "add_day(): Not positive argument" };
		d += n;
	}
}
int main()
try {

	Chrono::Date d{ 1000 };
	cout << d.get_days()<<'\n';
	d.add_day(5);
	cout << d.get_days() << '\n';
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