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

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
    NUM_STUDENTS( numStudents ),
    NUM_VENDING_MACHINES( numVendingMachines ),
    NUM_COURIERS( numCouriers ),
    isBufferEmpty( true ) {
    printHeadings();

    for ( int kind = Parent; kind <= BottlingPlant; ++kind ) {
        // There is only one of each of parent, watcard office, name server, truck,
        // and bottling plant.
        stateInfos[kind] = new StateInfo[1];
        numObjects[kind] = 1;
    }

    stateInfos[Student] = new StateInfo[NUM_STUDENTS];
    stateInfos[Vending] = new StateInfo[NUM_VENDING_MACHINES];
    stateInfos[Courier] = new StateInfo[NUM_COURIERS];

    numObjects[Student] = NUM_STUDENTS;
    numObjects[Vending] = NUM_VENDING_MACHINES;
    numObjects[Courier] = NUM_COURIERS;
}

Printer::~Printer() {
    for ( unsigned int kind = 0; kind < NUM_KINDS; ++kind ) {
        delete [] stateInfos[kind];
    }
}

void Printer::flush() {
    if ( isBufferEmpty ) {
        // Don't print anything if the buffer is empty.
        return;
    }

    for ( unsigned int kind = 0; kind < NUM_KINDS; ++kind ) {
        for ( unsigned int lid = 0; lid < numObjects[kind]; ++lid ) {
            stateInfos[kind][lid].flushState();

            if ( kind == NUM_KINDS - 1 && lid == numObjects[kind] - 1 ) {
                // Last column.  Don't print the tab.
                break;
            }

            cout << "\t";
        }
    }

    cout << endl;

    isBufferEmpty = true;
}

void Printer::printFinish( Kind kind, unsigned int lid ) {
    for ( unsigned int k = 0; k < NUM_KINDS; ++k ) {
        for ( unsigned int id = 0; id < numObjects[k]; ++id ) {
            if ( kind == k && lid == id ) {
                cout << "F";
            } else {
                cout << "...";
            }

            if ( k == NUM_KINDS - 1 && id == numObjects[k] - 1 ) {
                break;
            }

            cout << "\t";
        }
    }

    cout << endl;
}

void Printer::printHelper( Kind kind, unsigned int lid, char state, vector<int> values ) {
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
    print( kind, 0, state ); // lid = 0
}

void Printer::print( Kind kind, char state, int value1 ) {
    print( kind, 0, state, value1 ); // lid = 0
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
    print( kind, 0, state, value1, value2 ); // lid = 0
}

/**
 * lid = local id
 */
void Printer::print( Kind kind, unsigned int lid, char state ) {
    // Empty vector of values.
    vector<int> values;
    printHelper( kind, lid, state, values );
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
    // Vector with a single element: value1.
    vector<int> values( 1, value1 );
    printHelper( kind, lid, state, values );
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
    // Vector with elements value1 and value2.
    vector<int> values( 1, value1 );
    values.push_back( value2 );
    printHelper( kind, lid, state, values );
}

void Printer::StateInfo::setState( char state, vector<int> values ) {
    this->isEmpty = false;
    this->state = state;
    this->values = values;
}

void Printer::StateInfo::flushState() {
    if ( isEmpty ) {
        return;
    }

    cout << state;

    for ( vector<int>::iterator it = values.begin() ; it != values.end(); ++it ) {
        if ( it != values.begin() ) {
            cout << ",";
        }

        cout << *it;
    }

    isEmpty = true;
}

