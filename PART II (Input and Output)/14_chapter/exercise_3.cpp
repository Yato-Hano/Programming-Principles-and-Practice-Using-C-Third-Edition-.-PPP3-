/*
[3]
Place an Image on top of a Button; move both when the button is pushed. Use this random
number generator from PPP__suppor t to pick a new location for the ‘‘image button’’:
inline int rand_int(int min, int max)
{
    static default_random_engine ran;
    return uniform_int_distribution<>{min,max}(ran);
}
It returns a random int in the range [min,max).
*/

#include "PPP/GUI.h"

using namespace Graph_lib;

inline int rand_int(int min, int max)
{
    static default_random_engine ran{ unsigned(time(0)) };
    return uniform_int_distribution<>{min, max}(ran);
}
struct W_image :Window
{
    W_image(int w, int h, const string& title);
private:
    void move_rand() { 
        int x = rand_int(-10, 10);
        int y = rand_int(-10, 10);
        im.move(x, y); bt.move(x, y); 
    };
    Image im;
    Button bt;
};
W_image::W_image(int w, int h, const string& title)
    :Window{w,h,title}, 
    bt{ {100,100},100,100,"",[this] {move_rand(); } },
    im{ {100,100},"image.jpg" }
{
    attach(bt);
    attach(im);
    im.scale(100, 100);
}
int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
    W_image win{ 600,400,"chapter 14" };
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