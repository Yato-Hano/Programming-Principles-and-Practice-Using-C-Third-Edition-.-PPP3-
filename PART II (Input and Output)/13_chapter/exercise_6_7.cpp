/*
[6]
Design and implement a bar graph class. Its basic data is a vector<double> holding N val-
ues, and each value should be represented by a ‘‘bar’’ that is a rectangle where the height
represents the value.
[7]
Elaborate the bar graph class to allow labeling of the graph itself and its individual bars.
Allow the use of color.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

class Bar_graph :public Shape
{
public:
    Bar_graph(Point p, double x_scale,double y_scale);
    void draw_specifics(Painter& painter) const override;	
    vector<double>bars;
    vector<string>labels;
    string label;
private:
    double x_scale_ ,  y_scale_;
};
Bar_graph::Bar_graph(Point p, double x_scale = 25, double y_scale = 25)
    :x_scale_{ x_scale }, y_scale_{ y_scale }
{
    add(p);
}
void Bar_graph::draw_specifics(Painter& painter) const
{
    if (color().visibility())
    {
        Point p{ point(0) };
        painter.draw_text(Point(p.x-label.size()*14,p.y), label);
        for (int i = 0; i < bars.size(); i++)
        {
            Point pp = { p.x + int(i * x_scale_),p.y };
            painter.draw_rectangle(pp, x_scale_, bars[i] * -y_scale_);
                if (i < labels.size())
            painter.draw_text(pp, labels[i]);
        }
    }
}


int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
    Bar_graph bg{ {100,300} };
    bg.bars.push_back(8);
    bg.bars.push_back(5);
    bg.bars.push_back(1);
    bg.bars.push_back(-8);
    bg.labels.push_back("1");
    bg.labels.push_back("2");
    bg.labels.push_back("3");
    bg.label = "BARS";
    bg.set_fill_color(Color::blue);
    win.attach(bg);
    win.wait_for_button();
}
