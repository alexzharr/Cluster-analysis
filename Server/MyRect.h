//Zharikov Alexey 211

#pragma once
#include <vector>
#include "MyPoint.h"

class MyRect
{
private:
	static int rect_count;
	int points_num;
	double m_x, m_y;
	double length, width;
public:
	vector<MyPoint*>pts;
	MyRect();
	MyRect(double mx, double my, double len, double wid, int count);
	static int getCount() { return rect_count; }
	void setX(double coord_x) { m_x = coord_x; }
	void setY(double coord_y) { m_y = coord_y; }
	void setLen(double rect_len) { length = rect_len; }
	void setWid(double rect_wid) { width = rect_wid; }
	double getX() { return m_x; }
	double getY() { return m_y; }
	double getLen() { return length; }
	double getWidth() { return width; }
	~MyRect();
};

