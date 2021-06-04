//Zharikov Alexey 211

#pragma once
#include <vector>
#include "MyPoint.h"
using namespace std;

class SpTree
{
private:
	MyPoint* point;
public:
	vector<SpTree*> neighbors;
	vector<MyPoint*> t_p;
	vector<double> edges;
	SpTree();
	SpTree(MyPoint* p);
	void addPoint(MyPoint* p, MyPoint* q);
	void displayTree(ofstream& out);
};

