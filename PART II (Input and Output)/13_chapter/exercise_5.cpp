/*
[5]
‘‘Animate’’ (as in §13.5) the series 1−/3+1/5−1/7+1/9−1/11+ ... . It is known as Leibniz’s
series and converges to pi/4.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;
double ls(int x)
{
    double sum_y{0};
    double sign{ 1 };
    for (double i = 0; i < x; i++)
    {
        sum_y += sign / (2.0 * i + 1.0);
        sign = -sign;
    }
    sum_y *= 4;
    ofstream ofs{ "oout.txt",ios::app };
    ofs << sum_y << endl;
    return sum_y;
}
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    constexpr int xmax = 600;
    constexpr int ymax = 600;

    constexpr int x_orig = xmax / 2;
    constexpr int y_orig = ymax / 2;

    constexpr Point orig{ x_orig,y_orig };

    constexpr int n_points = 400;


    constexpr int x_scale = 5;
    constexpr int y_scale = 25;

    Simple_window win{ Point{100,100},xmax,ymax,"Function graphs" };

    constexpr int xlength = 400;
    constexpr int ylength = 400;

    constexpr int r_min = 1;
    constexpr int r_max = xlength/(2* x_scale);

    Axis x{ Axis::x,Point{x_orig - xlength / 2,y_orig}, xlength, xlength / x_scale, "" };
    Axis y{ Axis::y,Point{x_orig, y_orig + ylength / 2}, ylength, ylength / y_scale, "" };

    Function o{ ls,r_min,r_max,orig,n_points ,x_scale ,y_scale };

    win.attach(x);
    win.attach(y);
    win.attach(o);
    win.wait_for_button();
}
