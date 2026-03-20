/*
[13]
Design and implement a rational number class, Rational. A rational number has two parts: a
numerator and a denominator, for example, 5/6 (five-sixths, also known as approximately
.83333). Look up the definition if you need to. Provide assignment, addition, subtraction,
multiplication, division, and equality operators. Also, provide a conversion to double. Why
would people want to use a Rational class?
*/

import PPP;
using namespace std;

class Rational
{
public:
	Rational(int n, int d);
	operator double() const	{return double(numerator) / denominator;	}
//	Rational operator=(int n);
	void simplify_the_fraction();
	int get_numerator()const {	return numerator;	}
	int get_denominator()const {return denominator;	}
private:
	int numerator{ 1 };
	int denominator{ 1 };
};
void Rational::simplify_the_fraction()
{
	int devisor = gcd(numerator, denominator);
	numerator /= devisor;
	denominator /= devisor;
}
Rational::Rational(int n, int d=1)
	:numerator{ n }, denominator{ d }
{
		if (d == 0)throw exception{ "denominator is 0" };
}
void convert_to_common(Rational& r1, Rational&r2)
{
	int common_mult{ lcm(r1.get_denominator(),r2.get_denominator()) };
	int r1_multiplier{ common_mult / r1.get_denominator() };
	int r2_multiplier{ common_mult / r2.get_denominator() };
	r1 = { r1.get_numerator() * r1_multiplier,common_mult };
	r2 = { r2.get_numerator() * r2_multiplier,common_mult };
}
Rational operator-(Rational r1,  Rational r2)
{
	convert_to_common(r1, r2);
	return Rational{ r1.get_numerator() - r2.get_numerator() ,r1.get_denominator() };
}
Rational operator+(Rational r1, Rational r2)
{
	convert_to_common(r1, r2);
	return Rational{ r1.get_numerator() + r2.get_numerator() ,r1.get_denominator() };
}
Rational operator*(const Rational& r1, const Rational& r2)
{
	return Rational{ r1.get_numerator() * r2.get_numerator() ,r1.get_denominator() * r2.get_denominator() };
}
Rational operator/(const Rational& r1, const Rational& r2)
{
	return Rational{ r1.get_numerator() * r2.get_denominator() ,r1.get_denominator() * r2.get_numerator() };
}
ostream& operator<<(ostream& os,const Rational& r)
{
	return os << r.get_numerator() << '/' << r.get_denominator();
}
//Rational Rational::operator=(int n) {denominator = 1; numerator = n; return *this;}
int main()
try {
	Rational r{ 1,3 };
	Rational r2{ 2,5 };
	//convert_to_common(r, r2);
	//r.simplify_the_fraction();
	cout <<"r " << r << '\n';
	cout << "r2 " << r2 << '\n';
	cout << "+ " << r + r2 << '\n';
	cout << "- " << r - r2 << '\n';
	cout << "* " << r*r2 << '\n';
	cout << "/ " << r / r2 << '\n';
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