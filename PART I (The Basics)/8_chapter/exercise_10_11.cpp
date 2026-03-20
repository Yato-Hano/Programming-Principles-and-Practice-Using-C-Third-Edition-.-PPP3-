/*
[10]
Implement leapyear(int).
[11]
Design and implement a set of useful helper functions for the Date class with functions such
as next_workday() (assume that any day that is not a Saturday or a Sunday is a workday) and
week_of_year() (assume that week 1 is the week with January 1 in it and that the first day of a
week is a Sunday).
*/

import PPP;
//#include <expected>
using namespace std;

namespace Chrono 
{
	constexpr int days_in_month{ 31 }; // approximately
	constexpr double weeks_in_month{ days_in_month /7.0};

	bool leapyear(int year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
	struct Year {
		Year(int n) :y{ n } {
			//if (y < 0) throw exception{ "Not positive Year" };
		}
		int y;
	};
	enum class Month {
		jan = 0, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date;
	extern bool is_valid(Date d);
	int day_of_year(Date);
	int week_of_year(Date);
	Date add_day(Date d, int n);
	Date next_workday(Date date);

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

	int day_of_year(Date date)
		// very approximately
	{
		int days{ (int(date.month()) * days_in_month) + date.day() };

		return days;
	}

	int day_of_week(Date date)
		// very approximately
	{
		return day_of_year(date) % 7;

	}
	int week_of_year(Date date)
		// very approximately
	{
		return day_of_year (date)/7;
	}
	enum class Day {	
		sunday=1, monday, tuesday, wednesday, thursday, friday, saturday
	};
	Date next_workday(Date date)
		// very approximately. 1st is sunday (int(0) is sunday)
	{
		int days_to_add{};
		switch (Day(day_of_week(date)))
		{
			case Day::friday :
				days_to_add = 3;
				break;
			case Day::saturday:
				days_to_add = 2;
				break;
			default:
				days_to_add = 1;
				break;
		}
		return add_day(date,days_to_add);
	}
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
	vector<string> month_tbl = { "January", "February", "March" ,"April","May","June"
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
		if (n < 0)throw exception{ "add_day(): Not positive argument" };
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
	Chrono::Date d{ Chrono::Year{2025},Chrono::Month::jan,6 };
	cout << d << '\n';
	cout << "day_of_year: " << Chrono::day_of_year(d) << '\n';
	cout << "week_of_year: "<<Chrono::week_of_year(d) << '\n';
	cout << "day_of_week: " << Chrono::day_of_week(d) << '\n';
	cout << "next_workday: " << Chrono::next_workday(d) << '\n';

	Chrono::Date today{ Chrono::Year{2025} };
	cout << "Today: " << today << '\n';
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