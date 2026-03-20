/*
[6]
Define a class Regular_hexagon (a regular hexagon is a six-sided polygon with all sides of
equal length). Use the center and the distance from the center to a corner point as con-
structor arguments.
[7]
Tile a part of a window with Regular_hexagons (use at least eight hexagons).
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"
#include <numbers>

using namespace Graph_lib;

class Regular_hexagon :public Shape
{
public:
    Regular_hexagon(Point center, int radius);
    void draw_specifics(Painter& painter) const override;
private:
    int r;
    Point c;
};
void Regular_hexagon::draw_specifics(Painter& painter) const
{
    if (color().visibility())
       painter.draw_polygon(Closed_polyline{point(0),point(1), point(2), point(3), point(4),point(5)});
}
Regular_hexagon::Regular_hexagon(Point center, int radius)
    :c{center},r{radius}
{
    int numSides = 6;
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

    Vector_ref<Regular_hexagon> tiles; 
    constexpr int radius{ 50 };

    for (size_t i = 0; i < 15; i++)
    {
        int x = (radius*1.4)*i;
        int y = radius + ((i % 2) * radius);
        tiles.push_back(make_unique<Regular_hexagon>(Point{x, y}, radius));
        tiles[tiles.size()-1].set_fill_color(Color::blue);
        win.attach(tiles[tiles.size() - 1]);
    }

    win.wait_for_button();
}
