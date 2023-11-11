#include "polygon.h"


polygon::polygon()
{
	set();
	this->name = 0;
	this->scale = 100;
	this->xang = 0;
	this->yang = 0;
	this->zang = 0;
	this->xsh = 0;
	this->ysh = 0;
	this->zsh = 0;
}

polygon::polygon(point* one, point* two, point* three)
{
	this->name = 0;

	this->scale = 100;
	this->xang = 0;
	this->yang = 0;
	this->zang = 0;
	this->xsh = 0;
	this->ysh = 0;
	this->zsh = 0;

	refresh(one, two, three);

	this->setn();
}

void polygon::set()
{
	this->one.set_to(0, 0, 0);
	this->one.setn(1);

	this->two.set_to(30, 0, 0);
	this->two.setn(2);

	this->three.set_to(0, 30, 0);
	this->three.setn(3);
}

void polygon::shift_by(float dx, float dy, float dz)
{
	this->one.movx(dx);
	this->two.movx(dx);
	this->three.movx(dx);

	this->one.movy(dy);
	this->two.movy(dy);
	this->three.movy(dy);

	this->one.movz(dz);
	this->two.movz(dz);
	this->three.movz(dz);

	this->set_cent();
	this->set_anc();
}

void polygon::set_to(float x, float y, float z)
{
	float dx = x - this->centre.getx();
	float dy = y - this->centre.gety();
	float dz = z - this->centre.getz();

	shift_by(dx, dy, dz);
}

void polygon::refresh(point* one, point* two, point* three)
{
	this->one.setn(one->getn());
	this->one.setx(one->getx());//устанавливаем точку один
	this->one.sety(one->gety());
	this->one.setz(one->getz());

	this->two.setn(two->getn());
	this->two.setx(two->getx());//устанавливаем точку два
	this->two.sety(two->gety());
	this->two.setz(two->getz());

	this->three.setn(three->getn());
	this->three.setx(three->getx());//устанавливаем точку три
	this->three.sety(three->gety());
	this->three.setz(three->getz());

	this->set_cent();
	this->set_anc();
	this->set_2d();//////////////////////////////////////////
}

void polygon::refresh(point* anchor, point* one, point* two, point* three)
{
	
	this->one.setn(one->getn());
	this->one.setx(one->getx());//устанавливаем точку один
	this->one.sety(one->gety());
	this->one.setz(one->getz());

	this->two.setn(two->getn());
	this->two.setx(two->getx());//устанавливаем точку два
	this->two.sety(two->gety());
	this->two.setz(two->getz());

	this->three.setn(three->getn());
	this->three.setx(three->getx());//устанавливаем точку три
	this->three.sety(three->gety());
	this->three.setz(three->getz());

	this->set_cent();
	this->set_2d();
}

void polygon::set_cent()
{
	this->centre.setx((this->one.getx() + this->two.getx() + this->three.getx()) / 3);
	this->centre.sety((this->one.gety() + this->two.gety() + this->three.gety()) / 3);
	this->centre.setz((this->one.getz() + this->two.getz() + this->three.getz()) / 3);

	this->centre.set_2d();
}

void polygon::set_anc(point* anchor)
{
	if (anchor != nullptr)
	{
		this->anchor.setx(anchor->getx());
		this->anchor.sety(anchor->gety());
		this->anchor.setz(anchor->getz());
	}
	else
	{
		this->anchor.setx(centre.getx());
		this->anchor.sety(centre.gety());
		this->anchor.setz(centre.getz());
	}
}

void polygon::setn()
{
	this->name = one.getn() * 100 + two.getn() * 10 + three.getn();
}

void polygon::set_2d()
{
	one.set_2d();
	two.set_2d();
	three.set_2d();
}

float polygon::getcx()
{
	return this->centre.getx();
}

float polygon::getcy()
{
	return this->centre.gety();
}

float polygon::getcz()
{
	return this->centre.getz();
}

float polygon::getdcx()
{
	return this->centre.getdx();
}

float polygon::getdcy()
{
	return this->centre.getdy();
}

void polygon::movx(float shift)
{
	one.movx(shift);
	two.movx(shift);
	three.movx(shift);
	xsh += shift * (100 / scale);
	set_cent();
	set_anc();
}

void polygon::movy(float shift)
{
	one.movy(shift);
	two.movy(shift);
	three.movy(shift);
	ysh += shift * (100 / scale);
	set_cent();
	set_anc();
}

void polygon::movz(float shift)
{
	one.movz(shift);
	two.movz(shift);
	three.movz(shift);
	zsh += shift * (100 / scale);
	set_cent();
	set_anc();
}

void polygon::resize(float scale)
{
	this->scale += scale;
	this->set();//ресетаем грань в стартовую позицию
	
	point temp(&this->one, &this->two, &this->three);//создаём временный центр

	float dx = this->centre.getx() - temp.getx();//находим разницу между текущим и временной серединами
	float dy = this->centre.gety() - temp.gety();
	float dz = this->centre.getz() - temp.getz();

	shift_by(dx, dy, dz);//возвращаем грань на старое место

	this->one.resize(&this->anchor, this->scale);
	this->two.resize(&this->anchor, this->scale);
	this->three.resize(&this->anchor, this->scale);

	cout << "Resized!!!" << endl;
}

void polygon::resize(point* anchor, float scale)
{
	this->scale += scale;
	this->set();//ресетаем грань в стартовую позицию
	this->set_cent();
	this->set_anc(anchor);
	this->centre.shift_by(this->xsh, this->ysh, this->zsh);
	point temp(&this->one, &this->two, &this->three);//создаём временный центр

	this->centre.resize(&this->anchor, this->scale);

	float dx = this->centre.getx() - temp.getx();//находим разницу между текущим и временной серединами
	float dy = this->centre.gety() - temp.gety();
	float dz = this->centre.getz() - temp.getz();

	shift_by(dx, dy, dz);//возвращаем грань на старое место

	this->one.resize(&this->centre, this->scale);
	this->two.resize(&this->centre, this->scale);
	this->three.resize(&this->centre, this->scale);

	this->set_cent();
	this->set_anc();

	cout << "Resized!!!" << endl;
}

void polygon::rotX(float angle)
{
	this->xang += angle;
}

void polygon::rotY(float angle)
{
	this->yang += angle;
}

void polygon::rotZ(float angle)
{
	this->zang += angle;
}

void polygon::typeout()
{
	one.typeout();
	two.typeout();
	three.typeout();
	centre.typeout();
	anchor.typeout();
	cout << "Face " << this->name << ": " << centre.getx() << " " << centre.gety() << " " << centre.getz() << endl;
	cout << "Scale: " << this->scale << endl;
	cout << "X axis angle: " << this->xang << " degrees" << endl;
	cout << "Y axis angle: " << this->yang << " degrees" << endl;
	cout << "Z axis angle: " << this->zang << " degrees" << endl<<endl;
	cout << "X shift: " << this->xsh << endl;
	cout << "Y shift: " << this->ysh << endl;
	cout << "Z shift: " << this->zsh << endl;
}

void polygon::display()
{
	one.refresh();
	two.refresh();
	three.refresh();
	centre.refresh();
	refresh(&this->one, &this->two, &this->three);
	circle(centre.getdx(), centre.getdy(),1);
	line(one.getdx(), one.getdy(), two.getdx(), two.getdy());
	line(one.getdx(), one.getdy(), three.getdx(), three.getdy());
	line(three.getdx(), three.getdy(), two.getdx(), two.getdy());
}

polygon::~polygon()
{
}
