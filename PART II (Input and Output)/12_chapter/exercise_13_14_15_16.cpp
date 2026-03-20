/*
[13]
Define a Binar y_tree class derived from Shape. Giv e the number of levels as a parameter (lev-
els==0 means no nodes, levels==1 means one node, levels==2 means one top node with two
sub-nodes, levels==3 means one top node with two sub-nodes each with two sub-nodes, etc.).
Let a node be represented by a small circle. Connect the nodes by lines (as is conventional).
P.S. In computer science, trees conventionally grow downward from a top node (amusingly,
but logically, often called the root).
[14]
Modify Binar y_tree to draw its nodes using a virtual function. Then, derive a new class from
Binar y_tree that overrides that virtual function to use a different representation for a node
(e.g., a triangle).
[15]
Modify Binar y_tree to take a parameter (or parameters) to indicate what kind of line to use to
connect the nodes (e.g., an arrow pointing down or a red arrow pointing up). Note how this
exercise and the last use two alternative ways of making a class hierarchy more flexible and
useful.
[16]
Add an operation to Binar y_tree that adds text to a node. You may have to modify the design
of Binar y_tree to implement this elegantly. Choose a way to identify a node; for example,
you might give a string "lrrlr" for navigating left, right, right, left, and right down a binary tree
(the root node would match both an initial l and an initial r).
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

class Arrow :public Line {
public:
    Arrow(Point start, Point arrow_here);
    void draw_specifics(Painter& painter) const override;
};
class Binary_tree :public Shape
{
public:
    enum Direction{no_arrow,arrow_down,arrow_up};
    Binary_tree(Point root,int levels, Direction );
    const vector<Point>& get_points()const { return nodes; }
    const vector<pair<Point, Point>>& get_lines()const { return lines; }
    int get_node_size()const { return node_size; }
    void draw_specifics(Painter& painter) const override;
    void set_label(int, string);
protected:
    Direction arrow_direction;
private:
    int node_size{ 10 };
    int levels;
    vector<string>lables;
    vector<Point>nodes;// points are here to prevent adding points from derived classes
    vector<pair<Point,Point>>lines;
    void generate_points(Point xy, int lvl);
    void generate_nodes(Point xy, int lvl,int horizontal_s,int vertical_s, int depth);
};
void Binary_tree::set_label(int node, string lab)
{
    lables[node] = lab;
    redraw();
}
Binary_tree::Binary_tree(Point p, int lvls, Direction ar = no_arrow)
    :levels{lvls}, arrow_direction{ar}
{
    generate_points(p, lvls);
}
void Binary_tree::generate_points(Point p, int lvls)
{
    nodes.clear();
    lines.clear();
    if (lvls < 1)return;
    int horizontal_s = 30, vertical_s = 50;
    generate_nodes(p, lvls, horizontal_s, vertical_s,0);
    lables = vector<string>(nodes.size(), "");
}
void Binary_tree::generate_nodes(Point p, int lvls, int horizontal_space, int vertical_space, int depth)
{
    if (depth == lvls) return;
    ++depth;
   // add(p);
    nodes.push_back(p);
    int x = p.x - horizontal_space ;
    int y = p.y + vertical_space;
    if (depth != lvls)
         lines.push_back({ {p.x,p.y+ node_size},{x,y - node_size}});
    generate_nodes({ x,y }, lvls, horizontal_space, vertical_space, depth );
    x = p.x + horizontal_space ;
    if (depth  != lvls)
        lines.push_back({ {p.x,p.y + node_size},{x,y- node_size} });
    generate_nodes({ x,y }, lvls, horizontal_space, vertical_space, depth );
}

void Binary_tree::draw_specifics(Painter& painter) const
{
    if (color().visibility())
    {
        if (arrow_direction == no_arrow)
            for (size_t i = 0; i < lines.size(); i++)
                painter.draw_line(lines[i].first, lines[i].second);
        else
            if (arrow_direction == arrow_down)
                for (size_t i = 0; i < lines.size(); i++)
                    Arrow{ lines[i].first, lines[i].second }.draw_specifics(painter);
            else
                for (size_t i = 0; i < lines.size(); i++)
                    Arrow{ lines[i].second, lines[i].first }.draw_specifics(painter);

        for (size_t i = 0; i < nodes.size(); i++) {
            Circle{ nodes[i],node_size }.draw_specifics(painter);
            Text{nodes[i],lables[i] }.draw_specifics(painter);
        }
    }
}
//----------------------------------
Arrow::Arrow(Point p1, Point p2)
    :Line{ p1,p2 }
{
    const double dx = p2.x - p1.x;
    const double dy = p2.y - p1.y;
    const double angle = std::atan2(dy, dx);

    constexpr double arrow_length{ 15 };
    constexpr double arrow_angle{ 0.5 };

    const int x3 = p2.x - arrow_length * std::cos(angle + arrow_angle);
    const int y3 = p2.y - arrow_length * std::sin(angle + arrow_angle);

    const int x4 = p2.x - arrow_length * std::cos(angle - arrow_angle);
    const int y4 = p2.y - arrow_length * std::sin(angle - arrow_angle);

    Shape::add({ x3,y3 });
    Shape::add({ x4,y4 });
}
void Arrow::draw_specifics(Painter& painter) const
{
    painter.draw_line(point(0), point(1));
    painter.draw_polygon(Polygon{ point(1), point(2), point(3) }); // for fill color
}
//----------------------------------
class Rectangle_Binary_tree :public Binary_tree
{
public:
    using Binary_tree::Binary_tree;
    void draw_specifics(Painter& painter) const override;
private:
};
void Rectangle_Binary_tree::draw_specifics(Painter& painter) const
{
    if (color().visibility())
    {
        for (size_t i = 0; i < get_lines().size(); i++)
        {
            painter.draw_line(get_lines()[i].first, get_lines()[i].second);
        }
        for (size_t i = 0; i < get_points().size(); i++)
        {
            Point p{ get_points()[i] };
            int offset= get_node_size() / 2;
            Rectangle{{p.x- offset,p.y - offset} ,get_node_size(),get_node_size()}.draw_specifics(painter);
        }
    }
}
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
    Binary_tree bt{ {200,50},5,Binary_tree::arrow_up };
    bt.set_fill_color(Color::white);
    win.attach(bt);

    for (size_t i = 0; i < bt.get_node_size(); i++)
    {
        bt.set_label(i, "x");
        win.wait_for_button();
    }




}
