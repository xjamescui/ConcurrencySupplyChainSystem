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
        const unsigned int purchaseQuantity = g_randGenerator(1, this->MAX_PURCHASES);
        unsigned int currBalance = 5;

        // creates watcard from watcard office with $5 in balance
        WATCard::FWATCard fwatCard = this->cardOffice.create(this->ID, initialBalance);

        // buy the sodas
        for (unsigned int i = 0; i < purchaseQuantity; i++) {
            yield(g_randGenerator(1,10));
            while (true) {
                try {
                    // transfer money
                    const unsigned int amount = g_randGenerator(1, 10);
                    fwatCard = this->cardOffice.transfer(this->ID, amount, fwatCard());
                    currBalance += amount;
                    assert(fwatCard()->getBalance() == currBalance);
                    break;
                } catch (WATCardOffice::Lost& l) {
                    // retry: creates watcard from watcard office with $5 in balance
                    fwatCard.reset();
                    fwatCard = this->cardOffice.create(this->ID, initialBalance);
                    currBalance = 5;
                }
            } // while
        } // for
        delete fwatCard;
    }
public:
    Student( WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases ) :
        ID( id ),
        MAX_PURCHASES( maxPurchases ),
        cardOffice( cardOffice ) {
    }
};

void uMain::main() {
    const unsigned int numStudents = 5;
    const unsigned int numCouriers = 3;
    const unsigned int maxPurchases = 10;
    Printer prt(numStudents, 0, numCouriers);
    Bank bank(numStudents);

    for (unsigned int id = 0; id < numStudents; ++id) {
        bank.deposit(id, 200);
    }

    WATCardOffice cardOffice(prt, bank, numCouriers);
    Student * students[numStudents];

    for (unsigned int id = 0; id < numStudents; ++id) {
        students[id] = new Student(cardOffice, id, maxPurchases);
    }

    for (unsigned int id = 0; id < numStudents; ++id) {
        delete students[id];
    }
}

