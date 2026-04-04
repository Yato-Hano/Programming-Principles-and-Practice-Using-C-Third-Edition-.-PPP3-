/*
[9]
Modify the calculator from Chapter 6 to get its input from an input box and return its results
in an output box.
*/

#include "PPP/GUI.h"

using namespace Graph_lib;


struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) {} // token represents itself
	Token(char ch, double val) :kind(ch), value(val) {} // numbers
	Token(char ch, string val) :kind(ch), value(0), name(val) {} // variables
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
istringstream is;

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
constexpr char eof_ = 'f';

const string quit = "quit";
const string help = "help";
const string prompt = "> ";
const string result = "= ";

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch{ '1'};
	//while (is && ch == ' ')	is.get(ch);
	is >> ch;

	//if (!is) return Token(eof_, 0);

	{//testing
		ofstream ofs{ "get().txt",ios::app };
		ofs << ch <<'\n';
	}

	switch (ch)
	{
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case assign_:
			//case quit_:
			//case print_:
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
		{
			if (isalpha(ch))
			{ // variable starts with a lettter and contains letters '_' and digits
				string s;
				s += ch;
				while (is.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
				is.unget();
				//if (s == quit) return Token(quit_);
				//if (s == help) return Token(help_);
				if (s == "sin") return Token(sin_);
				if (s == "pow") return Token(pow_);
				if (s == "sqrt") return Token(sqrt_);
				return Token(name_, s);
			}
			error("Bad token");
		}
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
	 error("get: undefined name ", s);
}

void Symbol_table::set(string s, double d) // set variable
{
	for (int i = 0; i < st.names.size(); ++i)
		if (st.names[i].name == s) {
			if (st.names[i].is_const)   error("set: assignment to const ", s);
			st.names[i].value = d;
			return;
		}
	 error("set: undefined name ", s);
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
		if (t.kind != ')')  error("')' expected");
		return d;
	}
	case '-':
		return -primary();
	case '+':
		return primary();
	case sqrt_:
	{
		t = ts.get();
		if (t.kind != '(')  error("'(' expected");
		double d = expression();
		if (d < 0) error("negative argument for sqrt");
		t = ts.get();
		if (t.kind != ')')  error("')' expected");
		return sqrt(d);
	}
	case sin_:
	{
		t = ts.get();

		if (t.kind != '(') {
			ts.unget(t);
			error("'(' expected");
		}
		double d = expression();
		t = ts.get();
		if (t.kind != ')') {
			ts.unget(t);
			error("')' expected");
		}
		return sin(d);
	}
	case pow_:
	{
		t = ts.get();
		if (t.kind != '(')  error("'(' expected");
		double x = expression();
		t = ts.get();
		if (t.kind != ',')  error("',' expected");
		int i = int(expression());
		t = ts.get();
		if (t.kind != ')')  error("')' expected");
		return pow(x, i);
	}
	case number:
		return t.value;
	/*case Help_: case help_:
		ts.unget(t);
		return 0; // no number to return
	case print_:
		ts.unget(t);
		return 0;// no number to return*/
	case name_:
	{
		string name = t.name;
		t = ts.get();
		if (t.kind == assign_) return st.assign(name);
		ts.unget(t);
		return st.get(name);
	}
	default:
		 error("primary expected");
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
			if (d == 0)  error("divide by zero");
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
			//ts.unget(t);
			return left;
		}
	}
}

double Symbol_table::declare() // name = expression()
// assume we already have seen let
{
	Token t = ts.get();
	if (t.kind != name_)  error("name expected in declaration");
	string name = t.name;
	if (is_declared(name))  error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != assign_)  error("= missing in declaration of ", name);
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
		<< "Enter for print, " << quit << " for closing the pogram.\n";
}

void calculate(ostream&os)
{
	try
	{
		os  << statement();
	}
	catch (exception& e) {
		os << "exception: " << e.what();
	}
	catch (...) {
		os << "Some error.";
	}
}

class Calculator_window :public Window
{
public:
	Calculator_window(Application&);
private:
	Application* app;
	In_box input_b;
	Out_box result_box;
	Button quit;
	void run_();
};

Calculator_window::Calculator_window(Application& a)
	:Window{ 300,400,"Calculator" }
	, app{ &a }
, input_b{ {0,0},70,20,"Input: ",[this] {run_(); } }
, result_box{ {160,30},"Result: " }
, quit{ {x_max() - 70,0},70,20,"Quit",[this] {close(); app->quit(); } }
{
	attach(quit);

	attach(input_b);
	input_b.hide_buttons();
	input_b.show();

	attach(result_box);
	result_box.data.set_font_size(8);
	result_box.label.set_font_size(8);
}
void Calculator_window::run_()
{
	if (input_b.last_result() == In_box::accepted) {
		is.clear();
		is.str( input_b.last_string_value() );
		ostringstream os;
		calculate(os);
		{//testing
			ofstream ofs{ "run_().txt",ios::app };
			ofs << os.str() << '\n';
		}
		result_box.put(os.str());
	}
}
int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
	Calculator_window cw{ app };

    st.names.push_back(Variable{ "pi",3.14159265358979323846,true });
    st.names.push_back(Variable{ "k",1000 });

    app.gui_main();
}
catch (exception& e)
{
    ofstream ofs{ "errors.txt" };
    ofs << e.what() << '.' << endl;
}
catch (...)
{
    ofstream ofs{ "errors.txt" };
    ofs << "Some error." << endl;
}