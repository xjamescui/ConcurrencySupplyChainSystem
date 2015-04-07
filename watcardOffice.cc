#include "watcardOffice.h"
#include "MPRNG.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
    prt( prt ),
    bank( bank ),
    NUM_COURIERS( numCouriers ),
    shutdown( false ) {
}

WATCardOffice::~WATCardOffice() {
    while ( ! jobs.empty() ) {
        Job * job = jobs.front();
        jobs.pop();
        delete job;
    }
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Args args( sid, amount );
    Job * job = new Job( args );
    jobs.push( job );
    return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
    Args args( sid, amount, card );
    Job * job = new Job( args );
    jobs.push( job );
    return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
    if ( shutdown ) {
        return NULL;
    }

    Job * job = jobs.front();
    jobs.pop();
    return job;
}

void WATCardOffice::main() {
    Courier * couriers[ NUM_COURIERS ];

    for ( unsigned int i = 0; i < NUM_COURIERS; ++i ) {
        couriers[i] = new Courier( *this );
    }

    while ( true ) {
        _Accept( ~WATCardOffice ) {
            break;
        }
        or _When( ! jobs.empty() ) _Accept( requestWork ) {
        } or _Accept( create, transfer ) {
        }
    }

    shutdown = true;
    for ( unsigned int i = 0; i < NUM_COURIERS; ++i ) {
        // Allow the couriers to run to completion.
        _Accept( requestWork );
    }

    for ( unsigned int i = 0; i < NUM_COURIERS; ++i ) {
        delete couriers[i];
    }
}

WATCardOffice::Courier::Courier( WATCardOffice & watcardOffice ) : watcardOffice( watcardOffice ) {}

void WATCardOffice::Courier::main() {
    while ( true ) {
        Job * job = watcardOffice.requestWork();

        if ( ! job ) {
            break;
        }

        const Args args = job->args;
        WATCard * card = args.card;

        if ( ! card ) {
            // No card provided.  Create new card.
            card = new WATCard();
        }

        watcardOffice.bank.withdraw( args.sid, args.amount );

        // 1/6 chance of losing WatCard.
        if ( g_randGenerator( 5 ) == 0 ) {
            //WatCard lost.
            delete card;
            job->result.exception( new Lost );
        } else {
            card->deposit( args.amount );
            job->result.delivery( card );
        }

        delete job;
    }
}
