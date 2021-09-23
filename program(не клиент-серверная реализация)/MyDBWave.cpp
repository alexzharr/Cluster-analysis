//Zharikov Alexey 211

#include "MyDBWave.h"

void MyDBWave::startAlg(MyField& f)
{

	n = f.pts.size();
	cl_num = 1;
	ind1 = true;
	for (int i = 0; i < n; i++)
	{
		f.fc.back()->setA(i, 0);
		f.fc.back()->setB(i, 0);
	}
	while (ind1 == true)
	{
		ind1 = false;
		for (i = 0; i < n; i++)
			if ((f.fc.back()->getDB(i) != 0) && (f.fc.back()->getA(i) == 0))
			{
				f.fc.back()->setA(i, 1);
				ind1 = true;
				break;
			}
		if (ind1 == false)
			continue;

		t = 2;
		ind2 = true;
		while (ind2 == true)
		{
			ind2 = false;
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					if ((f.fc.back()->getDB(i) != 0) &&
						(f.fc.back()->getDB(j) != 0) &&
						(f.fc.back()->getA(i) == (t - 1)) &&
						(f.fc.back()->binary_matrix.b[i][j] == 1) &&
						(f.fc.back()->getB(j) == 0))
					{
						if (i == j)
							f.fc.back()->setB(j, t - 1);
						else
						{
							f.fc.back()->setB(j, t);
							ind2 = true;
						}
					}
			for (i = 0; i < n; i++)
			{
				if (f.fc.back()->getDB(i) == 0)
					continue;
				temp = f.fc.back()->getA(i);
				f.fc.back()->setA(i, f.fc.back()->getB(i));
				f.fc.back()->setB(i, temp);
			}
			t++;
		}
		for (i = 0; i < n; i++)
			if (f.fc.back()->getA(i) > 0)
			{
				f.fc.back()->setA(i, -cl_num);
				f.fc.back()->setB(i, -cl_num);
			}
		cl_num++;
	}
	for (i = 1; i < cl_num; i++)
	{
		MyCluster* new_cluster = new MyCluster();
		for (j = 0; j < n; j++)
			if (f.fc.back()->getA(j) == -i)
				new_cluster->c_p.push_back(f.pts[j]);
		f.fc.back()->clusters.push_back(new_cluster);
	}
}
void MyDBWave::displayAlg(MyField& f)
{
	ofstream ker_file, per_file, dust_file, edges_file;
	int n = MyPoint::getCount();

	ker_file.open("D:\\datafiles\\Kernal.txt");
	per_file.open("D:\\datafiles\\Periphery.txt");
	dust_file.open("D:\\datafiles\\Dust.txt");

	for (int i = 0; i < n; i++)
	{
		if (f.fc.back()->getDB(i) == 1)
			f.pts[i]->printToFile(ker_file, 0);
		else if (f.fc.back()->getDB(i) == 2)
			f.pts[i]->printToFile(per_file, 0);
		else
			f.pts[i]->printToFile(dust_file, 0);
	}
	ker_file.close();
	per_file.close();
	dust_file.close();
	edges_file.open("D:\\datafiles\\DBEdges.txt");
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if ((f.fc.back()->binary_matrix.b[i][j] == 1))
			{
				f.pts[i]->printToFile(edges_file, 0);
				f.pts[j]->printToFile(edges_file, 0);
				edges_file << endl;
			}
	edges_file.close();
}
