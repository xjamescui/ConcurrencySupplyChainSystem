#include "watcard.h"
#include <iostream>
using namespace std;

void uMain::main() {
    WATCard w;
    cout << "Initial balance: $" << w.getBalance() << endl;
    w.deposit(10);
    cout << "Balance after depositing $10: $" << w.getBalance() << endl;
    w.withdraw(5);
    cout << "Balance after withdrawing $5: $" << w.getBalance() << endl;
}
