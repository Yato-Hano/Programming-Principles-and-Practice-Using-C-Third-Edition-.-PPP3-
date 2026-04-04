/*
[7]
Using the techniques developed in the previous exercises, make an image of an airplane ‘‘fly
around’’ in a window. Hav e a ‘‘Start’’ and a ‘‘Stop’’ button.
*/

#include "PPP/GUI.h"

using namespace Graph_lib;

struct Flying_image_W :Window
{
    Flying_image_W(Application& a,int w, int h, Image& plane);
private:
    Application* app;
    int side{ 200 };
    Image& plane_im;
    Button fly;
    Button stop;
    Button close;
    bool fly_switch{ false };
    void fly_until_button();
};
void Flying_image_W::fly_until_button()
{
   static int sign_x{ 1 };
   static int sign_y{ 1 };
    while (fly_switch)
    {
        Point p= plane_im.point(0);

        if (x_max()<p.x + side)sign_x = -sign_x;
        else
            if (p.x <0)sign_x = -sign_x;

        if (y_max()<p.y + side )sign_y = -sign_y;
        else
            if (p.y < 0)sign_y = -sign_y;

        plane_im.move(5* sign_x, 5* sign_y);
        timer_wait(10);
    }
}
Flying_image_W::Flying_image_W(Application& a, int w, int h, Image& plane)
    :Window{w,h,"Flying plane"},
    app{&a},
    plane_im{plane},
    fly{ {w - 80,10},70,20,"Fly",[this] {fly_switch = true; fly_until_button(); } },
    stop{ {w - 80,40},70,20,"Stop",[this] {fly_switch = false;  } },
    close{ {w - 80,40 + 30},70,20,"Close",[this] {fly_switch = false; Window::close(); app->quit();  } }

{
    plane_im.scale(side, side,false);
    attach(plane_im);
    attach(fly);
    attach(stop);
    attach(close);
}

int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
    Image plane{ {0,0},"plane.jpg" };
    Flying_image_W win{app,600,400,plane };
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