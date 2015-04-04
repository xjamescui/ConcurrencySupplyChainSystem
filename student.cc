#include "student.h"
#include "vendingMachine.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases ) : 
    printer(&prt), 
    nameServer(&nameServer),
    cardOffice(&cardOffice), 
    studentId(id),
    maxPurchases(maxPurchases){} // constructor

void Student::main() {

    unsigned int numFlavours = 4; // TODO remove this later, use NUM_FLAVOURS in config.h
    unsigned int initialBalance = 5;
    unsigned int purchaseQuantity = g_randGenerator(1, this->maxPurchases);
    int flavour =g_randGenerator(numFlavours - 1);

    // creates watcard from watcard office with $5 in balance
    WATCard::FWATCard fwatCard = this->cardOffice->create(this->studentId, initialBalance);

    // get vending machine location from nameserver
    VendingMachine* vendingMachine = this->nameServer->getMachine(this->studentId);

    // buy the sodas
    for (unsigned int i = 0; i < purchaseQuantity; i++) {
        yield(g_randGenerator(1,10));
        while (true) {
            try{
                try {
                    vendingMachine->buy((VendingMachine::Flavours)flavour, *(fwatCard()));
                    break;
                } catch (VendingMachine::Funds& f) {
                    // need to transfer money
                    fwatCard = this->cardOffice->transfer(this->studentId, (initialBalance + vendingMachine->cost()), fwatCard());
                    continue;
                } catch (VendingMachine::Stock& s) {
                    // out of stock, get a new vending machine
                    vendingMachine = this->nameServer->getMachine(this->studentId);
                    continue;
                }
            } catch (WATCardOffice::Lost& l) {
                // retry: creates watcard from watcard office with $5 in balance
                fwatCard.reset();
                fwatCard = this->cardOffice->create(this->studentId, initialBalance);
            }
        } // while
    } // for

} // main

