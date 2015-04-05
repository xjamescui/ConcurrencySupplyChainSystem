#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "printer.h"
#include "vendingMachine.h"

_Task NameServer {
    Printer& printer;
    const unsigned int NUM_VENDING_MACHINES;
    const unsigned int NUM_STUDENTS;

    VendingMachine** machines;
    int* assigned; // A VM assigned to each student

    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif // __NAMESREVER_H__
