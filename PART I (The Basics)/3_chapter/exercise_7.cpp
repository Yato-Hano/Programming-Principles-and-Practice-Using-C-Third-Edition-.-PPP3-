/*
[7]
Make a vector holding the ten string values "z ero", "one", . . . "nine". Use that in a program
that converts a digit to its corresponding spelled-out value; e.g., the input 7 gives the output
seven. Hav e the same program, using the same input loop, convert spelled-out numbers into
their digit form; e.g., the input seven gives the output 7.
*/

import PPP;
using namespace std;

constexpr int error_index{ -1 };

void turn_string_tolower(string& word)
{

	for (char& letter : word)
		letter = char(tolower(letter));

}

int word_to_digit(const vector<string>&number_literals, const string& word)
{
	int index{0};
	for (const string& w : number_literals)
	{
		if (w == word)
			return index;
		
		++index;
	}
	return error_index;
}

int main()
try {
	cout << "Type digit or word from 0 to 9 and hit enter.\n";
	
	vector<string>number_literals{ "zero","one","two","three", "four","five","six","seven","eight","nine" };
	string word;
	int digit_from_word{};

	for (char digit{}; cin >> digit;)
	{
		if ('0' <= digit && digit <= '9')
		{
			int index{ int(digit) - '0' };
			word=number_literals[index] ;
			digit_from_word = index;
		}
		else 
		{
			cin >> word;
			word = digit + word;
			turn_string_tolower(word);
			digit_from_word = word_to_digit(number_literals,word);
		}

		if (digit_from_word == error_index)
			cout << word << " is not what i know.\n";
		else 
			cout << digit_from_word << " is " << word<<".\n";

		word = "";
		digit_from_word = -2;
	}

	system("pause");
	return 0;
}
catch (const string& surprise)
{
	cerr << surprise << '.' << endl;
	system("pause");
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
}