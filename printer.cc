#include "printer.h"
#include <iostream>

void Printer::printHeadings() {
    // Print column headers.
    cout << "Parent\tWATOff\tNames\tTruck\tPlant";

    for ( unsigned int id = 0; id < NUM_STUDENTS; ++id ) {
	cout << "\t" << "Stud" << id;
    }

    for ( unsigned int id = 0; id < NUM_VENDING_MACHINES; ++id ) {
	cout << "\t" << "Mach" << id;
    }

    for ( unsigned int id = 0; id < NUM_COURIERS; ++id ) {
	cout << "\t" << "Cour" << id ;
    }

    cout << endl;

    const unsigned int numColumns = 5 + NUM_STUDENTS + NUM_VENDING_MACHINES + NUM_COURIERS;

    for ( unsigned int i = 0; ; ++i ) {
	cout << "*******";

	if ( i == numColumns - 1 ) {
	    // Last column.  Don't print the trailing tab.
	    break;
	}

	cout << "\t";
    }

    cout << endl;
}

Printer::Printer( 
	unsigned int numStudents, 
	unsigned int numVendingMachines, 
	unsigned int numCouriers ) :
        NUM_STUDENTS( numStudents ),
        NUM_VENDING_MACHINES( numVendingMachines )
        NUM_COURIERS( numCouriers ),
        isBufferEmpty( true ) {
    printHeadings();

    for ( int kind = Parent; kind <= BottlingPlant; ++kind ) {
        // There is only one of each of parent, watcard office, name server, truck, 
        // and bottling plant.	
	stateInfos[kind] = new StateInfo[1];
    }

    stateInfos[Student] = new StateInfo[NUM_STUDENTS];
    stateInfos[Vending] = new StateInfo[NUM_VENDING_MACHINES];
    stateInfos[Courier] = new StateInfo[NUM_COURIERS];
}

Printer::~Printer() {
    for ( int i = 0; i < NUM_KINDS; ++i ) {
	delete [] stateInfos[i];
    }
}

void Printer::flush() {
    if ( isBufferEmpty ) {
	// Don't print anything if the buffer is empty.
	return;
    }

    for ( int kind = Parent; kind <= BottlingPlant; ++kind ) {
	// Print columns corresponding to kinds that have only 1 object per kind.
	stateInfos[kind][0].flushState();
        cout << "\t";
    }

    // Print student columns.
    for ( int lid = 0; lid < NUM_STUDENTS; ++lid ) {
        stateInfos[Student][lid].flushState();	
	cout << "\t";
    }

    // Print vending machine columns.
    for ( int lid = 0; lid < NUM_VENDING_MACHINES; ++lid ) {
        stateInfos[Vending][lid].flushState();	
	cout << "\t";
    }

    // Print couriers.
    for ( int lid = 0; ; ++lid ) {
        stateInfos[Courier][lid].flushState();

	if ( lid == NUM_COURIERS - 1 ) {
	    // Last courier.  Don't print the tab.
	    break;
	}

       	cout << "\t";	
    }

    cout << endl; 

    isBufferEmpty = true;
}

void Printer::printFinish( Kind kind, unsigned int lid ) {
    for ( int k = Parent; k <= BottlingPlant; ++k ) {
	// Print columns corresponding to kinds that have only 1 object per kind.
	if ( kind == k ) {
	    cout << "F";
	} else {
	    cout << "...";
	}

        cout << "\t";
    }

    // Print student columns.
    for ( int id = 0; id < NUM_STUDENTS; ++id ) {
	if ( kind == Student && lid == id ) {
	    cout << "F";
	} else {
	    cout << "...";
	}

	cout << "\t";
    }

    // Print vending machine columns.
    for ( int id = 0; id < NUM_VENDING_MACHINES; ++id ) {
	if ( kind == Vending && lid == id ) {
	    cout << "F";
	} else {
	    cout << "...";
	}

	cout << "\t";
    }

    // Print couriers.
    for ( int id = 0; ; ++id ) {
	if ( kind == Courier && lid == id ) {
	    cout << "F";
	} else {
	    cout << "...";
	}

	if ( id == NUM_COURIERS - 1 ) {
	    // Last courier.  Don't print the tab.
	    break;
	}

       	cout << "\t";	
    }

    cout << endl; 
}

void Printer::print( Kind kind, unsigned int lid, char state, vector<int> values ) {
    if ( state == 'F' || ! stateInfos[kind][lid].isEmpty ) {
	// Either an object finished or about to overwrite a column.  
	// Flush buffer.
	flush();
    }

    if ( state == 'F' ) {	
	printFinish( kind, lid );
    } else {
	isBufferEmpty = false;
	stateInfos[kind][lid].setState( state, values );
    }
}

void Printer::print( Kind kind, char state ) {
    print( kind, 0, state );
}

void Printer::print( Kind kind, char state, int value1 ) {
    print( kind, 0, state, value1 );
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
    print( kind, 0, state, value1, value2 );
}

void Printer::print( Kind kind, unsigned int lid, char state ) { 
    // Empty vector of values.
    vector<int> values;
    print( kind, lid, state, values );
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
    // Vector with a single element: value1.
    vector<int> values( 1, value1 );
    print( kind, lid, state, values );
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
    // Vector with elements value1 and value2.
    vector<int> values( 1, value1 );
    values.push_back( value2 );
    print( kind, lid, state, values );
}
