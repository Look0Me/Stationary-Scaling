#define _USE_MATH_DEFINES 
#include "point.h"

void point::set_to(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void point::setn(int name)
{
    this->name = name;
}

void point::setx(float x)
{
    this->x = x;
}

void point::sety(float y)
{
    this->y = y;
}

void point::setz(float z)
{
    this->z = z;
}

void point::shift_by(float x, float y, float z)
{
    movx(x);
    movy(y);
    movz(z);
}

//void point::setdx()
//{
//    float cix = 500;//нулевой X на экране
//    this->dx = cix - this->x * cos(30 * M_PI / 180) + this->y * cos(30 * M_PI / 180);
//}
//
//void point::setdy()
//{
//    float ciy = 150;//нулевой Y на экране
//    this->dy = ciy + this->x * sin(30 * M_PI / 180) + this->y * sin(30 * M_PI / 180) - this->z;
//}

void point::set_2d()
{
    float cix = 500;//нулевой X на экране
    float ciy = 150;//нулевой Y на экране

    this->dx = cix - this->x * cos(30 * M_PI / 180) + this->y * cos(30 * M_PI / 180);
    this->dy = ciy + this->x * sin(30 * M_PI / 180) + this->y * sin(30 * M_PI / 180) - this->z;
}


int point::getn()
{
    return this->name;
}

float point::getx()
{
    return this->x;
}

float point::gety()
{
    return this->y;
}

float point::getz()
{
    return this->z;
}

float point::getdx()
{
    return this->dx;
}

float point::getdy()
{
    return this->dy;
}

void point::movx(float shift)
{
    setx(getx() + shift);
    refresh();
}

void point::movy(float shift)
{
    sety(gety() + shift);
    refresh();
}

void point::movz(float shift)
{
    setz(getz() + shift);
    refresh();
}

void point::resize(point* anchor, float scale)
{
    float dx = this->x - anchor->x;
    float dy = this->y - anchor->y;
    float dz = this->z - anchor->z;

    dx *= scale / 100;
    dy *= scale / 100;
    dz *= scale / 100;

    this->x = anchor->x + dx;
    this->y = anchor->y + dy;
    this->z = anchor->z + dz;
}

void point::rotate(point* anchor, float xang, float yang, float zang)//сюда пихаем ВСЁ, чтобы расчитать углы на всех осях
{
    rotate(&anchor->x, &anchor->y, &this->x, &this->y, zang);
    rotate(&anchor->x, &anchor->z, &this->x, &this->z, yang);
    rotate(&anchor->z, &anchor->y, &this->z, &this->y, xang);
}

void point::rotate(float* x1, float* y1, float* x2, float* y2, float angle)//сюда пихаются указатели на отдельные координаты точек для каждой оси
{
    int coq = 0;
    float an = 0;
    float dx = (*x2) - (*x1);
    float dy = (*y2) - (*y1);
    float L = sqrt(pow(dx, 2) + pow(dy, 2));
    if ((*x1) == (*x2) && (*y1) == (*y2))
        return;

    /*if (dy <= 0)
    {
        if (dx >= 0)
            coq = 1;
        else
            coq = 2;
    }
    else
    {
        if (dx >= 0)
            coq = 4;
        else
            coq = 3;
    }
    if (dx >= dy)
        an = acos(dx / L);
    else
        an = asin(dy / L);
    if (coq == 3)
        an += atan(1) * 4;
    else if (coq == 4)
        an = atan(1) * 8 - an;
    else if ((coq == 2) && (an == 0))
        an = atan(1) * 4;
    else if ((coq == 2) && (an < 0))
        an = atan(1) * 4 + an;*/
    
    an = angle * M_PI / 180;

    (*x2) = (*x1) + (L * cos(an));
    (*y2) = (*y1) - (L * sin(an));
}

void point::refresh()
{
    set_2d();
}

void point::typeout()
{
    cout << getn() << ": " << getx() << " " << gety() << " " << getz() << endl;
    cout << "dx = " << getdx() << " dy = " << getdy() << endl;
}

void point::display()
{
    refresh();
    circle(this->dx, this->dy,2);
}

point::point()
{
    this->name = 0;
    setx(0);
    sety(0);
    setz(0);
    set_2d();
    /*setdx();
    setdy();*/
}

point::point(point* one, point* two, point* three)
{
    this->setx((one->getx() + two->getx() + three->getx()) / 3);
    this->sety((one->gety() + two->gety() + three->gety()) / 3);
    this->setz((one->getz() + two->getz() + three->getz()) / 3);
}

point::point(int name, float x, float y, float z)
{
    this->name = name;
    setx(x);
    sety(y);
    setz(z);
    set_2d();
    /*setdx();
    setdy();*/
}

point::~point()
{
    cout << "Point " << this->name << "said 'bye!'" << endl;
}
