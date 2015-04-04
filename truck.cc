#include <algorithm>
#include "truck.h"
#include "bottlingPlant.h"
#include "vendingMachine.h"

using namespace std;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
    printer(prt),
    nameServer(nameServer),
    bottlingPlant(bottlingPlant),
    NUM_VENDING_MACHINES(numVendingMachines),
    MAX_STOCK_PER_FLAVOUR(maxStockPerFlavour) {} // constructor

bool Truck::truckEmpty() {
    for (unsigned int i = 0; i < NUM_FLAVOURS; i += 1) {
        if (this->cargo[i] > 0) return false;
    }// for

    return true;
}
void Truck::main() {

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
        } catch (BottlingPlant::Shutdown& shutdown) {
            return;
        }

        numVendingMachinesRestocked = 0;

        // Cyclically restock each vending machine
        for (unsigned int i= startingVendingMachine; i < NUM_VENDING_MACHINES; i = (i+1) % NUM_VENDING_MACHINES) {

            if (this->truckEmpty()) {
                // start with this vending machine next time shipment comes
                startingVendingMachine = i;
                break;
            }

            if (numVendingMachinesRestocked == NUM_VENDING_MACHINES) {
                // cycle completes
                break;
            }

            // get stock levels of each flavour for this vending machine
            unsigned int *inventory = machines[i]->inventory();

            // restock each flavour
            for (unsigned int f=0; f < NUM_FLAVOURS; f += 1) {
                int restockAmount= MAX_STOCK_PER_FLAVOUR - inventory[f];

                if (restockAmount > 0) {
                    restockAmount = min((unsigned int)restockAmount, this->cargo[f]);
                    inventory[f] += restockAmount;
                    this->cargo[f] -= restockAmount;
                } // if
            } // for

            // restocking is done for this vending machine
            machines[i]->restocked();
            numVendingMachinesRestocked += 1;
        } // for
    }
} // main

