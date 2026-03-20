/*
[11] 
Define a Group to be a container of Shapes with suitable operations applied to the various
members of the Group. Hint: Vector_ref. Use a Group to define a checkers (draughts) board
where pieces can be moved under program control.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

class Group : public Vector_ref<Shape>
{
public:
    void attach_to_window(Simple_window&);
    void move(int ,int);
    void set_color(Color);
    void set_fill_color(Color);
};
void  Group::attach_to_window(Simple_window& w)
{
    for (int i = 0; i < size(); i++)
    {
        w.attach(this->operator[](i));
    }
}
void Group::move(int dx,int dy)
{
    for (int i = 0; i < size(); i++)
    {
        this->operator[](i).move(dx, dy);
    }
}
void Group::set_color(Color c)
{
    for (int i = 0; i < size(); i++)
    {
        this->operator[](i).set_color(c);
    }
}
void Group::set_fill_color(Color c)
{
    for (int i = 0; i < size(); i++)
    {
        this->operator[](i).set_fill_color(c);
    }
}

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},1000,800,"chapter" };

    constexpr int square{ 60 }, board_size{ 8 };
    Group board;

    for (int y = 0;y < board_size; y++)
    {
        for (int x = 0; x < board_size; x++)
        {
            board.push_back(make_unique<Rectangle>(Point{ x * square,y * square }, square, square));

            if ((x + y) % 2 == 0) 
                board[(board.size() - 1)].set_fill_color(Color::white);
            else 
                board[(board.size() - 1)].set_fill_color(Color::dark_green);

        }
    }
    
    Group red_pieces;
    Group black_pieces;
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < board_size; x++)
        {
            if ((x + y) % 2 == 1)
            {
                red_pieces.push_back(make_unique<Circle>(Point{ x * square+ square/2,y * square + square / 2 }, 
                    square/2-5));
                red_pieces[(red_pieces.size() - 1)].set_fill_color(Color::red);
            }
            else
            {
                black_pieces.push_back(make_unique<Circle>(Point{ x * square + square / 2,y * square + square / 2 },
                    square / 2 - 5));
                black_pieces[(black_pieces.size() - 1)].set_fill_color(Color::black);
            }
        }
    }
    board.attach_to_window(win);
    red_pieces.attach_to_window(win);
    black_pieces.attach_to_window(win);
    win.wait_for_button();
    red_pieces.move(square, square);
    win.wait_for_button();
}
