#include "MyEM.h"

void MyEM::startAlg(MyField& f, int k)
{
	int l, n;
	double coef, delSquared, n_j, sum_j, max_p, max_p_ind;
	vector<vector<double>> p;
	FindCluster* f_cl = new FindCluster;

	srand(time(0));
	n = f.pts.size();
	p.assign(k, vector<double>(n));
	f_cl->y.assign(k, vector<double>(n));
	f_cl->weights.resize(k);
	f_cl->mu.resize(k);
	f_cl->sigma.resize(k);
	for (int j = 0; j < k; j++)
	{
		f_cl->sigma[j].assign(2, vector<double>(2));
		f_cl->sigma[j][0][0] = 1;
		f_cl->sigma[j][1][1] = 1;
		f_cl->weights[j] = 1.0 / k;
		f_cl->mu[j] = f.pts[rand() % n];
	}
	f.fc.push_back(f_cl);
	for (l = 0; l < 30; l++)
	{
		for (int j = 0; j < k; j++)
		{
			coef = 1 / (2 * Pi * pow(calcDet(f.fc.back()->sigma[j]), 0.5));
			for (int i = 0; i < n; i++)
			{
				delSquared = (f.fc.back()->sigma[j][1][1] / calcDet(f.fc.back()->sigma[j])) *
					pow((f.pts[i]->getX() - f.fc.back()->mu[j]->getX()), 2) +
					2 * (f.fc.back()->sigma[j][0][1] / calcDet(f.fc.back()->sigma[j])) *
					(f.pts[i]->getX() - f.fc.back()->mu[j]->getX()) * (f.pts[i]->getY() - f.fc.back()->mu[j]->getY()) +
					(f.fc.back()->sigma[j][0][0] / calcDet(f.fc.back()->sigma[j])) *
					pow((f.pts[i]->getY() - f.fc.back()->mu[j]->getY()), 2);
				p[j][i] = coef * pow(E, (-0.5 * delSquared));
			}
		}
		for (int i = 0; i < n; i++)
		{
			sum_j = 0;
			for (int j = 0; j < k; j++)
				sum_j += f.fc.back()->weights[j] * p[j][i];
			for (int j = 0; j < k; j++)
				f.fc.back()->y[j][i] = (f.fc.back()->weights[j] * p[j][i]) / sum_j;
		}
		f.fc.back()->inds.assign(k, vector<int>(n));
		for (int i = 0; i < n; i++)
		{
			max_p = f.fc.back()->y[0][i];
			max_p_ind = 0;
			for (int j = 1; j < k; j++)
				if (f.fc.back()->y[j][i] > max_p)
				{
					max_p = f.fc.back()->y[j][i];
					max_p_ind = j;
				}
			f.fc.back()->inds[max_p_ind][i] = 1;
		}
		displayEmStep(f, l, k);
		for (int j = 0; j < k; j++)
		{
			n_j = 0;
			for (int i = 0; i < n; i++)
				n_j += f.fc.back()->y[j][i];
			recalculateMu(f, j, n_j);
			recalculateSigma(f, j, n_j);
			recalculateWeights(f, j, n_j);
		}
	}
}

double MyEM::calcDet(vector<vector<double>> sig)
{
	return sig[0][0] * sig[1][1] - sig[1][0] * sig[0][1];
}

void MyEM::recalculateSigma(MyField& f, int j, double s)
{
	double scalar_xx = 0, scalar_yy = 0, scalar_xy = 0;

	for (unsigned int i = 0; i < f.pts.size(); i++)
	{
		scalar_xx += f.fc.back()->y[j][i] *
			pow((f.pts[i]->getX() - f.fc.back()->mu[j]->getX()), 2);
		scalar_xy += f.fc.back()->y[j][i] *
			(f.pts[i]->getX() - f.fc.back()->mu[j]->getX()) * (f.pts[i]->getY() - f.fc.back()->mu[j]->getY());
		scalar_yy += f.fc.back()->y[j][i] *
			pow((f.pts[i]->getY() - f.fc.back()->mu[j]->getY()), 2);
	}
	f.fc.back()->sigma[j][0][0] = scalar_xx / s;
	f.fc.back()->sigma[j][1][1] = scalar_yy / s;
	if ((scalar_xy / s) < 0)
	{
		f.fc.back()->sigma[j][0][1] = 0;
		f.fc.back()->sigma[j][1][0] = 0;
	}
	else
	{
		f.fc.back()->sigma[j][0][1] = scalar_xy / s;
		f.fc.back()->sigma[j][1][0] = scalar_xy / s;
	}
}

void MyEM::recalculateWeights(MyField& f, int j, double s)
{
	f.fc.back()->weights[j] = s / f.pts.size();
}

void MyEM::recalculateMu(MyField& f, int j, double s)
{
	double scalar_x = 0, scalar_y = 0;

	for (unsigned int i = 0; i < f.pts.size(); i++)
	{
		scalar_x += f.pts[i]->getX() * f.fc.back()->y[j][i];
		scalar_y += f.pts[i]->getY() * f.fc.back()->y[j][i];
	}
	f.fc.back()->mu[j]->setX(scalar_x / s);
	f.fc.back()->mu[j]->setY(scalar_y / s);
}

vector<vector<double>> MyEM::eigen(vector<vector<double>> sigma)
{
	double a = sigma[0][0], c = sigma[1][0];
	vector<double> eigens = findEigens(sigma);
	vector<vector<double>> res;
	if (eigens.size() == 0)
		return res;
	res.push_back(vector<double>{a - eigens[0], c});
	res.push_back(vector<double>{a - eigens[1], c});
	res.push_back(eigens);
	return res;
}

vector<double> MyEM::findEigens(vector<vector<double>> sigma)
{
	double a = sigma[0][0], d = sigma[1][1];
	double descr = (a + d) * (a + d) - 4 * calcDet(sigma);
	vector<double>lambda;
	if (descr >= 0)
	{
		lambda.push_back(((a + d) + sqrt(descr)) / 2.0);
		lambda.push_back(((a + d) - sqrt(descr)) / 2.0);
	}
	return lambda;
}

void MyEM::displayEmStep(MyField& f, int step, int k)
{
	int ind_max;
	ofstream points_file, ellipses_file;

	points_file.open("D:\\datafiles\\EMPoints\\EMPoints_" + to_string(step) + ".txt");
	ellipses_file.open("D:\\datafiles\\EMEllipses\\EMEllipses_" + to_string(step) + ".txt");
	for (int j = 0; j < k; j++)
	{
		vector<vector<double>> e_data = eigen(f.fc.back()->sigma[j]);
		ind_max = (e_data[2][0] > e_data[2][1]) ? 0 : 1;
		if (e_data[ind_max][1] < 0)
		{
			e_data[ind_max][0] *= -1;
			e_data[ind_max][1] += -1;
		}
		double angle = acos(e_data[ind_max][0] /
			sqrt(pow(e_data[ind_max][0], 2) + pow(e_data[ind_max][1], 2)));
		angle *= 180;
		angle /= Pi;
		f.fc.back()->mu[j]->printToFile(ellipses_file, 1);
		ellipses_file << 5 * e_data[2][1 - ind_max] << ' ' <<
			5 * e_data[2][ind_max] << ' ' << angle << endl;
		for (unsigned int i = 0; i < f.pts.size(); i++)
			if (f.fc.back()->inds[j][i] == 1)
			{
				f.pts[i]->printToFile(points_file, 1);
				points_file << j << endl;
			}
	}
	points_file.close();
	ellipses_file.close();
}
