// Zharikov Alexey 211

#pragma once
#include <vector>
#include "Triangle.h"

class Triangulation
{
private:
    vector <Triangle> triangles;
    int number_triangles, number_points;
    vector <vector <int>> triangle_indicators;
public:
    Triangulation();
    Triangulation(const Triangulation& Del_tr);
    const Triangulation& operator=(const Triangulation& Del_tr);
    unsigned int getSize();
    void addTriangle(Triangle T);
    void flipCorrection(Triangle T1, Triangle T2, int i, int j);
    Triangle getTriangle(int id);
    int findTriangle(MyPoint p, MyPoint q, int cur);
    void createTriangleIndicators();
    vector <MyPoint> findNeiPoints(MyPoint p);
    void printTriangulation();
    ~Triangulation() = default;
};
