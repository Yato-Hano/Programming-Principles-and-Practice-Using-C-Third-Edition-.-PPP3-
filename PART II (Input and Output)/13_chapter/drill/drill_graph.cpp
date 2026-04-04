/*

*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

double one(double) { return 1; }
double slope(double x) { return 0.5*x; }
double square(double x) { return x*x; }
//double cos_(double x) { return cos(x ); }
double cos_slope(double x) { return slope (x)+ cos(x); }

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;

    constexpr int xmax = 600;
    constexpr int ymax = 600;

    constexpr int x_orig = xmax / 2;
    constexpr int y_orig = ymax / 2;

    constexpr Point orig{ x_orig,y_orig };

    constexpr int r_min = -10;
    constexpr int r_max = 11;
    constexpr int n_points = 400;

    constexpr int x_scale = 20;
    constexpr int y_scale = 20;

    Simple_window win{ Point{100,100},xmax,ymax,"Function graphs" };

    constexpr int xlength = 400; 
    constexpr int ylength = 400;

    Axis x{ Axis::x,Point{x_orig- xlength/2,y_orig}, xlength, xlength / x_scale, "1 == 20 pixels" };
    Axis y{ Axis::y,Point{x_orig, y_orig + ylength/2}, ylength, ylength / y_scale, "1 == 20 pixels" };
    Mark m{ orig ,'0' };
    x.set_color(Color::red);
    y.set_color(Color::red);

    Function o{ one,r_min,r_max,orig,n_points ,x_scale ,y_scale };
    Function s{ slope,r_min,r_max,orig,n_points ,x_scale ,y_scale };
    Function sq{ square,r_min,r_max,orig,n_points ,x_scale ,y_scale };
    Function c{ [](double d) {return cos(d); },r_min,r_max,orig,n_points ,x_scale ,y_scale };
    Function cs{ cos_slope,r_min,r_max,orig,n_points ,x_scale ,y_scale};
    cs.set_color(Color::cyan);
    c.set_color(Color::blue);
    Text ts2{ Point{100,y_orig + 50},"0.5*x" };

    win.attach(ts2);
    win.attach(cs);
    win.attach(o);
    win.attach(c);
    win.attach(sq);
    win.attach(s);
    win.attach(x);
    win.attach(y);
    win.attach(m);
    win.wait_for_button();
}
