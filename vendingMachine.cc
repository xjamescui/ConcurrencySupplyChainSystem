#include "vendingMachine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
        unsigned int maxStockPerFlavour ){}
void VendingMachine::buy( Flavours flavour, WATCard &card ){}
unsigned int* VendingMachine::inventory(){}
void VendingMachine::restocked(){}
_Nomutex unsigned int VendingMachine::cost(){}
_Nomutex unsigned int VendingMachine::getId(){}

void VendingMachine::main(){}
