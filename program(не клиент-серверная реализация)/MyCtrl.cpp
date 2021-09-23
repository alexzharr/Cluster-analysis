//Zharikov Alexey 211

#include "MyCtrl.h"

void MyCtrl::printHelpFile()
{
	string line;
	ifstream help_file;
	help_file.open("D:\\datafiles\\HELP.txt");
	while (getline(help_file, line))
		cout << line << endl;
}
bool MyCtrl::getMode()
{
	return mode;
}
void MyCtrl::genCloud(double x_c, double y_c, double x_d, double y_d, int c)
{
	MyCloud* new_cloud = new MyCloud(x_c, y_c, x_d, y_d, c);
	field.clouds.push_back(new_cloud);
}
void MyCtrl::getBuffer(int cloud_num)
{
	buffer.b_p.resize(field.clouds[cloud_num]->pts.size());
	buffer.setX(field.clouds[cloud_num]->getX());
	buffer.setY(field.clouds[cloud_num]->getY());
	for (unsigned int i = 0; i < field.clouds[cloud_num]->pts.size(); i++)
		buffer.b_p[i] = field.clouds[cloud_num]->pts[i];
}
void MyCtrl::bufferShift(double shift_x, double shift_y)
{
	buffer.shiftCloud(shift_x, shift_y);
}
void MyCtrl::bufferTurn(double angle)
{
	buffer.turnCloud(angle);
}
void MyCtrl::bufferScale(double scale)
{
	buffer.scaleCloud(scale);
}
void MyCtrl::setBuffer(int cloud_num)
{
	if (cloud_num == MyCloud::getCount())
	{
		MyCloud* new_cloud = new MyCloud();
		field.clouds.push_back(new_cloud);
	}
	field.clouds[cloud_num]->pts.resize(buffer.b_p.size());
	field.clouds[cloud_num]->setX(buffer.getX());
	field.clouds[cloud_num]->setY(buffer.getY());
	for (unsigned int i = 0; i < buffer.b_p.size(); i++)
		field.clouds[cloud_num]->pts[i] = buffer.b_p[i];
}
void MyCtrl::createDistanceMatrix()
{
	mode = true;
	field.createDistanceMatrix();
}
void MyCtrl::createBinaryMatrix(double delta)
{
	field.createBinaryMatrix(delta);
}
void MyCtrl::startWaveAlg()
{
	wave.startAlg(field);
}
void MyCtrl::displayWaveAlg()
{
	wave.displayAlg(field);
}
void MyCtrl::createDBBinaryMatrix(double delta, int st)
{
	field.createDBBinaryMatrix(delta, st);
}
void MyCtrl::startDBWaveAlg()
{
	dbwave.startAlg(field);
}
void MyCtrl::displayDBScan()
{
	dbwave.displayAlg(field);
}
void MyCtrl::spaningTree()
{
	tree.startAlg(field);
}
void MyCtrl::displaySpaningTree()
{
	tree.displayAlg(field);
}
void MyCtrl::treeHist(int columns)
{
	tree.createHistogram(field);
}
void MyCtrl::startKmeansAlgorithm(int k)
{
	kmeans.startAlg(field, k, field.pts, 0);
}
void MyCtrl::displayKMeansAlgorithm()
{
	kmeans.displayAlg(field);
}
void MyCtrl::startEmAlgorithm(int k)
{
	em.startAlg(field, k);
}
void MyCtrl::startKerKmeansAlgorithm(int k, int p)
{
	ker_kmeans.startAlg(field, kmeans, k, p);
}
void MyCtrl::displayKerKmeansAlgorithm()
{
	ker_kmeans.displayAlg(field);
}
void MyCtrl::startForelAlgorithm(double radius, double coef)
{
	forel.startAlg(field, radius, coef);
}
void MyCtrl::hierAlgorithm()
{
	hier.startAlg(field);
}
void MyCtrl::displayHierAlgorithm()
{
	hier.displayAlg(field);
}
void MyCtrl::delonayTriangulation()
{
	vector<MyPoint>ps;
	ps.resize(field.pts.size());
	for (unsigned int i = 0; i < field.pts.size(); i++)
		ps[i] = *field.pts[i];
	field.generateTriangulation(ps);
}
void MyCtrl::funcInterpolation(double x, double y)
{
	MyPoint p(x, y);
	field.functionInterpolation(p);
}
void MyCtrl::fieldInfo()
{
	cout << "Number of clouds: " << MyCloud::getCount() << endl;
	cout << "Number of points: " << MyPoint::getCount() << endl;
	for (int i = 0; i < MyCloud::getCount(); i++)
	{
		cout << "Cloud " << i << " includes ";
		cout << field.clouds[i]->pts.size() << " points" << endl;;
	}
}
void MyCtrl::displayField()
{
	ofstream field_file;
	field_file.open("D:\\datafiles\\Field.txt");
	for (int i = 0; i < MyCloud::getCount(); i++)
		for (unsigned int j = 0; j < field.clouds[i]->pts.size(); j++)
		{
			field.clouds[i]->pts[j]->printToFile(field_file, 1);
			field_file << i << endl;
		}
	for (int i = 0; i < MyRect::getCount(); i++)
		for (unsigned int j = 0; j < field.rects[i]->pts.size(); j++)
		{
			field.rects[i]->pts[j]->printToFile(field_file, 1);
			field_file << i << endl;
		}
	field_file.close();
}

void MyCtrl::genRect(double x_c, double y_c, double x_d, double y_d, int c)
{
	MyRect* new_rect = new MyRect(x_c, y_c, x_d, y_d, c);
	field.rects.push_back(new_rect);
}
