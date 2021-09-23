//Zharikov Alexey 211

#include "MyBuffer.h"

MyBuffer::MyBuffer()
{
	b_p = {};
}

void MyBuffer::shiftCloud(double s_x, double s_y)
{
	b_x += s_x; b_y += s_y;
	for (int i = 0; i < b_p.size(); i++)
	{
		b_p[i]->setX(b_p[i]->getX() + s_x);
		b_p[i]->setY(b_p[i]->getY() + s_y);
	}
}

void MyBuffer::turnCloud(double a)
{
	double x, y;
	for (int i = 0; i < b_p.size(); i++)
	{
		x = b_p[i]->getX();
		y = b_p[i]->getY();
		b_p[i]->setX(b_x + (x - b_x) * cos(a) - (y - b_y) * sin(a));
		b_p[i]->setY(b_y + (x - b_x) * sin(a) + (y - b_y) * cos(a));
	}
}

void MyBuffer::scaleCloud(double sc)
{
	for (int i = 0; i < b_p.size(); i++)
	{
		b_p[i]->setX(b_x + sc * (b_p[i]->getX() - b_x));
		b_p[i]->setY(b_y + sc * (b_p[i]->getY() - b_y));
	}
}

