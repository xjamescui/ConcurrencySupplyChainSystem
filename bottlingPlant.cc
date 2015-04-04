#include "bottlingPlant.h"
#include "truck.h"
#include "MPRNG.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                              unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                              unsigned int timeBetweenShipments ) :
    printer(&prt),
    nameServer(&nameServer),
    NUM_VENDING_MACHINES(numVendingMachines),
    MAX_SHIPPED_PER_FLAVOUR(maxShippedPerFlavour),
    MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour),
    TIME_BETWEEN_SHIPMENTS(timeBetweenShipments),
    shutdown(false) {} // constructor

void BottlingPlant::getShipment( unsigned int cargo[] ) {
    if (this->shutdown) {
        uRendezvousAcceptor();
        throw Shutdown();
    } // if

    for (unsigned int i = 0; i < NUM_FLAVOURS; i += 1) {
        cargo[i] = this->produced[i];
        this->produced[i] = 0;
    } // for
} // getShipment

void BottlingPlant::produce() {
    for (unsigned int i = 0; i < NUM_FLAVOURS; i += 1) {
        this->produced[i] = g_randGenerator(MAX_SHIPPED_PER_FLAVOUR);
    } // for
} // produce

void BottlingPlant::main() {

    // create a truck
    Truck* truck = new Truck(*printer, *nameServer, *this, NUM_VENDING_MACHINES, MAX_STOCK_PER_FLAVOUR);

    // initial production and wait for truck to pick up
    this->produce();

    for (;;) {

        _Accept(~BottlingPlant) {
            this->shutdown = true;

            // need to wait for truck to come again so truck knows
            // we are shutting down
            _Accept(getShipment);
            break;
        }
        or _Accept(getShipment) {
            yield(TIME_BETWEEN_SHIPMENTS);
            this->produce();
        }
    } // for

    delete truck;
} // main
