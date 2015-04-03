#include "watcard.h"

WATCard::WATCard( const WATCard & ){}            // prevent copying
WATCard& WATCard::operator=( const WATCard & ){}
WATCard::WATCard(){}
void WATCard::deposit( unsigned int amount ){}
void WATCard::withdraw( unsigned int amount ){}
unsigned int WATCard::getBalance(){}
