#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}

void miniTest()
{
    std::cout<<"Functionality test beginning...\n";
    SortedMultiMap smm = SortedMultiMap(relation1);
    assert(smm.size() == 0);
    assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    smm.add(1,4);
    smm.add(1,5);
    assert(smm.size() == 4);

    smm.add(2,3);
    smm.add(2,1);
    smm.add(2,6);
    smm.add(2,8);

    assert(smm.size() == 8);

    assert(smm.trimValues(2) == 4);

    smm.add(2,3);
    smm.add(2,7);
    smm.add(5,6);
    smm.add(5,9);

    assert(smm.size() == 8);

    assert(smm.trimValues(2) == 2);
    assert(smm.trimValues(2) == 0);


    std::cout<<"Functionality test ending...\n";

}