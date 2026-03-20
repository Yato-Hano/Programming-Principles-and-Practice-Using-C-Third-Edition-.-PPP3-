/*
[5]
This exercise and the next few require you to design and implement a Book class, such as you
can imagine as part of software for a library. Class Book should have members for the ISBN,
title, author, and copyright date. Also store data on whether or not the book is checked out.
Create functions for returning those data values. Create functions for checking a book in and
out. Do simple validation of data entered into a Book; for example, accept ISBNs only of the
form n−n−n−x where n is an integer and x is a digit or a letter. Store an ISBN as a string.
[6]
Add operators for the Book class. Have the == operator check whether the ISBN numbers are
the same for two books. Have != also compare the ISBN numbers. Have a << print out the
title, author, and ISBN on separate lines.
[7]
Create an enumerated type for the Book class called Genre. Hav e the types be fiction, nonfic-
tion, periodical, biography, and children. Give each book a Genre and make appropriate
changes to the Book constructor and member functions.
[8]
Create a Patron class for the library. The class will have a user’s name, library card number,
and library fees (if owed). Have functions that access this data, as well as a function to set
the fee of the user. Have a helper function that returns a Boolean (bool) depending on
whether or not the user owes a fee.
[9]
Create a Librar y class. Include vectors of Books and Patrons. Include a struct called Transac-
tion to record when a book is checked out. Have it include a Book, a Patron, and a Date.
Make a vector of Transactions to keep a record of which books are out. Create functions to
add books to the library, add patrons to the library, and check out books. Whenever a user
checks out a book, have the library make sure that both the user and the book are in the
library. If they aren’t, report an error. Then check to make sure that the user owes no fees. If
the user does, report an error. If not, create a Transaction, and place it in the vector of Trans-
actions. Also write a function that will return a vector that contains the names of all Patrons
who owe fees.
*/

import PPP;
using namespace std;

chrono::year_month_day get_todays_date()
{
	const auto now = chrono::system_clock::now();
	const chrono::year_month_day today_utc{ chrono::floor<chrono::days>(now) };
	return today_utc;
}
int find_(const auto& sequence, const auto& object_to_find)
{
	for (int i = 0; i < sequence.size(); i++)
	{
		if (sequence[i] == object_to_find) return i;
	}
	return -1;
}
namespace lib
{
	class ISBN {
	public:
		ISBN() {};
		ISBN(string s); //form n−n−n−x where n is an integer and x is a digit or a letter.
		const string& get_data()const { return data; }
	private:
		string data;
	};
	ISBN::ISBN(string s)
	{
		istringstream is{ s };
		int n{};
		char x{};
		constexpr char dash{ '-' };
		for (int i = 0; i < 3; ++i)
		{
			if (is >> n)
			{
			} // all OK
			else
				throw exception{ "ISBN: an integer expected" };

			if (is.get(x) && x == dash)
			{
			}// all OK
			else
				throw exception{ "ISBN: '-' expected" };
		}
		is.get(x);
		if (iswdigit(x) || iswalpha(x))
		{
		}// all OK
		else throw exception{ "ISBN: last simbol is not a letter or a digit" };

		data = s; // now we are sure string is valid
	}
	istream& operator>>(istream& is, ISBN& s)
	{
		string data;
		getline(is, data);
		s = ISBN{ data }; // check in the constructor
		return is;
	}
	
	enum class Genre {	fiction, nonfiction, periodical, biography, children};
	const vector<string>lib_genre{ "Fiction", "Nonfiction", "Periodical", "Biography", "Children" };

	class Book
	{
	public:
		Book(ISBN i, Genre g, string book_title, string author_name, chrono::year_month_day copyright_date, bool book_checked_out);

		const ISBN& get_ISBN()const { return identifier; }
		const Genre& get_genre()const { return genre; }
		const string& get_title()const { return title; }
		const string& get_author()const { return author; }
		const chrono::year_month_day& get_copyright()const { return copyright; }
		const bool& is_checked_out()const { return checked_out; }
		void check_out();
		void check_in();
	private:
		ISBN identifier;
		Genre genre;
		string title;
		string author;
		chrono::year_month_day copyright;
		bool checked_out{ false };
	};
	Book::Book(ISBN i, Genre g, string book_title, string author_name, chrono::year_month_day copyright_date, bool book_checked_out = false)
		:identifier{ i }, genre{ g }, title {book_title	}, author{ author_name }, copyright{ copyright_date }, checked_out{ book_checked_out }
	{
	}
	void Book::check_out()
	{
		checked_out = true;
	}
	void Book::check_in()
	{
		checked_out = false;
	}
	bool operator==(const Book& b1, const Book& b2)
	{
		return b1.get_ISBN().get_data() == b2.get_ISBN().get_data();
	}
	bool operator!=(const Book& b1, const Book& b2)
	{
		return !(b1== b2);
	}
	ostream& operator<<(ostream& os, const Book & a_book)
	{
		os <<"Title: " << a_book.get_title() << '\n'
			<< "Genre: " << lib_genre[int(a_book.get_genre())] << '\n'
			<< "Author: " << a_book.get_author() << '\n'
			<< "ISBN: " << a_book.get_ISBN().get_data() << '\n';
			return os;
	}

