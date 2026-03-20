/*
[18] 
There is an Arc class in Graph.h. Find it and use it to define a box with rounded corner.
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
    Arc l0{ nw(*this), radius, radius,90,90 };
    Arc l1{ ne(*this), radius, radius,90,-90 };
    Arc l2{ se(*this), radius, radius,0,-90 };
    Arc l3{ sw(*this), radius, radius,180 ,90 };
    l0.draw_specifics(painter);
    l1.draw_specifics(painter);
    l2.draw_specifics(painter);
    l3.draw_specifics(painter);

    Line{ n(l0),n(l1) }.draw_specifics(painter);
    Line{ e(l1),e(l2) }.draw_specifics(painter);
    Line{ s(l2),s(l3) }.draw_specifics(painter);
    Line{ w_(l3),w_(l0) }.draw_specifics(painter);
}

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
   
    Box_rounded c{ {200,200},20,10 };

    win.attach(c);
    win.wait_for_button();
}
