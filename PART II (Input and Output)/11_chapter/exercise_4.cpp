/*
[4]
Write a program that draws a class diagram like the one in §10.6. It will simplify matters
if you start by defining a Box class that is a rectangle with a text label.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

class Box :public Rectangle
{
public:
    Box(Point, string);
    void draw_specifics(Painter& painter) const override;
private:
    Text lable;
};

void Box::draw_specifics(Painter& painter) const
{
    Rectangle::draw_specifics(painter);
    lable.draw_specifics(painter);
}
Box::Box(Point p, string s)
    :   Rectangle(p,15* s.length(), 25)
    ,lable{{p.x+ 5,p.y+ 5},s}
{
    set_fill_color(Color::cyan);
}


class Arrow :public Line {
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
    set_fill_color(Color::black);
}

void Arrow::draw_specifics(Painter& painter) const
{
    painter.draw_line(point(0), point(1));
    painter.draw_polygon(Polygon{ point(1), point(2), point(3) }); // for fill color
}
Point n(const Rectangle& r)
// top center 
{
    return { r.point(0).x + (r.width() / 2),r.point(0).y };
}
Point s(const Rectangle& r)
// bottom center 
{
    return { r.point(0).x + (r.width() / 2),r.point(0).y + r.height() };
}

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},800,400,"chapter" };
    Box box0{ {50,50},"Window" };
    Box box1{ {250,50},"Line_style" };
    Box box2{ {450,50},"Color" };
    Box box3{ {50,100},"Simple_window" };
    Box box4{ {350,100},"Shape" };
    Box box5{ {550,100},"Point" };
    Box box6{ {50,150},"Lines" };
    Box box7{ {150,150},"Polygon" };
    Box box8{ {300,150},"Axis" };
    Box box9{ {400,150},"Rectangle" };
    Box box10{ {540,150},"Text" };
    Box box11{ {650,150},"Image" };

    Arrow a0{ n(box3),s(box0) };
    Arrow a1{ n(box6),s(box4) };
    Arrow a2{ n(box7),s(box4) };
    Arrow a3{ n(box8),s(box4) };
    Arrow a4{ n(box9),s(box4) };
    Arrow a5{ n(box10),s(box4) };
    Arrow a6{ n(box11),s(box4) };

    win.attach(a0);
    win.attach(a1);
    win.attach(a2);
    win.attach(a3);
    win.attach(a4);
    win.attach(a5);
    win.attach(a6);

    win.attach(box6);
    win.attach(box7);
    win.attach(box8);
    win.attach(box9);
    win.attach(box10);
    win.attach(box11);

    win.attach(box3);
    win.attach(box4);
    win.attach(box5);

    win.attach(box0);
    win.attach(box1);
    win.attach(box2);

    win.wait_for_button();
}

