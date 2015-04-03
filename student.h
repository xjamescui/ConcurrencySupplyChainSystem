#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "printer.h"
#include "nameServer.h"
#include "watcardOffice.h"

_Task Student {
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif // __STUDENT_H__
