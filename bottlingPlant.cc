#include <iostream>
#include "bottlingPlant.h"
#include "truck.h"
#include "MPRNG.h"

using namespace std;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                              unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                              unsigned int timeBetweenShipments ) :
    printer(prt),
    nameServer(nameServer),
    NUM_VENDING_MACHINES(numVendingMachines),
    MAX_SHIPPED_PER_FLAVOUR(maxShippedPerFlavour),
    MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour),
    TIME_BETWEEN_SHIPMENTS(timeBetweenShipments),
    shutdown(false),
    totalProduced(0) {
    for (unsigned int i = 0; i < NUM_FLAVOURS; i += 1) {
        this->produced[i] = 0;
    } // for
} // constructor

void BottlingPlant::getShipment( unsigned int cargo[] ) {
    if (this->shutdown) {
        uRendezvousAcceptor();
        throw Shutdown();
    } // if

    for (unsigned int i = 0; i < NUM_FLAVOURS; i += 1) {
        cargo[i] = this->produced[i];
        this->produced[i] = 0;
    } // for

    printer.print(Printer::BottlingPlant, 'P');
} // getShipment


/**
 * Produce rand(MAX_SHIPPED_PER_FLAVOUR) stocks for each flavour
 */
void BottlingPlant::productionRun() {
    yield(TIME_BETWEEN_SHIPMENTS);
    this->totalProduced = 0;
    for (unsigned int i = 0; i < NUM_FLAVOURS; i += 1) {
        this->produced[i] = g_randGenerator(MAX_SHIPPED_PER_FLAVOUR);
        this->totalProduced += this->produced[i];
    } // for
    printer.print(Printer::BottlingPlant, 'G', this->totalProduced);
} // produce



void BottlingPlant::main() {
    printer.print(Printer::BottlingPlant, 'S');
    // create a truck
    Truck* truck = new Truck(printer, nameServer, *this, NUM_VENDING_MACHINES, MAX_STOCK_PER_FLAVOUR);

    // initial production and wait for truck to pick up
    this->productionRun();

    for (;;) {
        _Accept( ~BottlingPlant ) {
            this->shutdown = true;
            break;
        }
        or _Accept(getShipment) {
            this->productionRun();
        }
    } // for

    // need to wait for truck to come again so truck knows
    // we are shutting down
    _Accept(getShipment);

    delete truck;

    printer.print(Printer::BottlingPlant, 'F');
} // main
