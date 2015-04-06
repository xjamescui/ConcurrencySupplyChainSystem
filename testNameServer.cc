#include <iostream>
#include "nameServer.h"
#include "vendingMachine.h"
#include <assert.h>
#include "MPRNG.h"

using namespace std;

MPRNG g_randGenerator; // global

void uMain::main() {

    int seed = getpid();
    unsigned int numStudents = 20;
    unsigned int numVendingMachines = 8;
    unsigned int maxStockPerFlavour = 5;
    unsigned int sodaCost = 4;

    g_randGenerator.seed(seed);

    Printer printer(numStudents, numVendingMachines, 0);
    NameServer ns(printer, numVendingMachines, numStudents);

    VendingMachine* machines[numVendingMachines];

    for (unsigned int i = 0; i < numVendingMachines; i += 1) {
        machines[i] = new VendingMachine(printer, ns, i, sodaCost, maxStockPerFlavour);
    }

    assert(ns.getMachine(0)->getId() == 0);
    assert(ns.getMachine(1)->getId() == 1);
    assert(ns.getMachine(2)->getId() == 2);
    assert(ns.getMachine(16)->getId() == 0);
    assert(ns.getMachine(18)->getId() == 2);
    assert(ns.getMachine(19)->getId() == 3);

    VendingMachine** list = ns.getMachineList();

    assert (list != NULL);
    for (unsigned int i = 0; i < numVendingMachines; i += 1) {
        assert(list[i]->getId() == i);
        assert(list[i]->cost() == sodaCost);
    }

    cout << "all tests pass!" << endl;


    for (unsigned int i = 0; i < numVendingMachines; i += 1) {
        delete machines[i];
    }

} // uMain::main
