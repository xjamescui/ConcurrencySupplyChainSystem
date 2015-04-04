#include <iostream>
#include <cstdlib>
#include "bottlingPlant.h"
#include "MPRNG.h"

using namespace std;

MPRNG g_randGenerator;

void uMain::main() {

    int seed = getpid();
    unsigned int numStudents = 4;
    unsigned int numVendingMachines = 8;
    unsigned int maxShippedPerFlavour = 5;
    unsigned int maxStockPerFlavour = 5;
    unsigned int timeBetweenShipments = 3;

    g_randGenerator.seed(seed);

    Printer printer(numStudents, numVendingMachines, 0);
    NameServer ns(printer, numVendingMachines, numStudents);
    BottlingPlant plant(printer, ns, numVendingMachines, maxShippedPerFlavour, maxStockPerFlavour, timeBetweenShipments);

} // main
