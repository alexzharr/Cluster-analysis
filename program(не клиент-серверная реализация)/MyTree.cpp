#include "MyTree.h"
#include "DistMatrix.h"

void MyTree::startAlg(MyField& f)
{
	int k, n, id_p, id_q;
	double min_dist;
	ofstream file("D:\\datafiles\\TreeHistogram.txt");
	n = MyPoint::getCount();;
	f.tree = new SpTree(f.pts[0]);
	for (int i = 0; i <= n - 2; i++)
	{
		id_p = -1;
		id_q = -1;
		min_dist = DBL_MAX;
		for (unsigned int j = 0; j < f.tree->t_p.size(); j++)
			for (k = 0; k < n; k++)
			{
				if ((k != j) &&
					(find(f.tree->t_p.begin(), f.tree->t_p.end(), f.pts[k]) == f.tree->t_p.end()) &&
					(f.dist_matrix.a[f.tree->t_p[j]->getID()][k] < min_dist))
				{
					id_p = k;
					id_q = f.tree->t_p[j]->getID();
					min_dist = f.dist_matrix.a[f.tree->t_p[j]->getID()][k];
				}
			}
		f.tree->addPoint(f.pts[id_p], f.pts[id_q]);
		f.tree->t_p.push_back(f.pts[id_p]);
		f.tree->edges.push_back(f.dist_matrix.a[id_p][id_q]);
		file << f.dist_matrix.a[id_p][id_q] << '\n';
	}
	displayAlg(f);
}

void MyTree::createHistogram(MyField& f)
{
	ofstream file("D:\\datafiles\\TreeHistogram.txt");
	for (unsigned int i = 0; i < f.tree->edges.size(); i++)
		file << f.tree->edges[i] << '\n';
	file.close();
}

void MyTree::displayAlg(MyField& f)
{
	ofstream tree_file;
	tree_file.open("D:\\datafiles\\SpaningTree.txt");
	f.tree->displayTree(tree_file);
	tree_file.close();
}
