// Zharikov Alexey 211
#pragma once
#include "MyPoint.h"

class Triangle
{
private:
	MyPoint A, B, C;
	int id;
	int nei_triangle_id;
public:
	Triangle();
	Triangle(MyPoint a, MyPoint b, MyPoint c);
	Triangle(const Triangle& T);
	~Triangle() = default;
	const Triangle& operator=(const Triangle& T);
	MyPoint getA();
	MyPoint getB();
	MyPoint getC();
	int getID();
	int getNeiTriangleID();
	void assignA(MyPoint a);
	void assignB(MyPoint b);
	void assignC(MyPoint c);
	void assignID(int k);
	void assingNeiTriangleID(int k);
	void printTriangle(ofstream& file);
};
