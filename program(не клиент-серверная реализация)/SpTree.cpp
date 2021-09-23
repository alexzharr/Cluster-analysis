//Zharikov Alexey 211

#include "SpTree.h"

SpTree::SpTree()
{
	neighbors = {};
	t_p = {};
	edges = {};
}

SpTree::SpTree(MyPoint* p) : point(p)
{
	neighbors = {};
	t_p = {};
	edges = {};
	t_p.push_back(p);
}

void SpTree::addPoint(MyPoint* p, MyPoint* q)
{
	if (point == q)
	{
		SpTree* new_tree = new SpTree(p);
		neighbors.push_back(new_tree);
	}
	else
		for (SpTree* nb : neighbors)
			nb->addPoint(p, q);
}


void SpTree::displayTree(ofstream& out)
{
	for (SpTree* nb : neighbors)
	{
		point->printToFile(out, 0);
		nb->point->printToFile(out, 0);
		out << endl;
		nb->displayTree(out);
	}
}
