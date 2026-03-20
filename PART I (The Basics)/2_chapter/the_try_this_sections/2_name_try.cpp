// 'try this' from chapter 2.3

//import std;
import PPP;




int main()
{
	std::cout << "Hello, please enter your first name followed by the last name and age.\n";
	
	
	std::string first_name{ "???" };
	
	
	std::string last_name;
	double age{ -1 };
	std::cin >> first_name >> last_name >> age;
	std::cout << "Hello " << first_name << ' ' << last_name << "(age - " << age*12 << " months)"<<'\n';
	system("pause");
	return 0;

}