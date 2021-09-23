//Zharikov Alexey 211

#pragma once
#include <vector>
#include "MyPoint.h"

class MyCloud
{
private:
	static int cloud_count;
	double m_x, m_y;
	double d_x, d_y;
public:
	vector<MyPoint*>pts;
	MyCloud();
	MyCloud(double mx, double my, double dx, double dy, int count);
	static int getCount() { return cloud_count; }
	void setX(double coord_x) { m_x = coord_x; }
	void setY(double coord_y) { m_y = coord_y; }
	double getX() { return m_x; }
	double getY() { return m_y; }
	~MyCloud();
};

