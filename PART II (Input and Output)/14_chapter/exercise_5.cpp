/*
[5]
Write a program that draws a shape of your choice and moves it to a new point each time you
click ‘‘Next.’’ The new point should be determined by a coordinate pair read from an input
stream.
*/

#include "PPP/GUI.h"

using namespace Graph_lib;

struct Moving_Shape_W :Window
{
    Moving_Shape_W(int, int, istream& coordinates);
    Circle circle;
private:
    istream& ist;
    Button next;
    void move();
};
void Moving_Shape_W::move()
{
    int x{}, y{}; 
    if (ist >> x >> y)
        circle.move(x - circle.point(0).x, y - circle.point(0).y);
    else
        Window::close();
}
Moving_Shape_W::Moving_Shape_W(int w, int h, istream& coordinates)
    :Window{w,h,"Moving Shape"}
    , circle{ {0,0},100 }
    , ist{coordinates}
    , next{ {w - 70,0},70,20,"Next",[this] {move(); } }
{
    attach(circle);
    attach(next);
}


int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
    ifstream ifs{ "input.txt" };
    Moving_Shape_W msw{ 600,600,ifs };
    msw.circle.set_fill_color(Color::blue);
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