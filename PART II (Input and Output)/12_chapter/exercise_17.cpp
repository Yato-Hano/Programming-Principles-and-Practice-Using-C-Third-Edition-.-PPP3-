/*
[17] 
Define a class Controller with four virtual functions on(), off(), set_level(int), and show().
Derive at least two classes from Controller. One should be a simple test class where show()
prints out whether the class is set to on or off and what is the current level. The second
derived class should somehow control the line color of a Shape; the exact meaning of ‘‘level’’
is up to you. Try to find a third ‘‘thing’’ to control with such a Controller class.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;
class Controller :public Shape
{
public:
    virtual void  on() { is_on = true; }
    virtual void off() { is_on = false; }
    virtual void set_level(int l) { lvl = l; }
    virtual void  show() const = 0;
protected: 
    bool is_on{ false };
    int lvl{ 0 };
};
class Controller_test :public Controller
{
public:
    void  show()const
    {
        if (is_on)
            cout<<"ON.";
        else
            cout << "OFF.";
        cout << "LVL=="<<lvl<<'.';
    }
    virtual void draw_specifics(Painter& painter) const
    {
        if(is_on)
            Text{ {20,20},"ON." }.draw_specifics(painter);
        else
            Text{ {20,20},"OFF." }.draw_specifics(painter);

        Text{ {50,20},"LVL=="+to_string(lvl)}.draw_specifics(painter);
    }
};

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
    Controller_test ct;
    ct.set_level(3);
    ct.on();
    win.attach(ct);
    win.wait_for_button();
}
