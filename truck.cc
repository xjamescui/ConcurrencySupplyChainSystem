#include "truck.h"

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : 
    printer(&prt), 
    nameServer(&nameServer), 
    bottlingPlant(&bottlingPlant),
    NUM_VENDING_MACHINES(numVendingMachines), 
    MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour){} // constructor

void Truck::main(){

    // get location of each vending machine from the name server
    VendingMachine** machines = this->nameServer->getMachineList();

    // yield
    yield(g_randGenerator(1,10));

    // get new shipment from bottlingPlant
    this->bottlingPlant->getShipment()

} // main

