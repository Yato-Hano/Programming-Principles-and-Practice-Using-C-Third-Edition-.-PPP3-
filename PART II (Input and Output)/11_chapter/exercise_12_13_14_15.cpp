/*
[12] 
Define a right triangle class. Make an octagonal shape out of eight right triangles of dif-
ferent colors.
[13]
‘‘Tile’’ a window with small right triangles.
[14]
Do the previous exercise, but with hexagons.
[15]
Do the previous exercise, but using hexagons of a few different colors.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"
#include <numbers>

using namespace Graph_lib; 

double get_angle_radians(double angle_degree) 
{
    return angle_degree * (std::numbers::pi / 180.0);
}

class Right_triangle :public Shape
{
public:
    Right_triangle(Point right_angle, int width_x, int height_y, int rotation_degree);
    void draw_specifics(Painter& painter) const;
private:
    int w,h;

};
Point rotate_point(Point center, double angleInRadians, Point p)
{
    double s = std::sin(angleInRadians);
    double c = std::cos(angleInRadians);

    double temp_x = p.x - center.x;
    double temp_y = p.y - center.y;

    double xnew = temp_x * c - temp_y * s;
    double ynew = temp_x * s + temp_y * c;

    p.x = xnew + center.x;
    p.y = ynew + center.y;

    return p;
}

Right_triangle::Right_triangle(Point right_angle, int width_x, int height_y, int rotation_degree=0)
   : w{ width_x },h{ height_y }
{
    Shape::add(right_angle);
    Point p1{ right_angle.x + width_x,right_angle.y };
    Point p2{ right_angle.x ,right_angle.y+ height_y };

    Shape::add(rotate_point(right_angle,get_angle_radians(rotation_degree), p1));
    Shape::add(rotate_point(right_angle, get_angle_radians(rotation_degree), p2));
}
void Right_triangle::draw_specifics(Painter& painter) const
{
    if (color().visibility())
        painter.draw_polygon(*this);
}
vector<Point> get_octagon(Point center, int radius)
{
    if (radius <= 0) return {};
    vector<Point> vp;
    double angleIncrement = 2.0 * numbers::pi / 8; // The angle between consecutive vertices in radians

    for (int i = 0; i < 8; ++i)
    {
        double currentAngle = i * angleIncrement;
        Point p;
        p.x = center.x + radius * std::cos(currentAngle);
        p.y = center.y + radius * std::sin(currentAngle);
        vp.push_back(p);
    }
    return vp;
}
//-----------------------------------------------------------

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
        painter.draw_polygon(Closed_polyline{ point(0),point(1), point(2), point(3), point(4),point(5) });
}
Regular_hexagon::Regular_hexagon(Point center, int radius)
    :c{ center }, r{ radius }
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
//--------------------------------------------------

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},1000,800,"chapter 11" };
    //-----------------------------
    // octagon
    Point center{ 300,200 };
    int octagon_radius= 100;
    vector<Point> oct = get_octagon(center, octagon_radius);
    Vector_ref<Right_triangle> vr;
    int rotation_degree = 160;
    int octagon_side = 77; // calculated 76,5
    int color = 0;
    for (int i = 0; i < oct.size(); i++)
    {
        vr.push_back(make_unique<Right_triangle>(oct[i], octagon_side, octagon_side, rotation_degree));
        vr[vr.size() - 1].set_fill_color(color);
        win.attach(vr[vr.size() - 1]);
        ++color;
        rotation_degree += 45;
    }
    win.wait_for_button();
    // ---------------------------
    //tilling with Regular_hexagon
    Vector_ref<Regular_hexagon> vpol;
    int hexagon_side = 50;
    int dx = 0;
     color = 0;
    for (int y = 0; y <= win.y_max(); y += round(sqrt(3) / 2 * hexagon_side)) 
    {
        if (dx == 0) dx = 1.5 * hexagon_side;
        else dx = 0;
        for (int x = 0; x <= win.x_max(); x += 3 * hexagon_side)
        {
            vpol.push_back(make_unique< Regular_hexagon>(Point(x + dx, y), hexagon_side));
            vpol[vpol.size() - 1].set_fill_color(color);
            win.attach(vpol[vpol.size() - 1]);
            ++color;
        }
    }

    win.wait_for_button();
    // ---------------------------
    //tilling with Right_triangle
    Vector_ref<Right_triangle> vtri;
    int side_length = 50;
    color = 0;
    for (int x = 0; x < win.x_max(); x += side_length) 
    {
        for (int y = 0; y < win.y_max(); y += side_length)
        {
            vtri.push_back(make_unique< Right_triangle>(Point(x, y), side_length, side_length, 0));
            vtri[vtri.size() - 1].set_fill_color(color);
            ++color;
            win.attach(vtri[vtri.size() - 1]);
            vtri.push_back(make_unique< Right_triangle>(Point(x + side_length, y + side_length), side_length, side_length, 180));
            vtri[vtri.size() - 1].set_fill_color(color);
            win.attach(vtri[vtri.size() - 1]);
            ++color;
        }
    }
    win.wait_for_button();
}



