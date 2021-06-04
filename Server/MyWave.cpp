//Zharikov Alexey 211

#include "MyWave.h"

void MyWave::startAlg(MyField& f)
{
	vector<MyPoint*> help_pts = f.pts;
	n = f.pts.size();
	cl_num = 1;
	ind1 = true;
	while (ind1 == true)
	{
		ind1 = false;
		for (int i = 0; i < n; i++)
			if (f.fc.back()->getA(i) == 0)
			{
				f.fc.back()->setA(i,1);
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
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
				{
					if ((f.fc.back()->getA(i) == (t - 1)) &&
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
				}
			for (int i = 0; i < n; i++)
			{
				temp = f.fc.back()->getA(i);
				f.fc.back()->setA(i, f.fc.back()->getB(i));
				f.fc.back()->setB(i, temp);
			}
			t++;
		}
		for (int i = 0; i < n; i++)
			if (f.fc.back()->getA(i) > 0)
			{
				f.fc.back()->setA(i, -cl_num);
				f.fc.back()->setB(i, -cl_num);
			}
		cl_num++;
	}
	for (int i = 1; i < cl_num; i++)
	{
		MyCluster* new_cluster = new MyCluster();
		for (int j = 0; j < n; j++)
			if (f.fc.back()->getA(j) == -i)
				new_cluster->c_p.push_back(f.pts[j]);
		f.fc.back()->clusters.push_back(new_cluster);
	}
}

void MyWave::displayAlg(MyField& f)
{
	ofstream edges_file;
	int n = MyPoint::getCount();

	edges_file.open("D:\\datafiles\\WaveEdges.txt");
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
