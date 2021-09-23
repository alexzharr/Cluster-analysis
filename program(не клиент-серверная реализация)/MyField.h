//Zharikov Alexey 211

#pragma once
#include <vector>
#include "MyPoint.h"
#include "SpTree.h"
#include "MyCloud.h"
#include "MyRect.h"
#include "FindCluster.h"
#include "MyCluster.h"
#include "DistMatrix.h"
#include "Triangle.h"
#include "Triangulation.h"
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

constexpr auto Pi = 3.1415926535;
constexpr auto E = 2.7182818284;

class MyField
{
public:

	vector<FindCluster*>fc;
	vector<MyCloud*>clouds;
	vector<MyRect*>rects;
	vector<MyPoint*>pts;
	DistMatrix dist_matrix;
	SpTree* tree;


	MyField();
	double distPts(MyPoint* p1, MyPoint* p2);
	void createDistanceMatrix();
	void createBinaryMatrix(double d);
	void createDBBinaryMatrix(double d, int s);
	Triangulation generateTriangulation(vector<MyPoint>& pts);
	double scalarCos(MyPoint a, MyPoint b, MyPoint c);
	vector<MyPoint> convexHull(vector<MyPoint> pts);
	double leftTurn(MyPoint p, MyPoint q, MyPoint r);
	void polarSort(vector<MyPoint>& pts);
	void findMinY(vector<MyPoint>& pts);
	double gaussFunc(double x);
	double someFunc(double x, double y);
	void functionInterpolation(MyPoint p);
};

