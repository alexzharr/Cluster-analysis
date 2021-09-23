//Zharikov Alexey 211

#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class MyPoint
{
private:
	double x, y, f;
	int id;
	static int point_count;
public:
	MyPoint();
	MyPoint(double x, double y);
	MyPoint(const MyPoint& v);
	const MyPoint& operator=(const MyPoint& v);
	friend MyPoint operator+(const MyPoint& v, const MyPoint& u);
	friend MyPoint operator-(const MyPoint& v, const MyPoint& u);
	friend MyPoint operator*(double lambda, const MyPoint& v);
	friend MyPoint operator*(const MyPoint& v, double lambda);
	double length();
	void setX(double coord_x) { x = coord_x; }
	void setY(double coord_y) { y = coord_y; }
	void setF(double coord_f) { f = coord_f; }
	void setID(int n) { id = n; }
	double getX() { return x; }
	double getY() { return y; }
	double getF() { return f; }
	int getID() { return id; }
	static int getCount() { return point_count; }
	void printToFile(ofstream& f, int mode);
	~MyPoint();
};

