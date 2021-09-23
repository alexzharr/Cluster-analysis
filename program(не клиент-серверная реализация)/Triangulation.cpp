// Zharikov Alexey 211

#include "Triangulation.h"

Triangulation::Triangulation() { number_triangles = number_points = 0; }

Triangulation::Triangulation(const Triangulation& Del_tr)
{
	triangles = Del_tr.triangles;
	number_triangles = Del_tr.number_triangles;
	number_points = Del_tr.number_points;
	triangle_indicators = Del_tr.triangle_indicators;
}
const Triangulation& Triangulation::operator=(const Triangulation& Del_tr)
{
	triangles = Del_tr.triangles;
	number_triangles = Del_tr.number_triangles;
	number_points = Del_tr.number_points;
	triangle_indicators = Del_tr.triangle_indicators;
	return *this;
}
unsigned int Triangulation::getSize() { return number_triangles; }
void Triangulation::addTriangle(Triangle T)
{
	T.assignID(number_triangles);
	triangles.push_back(T);
	number_triangles++;
	number_points = number_points + 3;
}
void Triangulation::flipCorrection(Triangle T1, Triangle T2, int i, int j)
{
	vector <Triangle>::iterator it;
	it = triangles.begin();
	triangles.erase(it + i);
	triangles.insert(it + i, T1);
	triangles.erase(it + j);
	triangles.insert(it + j, T2);
}
Triangle Triangulation::getTriangle(int id) { return triangles[id]; }
int Triangulation::findTriangle(MyPoint p, MyPoint q, int cur)
{
	for (int i = 0; i < number_triangles; i++)
	{
		if (i == cur)
			continue;
		MyPoint a = triangles[i].getA(), b = triangles[i].getB(), c = triangles[i].getC();
		if (a.getID() == p.getID() && b.getID() == q.getID()) return i;
		else if (a.getID() == p.getID() && c.getID() == q.getID()) return i;
		else if (b.getID() == p.getID() && a.getID() == q.getID()) return i;
		else if (c.getID() == p.getID() && a.getID() == q.getID()) return i;
		else if (b.getID() == p.getID() && c.getID() == q.getID()) return i;
		else if (c.getID() == p.getID() && b.getID() == q.getID()) return i;
	}
	return -1;
}
void Triangulation::createTriangleIndicators()
{
	triangle_indicators.resize(number_triangles);
	for (int i = 0; i < number_triangles; i++) triangle_indicators[i].resize(number_triangles);
	for (int i = 0; i < number_triangles; i++)
	{
		for (int j = 0; j < number_triangles; j++) triangle_indicators[i][j] = 0;
	}
	for (int i = 0; i < number_triangles; i++)
	{
		for (int j = 0; j < number_triangles; j++)
			if (triangles[i].getNeiTriangleID() == j) triangle_indicators[i][j] = triangle_indicators[j][i] = 1;
	}
}
vector <MyPoint> Triangulation::findNeiPoints(MyPoint p)
{
	int i, j, k;
	vector <MyPoint> nei_pts;

	for (i = 0; i < number_triangles; i++)
	{
		if (triangles[i].getA().getID() == p.getID())
		{
			k = i;
			if (triangles[k].getA().getID() != p.getID()) nei_pts.push_back(triangles[k].getA());
			if (triangles[k].getB().getID() != p.getID()) nei_pts.push_back(triangles[k].getB());
			if (triangles[k].getC().getID() != p.getID()) nei_pts.push_back(triangles[k].getC());
			for (j = 0; j < number_triangles; j++)
			{
				if (triangle_indicators[k][j] == 1 && j != k)
				{
					if (triangles[j].getA().getID() == p.getID() || triangles[j].getB().getID() == p.getID() ||
						triangles[j].getC().getID() == p.getID())
					{
						if (triangles[k].getA().getID() != p.getID()) nei_pts.push_back(triangles[k].getA());
						if (triangles[k].getB().getID() != p.getID()) nei_pts.push_back(triangles[k].getB());
						if (triangles[k].getC().getID() != p.getID()) nei_pts.push_back(triangles[k].getC());
					}
				}
			}
		}
		if (triangles[i].getB().getID() == p.getID())
		{
			k = i;
			if (triangles[k].getA().getID() != p.getID()) nei_pts.push_back(triangles[k].getA());
			if (triangles[k].getB().getID() != p.getID()) nei_pts.push_back(triangles[k].getB());
			if (triangles[k].getC().getID() != p.getID()) nei_pts.push_back(triangles[k].getC());
			for (j = 0; j < number_triangles; j++)
			{
				if (triangle_indicators[k][j] == 1 && j != k)
				{
					if (triangles[j].getA().getID() == p.getID() || triangles[j].getB().getID() == p.getID() ||
						triangles[j].getC().getID() == p.getID())
					{
						if (triangles[k].getA().getID() != p.getID()) nei_pts.push_back(triangles[k].getA());
						if (triangles[k].getB().getID() != p.getID()) nei_pts.push_back(triangles[k].getB());
						if (triangles[k].getC().getID() != p.getID()) nei_pts.push_back(triangles[k].getC());
					}
				}
			}
		}
		if (triangles[i].getC().getID() == p.getID())
		{
			k = i;
			if (triangles[k].getA().getID() != p.getID()) nei_pts.push_back(triangles[k].getA());
			if (triangles[k].getB().getID() != p.getID()) nei_pts.push_back(triangles[k].getB());
			if (triangles[k].getC().getID() != p.getID()) nei_pts.push_back(triangles[k].getC());
			for (j = 0; j < number_triangles; j++)
			{
				if (triangle_indicators[k][j] == 1 && j != k)
				{
					if (triangles[j].getA().getID() == p.getID() || triangles[j].getB().getID() == p.getID() ||
						triangles[j].getC().getID() == p.getID())
					{
						if (triangles[k].getA().getID() != p.getID()) nei_pts.push_back(triangles[k].getA());
						if (triangles[k].getB().getID() != p.getID()) nei_pts.push_back(triangles[k].getB());
						if (triangles[k].getC().getID() != p.getID()) nei_pts.push_back(triangles[k].getC());
					}
				}
			}
		}
	}
	for (i = 0; i < nei_pts.size(); i++)
	{
		for (j = i + 1; j < nei_pts.size(); j++)
		{
			if (nei_pts[i].getID() == nei_pts[j].getID())
			{
				nei_pts.erase(nei_pts.begin() + j);
				//				for (k = j; k < neighbouring_points.size()-1; k++) neighbouring_points[k] = neighbouring_points[k + 1];
			}
		}
	}
	return nei_pts;
}
void Triangulation::printTriangulation()
{
	ofstream f("D:\\datafiles\\Delonay.txt");
	for (int i = 0; i < number_triangles; i++)
		triangles[i].printTriangle(f);
	f.close();
}