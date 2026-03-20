/*
[9]
Draw a 300-by-200-pixel ellipse. Draw a 400-pixel-long x axis and a 300-pixel-long y
axis through the center of the ellipse. Mark the foci. Mark a point on the ellipse that is
not on one of the axes. Draw the two lines from the foci to the point.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,600,"chapter 11" };

    Point center{ 300,300 };
    Ellipse e{ center ,150,100 };

    Mark f1{ e.focus1() ,'x' };
    Mark f2{ e.focus2() ,'x' };

    Axis x{ Axis::x,{center.x-200,center.y} ,400 ,10};
    Axis y{ Axis::y,{center.x,center.y+150} ,300 ,10 };

    Mark p{ {center.x+50,center.y+50} ,'o'};
    Lines ll{ e.focus1(),p.point(0),e.focus2(),p.point(0) };

    win.attach(ll);
    win.attach(p);
    win.attach(x);
    win.attach(y);
    win.attach(f1);
    win.attach(f2);
    win.attach(e);

    win.wait_for_button();
}
