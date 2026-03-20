//chapter 2 Drill
// letter to a friend

import PPP;
using namespace std;



int main()
try{
	cout << "Enter the name of the person you want to write to.\n";
	string first_name; 
	cin >> first_name;

	cout << "Enter the name of the person you want to ask about.\n";
	string friend_name;
	cin >> friend_name;

	cout << "Enter the age of the recipient.\n";
	int age{ -1 };
	cin >> age;
	if (age < 1 || 109 < age)
		throw string("You are kidding!\n");

	cout << "Enter your name.\n";
	string your_name;
	cin >> your_name;

	cout << "Dear " << first_name << ",\n"
		<< "How are you? I am fine. I miss you.\n"
		<< "Today good weather in my town.\n"
		<< "I hear you just had a birthday and you are " << age << " years old.\n";

	if (age == 12)
		cout << "Next year you will be " << age + 1 << '\n';
	if (age == 17)
		cout << "Next year you will be able to vote.\n";
	if (70 < age)
		cout << "Are you retired?\n";

	cout << "Have you seen " << friend_name << " lately?\n"
		<< "Your sincerely\n\n"
		<< your_name <<".\n";
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