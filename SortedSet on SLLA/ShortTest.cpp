#include "ShortTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <assert.h>
#include <iostream>

bool r2(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}


void testAll() { 
	int vverif[5];
	int iverif;
	TComp e;

	SortedSet s1(r2);
	assert(s1.add(5) == true);
	assert(s1.add(1) == true);
	assert(s1.add(10) == true);
//	assert(s1.add(7) == true);
	SortedSetIterator it1 = s1.iterator();
	it1.first();
	e = it1.getCurrent();

//	std::cout<<e<<std::endl;
////	//
//	it1.next();
//    e = it1.getCurrent();
//    std::cout<<e<<std::endl;
//    it1.next();
//    e = it1.getCurrent();
//    std::cout<<e<<std::endl;
//    it1.next();
//    e = it1.getCurrent();
//    std::cout<<e<<std::endl;
//	//

	iverif = 0;
	vverif[iverif++] = e;
	it1.next();
	while (it1.valid()) {
		assert(e < it1.getCurrent());
		e = it1.getCurrent();
		vverif[iverif++] = e;
		it1.next();
	}
	//std::cout<<vverif[0]<<" "<<vverif[1]<<" "<<vverif[2]<<std::endl;
	assert((vverif[0] == 1) && (vverif[1] == 5) && (vverif[2] == 10));


	SortedSet s(r2);
	assert(s.isEmpty() == true);
	assert(s.size() == 0);
	assert(s.add(5) == true);
	assert(s.add(1) == true);
	assert(s.add(10) == true);
	assert(s.add(7) == true);
	assert(s.add(1) == false);
	assert(s.add(10) == false);
	assert(s.add(-3) == true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);

	SortedSetIterator it = s.iterator();
	iverif = 0;
	it.first();
	e = it.getCurrent();
	vverif[iverif++] = e;
	it.next();
	while (it.valid()) {
		assert(r2(e, it.getCurrent()));
		e = it.getCurrent();
		vverif[iverif++] = e;
		it.next();
	}
	assert((vverif[0] == -3) && (vverif[1] == 5) && (vverif[2] == 7) && (vverif[3] == 10));

}

bool cond(TElem e){
    if (e%2==0)
        return false;
    return true;
}

void testFilter(){
    std::cout<<"Filter tests are running...\n";
    SortedSet s(r2);
    assert(s.add(5) == true);
    assert(s.add(4) == true);
    assert(s.add(10) == true);
    assert(s.add(6)==true);
    assert(s.add(1)==true);

    s.filter(cond);
    assert(s.search(4)==false);
    assert(s.search(1)==true);
    assert(s.search(5)==true);
    assert(s.search(6)== false);
    assert(s.search(10)==false);
    std::cout<<"Filter tests are done...\n";

}