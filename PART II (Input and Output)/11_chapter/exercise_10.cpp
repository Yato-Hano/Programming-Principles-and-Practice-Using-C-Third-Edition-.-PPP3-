/*
[10]
Draw a circle. Move a mark around on the circle (let it move a bit each time you hit the
‘‘Next’’ button).
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"
#include <numbers>

using namespace Graph_lib;

Point get_point(const Circle& e, double angle_degree)
{
    double angle_radians{ angle_degree * (std::numbers::pi / 180.0) };
    int x = e.center().x + e.radius() * cos(angle_radians);
    int y = e.center().y + e.radius() * sin(angle_radians);
    return { x,y };
}
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter 11" };
    Circle c{ {200,200},100 };
    win.attach(c);

    for (size_t i = 0; i <= 360; i+=5)
    {
        Mark m{ get_point(c,i),'O' };
        win.attach(m);
        win.wait_for_button();
    }
}
