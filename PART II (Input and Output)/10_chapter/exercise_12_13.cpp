/*
[12]
A superellipse is a two-dimensional shape defined by the equation
| x/a |m + | y/b |n = 1; where m > 0 and n > 0.
Look up superellipse on the Web to get a better idea of what such shapes look like.
Write a program that draws ‘‘starlike’’ patterns by connecting points on a superellipse.
Take a, b, m, n, and N as arguments. Select N points on the superellipse defined by a, b,
m, and n. Make the points equally spaced for some definition of ‘‘equal.’’ Connect each
of those N points to one or more other points (if you like you can make the number of
points to which to connect a point another argument or just use N–1, i.e., all the other
points).
[13] 
Find a way to add color to the lines from the previous exercise. Make some lines one
color and other lines another color or other colors.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"
#include <numbers>

using namespace Graph_lib;

void add_points(Closed_polyline& cp, const vector<Point>& vertices)
{
    for (const Point& p : vertices)cp.add(p);
}

double sign(double val) {
    if (val > 0) return 1.0;
    if (val < 0) return -1.0;
    return 0.0;
}

vector<Point> generate_super_ellipse_points(Point center, double radius_x, double radius_y, double n, int num_points = 1000)
{
    vector<Point> points;
    for (int i = 0; i <= num_points; ++i) 
    {
        double t = (double(i) / num_points) * 2.0 * numbers::pi; // angle from 0 to 2*PI

        double cosT = cos(t);
        double sinT = sin(t);

        int x = center.x + pow(abs(cosT), 2 / n) * radius_x * sign(cosT);
        int y = center.y + pow(abs(sinT), 2 / n) * radius_y * sign(sinT);

        points.push_back({ x, y });
    }
    return points;
}
void get_star_pattern(Simple_window& win,const vector<Point>& points)
{
    const int N = points.size();
    const int shift = points.size()/5;

    static vector<Line*> lines;
    for (int i = 0; i < N; i+= shift)
    {
        for (int p = i + 1; p < N; p+= shift)
        {
            lines.push_back(new Line(points[i], points[p]) );
            lines[lines.size() - 1]->set_color(i+p);//kind of random color
            win.attach(*lines[lines.size()-1]);
        }
    }
   // win.wait_for_button();
}
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };

    vector<Point> vertices{ generate_super_ellipse_points({300,200 }, 150, 150, 4)};
    Closed_polyline super_ellipse;
    add_points(super_ellipse, vertices);

    get_star_pattern(win,vertices);

    win.attach(super_ellipse);
    win.wait_for_button();
}
