#include <iostream>
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

void usage( char *argv[] ) {
    cerr << "Usage: " << "soda [ config-file [ random-seed ] ] " << endl;
    exit( EXIT_FAILURE );
} // usage


void uMain::main() {

    string filename = "soda.config";
    int seed = getpid();
    switch (argc) {
        case 3:
            seed = atoi(argv[2]);
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
    }

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
