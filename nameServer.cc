#include "nameServer.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) : printer(prt), NUM_VENDING_MACHINES(numVendingMachines), NUM_STUDENTS(numStudents) {
    this->machines = new VendingMachine*[NUM_VENDING_MACHINES];
    this->assigned = new int[NUM_STUDENTS];
} // constructor


NameServer::~NameServer(){
   for (unsigned int i = 0; i < NUM_VENDING_MACHINES; i += 1) {
       delete this->machines[i];
   } // for 
   delete [] this->machines;
} // destructor


void NameServer::VMregister( VendingMachine *vendingmachine ){
    this->machines[vendingmachine->getId()] = vendingmachine;
} // VMregister


VendingMachine* NameServer::getMachine( unsigned int id ){
    VendingMachine *machine = this->machines[this->assigned[id]];

    // increment assignment
    this->assigned[id] = (this->assigned[id] + 1) % NUM_VENDING_MACHINES;

    return machine;

} // getMachine


VendingMachine** NameServer::getMachineList(){
    return this->machines;
} // getMachineList


void NameServer::main(){

    for (;;) {
        _Accept(~NameServer) {
            break;
        } or _Accept (VMregister, getMachine, getMachineList){
        }
    } // for

} // main
