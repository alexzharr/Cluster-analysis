//Zharikov Alexey 211

#pragma once
#include "MyField.h"
#include "MyKMeans.h"

class MyKerKMeans
{
private:
	int l, m, n;
	double min;
public:
	void startAlg(MyField& f, MyKMeans& km, int k, int p);
	void displayAlg(MyField& f);
};

