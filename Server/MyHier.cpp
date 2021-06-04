//Zharikov Alexey 211

#include "MyHier.h"

void MyHier::startAlg(MyField& f)
{
	n = MyPoint::getCount();
	vector<vector<double>>d = f.dist_matrix.a;
	vector<MyPoint> c_p;
	vector<double> col;
	MyPoint new_point;
	FindCluster* f_cl = new FindCluster();

	f.fc.push_back(f_cl);
	f.fc.back()->hier_e.assign(2, vector<MyPoint>(0));
	c_p.resize(n);
	for (int i = 0; i < n; i++)
		c_p[i] = *f.pts[i];
	for (int l = 0; l < (n - 1); l++)
	{
		min_i = 0; min_j = 1; min_dist = d[0][1];
		for (unsigned int i = 0; i < c_p.size(); i++)
			for (unsigned int j = i + 1; j < c_p.size(); j++)
				if (d[i][j] < min_dist)
				{
					min_i = i;
					min_j = j;
					min_dist = d[i][j];
				}
		new_point.setX((c_p[min_i].getX() + c_p[min_j].getX()) / 2);
		new_point.setY((c_p[min_i].getY() + c_p[min_j].getY()) / 2);
		f.fc.back()->hier_p.push_back(new_point);
		f.fc.back()->hier_e[0].push_back(c_p[min_i]);
		f.fc.back()->hier_e[1].push_back(c_p[min_j]);
		displayHierStep(f, l);

		d.erase(d.begin() + min_j);
		d.erase(d.begin() + min_i);
		for (unsigned int i = 0; i < d.size(); i++)
		{
			d[i].erase(d[i].begin() + min_j);
			d[i].erase(d[i].begin() + min_i);
		}
		c_p.erase(c_p.begin() + min_j);
		c_p.erase(c_p.begin() + min_i);
		c_p.push_back(new_point);
		col.clear();
		for (unsigned int i = 0; i < d.size(); i++)
		{
			d[i].push_back(f.distPts(&c_p[i], &c_p.back()));
			col.push_back(f.distPts(&c_p[i], &c_p.back()));
		}
		col.push_back(0);
		d.push_back(col);
	}
}

void MyHier::displayHierStep(MyField& f, int step)
{
	ofstream p_file, e_file;

	p_file.open("D:\\datafiles\\HPoints\\HPoints_" + to_string(step) + ".txt");
	e_file.open("D:\\datafiles\\HEdges\\HEdges_" + to_string(step) + ".txt");
	for (int i = 0; i < MyPoint::getCount(); i++)
		f.pts[i]->printToFile(p_file, 0);
	for (int i = 0; i < (step + 1); i++)
		f.fc.back()->hier_p[i].printToFile(p_file, 0);
	for (int i = 0; i < (step + 1); i++)
	{
		f.fc.back()->hier_e[0][i].printToFile(e_file, 0);
		f.fc.back()->hier_e[1][i].printToFile(e_file, 0);
		e_file << endl;
	}
	p_file.close();
	e_file.close();
}

void MyHier::displayAlg(MyField& f)
{
	ofstream e_file;

	e_file.open("D:\\datafiles\\HierEdges.txt");
	for (unsigned int i = 0; i < f.fc.back()->hier_e[0].size(); i++)
	{
		f.fc.back()->hier_e[0][i].printToFile(e_file, 0);
		f.fc.back()->hier_e[1][i].printToFile(e_file, 0);
		e_file << endl;
	}
	e_file.close();
}
