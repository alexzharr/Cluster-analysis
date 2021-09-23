//Zharikov Alexey 211

#include "MyPoint.h"

int MyPoint::point_count = 0;

MyPoint::MyPoint()
{}

MyPoint::MyPoint(const MyPoint& v)
{
    x = v.x;
    y = v.y;
    f = v.f;
    id = v.id;
}

const MyPoint& MyPoint::operator=(const MyPoint& v)
{
    x = v.x;
    y = v.y;
    f = v.f;
    id = v.id;
    return *this;
}

MyPoint operator+(const MyPoint& v, const MyPoint& u)
{
    return MyPoint(v.x + u.x, v.y + u.y);
}

MyPoint operator-(const MyPoint& v, const MyPoint& u)
{
    return MyPoint(v.x - u.x, v.y - u.y);
}

MyPoint operator*(double lambda, const MyPoint& v)
{
    return MyPoint(lambda * v.x, lambda * v.y);
}

MyPoint operator*(const MyPoint& v, double lambda)
{
    return MyPoint(lambda * v.x, lambda * v.y);
}

double MyPoint::length() { return sqrt(x * x + y * y); }

MyPoint::MyPoint(double x_coord, double y_coord) :
	x(x_coord), y(y_coord), id(point_count)
{
	point_count++;
}

void MyPoint::printToFile(ofstream& f, int mode)
{
	if (mode == 0)
		f << x << ' ' << y << endl;
	else
		f << x << ' ' << y << ' ';
}

MyPoint::~MyPoint()
{
}
