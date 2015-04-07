#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "printer.h"
#include "nameServer.h"
#include "config.h"

_Task BottlingPlant {
    Printer& printer;
    NameServer& nameServer;

    const unsigned int NUM_VENDING_MACHINES;
    const unsigned int MAX_SHIPPED_PER_FLAVOUR;
    const unsigned int MAX_STOCK_PER_FLAVOUR;
    const unsigned int TIME_BETWEEN_SHIPMENTS;

    bool shutdown;

    unsigned int totalProduced;
    unsigned int produced[NUM_FLAVOURS];
    void productionRun();
    void main();
public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                   unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                   unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
};

#endif // __BOTTLINGPLANT_H__
