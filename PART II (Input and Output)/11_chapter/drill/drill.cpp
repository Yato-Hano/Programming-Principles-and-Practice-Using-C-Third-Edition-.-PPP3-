/*
Drill
[1]
Make an 800-by-1000 Simple_window.
[2]
Put an 8-by-8 grid on the leftmost 800-by-800 part of that window (so that each square is 100
by 100).
[3]
Make the eight squares on the diagonal starting from the top left corner red (use Rectangle).
[4]
Find a 200-by-200-pixel image (JPEG or GIF) and place three copies of it on the grid (each
image covering four squares). If you can’t find an image that is exactly 200 by 200, use
set_mask() to pick a 200-by-200 section of a larger image. Don’t obscure the red squares.
[5]
Add a 100-by-100 image. Have it move around from square to square when you click the
‘‘Next’’ button. Just put wait_for_button() in a loop with some code that picks a new square
for your image.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},800,1000,"chapter 11 drill" };

    int x_size = win.x_max();
    int y_size = win.y_max()-200;
    constexpr int x_grid = 100;
    constexpr int y_grid = 100;

    Lines grid;
    for (int x = x_grid; x < x_size; x += x_grid)
        grid.add(Point{ x,0 }, Point{ x,y_size });
    for (int y = y_grid; y < y_size; y += y_grid)
        grid.add(Point{ 0,y }, Point{ x_size ,y });

    Vector_ref<Rectangle> squares;
    for (int xy = 0; xy < x_size; xy += x_grid)
    {
        squares.push_back(make_unique<Rectangle>(Point{ xy,xy }, x_grid, y_grid));
        win.attach(squares[squares.size() - 1]);
        squares[squares.size() - 1].set_fill_color(Color::red);
    }
    Image q{ {0,0},"q.png" };
    constexpr  bool not_to_keep_ratio = false;
    q.scale(x_grid, y_grid, not_to_keep_ratio);
    win.attach(q);
    win.attach(grid);

    for (int xy = 0; xy < x_size; xy += x_grid)
    {
        win.wait_for_button();
        q.move(x_grid, y_grid);
    }
   
}
