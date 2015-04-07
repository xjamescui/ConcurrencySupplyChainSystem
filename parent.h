#ifndef __PARENT_H__
#define __PARENT_H__

#include "printer.h"
#include "bank.h"

_Task Parent {
    Printer & prt;
    Bank & bank;
    const unsigned int NUM_STUDENTS;
    const unsigned int PARENTAL_DELAY;
    void main();
public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif // __PARENT_H__
