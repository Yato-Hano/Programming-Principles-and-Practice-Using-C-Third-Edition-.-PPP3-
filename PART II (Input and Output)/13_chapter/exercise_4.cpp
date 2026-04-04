/*
[4]
Graph a sine (sin()), a cosine (cos()), the sum of those (sin(x)+cos(x)), and the sum of the
squares of those (sin(x)∗sin(x)+cos(x)∗cos(x)) on a single graph. Do provide axes and
labels.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

double cos_(double x) { return cos(x); }
double sin_(double x) { return sin(x); }
double sum_(double x) { return cos(x) +sin(x); }
double square_(double x) { return cos(x)*cos(x) + sin(x)* sin(x); }

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

    Axis x{ Axis::x,Point{x_orig - xlength / 2,y_orig}, xlength, xlength / x_scale, "1 == 20 pixels" };
    Axis y{ Axis::y,Point{x_orig, y_orig + ylength / 2}, ylength, ylength / y_scale, "1 == 20 pixels" };

    Function o{ cos_,r_min,r_max,orig,n_points ,x_scale ,y_scale };
    Function s{ sin_,r_min,r_max,orig,n_points ,x_scale ,y_scale };
    Function sq{ square_,r_min,r_max,orig,n_points ,x_scale ,y_scale };
    Function cs{ sum_,r_min,r_max,orig,n_points ,x_scale ,y_scale };
    sq.set_color(Color::red);
    Text ts_o{ Point{100,y_orig - 150},"cos" };
    Text ts_s{ Point{100,y_orig -100},"sin" };
    Text ts_sq{ Point{100,y_orig - 50},"square" };
    Text ts_cs{ Point{100,y_orig },"sum" };

    win.attach(ts_o);
    win.attach(ts_s);
    win.attach(ts_sq);
    win.attach(ts_cs);
    win.attach(cs);
    win.attach(o);
    win.attach(sq);
    win.attach(s);
    win.attach(x);
    win.attach(y);
    win.wait_for_button();
}
