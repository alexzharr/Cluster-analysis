//Zharikov Alexey 211

#pragma once
#include <vector>
#include "MyPoint.h"
using namespace std;

class FormElement
{
private:
	double r;
	MyPoint center;
public:
	vector<MyPoint*>fe_p;

	FormElement();
	FormElement(MyPoint c, double radius);
	void setC(MyPoint c) { center = c; }
	void setR(double radius) { r = radius; }
	MyPoint getC() { return center; }
	double getR() { return r; }
};

