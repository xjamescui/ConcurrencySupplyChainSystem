#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "printer.h"
#include "watcard.h"
#include "nameServer.h"
#include "config.h"

_Task VendingMachine {
    Printer& printer;
    NameServer& nameServer;
    unsigned int stockLevel[NUM_FLAVOURS]; // the stock level of each flavour
    const unsigned int ID;
    const unsigned int SODA_COST;
    const unsigned int MAX_STOCK_PER_FLAVOUR; 
    bool restocking;
    void main();
  public:
    enum Flavours { BluesBlackCherry=0, ClassicCream=1, RockRootBeer=2, JazzLime=3 }; // flavours of soda (YOU DEFINE)
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif // __VENDINGMACHINE_H__
