/*
[5]
Draw a red 1/4-inch frame around a rectangle that is three-quarters the height of your
screen and two-thirds the width.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    constexpr int width_mm{ 300 }, height_mm{ 160 };
    constexpr int width_pixels{ 1920 }, height_pixels{ 1080 };
    constexpr double width_in{ width_mm / 25.4 }, height_in{ height_mm / 25.4 };//inches
    constexpr double width_PPI{ width_pixels / width_in };// pixels per inch
    Simple_window win{ {0,0},width_pixels,height_pixels,"chapter" };

    Rectangle r( {10,10},width_pixels * (2 / 3.0),height_pixels * (3 / 4.0));
    Rectangle frame({ 0,0 }, r.width()+20, r.height()+20);

    frame.set_style(Line_style(Line_style::solid, width_PPI*1/4.0));
    win.attach(r);
    win.attach(frame);

    r.set_fill_color(Color::blue);
    win.wait_for_button();
}
