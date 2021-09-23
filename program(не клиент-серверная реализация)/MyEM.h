//Zharikov Alexey 211

#pragma once
#include "MyField.h"

class MyEM
{
public:
	void startAlg(MyField& f, int k);
	double calcDet(vector<vector<double>> sig);
	void recalculateSigma(MyField& f, int j, double s);
	void recalculateWeights(MyField& f, int j, double s);
	void recalculateMu(MyField& f, int j, double s);
	vector<vector<double>> eigen(vector<vector<double>> sigma);
	vector<double> findEigens(vector<vector<double>> sigma);
	void displayEmStep(MyField& f, int step, int k);
	void displayAlg(MyField& f);
};

