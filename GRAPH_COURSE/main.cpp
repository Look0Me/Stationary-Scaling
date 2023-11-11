#define _USE_MATH_DEFINES // для C++
#include <cmath>
#include "graphics.h"
#include <iostream>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <math.h>
#include "point.h"
#include "polygon.h"

#define delt 50 //Shift
#define ang 30 //Angle
#define rsz 50  //Resize percent
#define sang 27 
#define fill_in 1
using namespace std;
//Переделано под классы
//void Move(float* cor1, float* cor2, float* cor3, float* cor4, float* cor5, int mode)
//{
//    switch (mode) {
//    case 0:
//        (*cor1) += delt;
//        (*cor2) += delt;
//        (*cor3) += delt;
//        (*cor4) += delt;
//        (*cor5) += delt;
//        break;
//    case 1:
//        (*cor1) -= delt;
//        (*cor2) -= delt;
//        (*cor3) -= delt;
//        (*cor4) -= delt;
//        (*cor5) -= delt;
//        break;
//    }
//}


void Resize(float* x1, float* y1, float* z1, float* x2, float* y2, float* z2, int
    mode) {
    float dx = (*x2) - (*x1);
    float dy = (*y2) - (*y1);
    float dz = (*z2) - (*z1);
    switch (mode) {
    case 0:
        dx *= static_cast<float>(100 + rsz) / static_cast<float>(100);
        dy *= static_cast<float>(100 + rsz) / static_cast<float>(100);
        dz *= static_cast<float>(100 + rsz) / static_cast<float>(100);
        break;
    case 1:
        dx *= static_cast<float>(100 - rsz) / static_cast<float>(100);
        dy *= static_cast<float>(100 - rsz) / static_cast<float>(100);
        dz *= static_cast<float>(100 - rsz) / static_cast<float>(100);
        break;
    }
    (*x2) = (*x1) + (dx);
    (*y2) = (*y1) + (dy);
    (*z2) = (*z1) + (dz);
}


