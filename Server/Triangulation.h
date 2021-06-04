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
    ~Triangulation() = default;
    void addTriangle(Triangle T);
    Triangle getTriangle(int id);
    int findTriangle(MyPoint p, MyPoint q);
    void createTriangleIndicators();
    vector <MyPoint> findNeiPoints(MyPoint p);
    void printTriangulation();
};
