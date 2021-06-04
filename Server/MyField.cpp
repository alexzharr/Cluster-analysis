//Zharikov Alexey 211
#pragma once
#include "MyField.h"
#include "Triangulation.h"
#include "Triangle.h"

MyField::MyField()
{
	clouds = {};
	pts = {};
	fc = {};
}
double MyField::distPts(MyPoint* p1, MyPoint* p2)
{
	return sqrt(pow(p1->getX() - p2->getX(), 2) +
		pow(p1->getY() - p2->getY(), 2));
}
void MyField::createDistanceMatrix()
{
	int n = MyPoint::getCount();

	dist_matrix.a.assign(n, vector<double>(n));
	for (int i = 0; i < MyCloud::getCount(); i++)
		pts.insert(end(pts), begin(clouds[i]->pts), end(clouds[i]->pts));
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			dist_matrix.a[i][j] = distPts(pts[i], pts[j]);
			dist_matrix.a[j][i] = dist_matrix.a[i][j];
		}
}
void MyField::createBinaryMatrix(double d)
{
	int n = MyPoint::getCount();

	FindCluster* f_cl = new FindCluster();
	f_cl->binary_matrix.b.assign(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			if (dist_matrix.a[i][j] < d)
			{
				f_cl->binary_matrix.b[i][j] = 1;
				f_cl->binary_matrix.b[j][i] = 1;
			}
	fc.push_back(f_cl);
}
void MyField::createDBBinaryMatrix(double d, int s)
{
	int n, count;
	FindCluster* f_cl = new FindCluster();

	n = MyPoint::getCount();
	f_cl->binary_matrix.b.assign(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		f_cl->setDB(i, 0);
	for (int i = 0; i < n; i++)
	{
		count = 0;
		for (int j = 0; j < n; j++)
			if (dist_matrix.a[i][j] < d)
				count++;
		if (count > s)
			f_cl->setDB(i, 1);
	}
	for (int i = 0; i < n; i++)
	{
		if (f_cl->getDB(i) != 0)
			continue;
		for (int j = 0; j < n; j++)
			if ((f_cl->getDB(j) == 1) && (dist_matrix.a[i][j] < d))
				f_cl->setDB(i, 2);
	}
	for (int i = 0; i < n; i++)
	{
		if (f_cl->getDB(i) == 0)
			continue;
		for (int j = i; j < n; j++)
		{
			if ((f_cl->getDB(j) != 0) && (dist_matrix.a[i][j] < d))
			{
				f_cl->binary_matrix.b[i][j] = 1;
				f_cl->binary_matrix.b[j][i] = 1;
			}
		}
	}
	fc.push_back(f_cl);
}
Triangulation MyField::generateTriangulation(vector <MyPoint>& pts)
{
	Triangulation triangulation;
	vector <MyPoint> vertices;
	int k;
	MyPoint a, b, c;
	vector <int> ind(pts.size(), 0);
	cout << pts.size();

	for (unsigned int i = 0; i < pts.size() - 1; i++)
	{
		for (unsigned int j = 0; j < pts.size() - 1 - i; j++)
		{
			if (pts[j].getX() > pts[j + 1].getX())
			{
				a = pts[j];
				pts[j] = pts[j + 1];
				pts[j + 1] = a;
			}
		}
	}
	a = pts[0];
	b = pts[1];
	c = pts[2];
	triangulation.addTriangle(Triangle(a, b, c));
	ind[0] = ind[1] = ind[2] = 1;
	c = pts[2];
	for (unsigned int i = 3; i < pts.size(); i++)
	{
		vertices.clear();
		for (unsigned int j = 0; j < pts.size(); j++)
		{
			if (ind[j] == 1) 
				vertices.push_back(pts[j]);
		}
		vertices = convexHull(vertices);
		for (unsigned int j = 0; j < vertices.size(); j++)
		{
			if (vertices[j].getX() == c.getX() && vertices[j].getY() == c.getY()) 
				k = j;
		}
		rotate(vertices.begin(), vertices.begin() + k, vertices.end());
		vertices.push_back(vertices[0]);
		a = c - pts[i];
		a.setID(c.getID());
		b = vertices[1] - pts[i];
		b.setID(vertices[1].getID());
		for (unsigned j = 2; j < vertices.size(); j++)
		{
			if (a.getX() * b.getY() - a.getY() * b.getX() < 0)
			{
				MyPoint p = a + pts[i];
				MyPoint q = b + pts[i];
				p.setID(a.getID());
				q.setID(b.getID());
				Triangle T = Triangle(pts[i], p, q);
				T.assingNeiTriangleID(triangulation.findTriangle(p, q));
				triangulation.addTriangle(T);
				ind[i] = 1;
			}
			if (a.getX() * b.getY() - a.getY() * b.getX() > 0) break;
			a = b;
			b = vertices[j] - pts[i];
			b.setID(vertices[j].getID());
		}
		reverse(vertices.begin(), vertices.end());
		a = c - pts[i];
		a.setID(c.getID());
		b = vertices[1] - pts[i];
		b.setID(vertices[1].getID());
		for (unsigned int j = 2; j < vertices.size(); j++)
		{
			if (a.getX() * b.getY() - a.getY() * b.getX() > 0)
			{
				MyPoint p = a + pts[i];
				MyPoint q = b + pts[i];
				p.setID(a.getID());
				q.setID(b.getID());
				Triangle T = Triangle(pts[i], p, q);
				T.assingNeiTriangleID(triangulation.findTriangle(p, q));
				triangulation.addTriangle(T);
				ind[i] = 1;
			}
			if (a.getX() * b.getY() - a.getY() * b.getX() < 0) break;
			a = b;
			b = vertices[j] - pts[i];
			b.setID(vertices[j].getID());
		}
		c = pts[i];
	}
	triangulation.printTriangulation();
	return triangulation;
}

vector <MyPoint> MyField::convexHull(vector <MyPoint> pts)
{
	vector <MyPoint> q;

	if (pts.size() < 3) 
		return pts;
	findMinY(pts);
	q.push_back(pts[0]);
	polarSort(pts);
	q.push_back(pts[1]);
	for (unsigned int i = 2; i < pts.size(); i++)
	{
		while (leftTurn(q[q.size() - 2], q[q.size() - 1], pts[i]) < 0 && q.size() > 1) 
			q.pop_back();
		q.push_back(pts[i]);
	}
	q.push_back(pts[0]);
	return q;
}
double MyField::leftTurn(MyPoint p, MyPoint q, MyPoint r)
{
	MyPoint v = q - p, u = r - q;
	return v.getX() * u.getY() - v.getY() * u.getX();
}

void MyField::polarSort(vector <MyPoint>& pts)
{
	vector <double> angles;
	MyPoint v;
	double a;

	for (unsigned int i = 0; i < pts.size(); i++)
	{
		if (i != 0)
		{
			if ((pts[i] - pts[0]).length() < 0.0001) angles.push_back(0);
			else angles.push_back(acos((pts[i] - pts[0]).getX() / (pts[i] - pts[0]).length()));
		}
		else angles.push_back(0);
	}
	for (unsigned int i = 0; i < pts.size() - 1; i++)
	{
		for (unsigned int j = 0; j < pts.size() - 1 - i; j++)
		{
			if (angles[j] > angles[j + 1])
			{
				a = angles[j];
				v = pts[j];
				angles[j] = angles[j + 1];
				pts[j] = pts[j + 1];
				angles[j + 1] = a;
				pts[j + 1] = v;
			}
		}
	}
}

void MyField::findMinY(vector <MyPoint>& pts)
{
	int k = 0;
	for (unsigned int i = 0; i < pts.size(); i++)
	{
		if ((i != k && pts[i].getY() < pts[k].getY()) ||
			(i != k && pts[i].getY() == pts[k].getY() &&
				pts[i].getX() < pts[k].getX()))
		{
			k = i;
		}
	}
	rotate(pts.begin(), pts.begin() + k, pts.end());
}

double MyField::gaussFunc(double x)
{
	return exp(-(x * x) / 2);
}

double MyField::someFunc(double x, double y)
{ 
	return (x*x+y*y)/5 + 1; 
}

void MyField::functionInterpolation(MyPoint p)
{
	vector <MyPoint> pts, pts0;
	vector <MyPoint> nei_pts;
	Triangulation triangulation;
	double h = 0.1, sum_w = 0, sum_w_y = 0, r, sum_y = 0, sum_eps = 0, mean_y = 0;
	vector <double> w;
	vector <double> eps;

	p.setID(MyPoint::getCount() + 1);
	p.setF(someFunc(p.getX(), p.getY()));
	pts.push_back(p);
	for (unsigned int i = 0; i < clouds.size(); i++)
	{
		for (unsigned int j = 0; j < clouds[i]->pts.size(); j++)
		{
			clouds[i]->pts[j]->setF(someFunc(clouds[i]->pts[j]->getX(), clouds[i]->pts[j]->getY()));
			pts.push_back(*clouds[i]->pts[j]);
		}
	}
	triangulation = generateTriangulation(pts);
	triangulation.printTriangulation();
	triangulation.createTriangleIndicators();
	nei_pts = triangulation.findNeiPoints(p);
	for (unsigned int i = 0; i < nei_pts.size(); i++) w.push_back(gaussFunc((p - nei_pts[i]).length() / h));
	for (unsigned int i = 0; i < nei_pts.size(); i++)
	{
		sum_w_y = sum_w_y + pts[i].getF() * w[i];
		sum_w = sum_w + w[i];
		//        cout << neighbouring_points[i].get_first_coordinate() << " " << neighbouring_points[i].get_second_coordinate() << " " << neighbouring_points[i].get_vector_id() << endl;
	}

	pts.clear();
	for (unsigned int i = 0; i < clouds.size(); i++)
	{
		for (unsigned int j = 0; j < clouds[i]->pts.size(); j++)
			pts.push_back(*clouds[i]->pts[j]);
	}
	for (unsigned int i = 0; i < pts.size(); i++) mean_y = mean_y + pts[i].getF();
	mean_y = mean_y * (1 / pts.size());
	for (unsigned int i = 0; i < pts.size(); i++)
	{
		nei_pts.clear();
		w.clear();
		pts0.clear();
		for (unsigned int j = 0; j < i; j++) 
			pts0.push_back(pts[i]);
		for (unsigned j = i + 1; j < pts.size(); j++) pts0.push_back(pts[i]);
		triangulation = generateTriangulation(pts0);
		triangulation.createTriangleIndicators();
		nei_pts = triangulation.findNeiPoints(pts[i]);
		for (unsigned j = 0; j < nei_pts.size(); j++) w.push_back(gaussFunc((pts[i] - nei_pts[i]).length() / h));
		for (unsigned j = 0; j < nei_pts.size(); j++)
		{
			sum_w_y = sum_w_y + pts0[i].getF() * w[i];
			sum_w = sum_w + w[i];
		}
		eps.push_back(pts[i].getF() - sum_w_y / sum_w);
		//cout << eps[i] << endl;
	}
	for (unsigned i = 0; i < pts.size(); i++)
		sum_y = sum_y + ((pts[i].getF() - mean_y) * (pts[i].getF() - mean_y));
	for (unsigned i = 0; i < pts.size(); i++) sum_eps = sum_eps + eps[i] * eps[i];
	r = 1 - sum_eps / sum_y;

	cout << "Real: " << p.getF() << ". Forecast: " << sum_w_y / sum_w << ". r^2=" << r << "." << endl;
}