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
		polygon(point* one, point* two, point* three);//������������
		void set();

		void shift_by(float dx, float dy, float dz);
		void set_to(float x, float y, float z);

		void refresh(point* one, point* two, point* three);//���������� ���������
		void refresh(point* anchor, point* one, point* two, point* three);
		void set_cent();//������ ������
		void set_anc(point* anchor = nullptr);
		//void set_dcent();//������ ���������� ������
		void setn();//������ �����
		void set_2d();//��������� ��������� ���������

		float getcx();//������� ������ �����
		float getcy();
		float getcz();
		float getdcx();//������� ��������� ���������
		float getdcy();

		//�������� � ������
		void movx(float shift = 10);//�������� �� ��� X
		void movy(float shift = 10);//�������� �� ��� Y
		void movz(float shift = 10);//�������� �� ��� Z

		void resize(float scale);//��������� ������� ������ ������������ ������
		void resize(point* anchor, float scale);//��������� ������� ������ �����-�����

		void rotX(float angle);//��������� ���� �������� �� ��� X
		void rotY(float angle);//��������� ���� �������� �� ��� Y
		void rotZ(float angle);//��������� ���� �������� �� ��� Z

		//void scale(point* anchor, int percent = 10);


		void typeout();//����� ������ � �������
		void display();//����� �� �����
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

