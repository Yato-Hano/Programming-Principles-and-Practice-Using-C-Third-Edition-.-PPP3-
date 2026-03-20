/*
[4]
Read a sequence of double values into a vector. Think of each value as the distance between
two cities along a given route. Compute and print the total distance (the sum of all dis-
tances). Find and print the smallest and greatest distance between two neighboring cities.
Find and print the mean distance between two neighboring cities.
*/

import PPP;
using namespace std;

int main()
try {
	cout << "Type distance values: ";
	vector<double> distance;
	for (double temp; cin >> temp; )
		distance.push_back(temp);

	if (distance.size() == 0) throw string{ "No data" };

	double sum = 0;
	for (double x : distance)
		sum += x;

	cout << "Mean: " << sum / distance.size() << '\n';

	sort(distance.begin(), distance.end());

	cout << "Lowest: " << distance[0] << '\n';
	cout << "Greatest: " << distance[distance.size()-1] << '\n';

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