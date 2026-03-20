/*

*/

import PPP;
//#include <expected>
using namespace std;

namespace Chrono {
	struct Year {
		Year(int n) :y{ n } {
			//if (y < 0) throw exception{ "Not positive Year" };
		}
		int y;
	};
	enum class Month {
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date;
	extern bool is_valid(Date d);

	class Date {
	public:
		Date() {}
		Date(Year yy) :y{ yy } {
			if (!is_valid(*this)) throw exception{ "Not valid date" };
		}
		Date(Year yy, Month mm, int dd)
			:y{ yy }, m{ mm }, d{ dd } {
			if (!is_valid(*this)) throw exception{ "Not valid date" };
		}
		const Year& year() const { return y; }
		const Month& month() const { return m; }
		const int& day() const { return d; }
	private:
		Year y{ 2001 };
		Month m{ Month::jan };
		int	d{ 1 };
	};
	bool is_valid(Date d)
	{
		if (d.year().y < 0) return false;//throw exception{ "Not positive Year" };
		if (d.month() < Month::jan || Month::dec < d.month())return false; //throw exception{ "Not valid Month" };
		if (d.day() < 1 || 31 < d.day())return false;// throw exception{ "Not valid Day" };
		return true;
	}
	Month operator++(Month& m)
		// prefix increment operator
	{
		m = (m == Month::dec) ? Month::jan : Month{ int(m) + 1 };
		// "wrap around"
		return m;
	}
	Year operator++(Year& m)
	{
		++m.y;
		return m;
	}
	ostream& operator<<(ostream& os, Year d)
	{
		return os << d.y;
	}
	vector<string> month_tbl = { "Not a month", "January", "February", "March" ,"April","May","June"
									,"July", "August", "September", "October", "November", "December" };

	ostream& operator<<(ostream& os, Month m)
	{
		return os << month_tbl[int(m)];
	}

	ostream& operator<<(ostream& os, Date d)
	{
		return os << d.year() << '/' << d.month() << '/' << d.day();
	}
	Date add_day(Date d, int n)
	{
		if(n<0)throw exception{ "add_day(): Not positive argument" };
		Year year = d.year();
		Month month = d.month();
		int day = d.day();
		while (n != 0)
		{
			++day;
			if (day == 32) 
			{ 
				day = 1;
				++month;
				if (month == Month::jan)
				{
					++year;
				}
			}
			--n;
		}
		return Date{ year ,month ,day };
	}
}
int main()
try {
	Chrono::Date d{ Chrono::Year{2025},Chrono::Month::dec,31 };
	cout << d << '\n';

	Chrono::Date today{ Chrono::Year{2025} };
	cout <<"Today: " << today << '\n';
	Chrono::Date tomorow{ add_day(today ,540) };
	cout << "Tomorow: " << tomorow << '\n';

	Chrono::Month m = Chrono::Month::jan;
	cout << m << '\n';
	++m;
	cout << m << '\n';
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