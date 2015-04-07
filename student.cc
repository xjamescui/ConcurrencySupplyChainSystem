#include "student.h"
#include "vendingMachine.h"
#include "config.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases ) :
    printer(prt),
    nameServer(nameServer),
    cardOffice(cardOffice),
    STUDENT_ID(id),
    MAX_PURCHASES(maxPurchases) {} // constructor

void Student::main() {

    const unsigned int INITIAL_BALANCE = 5;
    const unsigned int PURCHASE_QUANTITY = g_randGenerator(1, MAX_PURCHASES);
    const unsigned int FLAVOUR = g_randGenerator(NUM_FLAVOURS - 1);

    printer.print(Printer::Student, STUDENT_ID, 'S', FLAVOUR, PURCHASE_QUANTITY );

    // creates watcard from watcard office with $5 in balance
    WATCard::FWATCard fwatCard = this->cardOffice.create(STUDENT_ID, INITIAL_BALANCE);

    // get vending machine location from nameserver
    VendingMachine* vendingMachine = this->nameServer.getMachine(STUDENT_ID);
    printer.print(Printer::Student, STUDENT_ID, 'V', vendingMachine->getId());

    // buy the sodas
    for (unsigned int i = 0; i < PURCHASE_QUANTITY; i++) {
        yield(g_randGenerator(1,10));
        while (true) {
	    // if at first you don't succeed, try, try again.
            try {
                try {
                    vendingMachine->buy((VendingMachine::Flavours)FLAVOUR, *(fwatCard()));
                    printer.print(Printer::Student, STUDENT_ID, 'B', fwatCard()->getBalance());
		    // Success in buying soda
                    break;
                } catch (VendingMachine::Funds& f) {
                    // need to transfer money
                    fwatCard = this->cardOffice.transfer(STUDENT_ID, (INITIAL_BALANCE + vendingMachine->cost()), fwatCard());
                    yield(g_randGenerator(1,10));
                    continue;
                } catch (VendingMachine::Stock& s) {
                    // out of stock, get a new vending machine
                    vendingMachine = this->nameServer.getMachine(STUDENT_ID);
                    printer.print(Printer::Student, STUDENT_ID, 'V', vendingMachine->getId());
                    yield(g_randGenerator(1,10));
                    continue;
                } // try/catch
            } catch (WATCardOffice::Lost& l) {
                // retry: creates watcard from watcard office with $5 in balance
                printer.print(Printer::Student, STUDENT_ID, 'L');
                fwatCard.reset();
                fwatCard = this->cardOffice.create(STUDENT_ID, INITIAL_BALANCE);
            } // try/catch
        } // while
    } // for

    delete fwatCard;

    printer.print(Printer::Student, STUDENT_ID, 'F');
} // main

