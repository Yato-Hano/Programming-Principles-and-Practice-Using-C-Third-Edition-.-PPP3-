/*
    
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;
bool is_there(const char& ch, const string& unwanted)
{
    for (char c : unwanted)
    {
        if (ch == c)return true;
    }
    return false;
}
bool is_there(const string& word,const string& unwanted)
{
    for (char c:word)
    {
        if (is_there(c, unwanted))return true;
    }
    return false;
}

struct Person
{
    Person(string n1, string n2, int a):f_name{n1}, s_name{ n2 }, _age{a}{
        if (a < 0 || 150 < a)throw exception{ "age: out of range" };
        string unwanted{ ":;\"'[]*&^%$#@!" };
        if (is_there(f_name, unwanted))throw exception{ "f_name: unwanted char" };
        if (is_there(s_name, unwanted))throw exception{ "s_name: unwanted char" };
    }
    string first_name()const { return f_name; }
    string second_name()const { return s_name; }
    int age()const { return _age; }
private:
    string f_name,s_name;
    int _age;
};
ostream& operator<<(ostream& os, const Person& p)
{
    return os << p.first_name()<< ' ' << p.second_name() << ' ' << p.age();
}
istream& operator>>(istream& is, Person& p)
{
    string name,name2;
    int age;
    if(is >> name >>name2>> age)
      p = Person{ name,name2,age };
    return is;
}
int main(int /*argc*/, char* /*argv*/[])
try{
    Application app;
    ofstream ofs{ "out.txt" };
    ifstream ifs{ "p.txt" };
    vector<Person> vp;
    for (Person i{ "non","sec",15}; ifs >> i; )
    {
        vp.push_back(i);
    }
    for (Person p : vp)
    {
        ofs << p << '\n';
    }
}
catch (exception& e)
{
    ofstream ofs{ "errors.txt" };
    ofs << "Error: " << e.what() << endl;
}