#include "student.h"
#include "vendingMachine.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases ) : 
    printer(&prt), 
    nameServer(&nameServer),
    cardOffice(&cardOffice), 
    studentId(id),
    maxPurchases(maxPurchases){} // constructor

void Student::main() {

    // decide on quantity
    unsigned int purchaseQuantity = g_randGenerator(1, this->maxPurchases);

    // decide on flavor
    int flavour =g_randGenerator(3);

    // creates watcard from watcard office with $5 in balance
    WATCard::FWATCard fwatCard = this->cardOffice->create(this->studentId, 5);

    // get vending machine location from nameserver
    VendingMachine* vendingMachine = this->nameServer->getMachine(this->studentId);

    // buy the sodas
    for (unsigned int i = 0; i < purchaseQuantity; i++) {
        vendingMachine->buy((VendingMachine::Flavours)flavour, *(fwatCard()));
    } // for

} // main

