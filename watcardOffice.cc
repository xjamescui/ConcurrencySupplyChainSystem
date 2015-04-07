#include "watcardOffice.h"
#include "MPRNG.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
    prt( prt ),
    bank( bank ),
    NUM_COURIERS( numCouriers ),
    shutdown( false ) {
} // constructor

WATCardOffice::~WATCardOffice() {
    while ( ! jobs.empty() ) {
        Job * job = jobs.front();
        jobs.pop();
        delete job;
    } // while
} // destructor

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Args args( sid, amount );
    Job * job = new Job( args );
    jobs.push( job );
    prt.print(Printer::WATCardOffice, 'C', sid, amount);
    return job->result;
} // create

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    Args args( sid, amount, card );
    Job * job = new Job( args );
    jobs.push( job );
    prt.print(Printer::WATCardOffice, 'T', sid, amount);
    return job->result;
} // transfer

WATCardOffice::Job* WATCardOffice::requestWork() {
    if ( shutdown ) return NULL;

    Job * job = jobs.front();
    jobs.pop();
    prt.print(Printer::WATCardOffice, 'W');
    return job;
} // requestWork

void WATCardOffice::main() {
    prt.print(Printer::WATCardOffice, 'S');
    Courier * couriers[ NUM_COURIERS ];

    for ( unsigned int i = 0; i < NUM_COURIERS; ++i ) {
        couriers[i] = new Courier( i, prt, *this );
    } // for

    while ( true ) {
        _Accept( ~WATCardOffice ) {
            break;
        }
        or _When( ! jobs.empty() ) _Accept( requestWork ) {
        } or _Accept( create, transfer) {
        } // _Accept
    } // while

    shutdown = true;
    for ( unsigned int i = 0; i < NUM_COURIERS; ++i ) {
        // Allow the couriers to run to completion.
        _Accept( requestWork );
    } // for

    for ( unsigned int i = 0; i < NUM_COURIERS; ++i ) {
        delete couriers[i];
    } // for

    prt.print(Printer::WATCardOffice, 'F');
} // main

WATCardOffice::Courier::Courier(unsigned int id, Printer& prt, WATCardOffice & watcardOffice ) : ID(id), prt(prt), watcardOffice( watcardOffice ) {} // constructor

void WATCardOffice::Courier::main() {
    prt.print(Printer::Courier, ID, 'S');
    while ( true ) {
        Job * job = watcardOffice.requestWork();

        if ( ! job ) break;

        const Args args = job->args;
        WATCard * card = args.card;

        if ( ! card ) {
            // No card provided.  Create new card.
            card = new WATCard();
        } // if

        prt.print(Printer::Courier, ID, 't', args.sid, args.amount);
        watcardOffice.bank.withdraw( args.sid, args.amount );
        prt.print(Printer::Courier, ID, 'T', args.sid, args.amount);

        // 1/6 chance of losing WatCard.
        if ( g_randGenerator( 5 ) == 0 ) {
            //WatCard lost.
            delete card;
            job->result.exception( new Lost );
        } else {
            card->deposit( args.amount );
            job->result.delivery( card );
        } // if

        delete job;
    } // while

    prt.print(Printer::Courier, ID, 'F');
} // main
