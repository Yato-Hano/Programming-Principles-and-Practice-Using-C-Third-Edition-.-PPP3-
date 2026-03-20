/*
[7]
Read five names into a vector<string> name, then prompt the user for the ages of the people
named and store the ages in a vector<double> age. Then print out the five (name[i],ag e[i])
pairs. Sort the names (sor t(name .begin(),name .end())) and print out the (name[i],ag e[i]) pairs.
The tricky part here is to get the ag e vector in the correct order to match the sorted name
vector. Hint: Before sorting name, take a copy and use that to make a copy of ag e in the right
order after sorting name.
[8]
Do the previous exercise but allow an arbitrary number of names.
*/

import PPP;
using namespace std;

void take_input(vector<string>& names, vector<int>& ages)
{
	cout << "Enter names. End with |: ";
	for (string i; cin >> i &&i!="|"; )
		names.push_back(i);

	cout << "Enter ages. End with |: ";
	for (int i; cin >> i; )
	{
		if (i < 0 || 150 < i) throw exception{ "You are kidding" };
		ages.push_back(i);
	}
	if (ages.size() != names.size()) throw exception{ "ages.size()!=names.size()" };
}

int find_(const string& name_to_find, const vector<string>& names)
{
	for (int index{ 0 }; index < names.size(); ++index)
	{
		if (names[index] == name_to_find) return index;
	}
	throw string{ name_to_find + " name not found" };
}

void sort_(vector<string>& names, vector<int>& ages)
{
	if (ages.size() != names.size()) throw exception{ "ages.size()!=names.size()" };
	const vector<string> names_unsorted = names;
	const vector<int> agees_unsorted = ages;
	sort(names.begin(), names.end());
	for (int index{ 0 }; index < names.size(); ++index)
	{
		int next = find_(names[index], names_unsorted);
		//cout << index << ' ' << next<<'\n';// testing purposes
		ages[index] = agees_unsorted[next];
	}
}

void print_pairs(const vector<string>& names, const vector<int>& ages)
{
	if (ages.size() != names.size()) throw exception{ "ages.size()!=names.size()" };
	for (size_t i = 0; i < names.size(); ++i)
	{
		cout << names[i] << '\t' << ages[i] << '\n';
	}
}

int main()
try {
	vector<string>names;
	vector<int>ages;

	take_input(names, ages);
	sort_(names, ages);

	cout << "Names\tAges\n";
	print_pairs(names, ages);

	system("pause");
	return 0;
}
catch (const string& surprise)
{
	cerr << surprise << '.' << endl;
	system("pause");
	return 1;
}
catch (const exception& surprise)
{
	cerr << "Exception: " << surprise.what() << '.' << endl;
	system("pause");
	return 2;
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
	return 3;
}