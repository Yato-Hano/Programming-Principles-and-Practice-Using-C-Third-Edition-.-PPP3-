/*
[6]
Make an ‘‘analog clock,’’ that is, a clock with hands that move. You get the time of day from
the operating system through a library call. Hint: chrono::now(), sleep().
*/

#include "PPP/GUI.h"
#include <numbers>
#include <chrono>
#include <thread>

using namespace Graph_lib;

Point get_point_on(const Circle& e, double angle_degree)
{
    double angle_radians{ angle_degree * (std::numbers::pi / 180.0) };
    int x = e.center().x + e.radius() * cos(angle_radians);
    int y = e.center().y + e.radius() * sin(angle_radians);
    return { x,y };
}
struct Analog_Clock :Circle
{
    Analog_Clock(Point center, int radius);
    void draw_specifics(Painter& painter) const override;
    void set_seconds(int seconds) { set_point(1, get_point_on(*this, (seconds * 6) - 90)); }
    void set_minutes(int minutes) { set_point(2, get_point_on(*this, (minutes * 6)-90)); }
    void set_hours(int hours) { set_point(3, get_point_on(*this, (hours * 30)-90)); }
private:
};
void Analog_Clock::draw_specifics(Painter& painter)const
{
    Circle::draw_specifics(painter);

    Line second_hand{ center(),point(1) };
    second_hand.set_color(Color::red);
    second_hand.draw(painter);

    Line minute_hand{ center(),point(2) };
    minute_hand.set_color(Color::blue);
    minute_hand.draw(painter);

    Line hour_hand{ center(),point(3) }; //black
    hour_hand.draw(painter);
}
Analog_Clock::Analog_Clock(Point center, int radius)
    :Circle{center,radius}
{
    set_fill_color(Color::white);
    add({ center.x,center .y-radius}); // seconds point(1)
    add({ center.x,center.y - radius }); // minutes point(2)
    add({ center.x,center.y - radius }); //hours point(3)
}

struct Clock_W :Window
{
    Clock_W(int w, int h);
    void set_clock();
private:
    Analog_Clock ac;
    Button start;
    Button stop;
};
void Clock_W::set_clock()
{
    //std::this_thread::sleep_for(std::chrono::seconds(1));

    auto now = std::chrono::system_clock::now();
    auto local_time_point = std::chrono::zoned_time{ std::chrono::current_zone(),now }.get_local_time();
    auto time_of_day = std::chrono::hh_mm_ss{ local_time_point.time_since_epoch() };

    int hours = time_of_day.hours().count();
    int minutes = time_of_day.minutes().count();
    int seconds = time_of_day.seconds().count();

    ac.set_seconds(seconds);
    ac.set_minutes(minutes);
    ac.set_hours(hours);
}
Clock_W::Clock_W(int w, int h)
    :Window{w,h,"Analog Clock"},
    ac{{150,200},100},
    start{ {w - 70,0},70,20,"Set Clock",[this] {set_clock(); } },
    stop{ {w - 70,30},70,20,"Close",[this] {close(); } }
{
    attach(ac);
    attach(start);
    attach(stop);
}
int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
    Clock_W win{ 600,400 };

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