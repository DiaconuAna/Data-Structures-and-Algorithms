#include "ShortTest.h"
#include <assert.h>
#include "Bag.h"
#include "BagIterator.h"
#include <iostream>
void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
	assert(b.nrOccurrences(1) == 2);
	assert(b.nrOccurrences(7) == 1);
	assert(b.remove(1) == true);
	assert(b.remove(6) == false);
	assert(b.size() == 6);
	assert(b.nrOccurrences(1) == 1);
	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next();
	}
}

void testLabFunction()
{
    //testing the remove nr occurrences function
    Bag b;
    assert(b.isEmpty() == true);
    assert(b.size() == 0);
    b.add(3);
    for (int i=0;i<10;i++)
        b.add(5);
    b.add(7);
    assert(b.size()==12);
    assert(b.removeOccurrences(1,7) == 1);
    assert(b.size()==11);
    assert(b.removeOccurrences(3,5)==3);
    assert(b.size()==8);
    assert(b.removeOccurrences(10,5) == 7);
    assert(b.size()==1);
    try{
        b.removeOccurrences(-3,3);
    }
    catch (const char msg[256]) {
        assert(true);
    }
    assert(b.size()==1);
    std::cout<<"Laboratory functions tests done";
}

