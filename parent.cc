#include "parent.h"
#include "MPRNG.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
        prt( prt ),
	bank( bank ),
	NUM_STUDENTS( numStudents ),
	PARENTAL_DELAY( parentalDelay ) {
} // Parent::Parent 

void Parent::main(){
    prt.print(Printer::Parent, 'S');
    while ( true ) {
	_Accept( ~Parent ) {
	    break;
	} _Else {};

	yield( PARENTAL_DELAY );
	const unsigned int randStudent = g_randGenerator( NUM_STUDENTS - 1 );
	const unsigned int randAmount = g_randGenerator(1, 3);
	bank.deposit( randStudent, randAmount );
        prt.print(Printer::Parent, 'D', randStudent, randAmount);
    } // while

    prt.print(Printer::Parent, 'F');
} // main

