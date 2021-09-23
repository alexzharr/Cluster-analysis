//Zharikov Alexey 211

#pragma once
#include <vector>
#include "MyPoint.h"
#include "FormElement.h"
#include "MyCluster.h"
#include "BinaryMatrix.h"
using namespace std;

class FindCluster
{
private:
	vector<int> a_mark;
	vector<int> b_mark;
	vector<int> db_mark;
public:
	vector<MyCluster*>clusters;
	vector<FormElement*>for_el;
	vector<vector<int>>inds;
	vector<vector<double>>y;
	vector<MyPoint*>mu;
	vector<vector<vector<double>>>sigma;
	vector<double>weights;
	vector<vector<MyPoint*>>kers;
	vector<MyPoint>hier_p;
	vector<vector<MyPoint>>hier_e;
	vector<vector<MyPoint>>w_p;
	vector<vector<int>>fs_mark;

	BinaryMatrix binary_matrix;

	FindCluster();
	void setA(int num, int value) { a_mark[num] = value; }
	void setB(int num, int value) { b_mark[num] = value; }
	void setDB(int num, int value) { db_mark[num] = value; }
	int getA(int num) { return a_mark[num]; }
	int getB(int num) { return b_mark[num]; }
	int getDB(int num) { return db_mark[num]; }
};

