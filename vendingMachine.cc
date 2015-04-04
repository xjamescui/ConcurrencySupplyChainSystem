#include "vendingMachine.h"
#include "config.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) :
    printer(&prt),
    nameServer(&nameServer),
    id(id),
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
    if (card.getBalance() < SODA_COST) throw Funds();

    this->stockLevel[flavour] -= 1;
    card.withdraw(SODA_COST);
} // buy

unsigned int* VendingMachine::inventory() {
    this->restocking = true;
    return this->stockLevel;
} // inventory

void VendingMachine::restocked() {
    this->restocking = false;
} // restocked

_Nomutex unsigned int VendingMachine::cost() {
    return SODA_COST;
} // cost

_Nomutex unsigned int VendingMachine::getId() {
    return this->id;
} // getId

void VendingMachine::main() {
    // registering with name server
    this->nameServer->VMregister(this);

    for (;;) {
        _Accept(~VendingMachine) {
            break;
        }
        or _When (this->restocking) _Accept(restocked) {
        } or _When (!this->restocking) _Accept(buy, inventory) {
        }
    } // for

}// main
