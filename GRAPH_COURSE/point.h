#pragma once
#include <iostream>
#include "graphics.h"

using namespace std;

class point
{
	public:
		void set_to(float x, float y, float z);
		void setn(int name);
		void setx(float x);//������� �������� ���������
		void sety(float y);
		void setz(float z);
		void shift_by(float x, float y, float z);
		//void setdx(float x);//������� ��������� ���������
		//void setdy(float y);
		void set_2d();//��������� ��������� ���������
		//void set_2d(point* anchor, float scale, float xang, float yang, float zang);//��������� ��������� ��������� � ������ ���������� �����/������/����/������

		int getn();
		float getx();//�������
		float gety();
		float getz();
		float getdx();//������� ��������� ���������
		float getdy();

		//�������� � �������
		void movx(float shift = 10);//�������� �� ��� X
		void movy(float shift = 10);//�������� �� ��� Y
		void movz(float shift = 10);//�������� �� ��� Z

		void resize(point* anchor, float scale);
		void rotate(point* anchor, float xang, float yang, float zang);
		void rotate(float* x1, float* y1, float* x2, float* y2, float angle);

		void refresh();

		void typeout();//����������� � �������
		void display();//����������� �� ��������

		point();
		point(point* one, point* two, point* three);//������� ����� ���������� ��� �����
		point(int name, float x, float y, float z);
		~point();
	private:
		int name;
		float x;//�������� ����������
		float y;
		float z;
		float dx;//2� ����������
		float dy;
};

