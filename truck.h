#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"
#include "MPRNG.h"

_Task Truck {
    Printer* printer;
    NameServer* nameServer;
    BottlingPlant* bottlingPlant;
    const unsigned int NUM_VENDING_MACHINES;
    const unsigned int MAX_STOCK_PER_FLAVOUR;
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif // __TRUCK_H__
