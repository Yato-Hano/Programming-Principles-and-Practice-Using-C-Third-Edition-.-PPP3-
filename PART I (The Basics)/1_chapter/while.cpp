//  testing the the while-statement and ctrl+z

import std;
import PPP;
using namespace std;

int main()

{
	string c;
	string p;

	while (cin >> c) {
		if (c == p) cout << "Repeated: " << c << '\n';
		p = c;
	}
	cout << "Ended\n";
	system("pause");
	return 0;

}