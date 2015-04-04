#include <iostream>
#include "vendingMachine.h"
#include <assert.h>
using namespace std;

void uMain::main() {
  unsigned int sodaCost = 2;
  unsigned int maxStockPerFlavour = 5;
  unsigned int numStudents = 3;
  unsigned int numVendingMachines = 3;
  unsigned int numCouriers = 2;
  unsigned int vmId = 1;

  Printer printer(numStudents, numVendingMachines, numCouriers);
  NameServer ns(printer, numVendingMachines, numStudents);

  VendingMachine vm(printer, ns, vmId, sodaCost, maxStockPerFlavour);

  cout << "NOW TESTING VENDING MACHINE..." << endl;
  assert(vm.cost() == sodaCost);
  assert(vm.getId() == vmId);

  cout << "DONE!" << endl;

} // uMain::main
