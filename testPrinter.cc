#include "printer.h"

void uMain::main() {
    const unsigned int numStudents = 2;
    const unsigned int numMachines = 3;
    const unsigned int numCouriers = 1;
    Printer prt( numStudents, numMachines, numCouriers ); 

    // The following statements are grouped together into 
    // those that are expected to appear on the same line.
    prt.print( Printer::Parent, 'S' );
    prt.print( Printer::WATCardOffice, 'S' );
    prt.print( Printer::NameServer, 'S' );
    prt.print( Printer::Courier, 0, 'S' );

    prt.print( Printer::NameServer, 'R', 0 );
    prt.print( Printer::Vending, 0, 'S', 2 );
    prt.print( Printer::Parent, 'D', 1, 3 );
    prt.print( Printer::Vending, 1, 'S', 2 );
    prt.print( Printer::BottlingPlant, 'S' );
    prt.print( Printer::Student, 0, 'S', 1, 1 );
    prt.print( Printer::Vending, 2, 'S', 2 );
    prt.print( Printer::WATCardOffice, 'C', 0, 5 );

    prt.print( Printer::BottlingPlant, 'G', 11 ); 
    prt.print( Printer::NameServer, 'N', 0, 0 );
    prt.print( Printer::Truck, 'S' );
    prt.print( Printer::Student, 0, 'V', 0 );
    prt.print( Printer::Student, 1, 'S', 2, 2 );
    prt.print( Printer::Courier, 0, 't', 0, 5 );

    prt.print( Printer::Student, 1, 'V', 1 );
    prt.print( Printer::WATCardOffice, 'W' );
    prt.print( Printer::Courier, 0, 'T', 0, 5 );
    prt.print( Printer::Truck, 'P', 11 );

    prt.print( Printer::Truck, 'd', 0, 11 );
    
    prt.print( Printer::Truck, 'U', 0, 9 );

    prt.print( Printer::Truck, 'D', 0, 0 );
    prt.print( Printer::BottlingPlant, 'P' );
    prt.print( Printer::Vending, 0, 'r' );

    prt.print( Printer::Vending, 0, 'R' );
    prt.print( Printer::Student, 0, 'B', 3);

    prt.print( Printer::Student, 0, 'F' );

    prt.print( Printer::Student, 1, 'L' );
    prt.print( Printer::Vending, 0, 'B', 1, 1 );
    prt.print( Printer::Vending, 1, 'r' );

    prt.print( Printer::Vending, 1, 'R' );
    prt.print( Printer::Vending, 2, 'r' );
    prt.print( Printer::Student, 1, 'B', 3 );

    prt.print( Printer::Vending, 1, 'B', 2, 2 );
    prt.print( Printer::Vending, 2, 'R' );
    
    prt.print( Printer::Student, 1, 'F' );

    prt.print( Printer::Parent, 'F' );
    
    prt.print( Printer::WATCardOffice, 'F' );
   
    prt.print( Printer::NameServer, 'F' );
    
    prt.print( Printer::Truck, 'F' );
    
    prt.print( Printer::BottlingPlant, 'F' );
    
    prt.print( Printer::Vending, 0, 'F' );
    
    prt.print( Printer::Vending, 1, 'F' );

    prt.print( Printer::Vending, 2, 'F' );
    
    prt.print( Printer::Courier, 0, 'F' );
}
