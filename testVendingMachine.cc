#include <iostream>
#include "vendingMachine.h"
#include "watcard.h"
#include "bottlingPlant.h"
#include "MPRNG.h"
#include <assert.h>
using namespace std;

#define SODA_COST 2

MPRNG g_randGenerator(getpid());

void cardAndMachineTests(WATCard &card, VendingMachine &vm);

void uMain::main() {
    unsigned int maxStockPerFlavour = 5;
    unsigned int maxShippedPerFlavour = 3;
    unsigned int numStudents = 3;
    unsigned int numVendingMachines = 1;
    unsigned int numCouriers = 2;
    unsigned int vmId = 0;
    unsigned int timeBetweenShipments = 4;

    Printer printer(numStudents, numVendingMachines, numCouriers);
    NameServer ns(printer, numVendingMachines, numStudents);
    WATCard card;

    VendingMachine vm(printer, ns, vmId, SODA_COST, maxStockPerFlavour);

    cout << "NOW TESTING VENDING MACHINE..." << endl;
    assert(vm.cost() == SODA_COST);
    assert(vm.getId() == vmId);

    // has no stock and no money
    assert(card.getBalance() == 0);
    cout << "buying soda but no stock and with 0 balance on card.." << endl;
    try{
        vm.buy((VendingMachine::Flavours)1, card);
    } catch (VendingMachine::Funds &f) {
        cout << "BAD! caught Funds exception" << endl;
    } catch (VendingMachine::Stock &s) {
        cout << "GOOD! caught Stock exception" << endl;
    }

    // create bottling plant
    BottlingPlant plant(printer, ns, numVendingMachines, maxShippedPerFlavour, maxStockPerFlavour, timeBetweenShipments);

    yield(200);

    cardAndMachineTests(card, vm);

    cout << "DONE!" << endl;

} // uMain::main


void cardAndMachineTests(WATCard &card, VendingMachine &vm) {

    // has stock but no money
    assert (card.getBalance() == 0);
    cout << "buying soda but not enough money...." << endl;
    try{
        vm.buy((VendingMachine::Flavours)1, card);
    } catch (VendingMachine::Funds &f) {
        cout << "GOOD! caught Funds exception" << endl;
    } catch (VendingMachine::Stock &s) {
        cout << "BAD! caught Stock exception" << endl;
    }

    // has stock and enough money, now buy again
    cout << "reloading card with soda cost..." << endl;
    card.deposit(SODA_COST); 
    assert(card.getBalance() == SODA_COST);

    cout << "now buying again with stock and funds..." << endl;
    try{
        vm.buy((VendingMachine::Flavours)1, card);
    } catch (VendingMachine::Funds &f) {
        cout << "BAD! caught Funds exception" << endl;
    } catch (VendingMachine::Stock &s) {
        cout << "BAD! caught Stock exception" << endl;
    }

}
