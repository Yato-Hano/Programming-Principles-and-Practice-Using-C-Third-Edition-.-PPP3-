/*
[10]
Draw the source file diagram from §10.8.1.
*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;
struct Arrow {
    Point p1, p2, p3;
};
Arrow get_arrow(Point p1, Point p2)
{
   const double dx = p2.x - p1.x;
   const double dy = p2.y - p1.y;
   const double angle = std::atan2(dy, dx);

   constexpr double arrow_length{ 15 };
   constexpr double arrow_angle{ 0.3 };

   const int x3 = p2.x - arrow_length * std::cos(angle + arrow_angle);
   const int y3 = p2.y - arrow_length * std::sin(angle + arrow_angle);

   const int x4 = p2.x - arrow_length * std::cos(angle - arrow_angle);
   const int y4 = p2.y - arrow_length * std::sin(angle - arrow_angle);

   return Arrow{ p2,{x3,y3},{x4,y4} };
}
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"10_chapter" };

    constexpr int font_size{ 14 }, r_width{ font_size * 20 }, r_height{ font_size * 2 };
    constexpr int middle_of_rect{ r_width / 2 };

    Text t1_1{ {0,0},"Point.h:" };
    Text t1_2{ {0,font_size},"struct Point{...};" };
    Rectangle r1{ t1_2.point(0), r_width,r_height };
    r1.set_fill_color(Color::yellow);
    t1_1.set_color(Color::blue);
    t1_2.set_color(Color::blue);
    //
    Text t2_1{ {0,70},"Graph.h:" };
    Text t2_2{ {0,t2_1 .point(0).y+10 + font_size},"struct Shape { ... };"};
    Rectangle r2{ t2_2.point(0), r_width,r_height };

    r2.set_fill_color(Color::yellow);
    t2_1.set_color(Color::blue);
    t2_2.set_color(Color::blue);

    Line l1{ {r1.point(0).x + middle_of_rect,r2.point(0).y }, Point{r1.point(0).x+ middle_of_rect,r1.point(0).y+ r_height } };
    Arrow a1{ get_arrow(l1.point(0),l1.point(1))};
    Closed_polyline cp1{ a1.p1,a1.p2,a1.p3 };
    cp1.set_fill_color(Color::black);
    //
    Text t3_1{ {250,50},"Window.h:" };
    Text t3_2{ {t3_1.point(0).x,t3_1.point(0).y + font_size},"struct Window { ... };" };
    Rectangle r3{ t3_2.point(0), r_width,r_height };

    r3.set_fill_color(Color::yellow);
    t3_1.set_color(Color::blue);
    t3_2.set_color(Color::blue);

    Line l3{ {r3.point(0).x + middle_of_rect,r3.point(0).y }, Point{r1.point(0).x + middle_of_rect,r1.point(0).y + r_height } };
    Arrow a3{ get_arrow(l3.point(0),l3.point(1)) };
    Closed_polyline cp3{ a3.p1,a3.p2,a3.p3 };
    cp3.set_fill_color(Color::black);

    //
    Text t4_1{ {350,100},"GUI.h:" };
    Text t4_2{ {t4_1.point(0).x,t4_1.point(0).y + font_size},"struct Button { ... };" };
    Rectangle r4{ t4_2.point(0), r_width,r_height };
    Line l4{ {r4.point(0).x + middle_of_rect,r4.point(0).y }, Point{r3.point(0).x + middle_of_rect,r3.point(0).y + r_height } };
    Arrow a4{ get_arrow(l4.point(0),l4.point(1)) };
    Closed_polyline cp4{ a4.p1,a4.p2,a4.p3 };
    cp4.set_fill_color(Color::black);
    r4.set_fill_color(Color::yellow);
    t4_1.set_color(Color::blue);
    t4_2.set_color(Color::blue);
    //
    Text t5_1{ {250,150},"Simple_window.h:" };
    Text t5_2{ {t5_1.point(0).x,t5_1.point(0).y + font_size},"struct Simple_window { ... };" };
    Rectangle r5{ t5_2.point(0), r_width,r_height };
    Line l5{ {r5.point(0).x + middle_of_rect,r5.point(0).y }, Point{r4.point(0).x + middle_of_rect,r4.point(0).y + r_height } };
    Arrow a5{ get_arrow(l5.point(0),l5.point(1)) };
    Closed_polyline cp5{ a5.p1,a5.p2,a5.p3 };
    
    cp5.set_fill_color(Color::black);
    r5.set_fill_color(Color::yellow);
    t5_1.set_color(Color::blue);
    t5_2.set_color(Color::blue);
    //
    Text t6_1{ {200,250},"Ch10.cpp:" };
    Text t6_2{ {t6_1.point(0).x,t6_1.point(0).y + font_size},"int main() { ... }" };
    Rectangle r6{ t6_2.point(0), r_width,r_height };
    Line l6{ {r6.point(0).x + middle_of_rect,r6.point(0).y }, Point{r5.point(0).x + middle_of_rect,r5.point(0).y + r_height } };
    Arrow a6{ get_arrow(l6.point(0),l6.point(1)) };
    Closed_polyline cp6{ a6.p1,a6.p2,a6.p3 };

    Line l7{ {r6.point(0).x + middle_of_rect,r6.point(0).y }, Point{r2.point(0).x + middle_of_rect,r2.point(0).y + r_height } };
    Arrow a7{ get_arrow(l7.point(0),l7.point(1)) };
    Closed_polyline cp7{ a7.p1,a7.p2,a7.p3 };

    cp7.set_fill_color(Color::black);

    cp6.set_fill_color(Color::black);
    r6.set_fill_color(Color::yellow);
    t6_1.set_color(Color::blue);
    t6_2.set_color(Color::blue);
    //
    win.attach(l7);
    win.attach(cp7);

    win.attach(l6);
    win.attach(cp6);
    win.attach(r6);
    win.attach(t6_1);
    win.attach(t6_2);

    win.attach(l5);
    win.attach(cp5);
    win.attach(r5);
    win.attach(t5_1);
    win.attach(t5_2);

    win.attach(l4);
    win.attach(cp4);
    win.attach(r4);
    win.attach(t4_1);
    win.attach(t4_2);

    win.attach(l3);
    win.attach(cp3);
    win.attach(r3);
    win.attach(t3_1);
    win.attach(t3_2);

    win.attach(l1);
    win.attach(cp1);
    win.attach(r1);
    win.attach(t1_1);
    win.attach(t1_2);

    win.attach(r2);
    win.attach(t2_1);
    win.attach(t2_2);

    win.wait_for_button();
}
