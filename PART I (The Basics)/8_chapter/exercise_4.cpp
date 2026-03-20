/*
[4]
Do the previous exercise again but implement Name_pairs using a Name_pair class.
*/

import PPP;
using namespace std;

class Name_pair {
public:
	Name_pair(string n, double d) :name{ n }, age{ d } {}
	string name;
	double age;
};

class Name_pairs {
public:
	const vector<Name_pair>& data()const {	return name_age;}
	void push_back(Name_pair np) { name_age.push_back(np); }
	auto begin() { return name_age.begin(); }
	auto end() { return name_age.end(); }
private:
	vector<Name_pair>name_age;
};

bool operator==(const Name_pair& np1, const Name_pair& np2)
{
	return np1.name == np2.name&& np1.age == np2.age;
}
bool operator<(const Name_pair & np1, const Name_pair & np2)
{
	return np1.name < np2.name;
}

bool operator==(const Name_pairs& np1, const Name_pairs& np2)
{
	return np1.data() == np2.data();
}
bool operator!=(const Name_pairs& np1, const Name_pairs& np2)
{
	return !(np1 == np2);
}

istream& operator>>(istream& is, Name_pairs& np)
{
	cout << "Enter name age pairs. End with |: ";
	while (is)
	{
		string name;
		cout << "Name: ";
		is >> name;

		if (name == "|") break;
		double age{};
		cout << "Age: ";
		if (is >> age) {
			if (age < 0 || 150 < age) throw exception{ "You are kidding" };
			np.push_back({ name,age });
		}
	}
	return is;
}
ostream& operator<<(ostream& os, const Name_pairs& sequence)
{
	os << "Names\tAges\n";
	for (const Name_pair& np : sequence.data())
	{
		os << np.name << '\t' << np.age << '\n';
	}
	return os;
}


int main()
try {
	Name_pairs np;
	cin >> np;
	sort(np.begin(), np.end());
	cout << np;

	Name_pairs np2;
	cin >> np2;
	cout << np2;

	cout << "\n== " << (np == np2);
	cout << "\n!= " << (np != np2) << '\n';
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