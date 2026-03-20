/*
[3]
Draw your initials 150 pixels high. Use a thick line. Draw each initial in a different
color.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter 10" };

    Open_polyline g;
    Point g_start{ 100,100 };
    g.add(g_start);
    constexpr int x_shift{ 70 };
    constexpr int y_shift{ 100 };
    g.add({ g_start .x- x_shift,g_start .y});
    g.add({ g_start.x- x_shift,g_start.y+ y_shift });
    g.add({ g_start.x,g_start.y + y_shift });
    g.add({ g_start.x,g_start.y + (y_shift-20) });
    g.add({ g_start.x-20,g_start.y + (y_shift -20) });

    Open_polyline v;
    Point v_start{ 200,100 };
    v.add(v_start);
    v.add({ v_start .x+30,v_start .y+ y_shift });
    v.add({ v_start.x + 60,v_start.y });

    v.set_style(Line_style(Line_style::solid, 5));
    g.set_style(Line_style(Line_style::solid, 5));

    v.set_color(Color::yellow);
    g.set_color(Color::green);

    win.attach(v);
    win.attach(g);

    win.wait_for_button();
}
