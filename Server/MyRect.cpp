//Zharikov Alexey 211

#include "MyRect.h"
#include <ctime>
#include "MyPoint.h"

int MyRect::rect_count = 0;

MyRect::MyRect()
{
	rect_count++;
}

MyRect::MyRect(double mx, double my, double len, double wid, int count) :
	m_x(mx), m_y(my), length(len), width(wid), points_num(count)
{
	double x_shift, y_shift;
	srand(time(0));
	for (int i = 0; i < count; i++)
	{
		x_shift = len * (((double)rand() / RAND_MAX) - 0.5);
		y_shift = width * (((double)rand() / RAND_MAX) - 0.5);
		MyPoint* p = new MyPoint(mx + x_shift, my + y_shift);
		pts.push_back(p);
	}
	rect_count++;
}

MyRect::~MyRect()
{
	rect_count--;
}
