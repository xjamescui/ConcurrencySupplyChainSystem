#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "printer.h"
#include "nameServer.h"
#include "watcardOffice.h"
#include "MPRNG.h"

_Task Student {
    unsigned int studentId;
    unsigned int maxPurchases;
    NameServer* nameServer;
    WATCardOffice* cardOffice;
    Printer* printer;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif // __STUDENT_H__
