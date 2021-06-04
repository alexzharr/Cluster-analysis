//Zharikov Alexey 211

#include "FindCluster.h"

FindCluster::FindCluster()
{
	clusters = {};
	mu = {};
	weights = {};
	hier_p = {};
	a_mark.resize(MyPoint::getCount());
	b_mark.resize(MyPoint::getCount());
	db_mark.resize(MyPoint::getCount());
}
