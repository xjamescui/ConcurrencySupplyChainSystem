#include "watcardOffice.h"
#include "MPRNG.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
        prt( prt ),
        bank( bank ),
        NUM_COURIERS( numCouriers ) {
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

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ){
    Args args( sid, amount, card );
    Job * job = new Job( args );
    jobs.push( job );
    return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {    
    Job * job = jobs.front();
    jobs.pop();
    return job;
}

void WATCardOffice::main() {
    Courier couriers[ NUM_COURIERS ];

    while ( true ) {
	_Accept( ~WATCardOffice ) {
	    break;
	} or _When( ! jobs.empty() ) _Accept( requestWork ) {
	} or _Accept( create, transfer ) {
	}
    }
}

void WATCardOffice::Courier::main() {
    while ( true ) {
	Job * job = requestWork();
	WATCard * card = job->card;

	if ( ! card ) {
	    // No card provided.  Create new card.
	    card = new WATCard();
	}

	bank.withdraw( job->sid, job->amount );

	// 1/6 chance of losing WatCard.
	if ( g_randGenerator( 5 ) == 0 ) {
	    //WatCard lost. 
	    delete card;
	    job->result.exception( new Lost );
	}

	card->deposit( job->amount );
	job->result.delivery( card );
    }
}
