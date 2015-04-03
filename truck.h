#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "printer.h"
#include "nameServer.h"
#include "bottlingPlant.h"

_Task Truck {
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif // __TRUCK_H__
