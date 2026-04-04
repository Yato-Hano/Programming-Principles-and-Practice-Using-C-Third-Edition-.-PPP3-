/*
[1]
Make a My_window that’s a bit like Simple_window except that it has two buttons, next and
quit.
[2]
Make a window (based on My_window) with a 4-by-4 checkerboard of square buttons. When
pressed, a button performs a simple action, such as printing its coordinates in an output box,
or turns a slightly different color (until another button is pressed)
*/

#include "PPP/GUI.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

inline int rand_int(int min, int max)
{
    static default_random_engine ran{ unsigned(time(0)) };
    return uniform_int_distribution<>{min, max}(ran);
}

struct My_window :Simple_window
{
    My_window(Application& app, Point xy, int w, int h, const string& title);
private:
    Application* app_;
    Button quit_button;
    void quit();
};
My_window::My_window(Application&app,Point xy, int w, int h, const string& title)
    :Simple_window{xy,w,h,title} , app_(&app),
 quit_button(Point{ w - 70,40 }, 70, 20, "Quit", [this] {quit(); })
{
    attach(quit_button);
}
void My_window::quit()
{
    end_button_wait();
    app_->quit();
}

struct Checker_window :My_window
{
    Checker_window(Application& app, Point xy, int w, int h, const string& title);
private:
    //void change(int) {}
    Vector_ref<Rectangle>shapes;
    Vector_ref<Button>buttons;
};

Checker_window::Checker_window(Application& app, Point xy_wind,  int w, int h, const string& title)
    :My_window{ app,xy_wind,w,h,title }
{
    constexpr int size{ 50 };
    int position{0 };
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            shapes.push_back(make_unique<Rectangle>(Point{ x * size,y * size }, size, size));
            buttons.push_back(make_unique<Button>(Point{ x * size,y * size }, size, size,"",
                [this, position] {shapes[position].set_fill_color(rand_int(0, 250));}));
            attach(buttons[position]);
            attach(shapes[position]);
            ++position;
        }
    }
}
int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
    Checker_window win{app, {100,100},600,400,"chapter 14" };
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