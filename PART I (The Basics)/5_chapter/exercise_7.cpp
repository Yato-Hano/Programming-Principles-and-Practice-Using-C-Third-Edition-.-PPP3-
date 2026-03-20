/*
[7]
Write a program that reads digits and composes them into integers. For example, 123 is read
as the characters 1, 2, and 3. The program should output 123 is 1 hundred and 2 tens and 3
ones. The number should be output as an int value. Handle numbers with one, two, three, or
four digits. Hint: To get the integer value 5 from the character '5' subtract '0', that is,
'5'−'0'==5.
*/

import PPP;
using namespace std;

bool is_digit(char digit)
{
	return ('0' <= digit && digit <= '9');
}


int my_stoi(string number)
{
	int scale{ 1 }, result{ 0 };
	for (int index = (number.size()-1); 0 <= index; --index)
	{
		if (is_digit(number[index]))
			result += (number[index] - '0') * scale;
		else 
			throw string{ "not a digit" };
		scale *= 10;
	}
	return result;
}
string concatinate(char number, string word)
{
	word = string{ number } + " " + word;
	if ('1' < number) word+="s";
	return word;
}


int main()
try {

	while (cin)
	{
		string thousands{ "thousand" }, hundreds{ "hundred" }, tens{ "ten" }, ones{ "one" };
		cout << "Number: ";
		string number;
		cin >> number;
		switch (number.size())
		{
		case 4:
			thousands = concatinate(number[0] , thousands );
			hundreds = concatinate(number[1] , hundreds );
			tens = concatinate(number[2] , tens );
			ones = concatinate(number[3] , ones );
			break;
		case 3:
			thousands = { "" };
			hundreds = concatinate(number[0] , hundreds );
			tens = concatinate(number[1] , tens );
			ones = concatinate(number[2] , ones );
			break;
		case 2:
			thousands = { "" };
			hundreds = { "" };
			tens = concatinate(number[0] , tens );
			ones = concatinate(number[1] , ones );
			break;
		case 1:
			thousands = { "" };
			hundreds = { "" };
			tens = { "" };
			ones = concatinate(number[0] , ones );
			break;
		case 0:
			thousands = { "" };
			hundreds = { "" };
			tens = { "" };
			ones = { "" };
			break;
		default:
			throw string{ "max is 4 digit number" };
		}
		cout << my_stoi(number)<< " is " << thousands << " " << hundreds << " " << tens << " " << ones << '\n';
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