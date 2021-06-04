//Zharikov Alexey 211

#pragma once
#include <vector>
#include "MyPoint.h"
using namespace std;

class MyBuffer
{
private:
	double b_x, b_y;
public:
	vector<MyPoint*>b_p;

	MyBuffer();
	void setX(double coord_x) { b_x = coord_x; }
	void setY(double coord_y) { b_y = coord_y; }
	double getX() { return b_x; }
	double getY() { return b_y; }
	void shiftCloud(double s_x, double s_y);
	void turnCloud(double a);
	void scaleCloud(double sc);
};

