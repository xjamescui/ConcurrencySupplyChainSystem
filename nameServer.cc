#include "nameServer.h"
#include "vendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : printer(prt), NUM_VENDING_MACHINES(numVendingMachines), NUM_STUDENTS(numStudents) {
    this->machines = new VendingMachine*[NUM_VENDING_MACHINES];
    this->assigned = new int[NUM_STUDENTS];
    this->registrationCount = 0;

    for (unsigned int i = 0; i < NUM_VENDING_MACHINES; i += 1) {
        this->machines[i] = NULL;
    } // for

    for (unsigned int i = 0; i < NUM_STUDENTS; i += 1) {
        this->assigned[i] = (i % NUM_VENDING_MACHINES);
    } // for
} // constructor


NameServer::~NameServer() {
    delete [] this->machines;
    delete [] this->assigned;
} // destructor


void NameServer::VMregister( VendingMachine *vendingmachine ) {
    this->machines[vendingmachine->getId()] = vendingmachine;
    this->registrationCount += 1;
    printer.print(Printer::NameServer, 'R', vendingmachine->getId());
} // VMregister


VendingMachine* NameServer::getMachine( unsigned int id ) {
    VendingMachine *machine = this->machines[this->assigned[id]];
    // increment assignment
    this->assigned[id] = (this->assigned[id] + 1) % NUM_VENDING_MACHINES;
    printer.print(Printer::NameServer, 'N', id, machine->getId());
    return machine;
} // getMachine


VendingMachine** NameServer::getMachineList() {
    return this->machines;
} // getMachineList


void NameServer::main() {
    printer.print(Printer::NameServer, 'S');
    for (;;) {
        _Accept(~NameServer) {
            break;
        }
        or _Accept (VMregister, getMachineList) {
        } or _When(this->registrationCount > 0) _Accept( getMachine ) {} // _Accept
    } // for

    printer.print(Printer::NameServer, 'F');
} // main
