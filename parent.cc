#include "parent.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
        prt( prt ),
	bank( bank ),
	NUM_STUDENTS( numStudents ),
	PARENTAL_DELAY( parentalDelay ) {
} // Parent::Parent 

// TODO: Use the printer to print!
// TODO: Remove the cout's.
void Parent::main(){
    while ( true ) {
	_Accept( ~Parent ) {
	    cout << "Ending parent task" << endl;
	    break;
	} _Else {};

	yield( PARENTAL_DELAY );
	const unsigned int randStudent = g_randGenerator( NUM_STUDENTS - 1 );
	const unsigned int randAmount = g_randGenerator(1, 3);
	bank.deposit( randStudent, randAmount );
	cout << "Deposited $" << randAmount << " to student " << randStudent << endl;
    }
} // main

