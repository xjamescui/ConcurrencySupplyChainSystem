#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <vector>

using namespace std;

/* _Monitor / _Cormonitor Printer { */
_Monitor Printer {
    const static unsigned int NUM_KINDS = 8;
    const unsigned int NUM_STUDENTS;
    const unsigned int NUM_VENDING_MACHINES;
    const unsigned int NUM_COURIERS;
    struct StateInfo {
        bool isEmpty;        // Set to true to indicate empty state.
        char state;
        vector<int> values;
        StateInfo()  : isEmpty( true ) {}
        void setState( char state, vector<int> values );
        void flushState();
    };

    // Each array element here is an array corresponding to a specific kind.
    // E.g. The array element corresponding to parent is an array of size 1
    //      since there is only one parent.
    //      But the array element corresponding to student is an array of size
    //      NUM_STUDENTS.
    StateInfo * stateInfos[NUM_KINDS];

    // Number of objects of each kind.
    unsigned int numObjects[NUM_KINDS];

    bool isBufferEmpty;

    void printHeadings();
    void flush();
public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
private:
    void printFinish( Kind kind, unsigned int lid );
    void printHelper( Kind kind, unsigned int lid, char state, vector<int> values );

};

#endif // __PRINTER_H__
