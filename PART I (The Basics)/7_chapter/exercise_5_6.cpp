/*
[5]
Write two functions that reverse the order of elements in a vector<int>. For example, 1, 3, 5,
7, 9 becomes 9, 7, 5, 3, 1. The first reverse function should produce a new vector with the
reversed sequence, leaving its original vector unchanged. The other reverse function should
reverse the elements of its vector without using any other vectors (hint: swap).
[6]
Write versions of the functions from exercise 5, but with a vector<string>.
*/

import PPP;
using namespace std;

void print_(const auto& numbers)
{
	for (const auto& l : numbers)
		cout << l << ", ";
	cout << "\b\b.\n";
}
auto revers(auto sequnce)
{
	int right =  sequnce.size() - 1 ;
	for (int left = 0; left < right; )
	{
		swap(sequnce[left], sequnce[right]);
		++left;
		--right;
	}
	return sequnce;
}
void revers_this(auto& sequnce)
{
	int right = sequnce.size() - 1;
	for (int left = 0; left < right; )
	{
		swap(sequnce[left], sequnce[right]);
		++left;
		--right;
	}
}
int main()
try {
	print_(revers(vector<int>{1,2,3,4}));

	vector<string> s{ "a","b","c" };
	revers_this(s);
	print_(s);

	system("pause");
	return 0;
}
catch (const string& surprise)
{
	cerr << surprise << '.' << endl;
	system("pause");
	return 2;
}
catch (const exception& surprise)
{
	cerr << "Exception: " << surprise.what() << '.' << endl;
	system("pause");
	return 3;
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
	return 1;
}