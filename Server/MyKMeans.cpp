//Zharikov Alexey 211

#include "MyKMeans.h"

void MyKMeans::startAlg(MyField& f, int k, vector<MyPoint*> pt, int mode)
{
	n = pt.size();
	srand(time(0));
	if (mode == 0)
	{
		FindCluster* f_cl = new FindCluster();
		f.fc.push_back(f_cl);
	}
	f.fc.back()->mu.resize(k);
	f.fc.back()->inds.assign(k, vector<int>(n));
	for (int j = 0; j < k; j++)
		f.fc.back()->mu[j] = pt[rand() % n];
	ind = true;
	step = 0;
	while (ind == true)
	{
		ind = false;
		for (int i = 0; i < n; i++)
		{
			min_k = 0;
			min_d = f.distPts(pt[i], f.fc.back()->mu[0]);
			for (int j = 1; j < k; j++)
				if (f.distPts(pt[i], f.fc.back()->mu[j]) < min_d)
				{
					min_k = j;
					min_d = f.distPts(pt[i], f.fc.back()->mu[j]);
				}
			if (f.fc.back()->inds[min_k][i] == 0)
			{
				for (int j = 0; j < k; j++)
					f.fc.back()->inds[j][i] = 0;
				f.fc.back()->inds[min_k][i] = 1;
				ind = true;
			}
		}
		if (ind == true)
			for (int j = 0; j < k; j++)
			{
				sum = 0;
				for (int i = 0; i < n; i++)
					sum += f.fc.back()->inds[j][i];
				recalculateMuKmeans(f, j, sum, pt);
			}
		if (mode == 0)
			displayKmeansStep(f, step, k);
		step++;
	}

	for (int j = 0; j < k; j++)
	{
		MyCluster* new_cluster = new MyCluster();
		for (int i = 0; i < n; i++)
			if (f.fc.back()->inds[j][i] == 1)
				new_cluster->c_p.push_back(pt[i]);
		f.fc.back()->clusters.push_back(new_cluster);
	}
}
void MyKMeans::recalculateMuKmeans(MyField& f, int j, double s, vector<MyPoint*> p)
{
	double scalar_x = 0, scalar_y = 0;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		scalar_x += p[i]->getX() * f.fc.back()->inds[j][i];
		scalar_y += p[i]->getY() * f.fc.back()->inds[j][i];
	}
	f.fc.back()->mu[j]->setX(scalar_x / s);
	f.fc.back()->mu[j]->setY(scalar_y / s);
}
void MyKMeans::displayKmeansStep(MyField& f, int step, int k)
{
	ofstream p_file, mus_file;

	p_file.open("D:\\datafiles\\KMPoints\\KMPoints_" + to_string(step) + ".txt");
	mus_file.open("D:\\datafiles\\KMMus\\KMMus_" + to_string(step) + ".txt");
	for (int i = 0; i < MyPoint::getCount(); i++)
	{
		f.pts[i]->printToFile(p_file, 1);
		for (int j = 0; j < k; j++)
			if (f.fc.back()->inds[j][i] == 1)
				p_file << j << endl;
	}
	for (unsigned int j = 0; j < f.fc.back()->mu.size(); j++)
		f.fc.back()->mu[j]->printToFile(mus_file, 0);
	p_file.close();
	mus_file.close();
}
void MyKMeans::displayAlg(MyField& f)
{
	ofstream kmeans_file;

	kmeans_file.open("D:\\datafiles\\Kmeans.txt");
	for (unsigned int j = 0; j < f.fc.back()->mu.size(); j++)
	{
		for (unsigned int i = 0; i < f.pts.size(); i++)
			if (f.fc.back()->inds[j][i] == 1)
			{
				f.fc.back()->mu[j]->printToFile(kmeans_file, 0);
				f.pts[i]->printToFile(kmeans_file, 0);
				kmeans_file << endl;
			}
		kmeans_file << endl;
	}
	kmeans_file.close();
}