	class Patron
	{
	public:
		Patron(string users_name, unsigned lib_card_number, double lib_fee);
		const string& get_name()const { return name; }
		const unsigned& get_card_number()const { return card_number; }
		const double& get_fees()const { return fees; }
		const double& increment_fees(double increment); // use -increment to decreese the number. Hint: -object_name.get_fees() to set fees to 0. 
	private:
		string name;
		unsigned card_number;
		double fees{ 0 };
	};
	bool has_fees(const Patron& p)
	{
		return (0 < p.get_fees()) ? true : false;
	}
	Patron::Patron(string users_name, unsigned lib_card_number, double lib_fee = 0)
		:name{ users_name }, card_number{ lib_card_number }, fees{ lib_fee }
	{
	}
	const double& Patron::increment_fees(double d)
	{
		fees += d;
		return fees;
	}
	bool operator==(const Patron& b1, const Patron& b2)
	{
		return b1.get_card_number() == b2.get_card_number();
	}
	bool operator!=(const Patron& b1, const Patron& b2)
	{
		return !(b1 == b2);
	}

	struct Transaction
	{
		Book book;
		Patron patron;
		chrono::year_month_day date{};
	};
	bool operator==(const Transaction& b1, const Transaction& b2)
	{
		return b1.book== b2.book&&b1.patron==b2.patron;
	}
	bool operator!=(const Transaction& b1, const Transaction& b2)
	{
		return !(b1 == b2);
	}

	class Library
	{
	public:
		void push_back(Patron);
		void push_back(Book);
		void push_back(Transaction); //invariant: Patron and Book are in the Library, also the Patron has no fees
		const vector<Book>& get_books()const { return books; }
		const vector<Patron>& get_patrons()const { return patrons; }
		const vector<Transaction>& get_transactions()const { return transactions; }
	private:
		vector<Book> books;
		vector<Patron> patrons;
		vector <Transaction> transactions;
	};

	vector<Patron> patrons_with_fees(const vector<Patron>& vp)
	{
		vector<Patron> p_w_f;
		for (Patron p : vp)
		{
			if (has_fees(p))p_w_f.push_back(p);
		}
		return p_w_f;
	}
	vector<string> names_with_fees(const vector<Patron>& vp)
	{
		vector<string> p_w_f;
		for (Patron p : vp)
		{
			if (has_fees(p))p_w_f.push_back(p.get_name());
		}
		return p_w_f;
	}

	void Library::push_back(Patron p) { patrons.push_back(p); }
	void Library::push_back(Book p) { books.push_back(p); }
	void Library::push_back(Transaction p)
	{
		if (find_(books, p.book) == -1) throw exception{ "Transaction: No such book" };
		if (find_(patrons, p.patron) == -1) throw exception{ "Transaction: No such patron" };
		if (has_fees(p.patron)) throw exception{ "Transaction: This patron has fees" };
		p.book.check_out();
		transactions.push_back(p);
	}

}
int main()
try {
	//testing
	lib::Patron a_person{ "Name",31241,0.2 };
	lib::ISBN identifier{ "2-3-5-v" };
	chrono::year_month_day copyright_date = chrono::December/16/1770;
	lib::Book a_book1{ identifier ,lib::Genre::children,"Title","Author's Name",copyright_date };
	lib::Book a_book2{ lib::ISBN{"2-3-3-v" },lib::Genre::fiction,"Title","Author's Name",copyright_date };
	lib::Library l;
	l.push_back(a_person);
	l.push_back(a_book1);
	l.push_back(a_book2);
	//l.push_back(lib::Transaction{ a_book1 ,a_person ,get_todays_date()});

	cout << "\na_book\n";
	cout << a_book1 << '\n';
	cout << a_book2 << '\n';
	cout << a_book1.get_copyright() << '\n';
	cout << a_book1.is_checked_out() << '\n';

	cout <<"patrons_with_fees " << patrons_with_fees(l.get_patrons()).size() << '\n';

	cout << "names_with_fees " << names_with_fees(l.get_patrons()).size() << '\n';

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