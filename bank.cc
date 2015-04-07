#include "bank.h"

Bank::Bank( unsigned int numStudents ) :
    balances( new int[ numStudents ] ),
    cond( new uCondition[ numStudents ]) {

    for ( unsigned int id = 0; id < numStudents; ++id ) {
        balances[id] = 0;
    }
}

Bank::~Bank() {
    delete [] balances;
    delete [] cond;
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
    const int prevBalance = balances[id];
    balances[id] += amount;

    // Previous balance was negative ==> there is someone withdrawing that is waiting
    // for sufficient funds to be deposited into the account.
    // Current balance >= 0 ==> Sufficients funds have now been deposited.
    // This solution requires that there will never be multiple threads
    // calling withdraw() for the same student at a time.
    if ( prevBalance < 0 && balances[id] >= 0 ) {
        cond[id].signal();
    }
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    balances[id] -= amount;

    if ( balances[id] < 0 ) {
        // Insufficient funds.  Wait until there are sufficient funds.
        cond[id].wait();
    }
}
