//Zharikov Alexey 211

#pragma once
#include "MyField.h"

class MyDBWave
{
private:
	int i, j, n, t, temp, cl_num;
	bool ind1, ind2;
public:
	void startAlg(MyField& f);
	void displayAlg(MyField& f);
};

