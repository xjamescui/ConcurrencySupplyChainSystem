#include "watcardOffice.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
        prt( prt ),
        bank( bank ),
        NUM_COURIERS( numCouriers ) {
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Args args( sid, amount );
    Job * job = new Job( args );
    jobs.push( job );
    cond.signal();
    return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ){
    Args args( sid, amount, card );
    Job * job = new Job( args );
    jobs.push( job );
    cond.signal();
    return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {    
    if ( jobs.empty() ) {
	// Wait until there is a job.
	cond.wait();
    }

    Job * job = jobs.front();
    jobs.pop();
    return job;
}

void WATCardOffice::main() {
    Courier couriers[ NUM_COURIERS ];

    while ( true ) {
	_Accept( ~WATCardOffice ) {
	    break;
	} or _Accept( requestWork, create, transfer ) {
	}
    }
}
