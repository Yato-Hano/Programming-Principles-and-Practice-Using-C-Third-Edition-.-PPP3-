/*
[9]
Display an image on the screen, e.g., a photo of a friend. Label the image both with a
title on the window and with a caption in the window.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},800,600,"Tom Hanks" };
    
    Image tom_hanks{ {0,0},"Tom-Hanks.png" };
    Text label{ {0,0},"Tom Hanks" };

    win.attach(tom_hanks);
    win.attach(label);

    win.wait_for_button();
}
