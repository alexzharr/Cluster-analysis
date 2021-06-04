//Zharikov Alexey 211

#pragma once
#include "MyField.h"

class MyKMeans
{
private:
	int n, min_k, step;
	double min_d, sum;
	bool ind;
public:
	void startAlg(MyField& f, int k, vector<MyPoint*> pt, int mode);
	void recalculateMuKmeans(MyField& f, int j, double s, vector<MyPoint*> p);
	void displayKmeansStep(MyField& f, int step, int k);
	void displayAlg(MyField& f);
};

