// 'try this' from chapter 2.4
// also testing the order of calculations

import std;
import PPP;
using namespace std;

int main()
// simple program to exercise operators
{
	cout << "Please enter a floating−point value: ";
	int n = -1;
	int n2 = 0;
	int a=5;
	int b= 3;
	cin >> n;
		n >> n2;
		cout << "\nn2 == " << n2;
			cout << "\nn == " << n
		<< "\nn+1 == " << n + 1
		<< "\nthree times n == " << 3 * n
		<< "\ntwice n == " << n + n
		<< "\nn squared == " << n*n
		<< "\nhalf of n == " << n % 2
		<< "\nsquare root of n == " << sqrt(n)
		<< '\n';
			cout << "5 / 3 * 3 == " << 5 / 3 * 3<<'\n';
			cout << "a / b * b + a % b == " << a / b * b + a % b << '\n';
			cout <<"b + a % b == " << b + a % b << '\n';
			cout << "a % b == " << a % b << '\n';
			cout << "(b + a) % b == " << (b + a) % b << '\n';

			system("pause");
	return 0;
	
}