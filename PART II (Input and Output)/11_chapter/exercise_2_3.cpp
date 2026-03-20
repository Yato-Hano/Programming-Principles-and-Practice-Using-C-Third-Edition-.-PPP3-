
/*
[2]
Define functions n(), s(), e(), w(), center(), ne(), se(), sw(), and nw(). Each takes a Rectangle
argument and returns a Point. These functions define ‘‘connection points’’ on and in the
rectangle. For example, nw(r) is the northwest (top left) corner of a Rectangle called r.
[3]
Define the functions from exercise 2 for a Circle and an Ellipse. Place the connection
points on or outside the shape but not outside the bounding rectangle.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"
#include <numbers>

using namespace Graph_lib;

Point n(const Rectangle& r)
// top center 
{
    return { r.point(0).x+(r.width()/2),r.point(0).y};
}
Point s(const Rectangle& r)
// bottom center 
{
    return { r.point(0).x + (r.width() / 2),r.point(0).y+r.height()};
}
Point w(const Rectangle& r)
// left center 
{
    return { r.point(0).x ,r.point(0).y + (r.height()/2) };
}
Point e(const Rectangle& r)
// right center 
{
    return { r.point(0).x + r.width() ,r.point(0).y + (r.height() / 2) };
}
Point center(const Rectangle& r)
{
    return { r.point(0).x + (r.width() / 2) ,r.point(0).y + (r.height() / 2) };
}
Point nw(const Rectangle& r)
// top left
{
    return r.point(0);
}
Point ne(const Rectangle& r)
// top right
{
    return { r.point(0).x+r.width(),r.point(0).y};
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
//--------------------------
Point get_point(const Ellipse& e, double angle_degree)
{
    double angle_radians{ angle_degree * (std::numbers::pi/180.0)};
    int x = e.center().x + e.major() * cos(angle_radians);
    int y = e.center().y + e.minor() * sin(angle_radians);
    return { x,y };
}
Point get_point(const Circle& e, double angle_degree)
{
    double angle_radians{ angle_degree * (std::numbers::pi / 180.0) };
    int x = e.center().x + e.radius() * cos(angle_radians);
    int y = e.center().y + e.radius() * sin(angle_radians);
    return { x,y };
}

Point n(const Ellipse& e)
// top center 
{
    return get_point(e,-90);
}
Point s(const Ellipse& e)
// bottom center 
{
    return get_point(e, 90);
}
Point w(const Ellipse& e)
// left center 
{
    return get_point(e, 180);
}
Point e(const Ellipse& e)
// right center 
{
    return get_point(e, 0);
}
Point center(const Ellipse& e)
{
    return e.center();
}
Point nw(const Ellipse& e)
// top left
{
    return get_point(e, -90 - 45);
}
Point ne(const Ellipse& e)
// top right
{
    return get_point(e,-45);
}
Point se(const Ellipse& e)
// bottom right
{
    return get_point(e, 45);
}
Point sw(const Ellipse& e)
// bottom left
{
    return get_point(e, 90+45);
}
//----------------------------

Point n(const Circle& e)
// top center 
{
    return get_point(e, -90);
}
Point s(const Circle& e)
// bottom center 
{
    return get_point(e, 90);
}
Point w(const Circle& e)
// left center 
{
    return get_point(e, 180);
}
Point e(const Circle& e)
// right center 
{
    return get_point(e, 0);
}
Point center(const Circle& e)
{
    return e.center();
}
Point nw(const Circle& e)
// top left
{
    return get_point(e, -90 - 45);
}
Point ne(const Circle& e)
// top right
{
    return get_point(e, -45);
}
Point se(const Circle& e)
// bottom right
{
    return get_point(e, 45);
}
Point sw(const Circle& e)
// bottom left
{
    return get_point(e, 90 + 45);
}
//----------------------------
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
    Circle r{ {300,200},200 };
    Mark x1{ s(r) ,'s'};
    Mark x2{ w(r) ,'w' };
    Mark x3{ e(r) ,'e' };
    Mark x4{ n(r) ,'x' };

    win.attach(x1);
    win.attach(x2);
    win.attach(x3);
    win.attach(x4);
    win.attach(r);

    win.wait_for_button();
}
