#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "watcard.h"
#include "printer.h"
#include "bank.h"
#include <queue>

using namespace std;

_Task WATCardOffice {
    Printer & prt;
    Bank & bank;
    const unsigned int NUM_COURIERS;
    bool shutdown;                         // Whether or not the office is currently being shut down.
    struct Args {
        unsigned int sid;
        unsigned int amount;
        WATCard * card;
        Args( unsigned int sid, unsigned int amount ) : sid( sid ), amount( amount ), card( NULL ) {}
        Args( unsigned int sid, unsigned int amount, WATCard * card ) :
            sid( sid ),
            amount( amount ),
            card( card ) {
        }
    };

    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;          // return future
        Job( Args args ) : args( args ) {}
    };

    queue<Job *> jobs;

    _Task Courier {                        // communicates with bank
        WATCardOffice & watcardOffice;
        void main();
public:
        Courier( WATCardOffice & watcardOffice );
    };

    void main();
public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif // __WATCARDOFFICE_H__

