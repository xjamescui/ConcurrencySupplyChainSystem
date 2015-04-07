#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "printer.h"
#include "nameServer.h"
#include "watcardOffice.h"
#include "MPRNG.h"

_Task Student {
    Printer& printer;
    NameServer& nameServer;
    WATCardOffice& cardOffice;
    const unsigned int STUDENT_ID;
    const unsigned int MAX_PURCHASES;

    void main();
public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
    unsigned int maxPurchases );
};

#endif // __STUDENT_H__
