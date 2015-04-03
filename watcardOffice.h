#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "watcard.h"
#include "printer.h"
#include "bank.h"

_Task WATCardOffice {
    typedef int Args; // TODO: change this, this is temp just to make sure make works
    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;          // return future
        Job( Args args ) : args( args ) {}
    };
    _Task Courier { };                 // communicates with bank

    void main();
  public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif // __WATCARDOFFICE_H__

