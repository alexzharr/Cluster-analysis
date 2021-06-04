// Zharikov Alexey 211

#include "Triangle.h"

Triangle::Triangle() { A = B = C = MyPoint(0, 0); id = 0; }

Triangle::Triangle(MyPoint a, MyPoint b, MyPoint c) { A = a; B = b; C = c; id = 0; }

Triangle::Triangle(const Triangle& T) { A = T.A; B = T.B; C = T.C; id = T.id; nei_triangle_id = T.nei_triangle_id; }

const Triangle& Triangle::operator=(const Triangle& T)
{
	A = T.A; B = T.B; C = T.C; id = T.id; nei_triangle_id = T.nei_triangle_id;
	return *this;
}

MyPoint Triangle::getA() { return A; }

MyPoint Triangle::getB() { return B; }

MyPoint Triangle::getC() { return C; }

int Triangle::getID() { return id; }

int Triangle::getNeiTriangleID() { return nei_triangle_id; }

void Triangle::assignA(MyPoint a) { A = a; }

void Triangle::assignB(MyPoint b) { B = b; }

void Triangle::assignC(MyPoint c) { C = c; }

void Triangle::assignID(int k) { id = k; }

void Triangle::assingNeiTriangleID(int k) { nei_triangle_id = k; }

void Triangle::printTriangle(ofstream& file)
{
	A.printToFile(file, 0);  B.printToFile(file, 0);
	file << '\n';
	B.printToFile(file, 0);  C.printToFile(file, 0);
	file << '\n';
	C.printToFile(file, 0);  A.printToFile(file, 0);
	file << '\n';
}
