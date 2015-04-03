#include <iostream>
#include <cstdlib>
#include "MPRNG.h"
#include "config.h"

using namespace std;

MPRNG g_randGenerator; // global

void usage( char *argv[] ) {
    cerr << "Usage: " << "soda [ config-file [ random-seed ] ] " << endl;
    exit( EXIT_FAILURE );
} // usage


void uMain::main() {

    string filename = "soda.config";
    int seed = getpid();

    switch (argc) {
        case 3:
            filename = argv[1];
            seed = atoi(argv[2]);
            break;
        case 2:
            filename = argv[1];
            break;
        case 1:
            break;
        default:
            usage(argv);
    } // switch

    g_randGenerator.seed(seed);

    ConfigParms params;
    processConfigFile(filename.c_str(), params);

    // TODO
    cout << "Hi the program is running" << endl;
    cout << "sodaCost: " << params.sodaCost << endl;
    cout << "numStudents: " << params.numStudents << endl;
    cout << "maxPurchases: " << params.maxPurchases << endl;

} // uMain::main
