#include "MPRNG.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"

MPRNG g_randGenerator(getpid());

void uMain::main() {
    const unsigned int numStudents = 5;
    const unsigned int parentalDelay = 5;
    Printer prt(numStudents, 0, 0);
    Bank bank(numStudents);
    Parent parent( prt, bank, numStudents, parentalDelay );
    yield(200);
}