void Rotate(float* x1, float* y1, float* x2, float* y2, int mode)
{
    int coq = 0;
    float an = 0;
    float dx = static_cast<float>((*x2) - (*x1));
    float dy = static_cast<float>((*y2) - (*y1));
    float L = sqrt(pow(dx, 2) + pow(dy, 2));
    if ((*x1) == (*x2) && (*y1) == (*y2))
        return;

    if (dy <= 0)
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
        an = atan(1) * 4 + an;
    switch (mode)
    {
    case 0:
        an += ang * atan(1) * 4 / 180;
        break;
    case 1:
        an -= ang * atan(1) * 4 / 180;
        break;
    }
    (*x2) = (*x1) + (L * cos(an));
    (*y2) = (*y1) - (L * sin(an));
}
// линейная закраска
void horver(float* x1, float* y1, float* x2, float* y2, float* x3, float* y3)
{
    if (fill_in)
    {
        //Переменные, в которых хранятся граничные значения фигуры; Координаты средней точки по оси Х
        float tp = 0, bot = 0, lft = 0, rght = 0, midlx = 0, midly = 0;
        tp = min(min((*y1), (*y3)), min((*y1), (*y2)));
        bot = max(max((*y1), (*y3)), max((*y1), (*y2)));
        lft = min(min((*x1), (*x3)), min((*x1), (*x2)));
        rght = max(max((*x1), (*x3)), max((*x1), (*x2)));
        //Переменные для координат точек 1, 2, 3, считая сверху вниз
        float topx = 0, topy = 0, midx = 0, midy = 0, botx = 0, boty = 0; //Переменные для координат точек 1, 2, 3, считая сверху вниз
        //Х-координаты для закрашивающей прямой; переменная для перемещения прошлой двойки между собой
        float pt1 = 0, pt2 = 0, ptv = 0, d1 = 0, d2 = 0;
        int cho = 0; //Переменная для свитч-кейса закраски
        //Жонглируем координатами относительно вертикальной оси
        {
            if ((*y1) == tp)
            {
                topx = (*x1);
                topy = (*y1);
                //cout << "A is top\n";
            }
            else if ((*y1) == bot)
            {
                botx = (*x1);
                boty = (*y1);
                //cout << "A is bot\n";
            }
            else
            {

                midx = (*x1);
                midy = (*y1);
                //cout << "A is mid\n";
            }
            //------------------------------
            if ((*y2) == tp)
            {
                topx = (*x2);
                topy = (*y2);
                //cout << "B is top\n";
            }
            else if ((*y2) == bot)
            {
                botx = (*x2);
                boty = (*y2);
                //cout << "B is bot\n";
            }
            else
            {
                midx = (*x2);
                midy = (*y2);
                //cout << "B is mid\n";
            }
            //------------------------------
            if ((*y3) == tp)
            {
                topx = (*x3);
                topy = (*y3);
                //cout << "C is top\n";
            }
            else if ((*y3) == bot)
            {
                botx = (*x3);
                boty = (*y3);
                //cout << "C is bot\n";
            }
            else
            {
                midx = (*x3);
                midy = (*y3);
                //cout << "C is mid\n";
            }
            //------------------------------
        }
        //Находим среднюю точку относительно оси Х
        {
            if (((*x1) != lft) && ((*x1) != rght))
            {
                midlx = (*x1);
                midly = (*y1);
                //cout << "A mid\n";
            }
            if (((*x2) != lft) && ((*x2) != rght))
            {
                midlx = (*x2);
                midly = (*y2);
                //cout << "B mid\n";
            }
            if (((*x3) != lft) && ((*x3) != rght))
            {
                midlx = (*x3);
                midly = (*y3);
                //cout << "C mid\n";
            }
        }
        for (int i = ceil(topy); i < ceil(midy); i++)//Закрашиваем верхнюю половину треугольника
        {
            cho = 0; //Очищаем свитч-кейс переменную
            pt1 = ((i - topy) / (midy - topy)) * (midx - topx) + topx; //Находим пересечение 1
            pt2 = ((i - topy) / (boty - topy)) * (botx - topx) + topx; //Находим пересечение 2
            if (pt1 > pt2)//Ставим их слева направо
            {
                ptv = pt1;
                pt1 = pt2;
                pt2 = ptv;
            }

            if (pt1 < lft)//Если полученный Х выходит за крайние значения, заменяемкрайним значением
                pt1 = lft;
            if (pt2 > rght)
                pt2 = rght;
            d1 = abs(midlx - pt1); //Находим, какой конец закрашивающей прямой сидит ближе к средней по Х точке
            d2 = abs(midlx - pt2);
            if (d1 < d2) //Если левый конец ближе к средней точке...
            {
                //Если счётчик высоты равен Y координате средней по Х точки и левая точка для закраски левее ценральной...
                if ((i == round(midly)) && (pt1 < midlx))
                {
                    if (i <= round(tp)) //Если счётчик высоты совпадает или меньше верхней точки...
                    {
                        cho = 3; //Не чертим эту линию
                        /* setcolor(4);
                        linus(round(midlx-5), i-1, round(midlx), i-1);
                        setcolor(fillc);*/
                    }
                    else
                        cho = 1; //Чертим линию, но вместо pt1 используем midlx
                    /*linus(midlx, 0 ,midlx,900);*/
                }
            }
            else //Если правый конец ближе к средней точке...
            {
                //Если счётчик высоты равен Y координате средней по Х точки и правая точка для закраски правее ценральной...
                if ((i == round(midly)) && (pt2 > midlx))
                {
                    if (i <= round(tp)) //Если счётчик высоты совпадает или меньше верхней точки...
                    {
                        cho = 3; //Не чертим эту линию
                        /*setcolor(4);
                        linus(round(midlx + 5), i-1, round(midlx), i-1);

                        setcolor(fillc);*/
                    }
                    else
                        cho = 2; //Чертим линию, но вместо pt2 используем midlx
                    /*linus(midlx, 0, midlx, 900);*/
                }
            }
            switch (cho) //Свитч-кейс для закраски
            {
            case 1:
                line(round(midlx), i, round(pt2), i);
                /*//cout << "1\n";*/
                break;
            case 2:
                line(round(pt1), i, round(midlx), i);
                /*//cout << "2\n";*/
                break;
            case 3:
                /*//cout << "3\n";*/
                break;
            default:
                line(round(pt1), i, round(pt2), i);
                break;
            }
        }
        //Закрашиваем нижнюю половину треугольника (тут меньше комментов,пушо происходит почти то же самое)
        for (int i = ceil(midy); i < floor(boty); i++)
        {
            cho = 0;
            pt1 = ((i - midy) / (boty - midy)) * (botx - midx) + midx;
            pt2 = ((i - topy) / (boty - topy)) * (botx - topx) + topx;
            if (pt1 > pt2)//Ставим их слева направо
            {
                ptv = pt1;
                pt1 = pt2;
                pt2 = ptv;
            }

            if (pt1 < lft)//Если полученный Х выходит за крайние значения, заменяем крайним значением
                pt1 = lft;
            if (pt2 > rght)
                pt2 = rght;
            d1 = abs(midlx - pt1);
            d2 = abs(midlx - pt2);
            if (d1 < d2)
            {
                if ((i == round(midly)) && (pt1 < midlx))
                {
                    if (i >= round(bot))
                    {
                        cho = 3;
                        //setcolor(4);
                        /*linus(round(midlx - 20), i+1, round(midlx), i+1);*/
                       // setcolor(fillc);
                    }
                    else
                        cho = 1;
                    /*linus(midlx, 0, midlx, 900);*/
                }
            }
            else
            {
                if ((i == round(midly)) && (pt2 > midlx))
                {
                    if (i >= round(bot))
                    {
                        cho = 3;
                        //setcolor(0);
                        ///*linus(round(midlx + 20), i+1, round(midlx), i+1);*/
                        ////setcolor(fillc);
                    }
                    else
                        cho = 2;
                    /*linus(midlx, 0, midlx, 900);*/
                }
            }
            switch (cho)
            {
            case 1:
                line(round(midlx), i, round(pt2), i);
                //cout << "1\n";
                break;
            case 2:
                line(round(pt1), i, round(midlx), i);
                //cout << "2\n";
                break;
            case 3:
                //cout << "3\n";
                break;
            default:
                line(round(pt1), i, round(pt2), i);
                break;
            }
        }
    }
}

