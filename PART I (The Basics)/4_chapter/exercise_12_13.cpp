/*
[12]
Implement a little guessing game called (for some obscure reason) ‘‘Bulls and Cows.’’ The
program has a vector of four different integers in the range 0 to 9 (e.g., 1234 but not 1122)
and it is the user’s task to discover those numbers by repeated guesses. Say the number to be
guessed is 1234 and the user guesses 1359; the response should be ‘‘1 bull and 1 cow’’
because the user got one digit (1) right and in the right position (a bull) and one digit (3) right
but in the wrong position (a cow). The guessing continues until the user gets four bulls, that
is, has the four digits correct and in the correct order.
[13]
The program is a bit tedious because the answer is hard-coded into the program. Make a ver-
sion where the user can play repeatedly (without stopping and restarting the program) and
each game has a new set of four digits. You can get four random digits by calling the random
number generator random_int(0,9) from PPP_suppor t (and §4.7.5) four times. You will note
that if you run that program repeatedly, it will pick the same sequence of four digits each
time you start the program. To avoid that, ask the user to enter a number (any number) and
call seed(n), also from PPP_suppor t, where n is the number the user entered before calling
random_int(0,10). Such an n is called a seed, and different seeds give different sequences of
random numbers.
*/

import PPP;
using namespace std;

bool is_there(const vector<int>& numbers, const int& num){

	for (const int& n : numbers) { 
		if (n == num) 
			return true; 
	}
	return false;
}

int find_cows(const vector<int>& numbers, const vector<int>& guess)
//
{
	if (numbers.size() != guess.size()) throw string{"size missmatch in find_cows()"};
	int cows{0};
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		if (is_there(numbers, guess[i]))
			cows += 1;
	}
	return cows;
}

int find_bulls(const vector<int>& numbers, const vector<int>& guess)
//
{
	if (numbers.size() != guess.size()) throw string{ "size missmatch in find_cows()" };
	int bulls{ 0 };
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		if (numbers[i] == guess[i])
			bulls += 1;
	}
	return bulls;
}

vector<int> get_four_random_numbers()
//4 different numbers in [0,9] range
{
	default_random_engine engine{ unsigned(time(0)) };
	uniform_int_distribution<int> dist(0,9);
	vector<int>numbers;
	for (size_t i = 0; i < 4; i++)
	{
		int rn = dist(engine);
		while(is_there(numbers,rn)) 
			rn= dist(engine);
		numbers.push_back(rn);
	}
	return numbers;
}
void print_numbers(const vector<int>& numbers, const int& N)
{
	PPP::expect([&] {return 0 <= N; }, "Not positive argument");
	PPP::expect([&] {return N <= numbers.size(); }, "print_numbers() Too few numbers " + to_string(numbers.size()));

	for (int num{}; num < N; ++num)
		cout << numbers[num] << ' ';
	cout << '\b';
}
bool validate_digit(const vector<int>& guess, const int& digit)
// different and in [0:9] digit
{
	if (is_there(guess, digit)) return false;
	if (digit < 0 || 9 < digit)return false;
	return true;
}

vector<int> get_guess()
//4 different digits in [0:9] 
{
	vector<int>guess;
	for (int digit{ 0 }; guess.size() < 4 && cin >> digit;)
	{
			if (validate_digit(guess, digit))
				guess.push_back(digit);
			else 
				break;
	}	
	//print_numbers(guess, guess.size()); cout << '\n'; // for testing purposes

	if (guess.size() != 4) throw string{"Bad guess: repeated digit or not in [0:9] range"};	
	return guess;
}

int main()
try {
	vector<int>secret_number = get_four_random_numbers();
	
	//print_numbers(secret_number, secret_number.size()); cout << '\n'; // for testing purposes
	
	vector<int>guess;

	while(true)
	try 
	{
		cout << "Enter 4 different digits in [0:9] range: ";
		guess = get_guess(); // until guess is validated. if not get_guess() does throw
		int bulls{ find_bulls(secret_number,guess) }, cows{ find_cows (secret_number,guess)};

		cout << bulls << " bulls and " << cows << " cows.\n";

		if(bulls== guess.size()) break; 
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




/* It wasn't useful
int find_(const vector<int>& numbers, const int& num)
//returns index. if there is not then -1
{
	constexpr int not_found{ -1 };
	int index{ 0 };
	for (const int& n : numbers)
	{
		if (n == num)
			return index;
		++index;
	}
	return not_found;
}
*/