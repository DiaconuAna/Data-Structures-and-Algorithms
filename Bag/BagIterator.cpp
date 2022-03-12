#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
this -> currentP = 0;
}

void BagIterator::first() {
    this -> currentP = 0;
}


void BagIterator::next() {
	if (this -> currentP >= bag.PositionIndex)
    {
	    throw exception();
    }
	else{
	    this->currentP ++;
	}
}


bool BagIterator::valid() const {
	if (this -> currentP < bag.PositionIndex)
	    return true;
	return false;
}



TElem BagIterator::getCurrent() const
{
    if (this -> currentP >= bag.PositionIndex)
    {
        throw exception();
    }
    else
        return bag.U[bag.P[this->currentP]];
}
