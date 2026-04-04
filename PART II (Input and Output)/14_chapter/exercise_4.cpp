/*
[4]
Make a menu with items that make a circle, a square, an equilateral triangle, and a hexagon,
respectively. Make an input box (or two) for giving a coordinate pair, and place the shape
made by pressing a menu item at that coordinate. Sorry, no drag and drop.
*/

#include "PPP/GUI.h"
#include <numbers>

using namespace Graph_lib;

class Regular_polygon :public Shape
{
public:
    Regular_polygon(Point center, int radius,int sides=6);
    void draw_specifics(Painter& painter) const override;
};
void Regular_polygon::draw_specifics(Painter& painter) const
{
    if (color().visibility()) {

        painter.draw_polygon(*this);
    }
}
Regular_polygon::Regular_polygon(Point center, int radius,int sides)
{
    double angleIncrement = 2.0 * numbers::pi / sides; // The angle between consecutive vertices in radians

    for (int i = 0; i < sides; ++i)
    {
        double currentAngle = i * angleIncrement;
        Point p;
        p.x = center.x + radius * std::cos(currentAngle);
        p.y = center.y + radius * std::sin(currentAngle);
        add(p);
    }
}
struct Regular_window :Window
{
    Regular_window(int w, int h);			
    enum S_Type{circle,square,triangle,hexagon};
private:
    void create_shape(S_Type);
    In_box next_coordinates;
    Menu shape_buttons;
    Point next_xy();
    Vector_ref<Shape> shapes;
};

Point Regular_window::next_xy()
{
    int x = 0;
    int y = 0;

    if (next_coordinates.last_result() == In_box::accepted) {
        string s = next_coordinates.last_string_value();
        istringstream iss{ s };
        iss >> x >> y;
    }
    return Point{ x,y };
}
void Regular_window::create_shape(S_Type st)
{
    constexpr int radius{ 100 };
    Point p = next_xy();
    int position = shapes.size();
    switch (st)
    {
    case Regular_window::circle:
        shapes.push_back(make_unique<Circle>(p, radius));
        break;
    case Regular_window::square:
        shapes.push_back(make_unique<Rectangle>(p, radius, radius));
        break;
    case Regular_window::triangle:
    {
        shapes.push_back(make_unique<Regular_polygon>(p, radius, 3));
        //  auto a = new Closed_polyline; //An alternative is to make a class Triangle
        // shapes.push_back(*a);
        // get_regular_polygon(*a, p, radius, 3); //Shape's add() is not virtual
        break;
    }
    case Regular_window::hexagon:
        shapes.push_back(make_unique<Regular_polygon>(p, radius, 6));
        break;
    default:
        break;
    }
    attach(shapes[position]);
}
Regular_window::Regular_window(int w, int h)
    :Window{ w,h,"Regular"},
    next_coordinates{ Point{0,0},70,20,"x y",[this]() { next_xy(); } },
    shape_buttons{{w-70,20},70,20,Menu::vertical,"shapes"}
{
    shape_buttons.attach(make_unique<Button>(Point{ 0,0 }, 0, 0, "Circle",
        [this] {create_shape(S_Type::circle); }));
    shape_buttons.attach(make_unique<Button>(Point{ 0,0 }, 0, 0, "Square",
        [this] {create_shape(S_Type::square); }));
    shape_buttons.attach(make_unique<Button>(Point{ 0,0 }, 0, 0, "Triangle",
        [this] {create_shape(S_Type::triangle); }));
    shape_buttons.attach(make_unique<Button>(Point{ 0,0 }, 0, 0, "Hexagon",
        [this] {create_shape(S_Type::hexagon); }));
    attach(shape_buttons);
    attach(next_coordinates);
    next_coordinates.show();
    next_coordinates.hide_buttons();
}
int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
    Regular_window win{ 600,400};
    app.gui_main();
}
catch (exception& e)
{
    ofstream ofs{ "errors.txt" };
    ofs << e.what() << '.' << endl;
}
catch (...)
{
    ofstream ofs{ "errors.txt" };
    ofs << "Some error." << endl;
}