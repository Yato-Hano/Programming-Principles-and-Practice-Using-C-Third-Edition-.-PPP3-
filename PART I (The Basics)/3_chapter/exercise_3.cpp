/*
[3]
If we define the median of a sequence as ‘‘a number so that exactly as many elements come
before it in the sequence as come after it,’’ fix the program in §3.6.3 so that it always prints
out a median. Hint: A median need not be an element of the sequence.
*/

import PPP;
using namespace std;

int main()
try {

	cout << "Type values: ";
	vector<double> temps;// temperatures
	for (double temp; cin >> temp; )
		temps.push_back(temp);

	if (temps.size() == 0) throw string{ "No data." };

	double sum = 0;
	for (double x : temps)
		sum += x;

	cout << "Average temperature: " << sum / temps.size() << '\n';
	
	sort(temps.begin(),temps.end());
	size_t index{ temps.size() / 2 };
	double median{};
	cout << "index: " << index<<'\n';
	if (temps.size() % 2)
	{//odd size
		median = temps[index]; //exactly in the middle
	}
	else { //even size. 
		median = temps[index];
		median += temps[index-1];
		median /= 2.0; //mean of 2 numbers in the middle
	}

	cout << "Median temperature: " << median << '\n';
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