/*
	drill

	// a simple expression grammar :
Expression:
	Term
	Expression "+" Term
	Expression "−" Term
Term :
	Primar y
	Term "∗" Primar y
	Term "/" Primary
	Term "%" Primary
Primar y :
	Number
	pow "(" Expression "," Expression ")" // int only
	sqrt "(" Expression ")"  // int only
	"(" Expression ")"
Number :
	floating−point−literal
*/


import PPP;
using namespace std;


struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) {} // token represents itself
	Token(char ch, double val) :kind(ch), value(val) {} // numbers
	Token(char ch, string val) :kind(ch), name(val) {} // variables
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) {}

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char); // ignore utill char argument
};

constexpr char let = '#'; // declaration
constexpr char sqrt_ = 's';
constexpr char pow_ = 'p';
constexpr char name = 'a';
constexpr char quit_ = 'Q';
constexpr char print_ = ';';
constexpr char number = '8'; // ndicates  numbers

const string quit = "exit";
const string prompt = "> ";
const string result = "= ";

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case quit_:
	case print_:
	case let:
	case ',': // for pow(x,i)
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		cin.unget();
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		if (isalpha(ch)) { // variable starts with a lettter and contains letters and digits
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.unget();
			if (s == quit) return Token(quit_);
			if (s == "pow") return Token(pow_);
			if (s == "sqrt") return Token(sqrt_);
			return Token(name, s);
		}
		PPP::error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) {}
};

vector<Variable> names;

double get_value(string s)  // get variable
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	PPP::error("get: undefined name ", s);
}

void set_value(string s, double d) // set variable
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	PPP::error("set: undefined name ", s);
}

bool is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary() // deals with ( )  and numbers
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') PPP::error("')' expected");
		return d;
	}
	case '-':
		return -primary();
	case '+':
		return primary();
	case sqrt_:
	{
		t = ts.get();
		if (t.kind != '(') PPP::error("'(' expected");
		double d = expression();
		if(d<0)PPP::error("negative argument for sqrt");
		t = ts.get();
		if (t.kind != ')') PPP::error("')' expected");
		return sqrt(d);
	}
	case pow_:
	{
		t = ts.get();
		if (t.kind != '(') PPP::error("'(' expected");
		double x =expression();
		t = ts.get();
		if (t.kind != ',') PPP::error("',' expected");
		int i = PPP::narrow<int>(expression());
		t = ts.get();
		if (t.kind != ')') PPP::error("')' expected");
		return pow(x,i);
	}
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		PPP::error("primary expected");
	}
}

double term()// deals with * /
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) PPP::error("divide by zero");
			left /= d;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression() // deals with + -
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration() // name = expression()
{
	Token t = ts.get();
	if (t.kind != name) PPP::error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) PPP::error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') PPP::error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print_);
}

void calculate()
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print_) t = ts.get();
		if (t.kind == quit_) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		clean_up_mess();
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {

	names.push_back(Variable{ "k",1000 });
	calculate();
	system("pause");
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != print_);
	system("pause");
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != print_);
	system("pause");
	return 2;
}