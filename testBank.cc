#include "bank.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

MPRNG mprng(getpid());

_Task Depositor {
    Bank &bank;
    void main() {
	for ( int i = 0; i < 10; ++i ) {
	    yield( mprng(10) );
	    const unsigned int randStudent = mprng(1);
	    const unsigned int randAmount = mprng(10);
	    bank.deposit( randStudent, randAmount );
	    cout << "Deposited $" << randAmount << " to student " << randStudent << endl;
	}
    }
  public:
    Depositor( Bank & bank ) : bank(bank) {}
};

_Task Withdrawer {
    Bank &bank;
    void main() {
	for ( int i = 0; i < 10; ++i ) {
	    yield( mprng(10) );
	    const unsigned int randStudent = mprng(1);
	    const unsigned int randAmount = mprng(10);
	    cout << "Attempting to withdraw $" << randAmount << " from student " << randStudent << endl;
	    bank.withdraw( randStudent, randAmount );
	    cout << "Withdrew $" << randAmount << " from student " << randStudent << endl;
	}
    }
  public:
    Withdrawer( Bank & bank ) : bank(bank) {}
};

void uMain::main() {
    Bank bank(2);
    Withdrawer w(bank);
    Depositor d(bank);
}

