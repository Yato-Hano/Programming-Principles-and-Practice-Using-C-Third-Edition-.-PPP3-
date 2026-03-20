/*

*/

#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

class Smiley :public Circle //happy
{
public:
    using Circle::Circle;
    void draw_specifics(Painter& painter) const override;

};
void Smiley::draw_specifics(Painter& painter) const
{
    Circle::draw_specifics(painter);
    int eye_r = radius() / 10;
    int eye_shift= 3* eye_r;
    painter.draw_ellipse({ center().x - eye_shift,center().y - eye_shift }, eye_r, eye_r);
    painter.draw_ellipse({ center().x + eye_shift,center().y - eye_shift }, eye_r, eye_r);
    Arc(Point( center().x,center().y + eye_shift ), eye_r*4, eye_r*2, -20, -160).draw_specifics(painter);
}

class Smiley_person :public Smiley //happy
{
public:
    using Smiley::Smiley;
    void draw_specifics(Painter& painter) const override;

};
void Smiley_person::draw_specifics(Painter& painter) const
{
    Smiley::draw_specifics(painter);
    painter.draw_ellipse({ center().x ,center().y- radius() }, int(radius() * 1.5), radius() / 2);
    painter.draw_rectangle({ center().x - int(radius()/1.5),center().y - radius() *2}, int(radius() * 1.5), radius());
}

class Frowny :public Circle // sad
{
public:
    using Circle::Circle;
    void draw_specifics(Painter& painter) const override;

};
void Frowny::draw_specifics(Painter& painter) const
{
    Circle::draw_specifics(painter);
    int eye_r = radius() / 10;
    int eye_shift = 3 * eye_r;
    painter.draw_ellipse({ center().x - eye_shift,center().y - eye_shift }, eye_r, eye_r);
    painter.draw_ellipse({ center().x + eye_shift,center().y - eye_shift }, eye_r, eye_r);
    Arc(Point(center().x, center().y + eye_shift*2), eye_r * 4, eye_r * 2, 20, 150).draw_specifics(painter);
}

class Frowny_person :public Frowny 
{
public:
    using Frowny::Frowny;
    void draw_specifics(Painter& painter) const override;

};
void Frowny_person::draw_specifics(Painter& painter) const
{
    Frowny::draw_specifics(painter);
    painter.draw_ellipse({ center().x ,center().y - radius() }, int(radius() * 1.5), radius() / 2);
    painter.draw_pie(Point( center().x - radius() /2 ,center().y - radius() *1.7 ),
        radius() ,   radius()*1.5, 
        0,2900);
}
int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Simple_window win{ {100,100},600,400,"chapter" };

    Smiley_person sm{ {100,100},50 };
    Frowny_person fr{ {300,100},50 };

    sm.set_fill_color(Color::white);
    fr.set_fill_color(Color::white);

    win.attach(fr);
    win.attach(sm);

    win.wait_for_button();
}
