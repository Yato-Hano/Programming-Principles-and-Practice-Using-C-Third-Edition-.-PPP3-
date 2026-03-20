/*
[14]
Design and implement a Money class for calculations involving dollars and cents where arith-
metic has to be accurate to the last cent using the 4/5 rounding rule (.5 of a cent rounds up;
anything less than .5 rounds down). Represent a monetary amount as a number of cents in a
long int, but input and output as dollars and cents, e.g., $123.45. Do not worry about amounts
that don’t fit into a long int.
[15]
Refine the Money class by adding a currency (given as a constructor argument). Accept a
floating-point initializer as long as it can be exactly represented as a long int. Don’t accept
illegal operations. For example, Money∗Money doesn’t make sense, and USD1.23+DKK5.00 makes sense only if you provide a conversion table defining the conversion factor between
U.S. dollars (USD) and Danish kroner (DKK).
[16]
Define an input operator (>>) that reads monetary amounts with currency denominations,
such as USD1.23 and DKK5.00, into a Money variable. Also define a corresponding output
operator (<<).
*/

import PPP;
using namespace std;


enum class Currency {
	USD,DKK,No_curr
};

vector<string> literals_table{ "USD","DKK" };
vector<double> conversion_rates{100,0.15581 }; //to USD

class Money
{
public:
	Money(double, Currency);
	double get_value() const;
	Currency get_currency() const;
private:
	Currency currency;
	long int USD_coins{ 0 };
};
double Money::get_value()const
{
	return USD_coins/ conversion_rates[int(currency)];
}
Currency Money::get_currency()const
{
	return currency;
}
Money::Money(double value, Currency curr)
	:USD_coins{ long int(round(value * conversion_rates[int(curr)])) }, currency{ curr }
{
	if (USD_coins < 0) throw exception{ "Money: negative argument" };
}
Currency find_currency(const string &literal)
{
	for (size_t i = 0; i < literals_table.size(); i++)
	{
		if (literal == literals_table[i])return Currency(i);
	}
	return Currency::No_curr;
}

Currency get_currency(istream& is)
{
	string literal;
	char letter{ ' ' };

	while (is.get(letter)&&iswspace(letter));
	is.putback(letter);

	while (is.get(letter) && iswalpha(letter))literal += toupper(letter);
	is.putback(letter);
    return	find_currency(literal);
}
istream& operator>>(istream& is, Money& m)
{
	Currency c = get_currency(is);
	if (c == Currency::No_curr) throw exception{ "Money: No such currency" };
	double val{ 0 };
	if(!(is>>val))throw exception{ "Money: Bad value" };
	m = { val,c };
	return is;
}

ostream& operator<<(ostream& os,const Money& m)
{
	return os << literals_table[int(m.get_currency())]<<m.get_value();
}

int main()
try {
	for(Money m{ 100,Currency::DKK };true;)
	{
		cout << "> ";
		cin >> m;
		cout << m << '\n';
	}
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