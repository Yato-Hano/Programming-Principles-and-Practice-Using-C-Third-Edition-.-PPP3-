/*
[4]
Draw a 3-by-3 tic-tac-toe board of alternating white and red squares.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"4" };

    Point p1_start{ 50,50 };
    constexpr int side_length{ 50 };

    Rectangle r1{ p1_start ,side_length ,side_length };
    Rectangle r2{ {p1_start.x,p1_start.y+ side_length} ,side_length ,side_length};
    Rectangle r3{ {p1_start.x,p1_start.y + (side_length*2)} ,side_length ,side_length };

    Rectangle r4{ {p1_start.x+ side_length,p1_start.y} ,side_length ,side_length };
    Rectangle r5{ {p1_start.x + side_length,p1_start.y + side_length} ,side_length ,side_length };
    Rectangle r6{ {p1_start.x + side_length,p1_start.y + (side_length * 2)} ,side_length ,side_length };

    Rectangle r7{ {p1_start.x + (side_length * 2),p1_start.y} ,side_length ,side_length };
    Rectangle r8{ {p1_start.x + (side_length * 2),p1_start.y + side_length} ,side_length ,side_length };
    Rectangle r9{ {p1_start.x + (side_length * 2),p1_start.y + (side_length * 2)} ,side_length ,side_length };

    r1.set_fill_color(Color::white);
    r3.set_fill_color(Color::white);
    r5.set_fill_color(Color::white);
    r7.set_fill_color(Color::white);
    r9.set_fill_color(Color::white);

    r2.set_fill_color(Color::red);
    r4.set_fill_color(Color::red);
    r6.set_fill_color(Color::red);
    r8.set_fill_color(Color::red);

    win.attach(r1);
    win.attach(r2);
    win.attach(r3);
    win.attach(r4);
    win.attach(r5);
    win.attach(r6);
    win.attach(r7);
    win.attach(r8);
    win.attach(r9);

    win.wait_for_button();
}
