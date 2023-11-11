#pragma once
#define _USE_MATH_DEFINES 
#include <math.h>
#include "point.h"
#include <stdlib.h>


using namespace std;

class polygon
{
	public:
		polygon();
		polygon(point* one, point* two, point* three);//конструкторы
		void set();

		void shift_by(float dx, float dy, float dz);
		void set_to(float x, float y, float z);

		void refresh(point* one, point* two, point* three);//перезапись координат
		void refresh(point* anchor, point* one, point* two, point* three);
		void set_cent();//сеттер центра
		void set_anc(point* anchor = nullptr);
		//void set_dcent();//сеттер двумерного центра
		void setn();//сеттер имени
		void set_2d();//установка двумерных координат

		float getcx();//геттеры центра грани
		float getcy();
		float getcz();
		float getdcx();//геттеры двумерных координат
		float getdcy();

		//ƒ≈…—“¬»я — √–јЌ№ё
		void movx(float shift = 10);//движение по оси X
		void movy(float shift = 10);//движение по оси Y
		void movz(float shift = 10);//движение по оси Z

		void resize(float scale);//изменение размера вокруг собственного центра
		void resize(point* anchor, float scale);//изменение размера вокруг точки-€кор€

		void rotX(float angle);//изменение угла поворота по оси X
		void rotY(float angle);//изменение угла поворота по оси Y
		void rotZ(float angle);//изменение угла поворота по оси Z

		//void scale(point* anchor, int percent = 10);


		void typeout();//вывод данных в консоль
		void display();//вывод на экран
		/*void type_one();
		void type_two();
		void type_three();*/

		~polygon();
	private:
		int name;
		float xsh;
		float ysh;
		float zsh;
		float scale;
		float xang;
		float yang;
		float zang;
		point anchor;
		point centre;
		point one;
		point two;
		point three;
};

