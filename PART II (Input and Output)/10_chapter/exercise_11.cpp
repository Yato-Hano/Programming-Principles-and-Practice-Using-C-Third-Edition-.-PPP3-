/*
[11]
Draw a series of regular polygons, one inside the other. The innermost should be an equi-
lateral triangle, enclosed by a square, enclosed by a pentagon, etc. For the mathemati-
cally adept only: let all the points of each N-polygon touch sides of the (N+1)-polygon.
Hint: The trigonometric functions are found in <cmath> and module std (PPP2.§24.8).
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"
#include <numbers>

using namespace Graph_lib;

vector<Point> calculatePolygonVertices(int numSides, double radius, double centerX, double centerY)
{
    if (numSides < 3 || radius <= 0) return {};
    
    vector<Point> vertices;
    double angleIncrement = 2.0 * numbers::pi / numSides; // The angle between consecutive vertices in radians

    for (int i = 0; i < numSides; ++i) {
        double currentAngle = i * angleIncrement;

        Point p;
        p.x = centerX + radius * std::cos(currentAngle);
        p.y = centerY + radius * std::sin(currentAngle);

        vertices.push_back(p);
    }

    return vertices;
}
void add_points(Closed_polyline& cp, const vector<Point>& vertices)
{
    for (const Point& p : vertices)cp.add(p);
}
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},800,600,"chapter" };

    vector<Point> vertices{ calculatePolygonVertices(6,200,250,250)};
    Closed_polyline hexagon;
    add_points(hexagon, vertices);

    vertices =calculatePolygonVertices(5,150,250,250) ;
    Closed_polyline pentagon;
    add_points(pentagon, vertices);

    vertices = calculatePolygonVertices(4, 100, 250, 250);
    Closed_polyline square;
    add_points(square, vertices);

    vertices = calculatePolygonVertices(3, 50, 250, 250);
    Closed_polyline triangle;
    add_points(triangle, vertices);

    win.attach(triangle);
    win.attach(square);
    win.attach(hexagon);
    win.attach(pentagon);

    win.wait_for_button();
}
