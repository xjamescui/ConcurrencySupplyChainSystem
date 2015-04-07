#include <algorithm>
#include "truck.h"
#include "bottlingPlant.h"
#include "vendingMachine.h"

using namespace std;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
    printer(prt),
    nameServer(nameServer),
    bottlingPlant(plant),
    NUM_VENDING_MACHINES(numVendingMachines),
    MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour) {} // constructor

bool Truck::truckEmpty() {
    for (unsigned int i = 0; i < NUM_FLAVOURS; i += 1) {
        if (this->cargo[i] > 0) return false;
    } // for

    return true;
} // truckEmpty

unsigned int Truck::countCargo() {
    unsigned int total = 0;
    for (unsigned int i = 0; i < NUM_FLAVOURS; i += 1 ) {
        total += this->cargo[i];
    } // for
    return total;
} // countCargo

void Truck::main() {
    printer.print(Printer::Truck, 'S');
    // get location of each vending machine from the name server
    VendingMachine** machines = this->nameServer.getMachineList();
    unsigned int numVendingMachinesRestocked;
    unsigned int startingVendingMachine = 0;

    for (;;) {
        // yield
        yield(g_randGenerator(1,10));

        // throw any previous leftover sodas on the truck
        for (unsigned int i= 0; i < NUM_FLAVOURS; i += 1) {
            this->cargo[i] = 0;
        } // for

        // get new shipment from bottlingPlant
        try {
            this->bottlingPlant.getShipment(this->cargo);
            printer.print(Printer::Truck, 'P', countCargo());
        } catch (BottlingPlant::Shutdown& shutdown) {
            break;
        }

        numVendingMachinesRestocked = 0;

        // Cyclically restock each vending machine
        for (unsigned int i= startingVendingMachine ;; i = (i+1) % NUM_VENDING_MACHINES) {

            if (this->truckEmpty()) startingVendingMachine = i; // start with this vending machine next time shipment comes
            if (this->truckEmpty() || numVendingMachinesRestocked == NUM_VENDING_MACHINES) break; // empty truck or cycle completes

            // get stock levels of each flavour for this vending machine
            printer.print(Printer::Truck, 'd', i, countCargo());
            unsigned int *inventory = machines[i]->inventory();

            // restock each flavour
            unsigned int totalUnfilledAmount = 0;
            for (unsigned int f=0; f < NUM_FLAVOURS; f += 1) {
                int restockAmount= MAX_STOCK_PER_FLAVOUR - inventory[f];

                if (restockAmount > 0) {
                    restockAmount = min((unsigned int)restockAmount, this->cargo[f]);
                    inventory[f] += restockAmount;
                    totalUnfilledAmount += MAX_STOCK_PER_FLAVOUR - inventory[f];
                    this->cargo[f] -= restockAmount;
                } // if
            } // for

            if (totalUnfilledAmount > 0) printer.print(Printer::Truck, 'U', i, totalUnfilledAmount);

            // restocking is done for this vending machine
            machines[i]->restocked();
            numVendingMachinesRestocked += 1;
            printer.print(Printer::Truck, 'D', i, countCargo());
        } // for
    }

    printer.print(Printer::Truck, 'F');
} // main

