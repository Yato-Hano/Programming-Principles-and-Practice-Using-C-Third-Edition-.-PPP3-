/*
[8]
Provide a currency converter. Read the conversion rates from a file on startup. Enter an
amount in an input window and provide a way of selecting currencies to convert to and from
(e.g., a pair of menus).
*/

#include "PPP/GUI.h"

using namespace Graph_lib;

struct From_To
{
    int from{};
    int to{};
};

class Conversion_window :public Window
{
public:
    Conversion_window(Application&);
private:
    Application* app;
    Menu from_m;
    Menu to_m;
   // Button run;
    In_box input_b;
    Out_box result_box;
    Button quit;

    vector<string>currency_names;
    vector<double>rates;//to USD
    From_To current_indicator;
    void run_();
    string convert(double);
};
void Conversion_window::run_()
{
    if (input_b.last_result() == In_box::accepted) {
        istringstream istr{ input_b.last_string_value() };
        double current_value{};
        istr >> current_value;
        string result = convert(current_value);
        result_box.put(result);
    }
}
string Conversion_window::convert(double current_value)
{
   double dollars = rates[current_indicator.from]* current_value;
   double result = dollars/rates[current_indicator.to];
   ostringstream os;
   os << currency_names[current_indicator.from] <<current_value
       << "=" 
       << currency_names[current_indicator.to]<<result; 
  return os.str();//to outbox
}
Conversion_window::Conversion_window(Application&a)
    :Window{300,400,"Currency converter"}
    ,app{&a}
   , from_m{{50,70},70,20,Menu::vertical,"from"}
   , to_m{ {150,70},70,20,Menu::vertical,"to" }
  // , run{ {75,50},20,20,">",[this] {run_(); } }
       , input_b{ {0,0},70,20,"Input: ",[this] {run_(); } }
       , result_box{{160,30},"Res: "}
       , quit{ {x_max() - 70,0},70,20,"Quit",[this] {close(); app->quit(); } }
{
    ifstream ifs{ "curr.txt" };
    if (!ifs)throw exception{ "No file" };

    attach(from_m);
    attach(to_m);
   // attach(run);
    attach(quit);

    attach(input_b);
    input_b.hide_buttons();
    input_b.show();

    attach(result_box);
    result_box.data.set_font_size(8);
    result_box.label.set_font_size(8);

    string curr; double rate{};
    for (size_t i = 0; ifs>>curr>>rate; i++)
    {
        from_m.attach(make_unique<Button>(Point{}, 0, 0, curr, [i, this] {current_indicator.from = i; }));
        to_m.attach(make_unique<Button>(Point{}, 0, 0, curr, [i, this] {current_indicator.to = i; }));
        rates.push_back(rate);
        currency_names.push_back(curr);
    }
    if(!ifs.eof())throw exception{ "Bad rate format" };
}
int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
    Conversion_window win{ app};
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