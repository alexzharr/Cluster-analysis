//Zharikov Alexey 211

#pragma once
#include "MyField.h"
#include "MyBuffer.h"
#include "MyWave.h"
#include "MyDBWave.h"
#include "MyKMeans.h"
#include "MyKerKMeans.h"
#include "MyTree.h"
#include "MyEM.h"
#include "MyForel.h"
#include "MyHier.h"

class MyCtrl
{
private:
	bool mode = false;
public:
	MyField field;
	MyBuffer buffer;
	MyWave wave;
	MyDBWave dbwave;
	MyTree tree;
	MyKMeans kmeans;
	MyKerKMeans ker_kmeans;
	MyEM em;
	MyForel forel;
	MyHier hier;

	void printHelpFile();
	bool getMode();
	void genCloud(double x_c, double y_c, double x_d, double y_d, int c);
	void genRect(double x_c, double y_c, double x_d, double y_d, int c);
	void getBuffer(int cloud_num);
	void bufferShift(double shift_x, double shift_y);
	void bufferTurn(double angle);
	void bufferScale(double scale);
	void setBuffer(int cloud_num);
	void createDistanceMatrix();
	void createBinaryMatrix(double delta);
	void startWaveAlg();
	void displayWaveAlg();
	void createDBBinaryMatrix(double delta, int st);
	void startDBWaveAlg();
	void displayDBScan();
	void spaningTree();
	void displaySpaningTree();
	void treeHist(int columns);
	void startKmeansAlgorithm(int k);
	void displayKMeansAlgorithm();
	void startEmAlgorithm(int k);
	void startKerKmeansAlgorithm(int k, int p);
	void displayKerKmeansAlgorithm();
	void forelAlgorithm(double radius, double coef);
	void hierAlgorithm();
	void displayHierAlgorithm();
	void delonayTriangulation();
	void funcInterpolation(double x, double y);
	void fieldInfo();
	void displayField();
};

