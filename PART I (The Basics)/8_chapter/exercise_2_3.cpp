/*
[2]
Design and implement a Name_pairs class holding (name,age) pairs where name is a string
and age is a double. Represent that as a vector<string> (called name) and a vector<double>
(called ag e) member. Provide an input operation read_names() that reads a series of names.
Provide a read_ages() operation that prompts the user for an age for each name. Provide a
print() operation that prints out the (name[i],ag e[i]) pairs (one per line) in the order determined
by the name vector. Provide a sor t() operation that sorts the name vector in alphabetical order
and reorganizes the ag e vector to match. Implement all ‘‘operations’’ as member functions.
Test the class (of course: test early and often).
[3]
Replace Name_pair::print() with a (global) operator << and define == and != for Name_pairs.
*/

import PPP;
using namespace std;

class Name_pairs {
public:
	void read_names();
	void read_ages();
	const vector<string>& names() const { return name; }
	const vector<double>& ages() const { return age; }
	void sort();
private:
	vector<string>name;
	vector<double>age;
};

int find_(const string& name_to_find, const vector<string>& names)
{
	for (int index{ 0 }; index < names.size(); ++index)
	{
		if (names[index] == name_to_find) return index;
	}
	throw string{ name_to_find + " name not found" };
}

void Name_pairs::sort()
{
	if (age.size() != name.size()) throw exception{ "ages.size()!=names.size()" };
	const vector<string> names_unsorted = name;
	const vector<double> agees_unsorted = age;
	std::sort(name.begin(), name.end());
	for (int index{ 0 }; index < name.size(); ++index)
	{
		int next = find_(name[index], names_unsorted);
		age[index] = agees_unsorted[next];
	}
}

void Name_pairs::read_names()
{
	cout << "Enter names. End with |: ";
	for (string i; cin >> i && i != "|"; )
		name.push_back(i);
}

bool operator==(const Name_pairs& np1, const Name_pairs& np2)
{
	return np1.names()== np2.names() && np1.ages() == np2.ages();
} 
bool operator!=(const Name_pairs& np1, const Name_pairs& np2)
{
	return !(np1 == np2);
}
ostream& operator<<(ostream& os, const Name_pairs& np)
{
	if (np.names().size() != np.ages().size()) throw exception{ "ages.size()!=names.size()" };
	os << "Names\tAges\n";
	for (size_t i = 0; i < np.names().size(); ++i)
		os << np.names()[i] << '\t' << np.ages()[i] << '\n';
	return os;
}

void Name_pairs::read_ages()
{
	cout << "Enter ages: ";
	for (int i{}; name.size() != age.size(); ++i)
	{
		cout << name[i] << ": ";
		double d{};
		cin >> d;
		if(!cin)throw exception{ "Please use numbers only" };
		if (d < 0 || 150 < d) throw exception{ "You are kidding" };
		age.push_back(d);
	}
}


int main()
try {
	Name_pairs np;
	np.read_names();
	np.read_ages();
	np.sort();
	cout << np;

	Name_pairs np2;
	np2.read_names();
	np2.read_ages();
	//np2.sort();
	cout << np2;

	cout << "\n== " << (np == np2);
	cout << "\n!= " << (np != np2)<<'\n';
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