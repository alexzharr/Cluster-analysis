//Zharikov Alexey 211

#include "MyForel.h"

void MyForel::startAlg(MyField& f, double r, double c)
{
	bool ind1, ind2;
	int n = MyPoint::getCount();
	int st, counter;
	double sum_x, sum_y;
	FindCluster* f_cl = new FindCluster();
	MyPoint cur;

	f.fc.push_back(f_cl);
	f.fc.back()->w_p.resize(3);
	f.fc.back()->fs_mark.resize(3);
	for (int i = 0; i < n; i++)
		f.fc.back()->w_p[0].push_back(*f.pts[i]);
	st = 1;
	for (int j = 0; j < 3; j++)
	{
		f.fc.back()->for_el.clear();
		for (int u = 0; u < (j + 1); u++)
			for (unsigned int v = 0; v < f.fc.back()->w_p[u].size(); v++)
				f.fc.back()->fs_mark[u][v] = u;
		ind1 = true;
		while (ind1 == true)
		{
			ind1 = false;
			for (unsigned int i = 0; i < f.fc.back()->w_p[j].size(); i++)
				if (f.fc.back()->fs_mark[j][i] == j)
				{
					cur = f.fc.back()->w_p[j][i];
					ind1 = true;
					break;
				}
			ind2 = true;
			while (ind2 == true)
			{
				ind2 = false;
				sum_x = 0; sum_y = 0; counter = 0;
				for (unsigned int i = 0; i < f.fc.back()->w_p[j].size(); i++)
					if ((f.distPts(&cur, &f.fc.back()->w_p[j][i]) < (pow(c, j) * r)) &&
						(f.fc.back()->fs_mark[j][i] == j))
					{
						sum_x += f.fc.back()->w_p[j][i].getX();
						sum_y += f.fc.back()->w_p[j][i].getY();
						counter++;
					}
				if (((cur.getX() != (sum_x / counter)) ||
					(cur.getY() != (sum_y / counter))) &&
					(counter != 0))
				{
					cur.setX(sum_x / counter);
					cur.setY(sum_y / counter);
					ind2 = true;
				}
				else
				{
					FormElement* fe = new FormElement(cur, (pow(c, j) * r));
					for (unsigned int i = 0; i < f.fc.back()->w_p[j].size(); i++)
						if ((f.distPts(&cur, &f.fc.back()->w_p[j][i]) < (pow(c, j) * r)) &&
							(f.fc.back()->fs_mark[j][i] == j))
						{
							f.fc.back()->fs_mark[j][i] = (j + 1);
							cout << f.fc.back()->fs_mark[j][i];
							fe->fe_p.push_back(&f.fc.back()->w_p[j][i]);
						}
					if (j != 2)
						f.fc.back()->w_p[j + 1].push_back(fe->getC());
					f.fc.back()->for_el.push_back(fe);
				}
			}
			displayForelStep(f, st, (pow(c, j) * r));
			st++;
		}
	}
}

void MyForel::displayForelStep(MyField& f, int step, double r)
{
	ofstream p_file, c_file;

	p_file.open("D:\\datafiles\\FPoints\\FPoints_" + to_string(step) + ".txt");
	c_file.open("D:\\datafiles\\FCircles\\FCircles_" + to_string(step) + ".txt");
	for (int j = 0; j < 3; j++)
		for (unsigned int i = 0; i < f.fc.back()->w_p[j].size(); i++)
		{
			f.fc.back()->w_p[j][i].printToFile(p_file, 1);
			p_file << f.fc.back()->fs_mark[j][i] << endl;
		}
	for (unsigned int i = 0; i < f.fc.back()->for_el.size(); i++)
	{
		f.fc.back()->for_el[i]->getC().printToFile(c_file, 1);
		c_file << f.fc.back()->for_el[i]->getR() << endl;
	}
	p_file.close();
	c_file.close();
}