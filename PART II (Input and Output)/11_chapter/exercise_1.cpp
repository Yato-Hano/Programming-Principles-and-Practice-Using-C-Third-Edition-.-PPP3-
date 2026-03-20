/*
[1]
Define a class Arrow, which draws a line with an arrowhead.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

class Arrow :public Line{
public:
    Arrow(Point start, Point arrow_here);
    void draw_specifics(Painter& painter) const override;
};

Arrow::Arrow(Point p1, Point p2)
    :Line{ p1,p2 }
{
    const double dx = p2.x - p1.x;
    const double dy = p2.y - p1.y;
    const double angle = std::atan2(dy, dx);

    constexpr double arrow_length{ 15 };
    constexpr double arrow_angle{ 0.5 };

    const int x3 = p2.x - arrow_length * std::cos(angle + arrow_angle);
    const int y3 = p2.y - arrow_length * std::sin(angle + arrow_angle);

    const int x4 = p2.x - arrow_length * std::cos(angle - arrow_angle);
    const int y4 = p2.y - arrow_length * std::sin(angle - arrow_angle);

    Shape::add({ x3,y3 });
    Shape::add({ x4,y4 });
}

void Arrow::draw_specifics(Painter& painter) const
{
    painter.draw_line(point(0), point(1));
    painter.draw_polygon(Polygon{ point(1), point(2), point(3) }); // for fill color
}

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter 11" };

    Arrow a{ {10,10},{100,100} };

    win.attach(a);
    a.set_fill_color(Color::blue);
    win.wait_for_button();
}
