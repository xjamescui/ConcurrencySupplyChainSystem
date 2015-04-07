#include <iostream>
#include <sstream>
#include <cstdlib>
#include "MPRNG.h"
#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "student.h"
#include "nameServer.h"
#include "watcardOffice.h"
#include "vendingMachine.h"
#include "bottlingPlant.h"

using namespace std;

MPRNG g_randGenerator; // global

bool convert(int &val, char *buffer) {		// convert C string to integer
    std::stringstream ss( buffer );		// connect stream and buffer
    ss >> dec >> val;				// convert integer from buffer
    return ! ss.fail() &&			// conversion successful ?
           // characters after conversion all blank ?
           string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

void usage( char *argv[] ) {
    cerr << "Usage: " << "soda [ config-file [ random-seed ] ] " << endl;
    exit( EXIT_FAILURE );
} // usage


void uMain::main() {

    string filename = "soda.config";    // default value.
    int seed = getpid();                // default value.
    switch (argc) {
      case 3:
        if (!convert(seed,argv[2]) || seed < 0) {
            cerr << "Seed must be a positive integer" << endl;
            exit( EXIT_FAILURE );
        } // if
      case 2:
        filename = argv[1];
      case 1:
        break;
      default:
        usage(argv);
    } // switch

    g_randGenerator.seed(seed);

    ConfigParms params;
    processConfigFile(filename.c_str(), params);

    Printer printer(params.numStudents, params.numVendingMachines, params.numCouriers);
    Bank bank(params.numStudents);
    Parent parent(printer, bank, params.numStudents, params.parentalDelay);
    WATCardOffice office(printer, bank, params.numCouriers);
    NameServer ns(printer, params.numVendingMachines, params.numStudents);

    VendingMachine* machines[params.numVendingMachines];

    for (unsigned int id = 0; id < params.numVendingMachines; ++id) {
        machines[id] = new VendingMachine(printer, ns, id, params.sodaCost, params.maxStockPerFlavour);
    } // for

    {
        // this scope is used to ensure that bottling plant is deleted before the vending machines
        BottlingPlant plant(printer, ns, params.numVendingMachines, params.maxShippedPerFlavour, params.maxStockPerFlavour, params.timeBetweenShipments);
        Student* students[params.numStudents];

        for (unsigned int id = 0; id < params.numStudents; ++id) {
            students[id] = new Student(printer, ns, office, id, params.maxPurchases);
        } // for

        for (unsigned int id = 0; id < params.numStudents; ++id) {
            delete students[id];
        } // for

    } // scope

    for (unsigned int id = 0; id < params.numVendingMachines; ++id) {
        delete machines[id];
    } // for

} // uMain::main
