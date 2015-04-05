#include "MPRNG.h"
#include "printer.h"
#include "bank.h"
#include "watcardOffice.h"
#include <assert.h>

MPRNG g_randGenerator(getpid());

_Task Student {
    const unsigned int ID;
    const unsigned int MAX_PURCHASES;
    WATCardOffice & cardOffice;

    void main() {
	const unsigned int initialBalance = 5;
	const unsigned int purchaseQuantity = g_randGenerator(1, this->maxPurchases);
	unsigned int currBalance = 5;

	// creates watcard from watcard office with $5 in balance
	WATCard::FWATCard fwatCard = this->cardOffice->create(this->ID, initialBalance);

	// buy the sodas
	for (unsigned int i = 0; i < purchaseQuantity; i++) {
	    yield(g_randGenerator(1,10));
	    while (true) {
		try{
		    // transfer money
		    const unsigned int amount = g_randGenerator(1, 10);
		    fwatCard = this->cardOffice->transfer(this->ID, g_randGenerator(1, 10), fwatCard());
		    currBalance += amount;
		    assert(fwatCard()->getBalance() == currBalance);
		} catch (WATCardOffice::Lost& l) {
		    // retry: creates watcard from watcard office with $5 in balance
		    fwatCard.reset();
		    fwatCard = this->cardOffice->create(this->ID, initialBalance);
		    currBalance = 5;
		}
	    } // while
	} // for	
    }
  public:
    Student( WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases ) : 
	    cardOffice( cardOffice ),
	    ID( id ),
	    MAX_PURCHASES( maxPurchases ) {} 
};

void uMain::main() {
    const unsigned int numStudents = 5;
    const unsigned int numCouriers = 3;
    const unsigned int maxPurchases = 10;
    Printer prt(numStudents, 0, numCouriers);
    Bank bank(numStudents);
    WATCardOffice cardOffice(prt, bank, numCouriers);
    Student * students[10];

    for (int id = 0; id < 10; ++id) {
	students[id] = new Student(cardOffice, id, maxPurchases);
    }

    for (int id = 0; id < 10; ++id) {
	delete students[id];
    }
}

    