void cent(float* x1, float* y1, float* z1, float* x2, float* y2, float* z2, float* x3,
    float* y3, float* z3, float* x, float* y, float* z)
{
    *(x) = (*(x1)+*(x2)+*(x3)) / 3;
    *(y) = (*(y1)+*(y2)+*(y3)) / 3;
    *(z) = (*(z1)+*(z2)+*(z3)) / 3;
}
//перегрузка для нижней грани
void cent(float* x1, float* y1, float* z1, float* x2, float* y2, float* z2, float* x3,
    float* y3, float* z3, float* x4, float* y4, float* z4, float* x, float* y, float* z)
{
    *(x) = (*(x1)+*(x2)+*(x3)+*(x4)) / 4;
    *(y) = (*(y1)+*(y2)+*(y3)+*(y4)) / 4;
    *(z) = (*(z1)+*(z2)+*(z3)+*(z4)) / 4;
}
void bubbleSort(float list[], int list2[], int list3[], int listLength)
{
    while (listLength--)
    {
        bool swapped = false;
        for (int i = 0; i < listLength; i++)
        {
            if (list[i] > list[i + 1])
            {
                swap(list[i], list[i + 1]);
                swap(list2[i], list2[i + 1]);
                swap(list3[i], list3[i + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}

float trueL(float* x1, float* y1, float* z1, float* x2, float* y2, float* z2)
{
    float dx = ((*x2) - (*x1));
    float dy = ((*y2) - (*y1));
    float dz = ((*z2) - (*z1));
    float L = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
    return L;
}
//грани рисуем 
void trin(float* x1, float* y1, float* x2, float* y2, float* x3, float* y3)
{
    line(*(x1), *(y1), *(x2), *(y2));
    line(*(x3), *(y3), *(x2), *(y2));
    line(*(x1), *(y1), *(x3), *(y3));
}
//квадрат рисуем
void square(float* x1, float* y1, float* x2, float* y2, float* x3, float* y3, float* x4, float* y4)
{
    line(*(x1), *(y1), *(x2), *(y2));
    line(*(x3), *(y3), *(x2), *(y2));
    line(*(x1), *(y1), *(x4), *(y4));
    line(*(x3), *(y3), *(x4), *(y4));
}

void shoot(float* x1, float* y1, float* x2, float* y2, float* x3, float* y3, float* x4,
    float* y4, float* x5, float* y5, int list[], int list2[])
{
    for (int i = 0; i < 5; i++)
    {
        switch (list[i])
        {
        case 0:
            if (list2[i])
            {
                setcolor(1);
                horver(x1, y1, x2, y2, x5, y5);
                setcolor(15);
                trin(x1, y1, x2, y2, x5, y5);
            }
            cout << "125" << endl;
            break;
        case 1:
            if (list2[i])
            {
                setcolor(2);
                horver(x2, y2, x3, y3, x5, y5);
                setcolor(15);
                trin(x5, y5, x2, y2, x3, y3);
            }
            cout << "235" << endl;
            break;
        case 2:
            if (list2[i])
            {
                setcolor(3);
                horver(x3, y3, x4, y4, x5, y5);
                setcolor(15);
                trin(x3, y3, x4, y4, x5, y5);
            }
            cout << "345" << endl;
            break;
        case 3:
            if (list2[i])
            {
                setcolor(4);
                horver(x1, y1, x4, y4, x5, y5);
                setcolor(15);
                trin(x1, y1, x4, y4, x5, y5);
            }
            cout << "145" << endl;
            break;
        case 4:
            if (list2[i])
            {
                setcolor(5);
                horver(x1, y1, x2, y2, x3, y3);
                horver(x1, y1, x4, y4, x3, y3);
                setcolor(15);
                square(x1, y1, x2, y2, x3, y3, x4, y4);
            }
            cout << "1234" << endl;
            break;
        }
    }
}

int facing(float cx, float cy, float cz, float x, float y, float z)
{
    float sx = 50, sy = 125, sz = 50;
    float ex = 155.905, ey = 219.776, ez = 97.9757;

    float ax = ex - sx, ay = ey - sy, az = ez - sz;
    float bx = x - cx, by = y - cy, bz = z - cz;

    float cosa = (ax * bx + ay * by + az * bz) / (sqrt(pow(ax, 2) + pow(ay, 2) + pow(az, 2)) * sqrt(pow(bx, 2) + pow(by, 2) + pow(bz, 2)));
    float anger = acos(cosa) * 180 / M_PI;

    cout << "cosa = " << cosa << endl;
    cout << "anger = " << anger << endl;
    if (cosa < 0.0001)
        return 0;
    return 1;
}

void face_for(float x1, float y1, float z1, float x2, float y2, float z2,
    float x3, float y3, float z3, float x4, float y4, float z4,
    float x5, float y5, float z5, float x, float y, float z, int list[])
{
    list[0] = facing(x, y, z, x1, y1, z1);
    list[1] = facing(x, y, z, x2, y2, z2);
    list[2] = facing(x, y, z, x3, y3, z3);
    list[3] = facing(x, y, z, x4, y4, z4);
    list[4] = facing(x, y, z, x5, y5, z5);
}

void measure(float* x1, float* y1, float* z1, float* x2, float* y2, float* z2, float* x3,
    float* y3, float* z3, float* x4, float* y4, float* z4, float* x5, float* y5, float* z5, int list[], int list2[])
{
    float cx1, cx2, cx3, cx4, cx5; //центральные точки граней
    float cy1, cy2, cy3, cy4, cy5;
    float cz1, cz2, cz3, cz4, cz5;
    cent(x1, y1, z1, x2, y2, z2, x5, y5, z5, &cx1, &cy1, &cz1);//125 определение средних точек граней
    cent(x5, y5, z5, x2, y2, z2, x3, y3, z3, &cx2, &cy2, &cz2);//235
    cent(x4, y4, z4, x3, y3, z3, x5, y5, z5, &cx3, &cy3, &cz3);//345
    cent(x4, y4, z4, x5, y5, z5, x1, y1, z1, &cx4, &cy4, &cz4);//145
    cent(x4, y4, z4, x3, y3, z3, x1, y1, z1, x2, y2, z2, &cx5, &cy5, &cz5);//1234
    float cx = (*x1 + *x2 + *x3 + *x4 + *x5) / 5;
    float cy = (*y1 + *y2 + *y3 + *y4 + *y5) / 5; //определение средней точки пирамиды
    float cz = (*z1 + *z2 + *z3 + *z4 + *z5) / 5;


    //точка для сравнения граней 
    float x0 = cx - 105905;
    float y0 = cy - 94776; //
    float z0 = cz - 47975;

    //определение, повёрнута ли грань лицом к наблюдателю
    face_for(cx1, cy1, cz1, cx2, cy2, cz2, cx3, cy3, cz3, cx4, cy4, cz4, cx5, cy5, cz5, cx, cy, cz, list2);
    float faceord[5]{};
    list[0] = 0;
    list[1] = 1;
    list[2] = 2;
    list[3] = 3;
    list[4] = 4;
    faceord[0] = trueL(&cx, &cy, &cz, &cx1, &cy1, &cz1);//125   заполнение массива дальности граней от наблюдателя
    faceord[1] = trueL(&cx, &cy, &cz, &cx2, &cy2, &cz2);//235
    faceord[2] = trueL(&cx, &cy, &cz, &cx3, &cy3, &cz3);//345
    faceord[3] = trueL(&cx, &cy, &cz, &cx4, &cy4, &cz4);//145
    faceord[4] = trueL(&cx, &cy, &cz, &cx5, &cy5, &cz5);//1234
    bubbleSort(faceord, list, list2, 5); //сортировка массивов face и facefor при помощи сортировки массива faceord
}


void Show_figure(float x1, float y1, float z1, float x2, float y2, float z2,
    float x3, float y3, float z3, float x4, float y4, float z4, float x5, float y5, float z5)
{
    float x0 = 800;
    float y0 = 400;

    float xf1;
    float xf2;
    float xf3;
    float xf4;
    float xf5;

    float yf1;
    float yf2;
    float yf3;
    float yf4;
    float yf5;

    //расчёт двумерных X координат точек
    xf1 = x0 - x1 * cos(sang * M_PI / 180) + y1;
    xf2 = x0 - x2 * cos(sang * M_PI / 180) + y2;
    xf3 = x0 - x3 * cos(sang * M_PI / 180) + y3;
    xf4 = x0 - x4 * cos(sang * M_PI / 180) + y4;
    xf5 = x0 - x5 * cos(sang * M_PI / 180) + y5;

    //расчёт двумерных Y координат точек
    yf1 = y0 - z1 + x1 * sin(sang * M_PI / 180);
    yf2 = y0 - z2 + x2 * sin(sang * M_PI / 180);
    yf3 = y0 - z3 + x3 * sin(sang * M_PI / 180);
    yf4 = y0 - z4 + x4 * sin(sang * M_PI / 180);
    yf5 = y0 - z5 + x5 * sin(sang * M_PI / 180);
    int face[5]{};//массив, в котором хранятся номера граней
    int facefor[5]{};//массив, в котором обозначается, какая грань находится спереди

    //тут мы рассчитываем в каком порядке выводить грани при помощи алгоритма художника
    measure(&x1, &y1, &z1, &x2, &y2, &z2, &x3, &y3, &z3, &x4, &y4, &z4, &x5, &y5, &z5, face, facefor);

    //вывод граней на экран
    shoot(&xf1, &yf1, &xf2, &yf2, &xf3, &yf3, &xf4, &yf4, &xf5, &yf5, face, facefor);
}


void Menu()
{
    outtextxy(20, 20, "Choose action:");
    outtextxy(20, 40, "The end");
    outtextxy(20, 60, "X+");
    outtextxy(20, 80, "X-");
    outtextxy(20, 100, "Y+");
    outtextxy(20, 120, "Y-");
    outtextxy(20, 140, "Z+");
    outtextxy(20, 160, "Z-");
    outtextxy(20, 180, "Bigger");
    outtextxy(20, 200, "Smaller");
    outtextxy(20, 220, "X rotation +");
    outtextxy(20, 240, "X rotation -");
    outtextxy(20, 260, "Y rotation +");
    outtextxy(20, 280, "Y rotation -");
    outtextxy(20, 300, "Z rotation +");
    outtextxy(20, 320, "Z rotation -");
}



int main()
{
    int choice = 0;
    initwindow(1300, 800);

    setcolor(WHITE);

    Menu();
    //Show_figure(..................);
    float x = 0;
    float y = 0;
    float z = 0;
    point a(1, x, y, z);
    /*point b(2, x + 30, y, z);
    point c(3, x, y + 30, z);*/
   /* a.typeout();
    b.typeout();
    c.typeout();*/
    polygon d;
    d.display();
    d.typeout();
    while (true)
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int MX = mousex();
            int MY = mousey();

            if (MX >= 20 && MX <= 76 && MY >= 40 && MY <= 60)
                choice = 0;
            else if (MX >= 20 && MX <= 40 && MY >= 60 && MY <= 80)
                choice = 1;
            else if (MX >= 20 && MX <= 40 && MY >= 80 && MY <= 100)
                choice = 2;
            else if (MX >= 20 && MX <= 40 && MY >= 100 && MY <= 120)
                choice = 3;
            else if (MX >= 20 && MX <= 40 && MY >= 120 && MY <= 140)
                choice = 4;
            else if (MX >= 20 && MX <= 40 && MY >= 140 && MY <= 160)
                choice = 5;
            else if (MX >= 20 && MX <= 40 && MY >= 160 && MY <= 180)
                choice = 6;
            else if (MX >= 20 && MX <= 70 && MY >= 180 && MY <= 200)
                choice = 7;
            else if (MX >= 20 && MX <= 75 && MY >= 200 && MY <= 220)
                choice = 8;
            else if (MX >= 20 && MX <= 110 && MY >= 220 && MY <= 240)
                choice = 9;
            else if (MX >= 20 && MX <= 105 && MY >= 240 && MY <= 260)
                choice = 10;
            else if (MX >= 20 && MX <= 110 && MY >= 260 && MY <= 280)
                choice = 11;
            else if (MX >= 20 && MX <= 105 && MY >= 280 && MY <= 300)
                choice = 12;
            else if (MX >= 20 && MX <= 110 && MY >= 300 && MY <= 320)
                choice = 13;
            else if (MX >= 20 && MX <= 105 && MY >= 320 && MY <= 340)
                choice = 14;
            else
                choice = 15;

            switch (choice)
            {
            case 1: //x+
                d.movx(10);
                break;
            case 2: //x-
                d.movx(-10);
                break;
            case 3: //y+
                d.movy(10);
                break;
            case 4: //y-
                d.movy(-10);
                break;
            case 5: //z+
                d.movz(10);
                break;
            case 6: //z-
                d.movz(-10);
                break;
            case 7: //bigger
                //d.set_to(100, 100, 0);
                d.resize(&a, 25);
                break;
            case 8: //smaller
                d.resize(&a, -25);
                break;
            case 9: // x rotate+
                d.rotX(30);
                break;
            case 10: // x rotate-
                d.rotX(-30);
                break;
            case 11:// y rotate+
                d.rotY(30);
                break;
            case 12:// y rotate-
                d.rotY(-30);
                break;
            case 13:// z rotate+
                d.rotZ(30);
                break;
            case 14:// z rotate-
                d.rotZ(-30);
                break;
            case 15://click on screen

                break;

            default:
                system("cls");
                cleardevice();
                closegraph();
                return 0;
                break;
            }
            system("cls");
            cleardevice();
            cout << choice << endl;
            
            /*a.movz();
            b.movx();
            c.movy();
            
            a.type_out();
            b.type_out();
            c.type_out();*/

            /*a.display();
            b.display();
            c.display();*/

            //d.refresh(&a, &b, &c);
            a.refresh();
            circle(a.getdx(),a.getdy(),3);
            d.typeout();
            d.display();
            //Show_figure(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5);

            Menu();

            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}
