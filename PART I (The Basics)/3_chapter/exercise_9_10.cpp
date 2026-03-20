/*
[9]
There is an old story that the emperor wanted to thank the inventor of the game of chess and
asked the inventor to name his reward. The inventor asked for one grain of rice for the first
square, 2 for the second, 4 for the third, and so on, doubling for each of the 64 squares. That
may sound modest, but there wasn’t that much rice in the empire! Write a program to calcu-
late how many squares are required to give the inventor at least 1000 grains of rice, at least
1,000,000 grains, and at least 1,000,000,000 grains. You’ll need a loop, of course, and prob-
ably an int to keep track of which square you are at, an int to keep the number of grains on
the current square, and an int to keep track of the grains on all previous squares. We suggest
that you write out the value of all your variables for each iteration of the loop so that you can
see what’s going on.

[10] 
Try to calculate the number of rice grains that the inventor asked for in exercise 9 above.
You’ll find that the number is so large that it won’t fit in an int or a double. Observe what
happens when the number gets too large to represent exactly as an int and as a double. What
is the largest number of squares for which you can calculate the exact number of grains
(using an int)? What is the largest number of squares for which you can calculate the approx-
imate number of grains (using a double)?

*/

import PPP;
using namespace std;

int main()
try {
	double sum_of_grains{1}, current_grains{1};
	int thousand{ 1000 }, million{ 1000000 }, a_lot{ 1000000000 };
	for (int square = 1; square !=65; square++)
	{
		cout << square << " square. " << current_grains << " grains on this square. "
		<< sum_of_grains << " sum of grains. ";

	
		if (a_lot < sum_of_grains&& a_lot!=-1)
		{
			cout << "1.000.000.000 grains!";
			a_lot = -1;
		}
		if (thousand < sum_of_grains && thousand != -1)
		{
			cout << "1000 grains!";
			thousand = -1;
		}
		if (million < sum_of_grains && million != -1)
		{
			cout << "1.000.000 grains!";
			million = -1;
		}
		cout << '\n';
		current_grains *= 2;
		sum_of_grains += current_grains;
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