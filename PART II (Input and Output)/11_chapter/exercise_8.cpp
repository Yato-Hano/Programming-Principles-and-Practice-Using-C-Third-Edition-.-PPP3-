/*
[8]
Define a class Regular_polygon. Use the center, the number of sides (>2), and the dis-
tance from the center to a corner as constructor arguments.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"
#include <numbers>

using namespace Graph_lib;

void add_points(Polygon& cp, const vector<Point>& vertices)
{
    for (const Point& p : vertices) cp.add(p);
}

class Regular_polygon :public Shape
{
public:
    Regular_polygon(Point center, int radius, int numSides);
    void draw_specifics(Painter& painter) const override;
private:
    int r;
    Point c;
};
void Regular_polygon::draw_specifics(Painter& painter) const
{
    if (color().visibility() && 2 < number_of_points())	// draw sole pixel?
    {
        painter.draw_polygon(*this);
    }
}
Regular_polygon::Regular_polygon(Point center, int radius,int numSides = 6)
    :c{ center }, r{ radius }
{
    if (numSides < 3 || radius <= 0) return;

    double angleIncrement = 2.0 * numbers::pi / numSides; // The angle between consecutive vertices in radians

    for (int i = 0; i < numSides; ++i)
    {
        double currentAngle = i * angleIncrement;
        Point p;
        p.x = center.x + radius * std::cos(currentAngle);
        p.y = center.y + radius * std::sin(currentAngle);
        add(p);
    }
}

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter 11" };

    Regular_polygon rp{ {100,100},50,3};
    rp.set_fill_color(Color::cyan);
    win.attach(rp);

    win.wait_for_button();
}
