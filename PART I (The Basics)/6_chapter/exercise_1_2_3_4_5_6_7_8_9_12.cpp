/*
[1]
Allow underscores in the calculator’s variable names.
[2]
Provide an assignment operator, =, so that you can change the value of a variable after you
have introduced it using let. Discuss why that can be useful and how it can be a source of
problems.
[3]
Provide named constants that you really can’t change the value of. Hint: You have to add a
member to Variable that distinguishes between constants and variables and check for it in
set_value(). If you want to let the user define constants (rather than just having pi and e
defined as constants), you’ll have to add a notation to let the user express that, for example,
const pi = 3.14;
[4]
The get_value(), set_value(), is_declared(), and define_name() functions all operate on the vari-
able var_table.
Define a class called Symbol_table with a member var_table of type
vector<Variable> and member functions get(), set(), is_declared(), and declare(). Rewrite the
calculator to use a variable of type Symbol_table.
[5]
Modify Token_stream::g et() to return Token(print) when it sees a newline. This implies look-
ing for whitespace characters and treating newline ('\n') specially. You might find the stan-
dard-library function isspace(ch), which returns true if ch is a whitespace character, useful.
[6]
Part of what every program should do is to provide some way of helping its user. Hav e the
calculator print out some instructions for how to use the calculator if the user presses the H
key (both upper- and lowercase).
[7]
Change the q and h commands to be quit and help, respectively.
[8]
The grammar in §6.6.4 is incomplete (we did warn you against overreliance on comments); it
does not define sequences of statements, such as 4+4; 5−6;, and it does not incorporate the
grammar changes outlined in §6.8. Fix that grammar. Also add whatever you feel is needed
for that comment as the first comment of the calculator program and its overall comment.
[9]
Suggest three improvements (not mentioned in this chapter) to the calculator. Implement one
of them.
[12]
Modify the calculator to accept input from any istream.
*/



/*
	// a simple expression grammar :
Calculation:
	Statement
	Print
	Quit
	Calculation Statement
Statement:
	Declaration
	Expression
Declaration:
	"let" Name "=" Expression
Expression:
	Term
	Expression "+" Term
	Expression "−" Term
Term :
	Primary
	Term "∗" Primary
	Term "/" Primary
	Term "%" Primary
Primary :
	Number
	pow "(" Expression "," Expression ")" // only int for the second operand
	sqrt "(" Expression ")"  //  only int
	sin "(" Expression ")" 
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
struct Variable {
	string name;
	double value;
	bool is_const;
	Variable(string n, double v) :name(n), value(v), is_const(false) {}
	Variable(string n, double v, bool c) :name(n), value(v), is_const(c) {}
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

class Symbol_table {
public:
	vector<Variable> names;
	double assign(string name); // name = expression()
	double declare(); // name = expression()
	double get(string s);
	void set(string s, double d); // set variable
	bool is_declared(string s);
};

Symbol_table st;
Token_stream ts;
istream& is = cin;

constexpr char let = '#'; // declaration
constexpr char sin_ = 'S';
constexpr char help_ = 'h';
constexpr char Help_ = 'H';
constexpr char assign_ = '=';
constexpr char sqrt_ = 's';
constexpr char pow_ = 'p';
constexpr char name_ = 'a';
constexpr char quit_ = 'Q';
constexpr char print_ = '\n';
constexpr char number = '8'; // ndicates  numbers

const string quit = "quit";
const string help = "help";
const string prompt = "> ";
const string result = "= ";

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch{ ' ' };
	while(ch==' ') is.get(ch);

	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case assign_:
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
		is.unget();
		double val;
		is >> val;
		return Token(number, val);
	}
	default:
		if (isalpha(ch)||ch=='_') { // variable starts with a lettter and contains letters and digits
			string s;
			s += ch;
			while (is.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			is.unget();
			if (s == quit) return Token(quit_);
			if (s == help) return Token(help_);
			if (s == "sin") return Token(sin_);
			if (s == "pow") return Token(pow_);
			if (s == "sqrt") return Token(sqrt_);
			return Token(name_, s);
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
	while (is.get(ch))
		if (ch == c) return;
}


double Symbol_table::get(string s)  // get variable
{
	for (int i = 0; i < st.names.size(); ++i)
		if (st.names[i].name == s) return st.names[i].value;
	PPP::error("get: undefined name ", s);
}

void Symbol_table::set(string s, double d) // set variable
{
	for (int i = 0; i < st.names.size(); ++i)
		if (st.names[i].name == s) {
			if(st.names[i].is_const) PPP::error("set: assignment to const ", s);
			st.names[i].value = d;
			return;
		}
	PPP::error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < st.names.size(); ++i)
		if (st.names[i].name == s) return true;
	return false;
}


double expression();

double primary() // deals with ( ), sin, pow, sqrt, variables and numbers
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
		if (d < 0)PPP::error("negative argument for sqrt");
		t = ts.get();
		if (t.kind != ')') PPP::error("')' expected");
		return sqrt(d);
	}
	case sin_:
	{
		t = ts.get();
	
		if (t.kind != '(') {
			ts.unget(t);
			PPP::error("'(' expected");
		}
		double d = expression();
		t = ts.get();
		if (t.kind != ')') {
			ts.unget(t);
			PPP::error("')' expected");
		}
		return sin(d);
	}
	case pow_:
	{
		t = ts.get();
		if (t.kind != '(') PPP::error("'(' expected");
		double x = expression();
		t = ts.get();
		if (t.kind != ',') PPP::error("',' expected");
		int i = PPP::narrow<int>(expression());
		t = ts.get();
		if (t.kind != ')') PPP::error("')' expected");
		return pow(x, i);
	}
	case number:
		return t.value;
	case Help_: case help_:
		ts.unget(t);
		return 0; // no number to return
	case print_:
		ts.unget(t);
		return 0;// no number to return
	case name_:
	{
		string name = t.name;
		t = ts.get();
		if (t.kind == assign_) return st.assign(name);
		ts.unget(t);
		return st.get(name);
	}
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

double Symbol_table::declare() // name = expression()
// assume we already have seen let
{
	Token t = ts.get();
	if (t.kind != name_) PPP::error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) PPP::error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != assign_) PPP::error("= missing in declaration of ", name);
	double d = expression();
	st.names.push_back(Variable(name, d));
	return d;
}
double Symbol_table::assign(string name) // name = expression()
// wealready have seen name =
{
	double d = expression();
	set(name, d);
	return d;
}
double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return st.declare();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print_);
}

void guide()
{
	cout << "Welcome to our simple calculator. Please enter expressions using floating−point numbers.\n"
		<< "Operators *, /, -, +, sqrt(x), pow(x,i), sin(x) are available\n"
		<< "Enter for print, "<< quit<< " for closing the pogram.\n";
}

void calculate()
{
	while (true)
		try
		{
			cout << prompt;
			Token t = ts.get();
			while (t.kind == print_) t = ts.get();
			if (t.kind == Help_ || t.kind == help_)
			{
				guide();
				t = ts.get();
			}
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
	st.names.push_back(Variable{ "pi",3.14159265358979323846,true });
	st.names.push_back(Variable{ "k",1000 });
	calculate();
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

