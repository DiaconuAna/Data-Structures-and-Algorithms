#include "ShortTest.h"
#include <assert.h>
#include "Map.h"
#include "MapIterator.h"
#include <iostream>

void testAll() { //call each function to see if it is implemented
	Map m;
	assert(m.isEmpty() == true);
	assert(m.size() == 0); //add elements
	assert(m.add(5,5)==NULL_TVALUE);
	assert(m.add(1,111)==NULL_TVALUE);
	assert(m.add(10,110)==NULL_TVALUE);
	assert(m.add(7,7)==NULL_TVALUE);
	assert(m.add(1,1)==111);
	assert(m.add(10,10)==110);
	assert(m.add(-3,-3)==NULL_TVALUE);
	assert(m.size() == 5);
	assert(m.search(10) == 10);
	//std::cout<<m.search(10)<<std::endl;
	assert(m.search(16) == NULL_TVALUE);
	assert(m.remove(1) == 1);
	assert(m.remove(6) == NULL_TVALUE);
	assert(m.size() == 4);

  //  std::cout<<"Part 1 done\n";

    TElem e;
    MapIterator id = m.iterator();
    id.first();
    int s1 = 0, s2 = 0;
//    std::cout<<id.getCurrent().first<<" "<<id.getCurrent().second<<std::endl;
    while (id.valid()) {
        e = id.getCurrent();
//        std::cout<<id.getCurrent().first<<" "<<id.getCurrent().second<<std::endl;
        s1 += e.first;
        s2 += e.second;
        id.next();
    }
    assert(s1 == 19);
    assert(s2 == 19);

}


void testFrequency(){
    std::cout<<"Frequency tests are running...\n";

    Map m;
    assert(m.size() == 0);
    assert(m.mostFrequent() == NULL_TVALUE);

    m.add(5,5);
    m.add(7,5);
    m.add(8,5);
    m.add(4,3);
    m.add(6,8);
    m.add(2,8);
    m.add(5,2);

    assert(m.size() == 6);
    assert(m.mostFrequent() == 5);

    m.add(13,8);
    assert(m.mostFrequent() == 8);

    m.add(16,2);
    m.add(17,2);
    assert(m.mostFrequent() == 2);

    m.add(34,2);
    assert(m.mostFrequent() == 2);

    std::cout<<"Frequency tests have finished...\n";
}