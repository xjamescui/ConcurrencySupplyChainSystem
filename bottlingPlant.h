#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "nameServer.h"

_Task BottlingPlant {
    void main();
  public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
};

#endif // __BOTTLINGPLANT_H__
