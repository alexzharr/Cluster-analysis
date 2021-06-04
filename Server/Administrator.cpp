#include "Administrator.h"
#pragma warning (disable:4996)

Administrator::Administrator() {}

Administrator::Administrator(const Administrator& admin) { ctrl = admin.ctrl; }

const Administrator& Administrator::operator=(const Administrator& admin) { ctrl = admin.ctrl; return *this; }

void Administrator::open_log()
{
    ofstream log_file("LOG FILE.txt");
    log_file << "Process started\n\n";
    log_file.close();
}

void Administrator::read_command(char* command)
{
    ofstream log_file("LOG FILE.txt", ios::app);
    bool check_command;
    char* c = strtok(command, " ");
    string s, com(c);
    vector <string> args;
    double t_1, t_2;
    ifstream help;

    check_command = false;
    if (command == "EXIT" || command == "exit" || strcmp(command, "EXIT")==0)
    {
        log_file << "The EXIT command was called -- successfully.\n\n";
        check_command = true;
    }
    if (command == "HELP" || command == "help")
    {
        log_file << "The HELP command was called -- successfully.\n\n";
        check_command = true;
        help.open("HELP.txt");
        while (getline(help, s)) cout << s << endl;
        cout << "\n";
        help.close();
    }
    if (command == "INFO" || command == "info")
    {
        log_file << "The INFO command was called -- successfully.\n\n";
        check_command = true;
    }
    while (c != NULL) {
        c = strtok(NULL, " ");
        if (c == NULL)
        {
            break;
        }
        args.push_back(c);
    }
    if (com == "GEN_CLOUD" || com == "generate_cloud")
    {
        if (args.size() == 0 && ctrl.getMode() == false)
        {
            ctrl.genCloud(1, 2, 1, 1, 100);
            ctrl.genCloud(2, -2, 3, 3, 50);

            log_file << "Generate cloud  -- successfuly.\n\n";
        }
        if ((args.size() < 5 || args.size() > 5) && ctrl.getMode() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 5 && ctrl.getMode() == false)
        {
            ctrl.genCloud(stod(args[0]), stod(args[1]), stod(args[2]), stod(args[3]), stod(args[4]));
            log_file << "Generate cloud: " << args[0] << " " << args[1] << " " << args[2] << " " << args[3] << " " << args[4] << " -- successfuly.\n\n";
        }
        check_command = true;
    }
    if (com == "MATRIX" || com == "matrix")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the creation of the distance matrix";
            t_1 = clock();
            ctrl.createDistanceMatrix();
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "BINARY" || com == "binary")
    {
        if (args.size() == 1)
        {
            log_file << "Starting the creation of the binary matrix (delta = " << stod(args[0]) << ")";
            t_1 = clock();
            ctrl.createBinaryMatrix(stod(args[0]));
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "DBBINARY" || com == "dbbinary")
    {
        if (args.size() == 2)
        {
            log_file << "Starting the creation of the dbbinary matrix (delta = " <<
                stod(args[0]) << ", (number of neigh&*oufffrs) = " << stod(args[1]);
            t_1 = clock();
            ctrl.createDBBinaryMatrix(stod(args[0]), stod(args[1]));
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "DISPLAY_FIELD" || com == "display_field")
    {
        ctrl.displayField();
        log_file << "Printing field to a file -- successfully.\n\n";
        check_command = true;
    }
    if (com == "GET_BUFFER" || com == "get_buffer")
    {
        if ((args.size() == 0 || args.size() > 1) && ctrl.getMode() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1 && ctrl.getMode() == false)
        {
            ctrl.getBuffer(stod(args[0]));
            log_file << "Add " << args[0] << "-th cloud from field in buffer -- successfully.\n\n";
        }
        if (ctrl.getMode() == true) log_file << "Attempt to add cloud from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "SET_BUFFER" || com == "set_buffer")
    {
        if ((args.size() == 0 || args.size() > 1) && ctrl.getMode() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1 && ctrl.getMode() == false)
        {
            ctrl.setBuffer(stod(args[0]));
            log_file << "Upload " << args[0] << "-th cloud from the buffer in field -- successfully.\n\n";
        }
        if (ctrl.getMode() == true) log_file << "Attempt to upload cloud from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "SHIFT" || com == "shift")
    {
        if ((args.size() < 3 || args.size() > 3) && ctrl.getMode() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 3 && ctrl.getMode() == false)
        {
            ctrl.bufferShift(stod(args[0]), stod(args[1]));
            log_file << "Shift " << args[0] << "-th cloud in buffer by vector (" << args[1] << ", " << args[2] << ") -- successfully.\n\n";
        }
        if (ctrl.getMode() == true) log_file << "Attempt to shift cloud from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "TURN" || com == "turn")
    {
        if ((args.size() < 2 || args.size() > 2) && ctrl.getMode() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 2 && ctrl.getMode() == false)
        {
            ctrl.bufferTurn(stod(args[0]));
            log_file << "Turn " << args[0] << "-th cloud in buffer at an angle " << args[1] << " -- successfully.\n\n";
        }
        if (ctrl.getMode() == true) log_file << "Attempt to turn cloud from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "SCALE" || com == "scale")
    {
        if ((args.size() < 2 || args.size() > 2) && ctrl.getMode() == false) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 2 && ctrl.getMode() == false)
        {
            ctrl.bufferScale(stod(args[0]));
            log_file << "Compression " << args[0] << "-th cloud in buffer -- successfully.\n\n";
        }
        if (ctrl.getMode() == true) log_file << "Attempt to compression cloud from field in buffer in the analysis state.\n\n";
        check_command = true;
    }
    if (com == "WAVE" || com == "wave")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the wave algorithm";
            t_1 = clock();
            ctrl.startWaveAlg();
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "DISPLAY_WAVE" || com == "display_wave")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the wave algorithm";
            t_1 = clock();
            ctrl.displayWaveAlg();
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
    }
    if (com == "DBSCAN" || com == "dbscan")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the DBSCAN algorithm, delta=1, k=1";
            t_1 = clock();
            ctrl.startDBWaveAlg();
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        if (args.size() == 1 || args.size() > 2) { log_file << "Incorrect data entered.\n\n"; }
        check_command = true;
    }
    if (com == "DISPLAY_DB" || com == "display_db")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the wave algorithm";
            t_1 = clock();
            ctrl.displayDBScan();
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "SPAINING_TREE" || com == "spaining_tree")
    {
        log_file << "Starting the spanning tree algorithm";
        t_1 = clock();
        ctrl.spaningTree();
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (com == "TREE_HIST" || com == "tree_hist")
    {
        log_file << "Starting the spanning tree histogram algorithm";
        t_1 = clock();
        ctrl.treeHist(stod(args[0]));
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (com == "K_MEANS" || com == "k_means")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the k means algorithm, k=1";
            t_1 = clock();
            ctrl.startKmeansAlgorithm(1);
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        if (args.size() > 1) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1)
        {
            log_file << "Starting the k means algorithm, k=" << args[0];
            t_1 = clock();
            ctrl.startKmeansAlgorithm(stod(args[0]));
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "DISPLAY_KMEANS" || com == "display_kmeans")
    {
        log_file << "Displaying the kmeans algorithm";
        t_1 = clock();
        ctrl.displayKMeansAlgorithm();
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (com == "KKM" || com == "kkm")
    {
        log_file << "Starting the spanning tree histogram algorithm";
        t_1 = clock();
        ctrl.startKerKmeansAlgorithm(stod(args[0]), stod(args[0]));
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (com == "DISPLAY_KKM" || com == "display_kkm")
    {
        log_file << "Displaying the kkm algorithm";
        t_1 = clock();
        ctrl.displayKerKmeansAlgorithm();
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (com == "EM" || com == "em")
    {
        if (args.size() == 0)
        {
            log_file << "Starting the em algorithm, k=1";
            t_1 = clock();
            ctrl.startEmAlgorithm(1);
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        if (args.size() > 1) { log_file << "Incorrect data entered.\n\n"; }
        if (args.size() == 1)
        {
            log_file << "Starting the EM algorithm, k=" << args[0];
            t_1 = clock();
            ctrl.startEmAlgorithm(stod(args[0]));
            t_2 = clock();
            log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        }
        check_command = true;
    }
    if (com == "HIERARCHY" || com == "hierarchy")
    {
        log_file << "Starting the hierarchical algorithm";
        t_1 = clock();
        ctrl.hierAlgorithm();
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (com == "DISPLAY_HIER" || com == "display_hier")
    {
        log_file << "Displaying the hierarchical algorithm";
        t_1 = clock();
        ctrl.displayHierAlgorithm();
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (com == "TRIANGULATE" || com == "triangulate")
    {
        log_file << "Starting the Dealonay triangulation algorithm";
        t_1 = clock();
        ctrl.delonayTriangulation();
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (com == "INTERPOL" || com == "interpol")
    {
        log_file << "Starting the interpolation algorithm";
        t_1 = clock();
        ctrl.funcInterpolation(stod(args[0]), stod(args[1]));
        t_2 = clock();
        log_file << " -- successfully.\nTime: " << (t_2 - t_1) / CLOCKS_PER_SEC << ".\n\n";
        check_command = true;
    }
    if (check_command == false) log_file << "Entered command that could not be recognized.\n\n";
}