/*
[2]
Define a class Fct that is just like Function except that it stores its constructor arguments.
Provide Fct with ‘‘reset’’ operations, so that you can use it repeatedly for different ranges,
different functions, etc.
[3]
Modify Fct from the previous exercise to take an extra argument to control precision or
whatever. Make the type of that argument a template parameter for extra flexibility.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

template<class Pressision>
class Fct_ :public Function 
{
    Pressision count_;//can't change number of points;
public:
    Fct_(std::function<double(double)> f, double r1, double r2, Point orig,
        Pressision count = 100, double xscale = 25, double yscale = 25);
    void reset() 
    {
        if (r2_ - r1_ <= 0) error("bad graphing range");
        if (count_ <= 0) error("non-positive graphing count");
        double dist = (r2_ - r1_) / count_;
        double r = r1_;
        for (Pressision i = 0; i < count_; ++i)
        {
            set_point(i,Point{ orig_.x + int(r * xscale_),orig_.y - int(fc_(r) * yscale_) });
            r += dist;
        }
        redraw();
    }
public:
    std::function<double(double)> fc_;
    double r1_ , r2_;
    Point orig_;
    double xscale_, yscale_;
};

template<class Pressision>
Fct_<Pressision>::Fct_(std::function<double(double)> f, double r1, double r2, Point xy, Pressision count, double xscale, double yscale)
    :Function{f,r1,r2,xy,int(count),xscale,yscale},fc_{f}
    ,r1_{r1},r2_{r2},orig_{xy},count_{count}, xscale_{xscale}, yscale_{yscale}
{

}
double slope(double x) { return 0.5 * x; }
double square(double x) { return x * x; }
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };
    Fct_<double> f{ slope ,-10,10,{300,200},200.5 };
    win.attach(f);
    win.wait_for_button();

    f.orig_={ 100,100 };
    f.reset();
    win.wait_for_button();
    f.fc_ = square;
    f.reset();
    win.wait_for_button();
}
