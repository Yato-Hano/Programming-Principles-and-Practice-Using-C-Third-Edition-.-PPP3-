/*
[11]
Write a program that plays the game ‘‘Rock, Paper, Scissors.’’ If you are not familiar with
the game do some research (e.g., on the Web using Google). Research is a common task for
programmers. Use a switch-statement to solve this exercise. Also, the machine should give
random answers (i.e., select the next rock, paper, or scissors randomly). Real randomness is
too hard to provide just now, so just build a vector with a sequence of values to be used as
‘‘the next value.’’ If you build the vector into the program, it will always play the same game,
so maybe you should let the user enter some values. Try variations to make it less easy for
the user to guess which move the machine will make next.
*/




import PPP;
using namespace std;

//0 2 or 1
int generate_random_number(int seed)
{
	vector<int>numbers{ 0,2,1 };
	seed = abs(seed*478);
	seed %= numbers.size();
	return numbers[seed];
}


bool check_vector(const vector<char>& possibilities, const char& choice)
{
	for (const char& c : possibilities) if (c == choice)return true;
	return false;
}

int get_index(const vector<char>& possibilities, const char& choice)
{
	int index{};
	for (const int& c : possibilities)
	{
		if (c == choice)return index;
		++index;
	}
	return -1;
}

int main()
try {
	constexpr int draw{ 0 }, win{ 1 }, loss{ 2 };
	constexpr int rock{ 0 }, paper{ 1 }, scissors{ 2 };
	int machine_choice{};
	char player_choice{};
	int result{  };
	vector<char>possibilities{ 'r','p','s' };
	vector<string> form{ "rock","paper","scissors"};

	cout <<"Welcome to rock paper scissors game.\n"
		<< "Enter a ranom number seed and after that the game will start: ";

	for (int seed= 0; cin >>seed; )
	{
		result = -1;//reset
		machine_choice = generate_random_number(seed); 
		cout << "New game starts. Enter your choice: r, p or s.\n";
		while (cin >> player_choice && check_vector(possibilities, player_choice) != true)
		{
			cout << player_choice << " is not the choice i know.\n";
		}
		
		player_choice = get_index(possibilities, player_choice);

		cout << "Your choice is " << form[player_choice] << ". "
			<< "Machine choice is " << form[machine_choice] << ". ";
		
		if (player_choice == machine_choice)
			result = draw;
		else
			switch (player_choice)
			{
			case rock:// 0
				if (machine_choice == scissors) //win in this case only
				{
					result = win;
				}
				else
				{
					result = loss;
				}
				break;
			case paper://1
				if (machine_choice == rock)//loss in this case only
				{
					result = win;
				}
				else //scissors
				{
					result = loss;
				}
				break;
			case scissors://2
				if (machine_choice== rock)//loss in this case only
				{
					result = loss;
				}
				else
				{ 
					result = win;
				}
				break;
			default:
				throw string{ "1st switch error" };
			}

		switch (result)
		{
		case draw:
			cout << "Draw!\n";
			break;
		case win:
			cout << "You win!\n";
			break;
		case loss:
			cout << "Machine wins!\n";
			break;
		default:
			throw string{ "2d switch error" };
		}
		cout << "Enter a new ranom number seed: ";
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