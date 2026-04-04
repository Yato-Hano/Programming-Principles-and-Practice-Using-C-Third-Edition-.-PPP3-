/*
[8]
Here is a collection of heights in centimeters together with the number of people in a
group of that height (rounded to the nearest 5cm): (170,7), (175,9), (180,23), (185,17),
(190,6), (195,1). How would you graph that data? If you can’t think of anything better,
do a bar graph. Remember to provide axes and labels. Place the data in a file and read it
from that file.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

struct Height_People
{
    int height;
    int people;
};

istream& operator>>(istream& o, Height_People& hp)
{
    return o >> hp.height >> hp.people;
}

vector<Height_People> read(string file_name)
{
    ifstream ifs{ file_name };
    if (!ifs)throw exception{ "No file" };
    vector<Height_People> hp;
    for (Height_People i; ifs>>i;)
    {
        hp.push_back(i);
    }
    return hp;
}
class Scale {
    int cbase;
    int vbase;
    double scale;
public:
    Scale(int b, int vb, double s) :cbase{ b }, vbase{ vb }, scale{ s } {}
    int operator()(double v) const { return cbase + (v-vbase)*scale; }
};
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    constexpr int xmax = 600;
    constexpr int ymax = 600;

    constexpr int x_orig = 50;
    constexpr int y_orig = ymax -50;

    constexpr Point orig{ x_orig,y_orig };

    Simple_window win{ Point{100,100},xmax,ymax,"Graph" };

    constexpr int xlength = xmax-100;
    constexpr int ylength = ymax-100;

    constexpr int r_min_height = 150;
    constexpr int r_max_height = 200;

    constexpr int r_min_people = 0;
    constexpr int r_max_people = 50;

    constexpr int x_scale = xlength / (r_max_height - r_min_height);
    constexpr int y_scale = ylength / (r_max_people - r_min_people);

    constexpr int x_notches = (r_max_height - r_min_height) / 10;
    constexpr int y_notches = (r_max_people - r_min_people) / 10;

    Axis x{ Axis::x,orig, xlength,  x_notches,
        "height | 1==10cm | 200cm max" };
    Axis y{ Axis::y,orig, ylength, y_notches,
        "N of people | 1==10 people| 50 people max" };
    Text zero{ orig ,"(0 people,150 cm)" };
    
    ofstream ofs{ "out_scale.txt" }; // for testing
    ofs << x_scale << ' ' << y_scale << '\n'
        << x_notches << ' ' << y_notches <<endl;

    Scale x_sc{ x_orig ,r_min_height ,x_scale };
    Scale y_sc{ y_orig ,r_min_people ,-y_scale };

    vector<Height_People> r{read("height_people.txt")};
    Vector_ref<Rectangle>vr;

    for (int i = 0; i < r.size(); i++)
    {
        vr.push_back(make_unique<Rectangle>(
            Point{ x_sc(r[i].height) ,y_sc(r[i].people) }
            ,Point{ x_sc(r[i].height)+ x_scale * 5,orig.y } ));//rounded to the nearest 5cm
        vr[i].set_fill_color(Color::blue);
        win.attach(vr[i]);
    }
    win.attach(zero);
    win.attach(x);
    win.attach(y);
    win.wait_for_button();
}
