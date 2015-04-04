#include "MPRNG.h"
#include "printer.h"
#include "bank.h"
#include "watcardOffice.h"

MPRNG g_randGenerator(getpid());

_Task Student {
    const unsigned int ID;
    WATCard::FWATCard fWatcard; 
    void main() {
	
	for ( int i = 0; i < 
