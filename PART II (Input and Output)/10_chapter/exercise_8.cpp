/*
[8]
Draw the Olympic five rings. If you can’t remember the colors, look them up.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},800,400,"Rings" };

    constexpr int radius = 80;

    Circle b{ {100,200},radius };
    Circle y{ Point(100+ radius*1.5,220),radius };
    Circle d{ Point(100 + radius * 1.5 * 2,200),radius };
    Circle g{ Point(100 + radius * 1.5*3,220),radius };
    Circle r{ Point(100 + radius * 1.5 * 4,200),radius };

    g.set_style(Line_style(Line_style::solid, 10));
    g.set_color(Color::green);
    r.set_style(Line_style(Line_style::solid, 10));
    r.set_color(Color::red);
    y.set_style(Line_style(Line_style::solid, 10));
    y.set_color(Color::yellow);
    b.set_style(Line_style(Line_style::solid, 10));
    b.set_color(Color::blue);
    d.set_style(Line_style(Line_style::solid, 10));
    d.set_color(Color::black);

    win.attach(b);
    win.attach(y);
    win.attach(d);
    win.attach(g);
    win.attach(r);

    win.wait_for_button();
}
