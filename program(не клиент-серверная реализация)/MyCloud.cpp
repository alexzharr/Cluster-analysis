//Zharikov Alexey 211

#include "MyCloud.h"
#include <ctime>
#include "MyPoint.h"

int MyCloud::cloud_count = 0;

MyCloud::MyCloud()
{
	cloud_count++;
}

MyCloud::MyCloud(double mx, double my, double dx, double dy, int count):
	m_x(mx), m_y(my), d_x(dx), d_y(dy)
{
	double x, y, x_shift, y_shift, r;

	srand(time(0));
	for (int i = 0; i < count; i++)
	{
		x_shift = 0; y_shift = 0;
		for (int j = 0; j < 100; j++)
		{
			r = (double)rand() / RAND_MAX;
			x_shift += (2 * r - 1) * 5 * dx;
		}
		for (int j = 0; j < 100; j++)
		{
			r = (double)rand() / RAND_MAX;
			y_shift += (2 * r - 1) * 5 * dy;
		}
		MyPoint* p = new MyPoint(mx + x_shift / 100, my + y_shift / 100);
		pts.push_back(p);
	}
	cloud_count++;
}

MyCloud::~MyCloud()
{
	cloud_count--;
}
