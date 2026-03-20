/*
[10] 
Define a class Box that is a closed shape like a Rectangle (so it has fill color), except that it
has rounded corners. Use class Pie that you can find in the PPP support code on www.strous-
trup.com/programming.html.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"
#include <numbers>

using namespace Graph_lib;

class Box_rounded :public Rectangle
{
public:
    using Rectangle::Rectangle;
    void draw_specifics(Painter& painter) const override;
private:

};
//---
Point get_point(const Ellipse& e, double angle_degree)
{
    double angle_radians{ angle_degree * (std::numbers::pi / 180.0) };
    int x = e.center().x + e.major() * cos(angle_radians);
    int y = e.center().y + e.minor() * sin(angle_radians);
    return { x,y };
}
Point n(const Ellipse& e)
// top center 
{
    return get_point(e, -90);
}
Point s(const Ellipse& e)
// bottom center 
{
    return get_point(e, 90);
}
Point w_(const Ellipse& e)
// left center 
{
    return get_point(e, 180);
}
Point e(const Ellipse& e1)
// right center 
{
    return get_point(e1, 0);
}
//---
Point nw(const Rectangle& r)
// top left
{
    return r.point(0);
}
Point ne(const Rectangle& r)
// top right
{
    return { r.point(0).x + r.width(),r.point(0).y };
}
Point se(const Rectangle& r)
// bottom right
{
    return { r.point(0).x + r.width(),r.point(0).y + r.height() };
}
Point sw(const Rectangle& r)
// bottom left
{
    return { r.point(0).x ,r.point(0).y + r.height() };
}
void Box_rounded::draw_specifics(Painter& painter) const
{
    constexpr int radius{ 10 };
    painter.set_color(Color::invisible);
    Pie l0{ nw(*this), radius, radius,90,90 };
    Pie l1{ ne(*this), radius, radius,90,-90 };
    Pie l2{ se(*this), radius, radius,0,-90 };
    Pie l3{ sw(*this), radius, radius,180 ,90 };

    Closed_polyline{ n(l0), n(l1) ,e(l1), e(l2),s(l2), s(l3),w_(l3), w_(l0) }.draw_specifics(painter);

    l0.draw_specifics(painter);
    l1.draw_specifics(painter);
    l2.draw_specifics(painter);
    l3.draw_specifics(painter);
}

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
    Box_rounded br{ {100,100},200,50 };
    br.set_fill_color(Color::cyan);
    win.attach(br);
    win.wait_for_button();
}
