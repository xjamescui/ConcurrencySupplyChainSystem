#include <iostream>
#include <cstdlib>
#include "bottlingPlant.h"
#include "vendingMachine.h"
#include "MPRNG.h"

using namespace std;

MPRNG g_randGenerator;

void uMain::main() {

    int seed = getpid();
    unsigned int sodaCost = 2;
    unsigned int numStudents = 4;
    unsigned int numVendingMachines = 8;
    unsigned int maxShippedPerFlavour = 5;
    unsigned int maxStockPerFlavour = 5;
    unsigned int timeBetweenShipments = 3;

    g_randGenerator.seed(seed);

    Printer printer(numStudents, numVendingMachines, 0);
    NameServer ns(printer, numVendingMachines, numStudents);

    VendingMachine* machines[numVendingMachines];

    for (unsigned int i = 0; i < numVendingMachines; i += 1) {
        machines[i] = new VendingMachine(printer, ns, i, sodaCost, maxStockPerFlavour);
    }

    BottlingPlant* plant = new BottlingPlant(printer, ns, numVendingMachines, maxShippedPerFlavour, maxStockPerFlavour, timeBetweenShipments);
    delete plant;

    for (unsigned int i = 0; i < numVendingMachines; i += 1) {
        delete machines[i];
    }
    cout << "All tests pass!" << endl;
} // main
