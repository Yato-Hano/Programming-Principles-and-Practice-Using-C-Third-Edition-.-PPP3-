//2 chapter. exercise 11
/*
Write a program that prompts the user to enter some number of pennies (1-cent coins), nick-
els (5-cent coins), dimes (10-cent coins), quarters (25-cent coins), half dollars (50-cent
coins), and one-dollar coins (100-cent coins). Query the user separately for the number of
each size coin, e.g., ‘‘How many pennies do you have?’’ Then your program should print out
something like this:
You have 23 pennies.
You have 17 nickels.
You have 14 dimes.
You have 7 quar ters.
You have 3 half dollars.
The value of all of your coins is 573 cents.
Make some improvements: if only one of a coin is reported, make the output grammatically
correct, e.g., 14 dimes and 1 dime (not 1 dimes). Also, report the sum in dollars and cents,
i.e., .73 instead of 573 cents.
*/
import PPP;
using namespace std;

int main()
try {
	int pennies{ 0 }, nickels{ 0 }, dimes{ 0 }, quarters{ 0 }, half_dollars{ 0 }, dollars{ 0 };

	cout << "How many pennies do you have? ";
	cin >> pennies;
	cout << "How many nickels do you have? ";
	cin >> nickels;
	cout << "How many dimes do you have? ";
	cin >> dimes;
	cout << "How many quarters do you have? ";
	cin >> quarters;
	cout << "How many half dollars do you have? ";
	cin >> half_dollars;
	cout << "How many dollars do you have? ";
	cin >> dollars;

	int coins{ pennies };
	coins += nickels*5;
	coins += dimes*10;
	coins += quarters*25;
	coins += half_dollars*50;
	coins += dollars * 100;

	string p{ "pennies"};
	if (1== pennies)p = "penny";
	string n{ "nickels" };
	if (1 == nickels)n.pop_back();
	string d{ "dimes" };
	if (1 == dimes)d.pop_back();
	string q{ "quarters" };
	if (1 == quarters)q.pop_back();
	string h{ "half dollars" };
	if (1 == half_dollars)h.pop_back();
	string dl{ "dollars" };
	if (1 == dollars)dl.pop_back();

	cout << "You have " << pennies << ' '<< p<< ".\n"
		<< "You have " << nickels << ' ' << n << ".\n"
		<< "You have " << dimes << ' ' << d << ".\n"
		<< "You have " << quarters << ' ' << q << ".\n"
		<< "You have " << half_dollars << ' ' << h << ".\n"
		<< "You have " << dollars << ' ' << dl << ".\n";
	dollars = coins/100;
	coins %= 100;

	if (1 != dollars&& dl!="dollars")dl += 's';
	string c{ "coins" };
	if (1 == coins)c.pop_back();

	cout << "The value of all of your coins is " << dollars <<' ' << dl << " and " << coins <<' ' << c<< ".\n";
	system("pause");
	return 0;
}
catch (const string& surprise)
{
	cerr << surprise << endl;
	system("pause");
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
}