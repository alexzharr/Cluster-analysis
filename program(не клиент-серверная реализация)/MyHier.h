//Zharikov Alexey 211

#pragma once
#include "MyField.h"

class MyHier
{
private:
	int min_i, min_j, n;
	double min_dist;
public:
	void startAlg(MyField& f);
	void displayHierStep(MyField& f, int step);
	void displayAlg(MyField& f);
};

