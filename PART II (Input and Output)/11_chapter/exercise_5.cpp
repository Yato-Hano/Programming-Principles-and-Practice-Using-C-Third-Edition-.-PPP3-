/*
[5]
Make an RGB color chart (e.g., search the Web for ‘‘RGB color chart’’).
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
    Vector_ref<Rectangle> rgb_chart;

    const int max = 256;
    const int side = 5;
    for (int r = 0; r < max; r += side)
    {
        for (int g = 0; g < max; g += side)
        {
            for (int b = 0; b < max; b += side)
            {
                int x = r + b;
                int y = g ;
                rgb_chart.push_back(make_unique<Rectangle>(Point{ x,y}, side, side));
                rgb_chart[rgb_chart.size() - 1].set_fill_color(Color{ r,g, b });
                rgb_chart[rgb_chart.size() - 1].set_color(Color::invisible);
                win.attach(rgb_chart[rgb_chart.size() - 1]);// move to the next color
            }
        }
    }
    win.wait_for_button();
}
