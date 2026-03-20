/*
[17]
Define a class Star. One parameter should be the number of points. Draw a few stars
with differing numbers of points, differing line colors, and differing fill colors.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"
#include <numbers>

using namespace Graph_lib;

class Star :public Shape
{
public:
    Star(Point center, int radius_outer, int radius_inner, int number_of_outer_points);
    void draw_specifics(Painter& painter) const override;
};
void Star::draw_specifics(Painter& painter) const
{
    painter.draw_polygon(*this);
}
Star::Star(Point center, int radius_outer, int radius_inner, int number_of_outer_points =3)
{
    double angleIncrement = (2.0 * std::numbers::pi) / number_of_outer_points;
    double currentAngle = -std::numbers::pi / 2.0; // Start at the top point

    for (int i = 0; i < number_of_outer_points; ++i)
    {
        // Outer point
        int x_outer = center.x + radius_outer * cos(currentAngle);
        int y_outer = center.y + radius_outer * sin(currentAngle);
        add({ x_outer, y_outer });

        // Inner point
        currentAngle += angleIncrement / 2.0;
        int x_inner = center.x + radius_inner * cos(currentAngle);
        int y_inner = center.y + radius_inner * sin(currentAngle);
        add({ x_inner, y_inner });

        // Move to the next outer point angle
        currentAngle += angleIncrement / 2.0;
    }
}




int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };

    Star st{ {200,200},100,20 };
    Star st2{ {300,200},100,20,5 };
    Star st3{ {400,200},100,20,10 };

    st.set_color(Color::blue);
    st2.set_color(Color::magenta);
    st3.set_color(Color::yellow);

    st.set_fill_color(Color::black);
    st2.set_fill_color(Color::cyan);
    st3.set_fill_color(Color::white);

    win.attach(st);
    win.attach(st2);
    win.attach(st3);

    win.wait_for_button();
}
