#include <iostream>
#include "vendingMachine.h"

using namespace std;

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) :
    printer(prt),
    nameServer(nameServer),
    ID(id),
    SODA_COST(sodaCost),
    MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour) ,
    restocking(false) {

    for (unsigned int i = 0; i < NUM_FLAVOURS; i ++) {
        this->stockLevel[i] = 0;
    } // for
} // constructor

void VendingMachine::buy( Flavours flavour, WATCard &card ) {

    if (this->stockLevel[flavour] == 0) {
        uRendezvousAcceptor();
        throw Stock();
    }
    if (card.getBalance() < SODA_COST) {
        uRendezvousAcceptor();
        throw Funds();
    }

    this->stockLevel[flavour] -= 1;
    card.withdraw(SODA_COST);
    printer.print(Printer::Vending, ID, 'B', flavour, this->stockLevel[flavour]); 
} // buy

unsigned int* VendingMachine::inventory() {
    printer.print(Printer::Vending, ID, 'r');
    this->restocking = true;
    return this->stockLevel;
} // inventory

void VendingMachine::restocked() {
    this->restocking = false;
    printer.print(Printer::Vending, ID, 'R');
} // restocked

_Nomutex unsigned int VendingMachine::cost() {
    return SODA_COST;
} // cost

_Nomutex unsigned int VendingMachine::getId() {
    return ID;
} // getId

void VendingMachine::main() {
    printer.print(Printer::Vending, ID, 'S', SODA_COST); 
    // registering with name server
    this->nameServer.VMregister(this);

    for (;;) {
        _Accept(~VendingMachine) {
            break;
        }
        or _When (this->restocking) _Accept(restocked) {
        } or _When (!this->restocking) _Accept(buy, inventory) {
        }
    } // for

    printer.print(Printer::Vending, ID, 'F');
}// main
