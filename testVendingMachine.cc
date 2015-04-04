#include <iostream>
#include "vendingMachine.h"
#include "watcard.h"
#include <assert.h>
using namespace std;

void cardAndMachineTests(WATCard &card, VendingMachine &vm);

void uMain::main() {
    unsigned int sodaCost = 2;
    unsigned int maxStockPerFlavour = 5;
    unsigned int numStudents = 3;
    unsigned int numVendingMachines = 3;
    unsigned int numCouriers = 2;
    unsigned int vmId = 1;

    Printer printer(numStudents, numVendingMachines, numCouriers);
    NameServer ns(printer, numVendingMachines, numStudents);
    WATCard card;

    VendingMachine vm(printer, ns, vmId, sodaCost, maxStockPerFlavour);

    cout << "NOW TESTING VENDING MACHINE..." << endl;
    assert(vm.cost() == sodaCost);
    assert(vm.getId() == vmId);

    cardAndMachineTests(card, vm);

    cout << "DONE!" << endl;

} // uMain::main


void cardAndMachineTests(WATCard &card, VendingMachine &vm) {

    cout << "buying soda but no stock and with 0 balance on card.." << endl;
    try{
        vm.buy((VendingMachine::Flavours)1, card);
    } catch (VendingMachine::Stock &s) {
        cout << "GOOD! caught Stock exception" << endl;
    }

}
