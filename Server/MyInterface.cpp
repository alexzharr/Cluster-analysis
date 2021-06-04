//Zharikov Alexey 211

/*#include "MyInterface.h"

MyInterface::MyInterface() : id(0), log("defaultlog.txt")
{
	log_f.open("D:\\logs\\" + log);
}
MyInterface::MyInterface(const unsigned int& id, string log) :
	id(id), log(log)
{
	log_f.open("D:\\logs\\" + log);
}
string MyInterface::getDate()
{
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	return to_string(1900 + ltm.tm_year) + '/' + to_string(1 + ltm.tm_mon) +
		'/' + to_string(ltm.tm_mday) + ' ' + to_string(ltm.tm_hour) + ':' +
		to_string(ltm.tm_min) + ':' + to_string(ltm.tm_sec);
}
vector<string>& MyInterface::split(const string& s, char delim, vector<string>& elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
		elems.push_back(item);
	return elems;
}
vector<string> MyInterface::split(const string& s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}
void MyInterface::toController(string user_command)
{
	vector<string> parsedString(split(user_command, ' '));
	vector<string> u;

	for (const auto& elem : parsedString)
		u.push_back(elem);
	if (u.size() == 0)
		return;
	if (u[0] == "HELP")
		ctrl.printHelpFile();
	else if (u[0] == "GEN_CLOUD")
	{
		cout << "...";
		if (ctrl.field.getMode() == true)
		{
			ctrl.genCloud(atof(u[1].c_str()), atof(u[2].c_str()),
				atof(u[3].c_str()), atof(u[4].c_str()), stoi(u[5].c_str()));
			log_f << getDate() << " [INFO] " << "User " << id << " generated "
				<< "cloud " << ctrl.field.clouds.size() - 1 << "." << endl;
		}
		else
		{
			log_f << getDate() << " [ERROR] "
				<< "User " << id << " Cloud generation request was rejected "
				<< "(Generation mode was false)" << endl;
			cout << "You can't use this command while gen_mode=false." << endl;
		}
		cout << "Done!" << endl;
	}
	else if (u[0] == "GEN_RECTANGLE")
	{
		cout << "...";
		if (ctrl.field.getMode() == true)
		{
			ctrl.genRect(atof(u[1].c_str()), atof(u[2].c_str()),
				atof(u[3].c_str()), atof(u[4].c_str()), stoi(u[5].c_str()));
			log_f << getDate() << " [INFO] " << "User " << id << " generated "
				<< "cloud " << ctrl.field.clouds.size() - 1 << "." << endl;
		}
		else
		{
			log_f << getDate() << " [ERROR] "
				<< "User " << id << " Rectangle generation request was rejected "
				<< "(Generation mode was false)" << endl;
			cout << "You can't use this command while gen_mode=false." << endl;
		}
		cout << "Done!" << endl;
	}
	else if (u[0] == "GET")
	{
		cout << "...";
		ctrl.getBuffer(stoi(u[1].c_str()));
		log_f << getDate() << " [INFO] " << "User " << id << " took " <<
			"the cloud " << stoi(u[1].c_str()) << " to the buffer." << endl;
		cout << "Done!" << endl;
	}
	else if (u[0] == "SHIFT")
	{
		cout << "...";
		ctrl.bufferShift(atof(u[1].c_str()), atof(u[2].c_str()));
		log_f << getDate() << " [INFO] " << "User " << id << " shifted " <<
			"the buffer cloud by (" << atof(u[1].c_str()) << '; ' <<
			atof(u[2].c_str()) << ")." << endl;
		cout << "Done!" << endl;
	}
	else if (u[0] == "TURN")
	{
		cout << "...";
		ctrl.bufferTurn((Pi / 180) * atof(u[1].c_str()));
		log_f << getDate() << " [INFO] " << "User " << id << " turned " <<
			"the buffer cloud by (" << atof(u[1].c_str()) << " degrees)." <<
			endl;
		cout << "Done!" << endl;
	}
	else if (u[0] == "SCALE")
	{
		cout << "...";
		ctrl.bufferScale(atof(u[1].c_str()));
		log_f << getDate() << " [INFO] " << "User " << id << " scaled " <<
			"the buffer cloud by " << atof(u[1].c_str()) << "." << endl;
		cout << "Done!" << endl;
	}
	else if (u[0] == "SET")
	{
		cout << "...";
		ctrl.setBuffer(stoi(u[1].c_str()));
		log_f << getDate() << " [INFO] " << "User " << id <<
			" placed the buffer cloud in the field (as cloud " <<
			atof(u[1].c_str()) << ")." << endl;
		cout << "Done!" << endl;
	}
	/*else if (u[0] == "CREATE_HIST")
	{
		ctrl.createHists(stoi(u[1].c_str()));
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created field histogram." << endl;
	}
	else if (u[0] == "CREATE_CLOUD_HIST")
	{
		ctrl.createCloudHists(stoi(u[1].c_str()), stoi(u[2].c_str()));
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created cloud " << stoi(u[1].c_str()) << " histogram." << endl;
	}
	else if (u[0] == "MATRIX")
	{
		cout << "...";
		ctrl.createDistanceMatrix();
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created distance matrix. Generation mode changed to " <<
			ctrl.field.getMode() << "." << endl;
		cout << "Done!" << endl;
	}
	else if (u[0] == "BINARY")
	{
		cout << "...";
		ctrl.createBinaryMatrix(atof(u[1].c_str()));
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created binary matrix (delta = " << atof(u[1].c_str()) << ")." << endl;
		cout << "Done!" << endl;
	}
	else if (u[0] == "WAVE")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" started the \'Connected component\' algorithm. ";
		ctrl.startWaveAlg();
		cout << "Done!" << endl;
	}
	else if (u[0] == "DISPLAY_WAVE")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created datafiles for the result of the dbscan algorithm (" <<
			"WaveEdges.txt).";
		ctrl.displayWaveAlg();
		cout << "Done!" << endl;
	}
	else if (u[0] == "DBBINARY")
	{
		cout << "...";
		ctrl.createDBBinaryMatrix(atof(u[1].c_str()), stoi(u[2].c_str()));
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created binary matrix taking into account only kernal and " <<
			"periphery points (delta = " << atof(u[1].c_str()) << ", " <<
			"deg = " << stoi(u[2].c_str()) << ")." << endl;
		cout << "Done!" << endl;
	}
	else if (u[0] == "DBWAVE")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" started the \'Dbscan\' algorithm. " << endl;
		ctrl.startDBWaveAlg();
		cout << "Done!" << endl;
	}
	else if (u[0] == "DISPLAY_DB")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created datafiles for the result of the dbscan algorithm (" <<
			"Kernal.txt, Periphery.txt, Dust.txt, DBEdges.txt)." << endl;
		ctrl.displayDBScan();
		cout << "Done!" << endl;
	}
	else if (u[0] == "SPTREE")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" started the \'Spaning tree\' algorithm." << endl;
		ctrl.spaningTree();
		cout << "Done!" << endl;
	}
	else if (u[0] == "DISPLAY_TREE")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created data file for the result of the spaning tree algorithm "
			<< " (SpainingTree.txt)." << endl;
		ctrl.displaySpaningTree();
		cout << "Done!" << endl;
	}
	else if (u[0] == "TREE_HIST")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created data file for displaying tree edges histogram"
			<< " (TreeHist.txt)." << endl;
		ctrl.spaningTreeHistogram(stoi(u[1].c_str()));
		cout << "Done!" << endl;
	}
	else if (u[0] == "KMEANS")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" started the \'Kmeans\' algorithm to find " <<
			stoi(u[1].c_str()) << " clusters. " << endl;
		ctrl.startKmeansAlgorithm(stoi(u[1].c_str()));
		cout << "Done!" << endl;
	}
	else if (u[0] == "DISPLAY_KMEANS")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created data file for the result of the Kmeans algorithm " <<
			"(Kmeans.txt)." << endl;
		ctrl.displayKMeansAlgorithm();
		cout << "Done!" << endl;
	}
	else if (u[0] == "EM")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" started the \'EM\' algorithm to find " << stoi(u[1].c_str()) <<
			" clusters. " << endl;
		ctrl.startEmAlgorithm(stoi(u[1].c_str()));
		cout << "Done!" << endl;
	}
	else if (u[0] == "KKMEANS")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" started the \'KerKmeans\' algorithm to find " <<
			stoi(u[1].c_str()) << " clusters with " << stoi(u[2].c_str()) <<
			" kernal points." << endl;
		ctrl.startKerKmeansAlgorithm(stoi(u[1].c_str()), stoi(u[2].c_str()));
		cout << "Done!" << endl;
	}
	else if (u[0] == "DISPLAY_KKMEANS")
	{
	cout << "...";
	log_f << getDate() << " [INFO] " << "User " << id <<
		" created data files for the result of the KerKmeans algorithm (" <<
		"KersKmeans.txt, Kerkmeans.txt)." << endl;
	ctrl.displayKerKmeansAlgorithm();
	cout << "Done!" << endl;
	}
	else if (u[0] == "INFO_FIELD")
		ctrl.fieldInfo();
	else if (u[0] == "INFO")
	{
		ctrl.sessionInfo(stoi(u[1].c_str()));
	}
	else if (u[0] == "FOREL")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" started the \'Forel\' algorithm with a radius of " <<
			atof(u[1].c_str()) << endl;
		ctrl.forelAlgorithm(atof(u[1].c_str()), atof(u[2].c_str()));
		cout << "Done!" << endl;
	}
	else if (u[0] == "HIER")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" started the Hierarchical algorithm" << endl;
		ctrl.hierAlgorithm();
	cout << "Done!" << endl;
	}
	else if (u[0] == "DISPLAY_HIER")
	{
		cout << "...";
		log_f << getDate() << " [INFO] " << "User " << id <<
			" created data file for the result of the Hierarchical algorithm (" <<
			"HierEdges.txt)." << endl;
		ctrl.displayHierAlgorithm();
		cout << "Done!" << endl;
	}
	else if (u[0] == "DISPLAY_FIELD")
	{
		cout << "...";
		ctrl.displayField();
		cout << "Done!" << endl;
	}
	else
		cout << "Unknown command. Write \"help\" to see a list of commands\n";
}*/