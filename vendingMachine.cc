#include "vendingMachine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ) :
    printer(&prt),
    nameServer(&nameServer),
    id(id),
    SODA_COST(sodaCost),
    MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour) ,
    NUM_FLAVOURS(4),
    restocking(false) {

        for (unsigned int i = 0; i < NUM_FLAVOURS; i ++) {
            this->stockLevel[i] = 0;
        } // for
    } // constructor

void VendingMachine::buy( Flavours flavour, WATCard &card ){

    if (this->restocking) _Accept(restocked);

    if (this->stockLevel[flavour] == 0) throw new Stock;
    if (card.getBalance() < SODA_COST) throw new Funds;

    this->stockLevel[flavour] -= 1;
    card.withdraw(SODA_COST);
} // buy

unsigned int* VendingMachine::inventory(){
    this->restocking = true;
    return this->stockLevel;
} // inventory

void VendingMachine::restocked(){
    this->restocking = false;
} // restocked

_Nomutex unsigned int VendingMachine::cost(){
    return SODA_COST;
} // cost

_Nomutex unsigned int VendingMachine::getId(){
    return this->id;
} // getId

void VendingMachine::main(){
    // registering with name server
    this->nameServer->VMregister(this);

    for (;;) {
        _Accept(~VendingMachine) {
            break;
        }
    } // for

}// main
