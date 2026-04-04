/*
[11] 
Find the average maximum temperatures for each month of the year for two or more loca-
tions (e.g., Cambridge, England, and Cambridge, Massachusetts; there are lots of towns
called ‘‘Cambridge’’) and graph them together. As ever, be careful with axes, labels, use
of color, etc.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

class Scale {
    int cbase;
    int vbase;
    double scale;
public:
    Scale(int b, int vb, double s) :cbase{ b }, vbase{ vb }, scale{ s } {}
    int operator()(double v) const { return cbase + (v - vbase) * scale; }
};
void read(Open_polyline&op,const Scale& sc_x, const Scale& sc_y,string file_name)
{
    ifstream ifs{ file_name };
    if (!ifs)throw exception{ "No file" };
    double temp{};
    for (int i{ 1 }; i<13&&ifs >> temp;++i)
    {
        op.add({sc_x(i),sc_y(temp)});
    }
}
int main(int /*argc*/, char* /*argv*/[])
try{
    Application app;
    constexpr int xmax = 600;
    constexpr int ymax = 600;

    constexpr int x_orig = 50;
    constexpr int y_orig = ymax - 50;

    constexpr Point orig{ x_orig,y_orig };

    Simple_window win{ Point{100,100},xmax,ymax,"Graph" };

    constexpr int xlength = xmax - 100;
    constexpr int ylength = ymax - 100;

    constexpr int min_month = 1;
    constexpr int max_month = 12;

    constexpr int min_temp = 0;
    constexpr int max_temp = 30;

    constexpr int x_scale = xlength/(max_month-min_month);
    constexpr int y_scale = ylength / (max_temp - min_temp);

    constexpr int x_notches = (max_month - min_month) / 1;
    constexpr int y_notches = (max_temp - min_temp) / 5;

    Scale x_sc{ x_orig ,min_month ,x_scale };
    Scale y_sc{ y_orig ,min_temp ,-y_scale };

    Axis x{ Axis::x,orig, xlength,  x_notches,
        "Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec" };
    Axis y{ Axis::y,orig, ylength, y_notches,
        "Temp C | 30C max | 1==5C" };
    x.label.move(-140, 0);

    Text tc{ y.notches.point(0),"5C" }   ;
    tc.move(-50, 0);
    Text tc1{ y.notches.point(4),"15C" };
    tc1.move(-50, 0);

    Open_polyline uk, ma;
    uk.set_color(Color::blue);
    ma.set_color(Color::red);
    read(uk, x_sc, y_sc, "temps1.txt");
    read(ma, x_sc, y_sc, "temps2.txt");
    Text uk_l{ uk.point(0),"UK-Cambridge" };
    Text ma_l{ ma.point(0),"MA-Cambridge" };
    uk_l.set_color(Color::blue);
    ma_l.set_color(Color::red);

    win.attach(uk_l);
    win.attach(ma_l);
    win.attach(uk);
    win.attach(ma);
    win.attach(tc1);
    win.attach(tc);
    win.attach(x);
    win.attach(y);
    win.wait_for_button();
}
catch (exception& e)
{
    ofstream ofs{ "errors.txt" };
    ofs << e.what() << '.' << endl;
}