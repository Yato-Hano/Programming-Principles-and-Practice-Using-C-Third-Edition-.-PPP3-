/*
[7]
Draw a two-dimensional house seen from the front, the way a child would: with a door,
two windows, and a roof with a chimney. Feel free to add details; maybe have ‘‘smoke’’
come out of the chimney.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},800,600,"chapter" };

    Rectangle house{ {250,250},300,300 };

    Closed_polyline roof;
    roof.add({ 250,250 });
    roof.add({ 400,150 });
    roof.add({ 250+300,250});

    Rectangle chimney{ {300,150},70,100 };

    Rectangle window1{ {300,300},70,100 };
    Rectangle window2{ {450,300},70,100 };

    Rectangle door{ {370,410},100,140 };

    chimney.set_fill_color(Color::yellow);
    roof.set_fill_color(Color::yellow);
    house.set_fill_color(Color::yellow);
    window1.set_fill_color(Color::white);
    window2.set_fill_color(Color::white);
    door.set_fill_color(Color::dark_yellow);

    win.attach(chimney);
    win.attach(roof);
    win.attach(house);
    win.attach(window2);
    win.attach(window1);
    win.attach(door);

    win.wait_for_button();
}
