/*
[17]
Write a program to solve quadratic equations.
A quadratic equation is of the form
ax2 + bx + c = 0. If you don’t know the formula for solving such an expression, do some
research. Remember, researching how to solve a problem is often necessary before a pro-
grammer can teach the computer how to solve it. Use doubles for the user inputs for a, b, and
c. Since there are two solutions to a quadratic equation, output both x1 and x2.
*/

import PPP;
using namespace std;

int main()
try {
	double a, b, c; 
	double discriminant, x1, x2;

	cout << "Enter coefficients a, b, and c: ";
    cin >> a >> b >> c;
    if (a==0) throw string{ "a==0" };

	discriminant = b * b - (4 * a * c);

    if (discriminant > 0) {
        // Real and distinct roots
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        x2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << "Roots are real and different." << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
    else if (discriminant == 0) {
        // Real and equal roots
        x1 = -b / (2 * a);
        cout << "Roots are real and same." << endl;
        cout << "x1 = x2 = " << x1 << endl;
    }
    else {
        // Complex roots
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-discriminant) / (2 * a);
       cout << "Roots are complex and different." <<endl;
        cout << "x1 = " << realPart << " + " << imaginaryPart << "i" << endl;
        cout << "x2 = " << realPart << " - " << imaginaryPart << "i" << endl;
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