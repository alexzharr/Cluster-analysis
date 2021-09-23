//Zharikov Alexey 211

#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include "MyCtrl.h"
using namespace std;

class MyInterface
{
private:
	int id;
	string log;
	ofstream log_f;
	MyCtrl ctrl;
public:
	MyInterface();
	MyInterface(const unsigned int& id, string log);
	int getId() { return id; }
	string getDate();
	vector<string>& split(const string& s, char delim, vector<string>& elems);
	vector<string> split(const string& s, char delim);
	void toController(string user_command);
};

