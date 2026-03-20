/*
[6]
Redo the ‘‘Bulls and Cows’’ game from exercise 12 in Chapter 4 to use four letters rather
than four digits.
*/


import PPP;
using namespace std;

constexpr char a_letter{ 'a' }, j_letter{ 'a' + 9 };//9 letters for range

bool is_there(const vector<char>& numbers, const char& num) {

	for (const char& n : numbers) {
		if (n == num)
			return true;
	}
	return false;
}

int find_cows(const vector<char>& numbers, const vector<char>& guess)
//
{
	if (numbers.size() != guess.size()) throw string{ "size missmatch in find_cows()" };
	int cows{ 0 };
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		if (is_there(numbers, guess[i]))
			++cows;
	}
	return cows;
}

int find_bulls(const vector<char>& numbers, const vector<char>& guess)
//
{
	if (numbers.size() != guess.size()) throw string{ "size missmatch in find_cows()" };
	int bulls{ 0 };
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		if (numbers[i] == guess[i])
			++bulls;
	}
	return bulls;
}

vector<char> get_four_random_letters()
//4 different numbers in [0,9] range
{
	default_random_engine engine{ unsigned(time(0)) };
	uniform_int_distribution<int> dist(a_letter, j_letter);
	vector<char>numbers;
	for (size_t i = 0; i < 4; i++)
	{
		char rn = dist(engine); // get random letter
		while (is_there(numbers, rn))
			rn = dist(engine);
		numbers.push_back(rn);
	}
	return numbers;
}
void print_numbers(const vector<char>& numbers, const int& N)
{
	PPP::expect([&] {return 0 <= N; }, "Not positive argument");
	PPP::expect([&] {return N <= numbers.size(); }, "print_numbers() Too few numbers " + to_string(numbers.size()));

	for (int num{}; num < N; ++num)
		cout << numbers[num] << ' ';
	cout << '\b';
}
bool validate_digit(const vector<char>& guess, const int& digit)
// different and in [0:9] digit
{
	if (is_there(guess, digit)) return false;
	if (digit < a_letter || j_letter < digit)return false;
	return true;
}

vector<char> get_guess()
//4 different digits in [0:9] 
{
	vector<char>guess;
	for (char letter{ 0 }; guess.size() < 4 && cin >> letter;)
	{
		if (validate_digit(guess, letter))
			guess.push_back(letter);
		else
			break;
	}
	//print_numbers(guess, guess.size()); cout << '\n'; // for testing purposes

	if (guess.size() != 4) throw string{ "Bad guess: repeated letter or not in [a:j] range" };
	return guess;
}

int main()
try {
	vector<char>secret_number = get_four_random_letters();

	print_numbers(secret_number, secret_number.size()); cout << '\n'; // for testing purposes

	vector<char>guess;

	while (true)
		try
		{
			cout << "Enter 4 different letters in ["<< a_letter<<':'<<j_letter<<"] range: ";
			guess = get_guess(); // until guess is validated. if not get_guess() does throw
			int bulls{ find_bulls(secret_number,guess) }, cows{ find_cows(secret_number,guess) };

			cout << bulls << " bulls and " << cows << " cows.\n";

			if (bulls == guess.size()) break;
		}
		catch (const string& oops)
		{
			cerr << oops << ".\n";
		}

		cout << "You've Won!\n";

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