/*
[5]
Write a program to play a numbers guessing game. The user thinks of a number between 1
and 100 and your program asks questions to figure out what the number is (e.g., ‘‘Is the num-
ber you are thinking of less than 50?’’). Your program should be able to identify the number
after asking no more than seven questions

	//***********************


	//version with auto-testing
	cout << "Come up with a number in the range [1:100] and answer no more than 7 questions.\n";
	for (double your_hidden_number{ 1 }; your_hidden_number != 101; ++your_hidden_number)
	{
		cout << your_hidden_number << " my_number.\n";
		double the_answer_number{ 50 };
		double shift{ 25 };
		for (int question_number{ 1 }; 0.3 < shift; ++question_number) // the 0.3 number was obtained through trial and error
		{
			cout << question_number << " question. Is your number less than " << round(the_answer_number)
				<< "? Shift " << shift << "\n";

			if (your_hidden_number < the_answer_number)
				the_answer_number -= shift;
			else
				the_answer_number += shift;

			shift /= 2.0;

			if (question_number == 8)throw string{ "More than 7 questions" };
		}
		the_answer_number = round(the_answer_number);
		cout << "Your number is " << the_answer_number << "!\n";

		if (the_answer_number == your_hidden_number) cout << "Sucsess!\n\n";
		else throw string{ "Fail" };

	}
	//********************
*/

import PPP;
using namespace std;

int main()
try {
	// here is version without auto-testing
	cout << "Come up with a number in the range [1:100] and answer no more than 7 questions.\n";

	double the_number{ 50 };
	double shift{ 25 };
	for (int question_number{ 1 }; 0.3 < shift; ++question_number) // the 0.3 number was obtained through trial and error
	{
		cout << question_number << " question. Is your number less than " << round(the_number )<< "? ";

		for (string answer; cin >> answer;)
		{
			if (answer == "yes")
			{
				the_number -= shift;
				shift /= 2.0;
				break;
			}
			else
				if (answer == "no")
				{
					the_number += shift;
					shift /= 2.0;
					break;
				}
				else cout << "Try yes or no answer.\n";
		}
		if (question_number == 8)throw string{ "More than 7 questions" };
	}

	cout << "Your number is " << round(the_number) << "!\n";



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