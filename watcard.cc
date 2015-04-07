#include "watcard.h"

WATCard::WATCard(): balance(0) {}

void WATCard::deposit( unsigned int amount ) {
    balance += amount;
} // deposit
void WATCard::withdraw( unsigned int amount ) {
    // It is the caller's responsibility to ensure that there are sufficient funds.
    balance -= amount;
} // withdraw

unsigned int WATCard::getBalance() {
    return balance;
} // getBalance
