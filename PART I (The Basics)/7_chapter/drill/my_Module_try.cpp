/*

*/
import foo;
import PPP;
using namespace std;

int main()
try {
	print_foo();
	set_foo(2);
	print_foo();
	cout << get_foo()<<'\n';
	print_foo();
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