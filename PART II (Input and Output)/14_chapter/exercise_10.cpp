/*
[10]
Provide a program where you can choose among a set of functions (e.g., sin() and log()), pro-
vide parameters for those functions, and then graph them.
*/

#include "PPP/GUI.h"

using namespace Graph_lib;

struct Functions_window :Window
{
    Functions_window(Application&p,int w, int h);
    enum F_Type { Sin,Log };
private:
    Application* app;
    void quit();
    void create_func(F_Type);
    In_box next_coordinates;
    In_box next_scale_x;
    In_box next_scale_y;
    Menu shape_buttons;
    Button quit_button;
    Axis x_ax;
    Axis y_ax;
    Point next_position();
    double next_scale(In_box& b);
    Vector_ref<Function> shapes;
};

double sin_(double x)
{
    return sin(x);
}
double log_(double x)
{
    return log(x);
}

void Functions_window::create_func(F_Type f)
{
    Point p{ next_position() };
    int number_of_points{ 100 };
    double x_scale{ next_scale (next_scale_x)}, y_scale{ next_scale(next_scale_y) };
    switch (f)
    {
    case Functions_window::Sin:
        shapes.push_back(make_unique<Function>(sin_,-10,10,p, number_of_points, x_scale, y_scale));
        break;
    case Functions_window::Log:
        shapes.push_back(make_unique<Function>(log_, -10, 10, p, number_of_points, x_scale, y_scale));
        break;
    default:
        return;
    }
    attach(shapes[shapes.size()-1]);
}
double Functions_window::next_scale(In_box&b)
{
    double sc = 0;
    if (b.last_result() == In_box::accepted) {
        string s = b.last_string_value();
        istringstream iss{ s };
        iss >> sc;
    }
    return sc;
}
Point Functions_window::next_position()
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
Functions_window::Functions_window(Application&p,int w, int h)
    :Window{ w,h,"Functions window" },
    app(&p),
    next_coordinates{ Point{0,0},70,20,"x y",[] { } },
    next_scale_x{ Point{0,h-60},70,20,"x scale",[] {} },
    next_scale_y{ Point{0,h-110},70,20,"y scale",[] {} },
    shape_buttons{ {w - 70,20},70,20,Menu::vertical,"shapes" },
    quit_button{ Point{w - 70,0}, 70, 20, "Quit", [this] { quit(); } },
    x_ax{Axis::x,{50,h/2},w-100,10},
    y_ax{ Axis::y,{w/2,h -50},h - 100,10 }
{
    shape_buttons.attach(make_unique<Button>(Point{ 0,0 }, 0, 0, "Log",
        [this] {create_func(F_Type::Log); }));
    shape_buttons.attach(make_unique<Button>(Point{ 0,0 }, 0, 0, "Sin",
        [this] {create_func(F_Type::Sin); }));
    attach(shape_buttons);
    attach(next_coordinates);
    next_coordinates.show();
    next_coordinates.hide_buttons();
    attach(next_scale_x);
    next_scale_x.show();
    next_scale_x.hide_buttons();
    attach(next_scale_y);
    next_scale_y.show();
    next_scale_y.hide_buttons();
    attach(x_ax);
    attach(y_ax);
    attach(quit_button);
}

void Functions_window::quit()
{
    close();
    app->quit();
}

int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
    Functions_window win{app, 600,600 };
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