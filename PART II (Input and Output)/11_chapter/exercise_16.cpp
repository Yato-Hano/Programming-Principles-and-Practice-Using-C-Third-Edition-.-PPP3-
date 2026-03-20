/*
[16]
Define a class Poly that represents a polygon but checks that its points really do make a
polygon in its constructor. Hint: You’ll have to supply the points to the constructor.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

class Poly :public Shape
{
public:
    Poly(initializer_list<Point>);
    void draw_specifics(Painter& painter) const override;
};
void Poly::draw_specifics(Painter& painter) const
{
    if(color().visibility())
        painter.draw_polygon(*this);
}
Poly::Poly(initializer_list<Point> ilp)
{
    if (ilp.size() < 3) error("less than 3 points in a Poly");

    Polygon poly_check;
    for (Point p : ilp) 
    {
        poly_check.add(p);
        Shape::add(p);
    }

}


int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
    Poly p{ {100,100},{150,150},{200,150} };
    win.attach(p);
    win.wait_for_button();
}
