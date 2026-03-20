// 'try this' from chapter 2.9

//import std;
import PPP;
using namespace std;

int main()
{

	double d = 0;
	while (cin >> d) {
		// repeat the statements below as long as we type in numbers
		int i = d;
		// tr y to squeeze a floating-point value into an integer value
		char c = i;
		cout << "d==" << d// tr y to squeeze an integer into a char
			// the original double
			<< " i==" << i
			// double converted to int
			<< " c==" << int(c)
			// int value of char
			<< " char(" << c << ")"// the char
			<< " round==" << round(d) << '\n'
			;
		
	}

	system("pause");
}