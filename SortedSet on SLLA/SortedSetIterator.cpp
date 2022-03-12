#include "SortedSetIterator.h"
#include <exception>

using namespace std;

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->currentIndex = multime.list.head;
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
void SortedSetIterator::first() {
    this->currentIndex = this->multime.list.head;

}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
void SortedSetIterator::next() {
    if(this->valid())
        currentIndex = multime.list.next[currentIndex];
    else
        throw exception();
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
TComp SortedSetIterator::getCurrent()
{    if(this->valid())
        return this->multime.list.elems[currentIndex];
    else
        throw exception();

}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
bool SortedSetIterator::valid() const {
	if (this->currentIndex == -1)
	    return false;
	else return true;

}
