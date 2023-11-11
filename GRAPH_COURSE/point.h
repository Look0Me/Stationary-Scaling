#pragma once
#include <iostream>
#include "graphics.h"

using namespace std;

class point
{
	public:
		void set_to(float x, float y, float z);
		void setn(int name);
		void setx(float x);//сеттеры истинных координат
		void sety(float y);
		void setz(float z);
		void shift_by(float x, float y, float z);
		//void setdx(float x);//сеттеры двумерных координат
		//void setdy(float y);
		void set_2d();//установка двумерных координат
		//void set_2d(point* anchor, float scale, float xang, float yang, float zang);//установка двумерных координат с учётом параметров грани/фигуры/неба/Аллаха

		int getn();
		float getx();//геттеры
		float gety();
		float getz();
		float getdx();//геттеры двумерных координат
		float getdy();

		//ДЕЙСТВИЯ С ТОЧКАМИ
		void movx(float shift = 10);//движение по оси X
		void movy(float shift = 10);//движение по оси Y
		void movz(float shift = 10);//движение по оси Z

		void resize(point* anchor, float scale);
		void rotate(point* anchor, float xang, float yang, float zang);
		void rotate(float* x1, float* y1, float* x2, float* y2, float angle);

		void refresh();

		void typeout();//отображение в консоли
		void display();//отображение на мониторе

		point();
		point(point* one, point* two, point* three);//создает точку посередине трёх точек
		point(int name, float x, float y, float z);
		~point();
	private:
		int name;
		float x;//истинные координаты
		float y;
		float z;
		float dx;//2Д координаты
		float dy;
};

