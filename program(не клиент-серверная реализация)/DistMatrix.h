#pragma once
#include <vector>

class DistMatrix
{
public:
	std::vector<std::vector<double>>a;

	DistMatrix();
	~DistMatrix();
};

