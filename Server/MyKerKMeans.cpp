//Zharikov Alexey 211

#include "MyKerKMeans.h"

void MyKerKMeans::startAlg(MyField& f, MyKMeans& km, int k, int p)
{
	n = MyPoint::getCount();
	FindCluster* f_cl = new FindCluster();
	f_cl->kers.assign(k, vector<MyPoint*>(p));
	f.fc.push_back(f_cl);
	km.startAlg(f, k, f.pts, 1);
	for (int j = 0; j < k; j++)
	{
		km.startAlg(f, p, f.fc.back()->clusters[j]->c_p, 1);
		f.fc.back()->kers[j] = f.fc.back()->mu;
	}
	f.fc.back()->inds.assign(k, vector<int>(n));
	for (l = 0; l < n; l++)
	{
		m = 0;
		min = f.distPts(f.pts[l], f.fc.back()->kers[0][0]);
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < p; j++)
				if (f.distPts(f.pts[l], f.fc.back()->kers[i][j]) < min)
				{
					min = f.distPts(f.pts[l], f.fc.back()->kers[i][j]);
					m = i;
				}
			f.fc.back()->inds[m][l] = 1;
		}
	}
	f.fc.back()->clusters.clear();
	for (int i = 0; i < k; i++)
	{
		MyCluster* new_cluster = new MyCluster();
		for (int j = 0; j < n; j++)
			if (f.fc.back()->inds[i][j] == 1)
				new_cluster->c_p.push_back(f.pts[j]);
		f.fc.back()->clusters.push_back(new_cluster);
	}
}

void MyKerKMeans::displayAlg(MyField& f)
{
	ofstream kers_file, clusters_file;

	kers_file.open("D:\\datafiles\\KersKmeans.txt");
	clusters_file.open("D:\\datafiles\\KerKmeans.txt");
	for (unsigned int j = 0; j < f.fc.back()->kers.size(); j++)
	{
		for (unsigned int i = 0; i < f.fc.back()->kers[j].size(); i++)
		{
			f.fc.back()->kers[j][i]->printToFile(kers_file, 1);
			kers_file << j << endl;
		}
		for (unsigned int i = 0; i < f.pts.size(); i++)
			if (f.fc.back()->inds[j][i] == 1)
			{
				f.pts[i]->printToFile(clusters_file, 1);
				clusters_file << j << endl;
			}
	}
	kers_file.close();
	clusters_file.close();
}
