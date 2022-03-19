#include <assert.h>
#include "Matrix.h"
#include <iostream>
using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);
	//cout<<"Hey\n";
	m.modify(1, 1, 5);
	//cout<<"Hello";
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
}

void moreTests()
{
    Matrix m(4, 4);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 4);
    m.modify(1, 1, 5);
    assert(m.element(1, 1) == 5);
    TElem old = m.modify(1, 1, 6);
    assert(m.element(1, 2) == NULL_TELEM);
    assert(m.element(1,1)==6);
    assert(old == 5);
    m.modify(2,2,4);
    assert(m.element(2,2)==4);
    m.modify(1,3,6);
    assert(m.element(1,3)==6);
    m.modify(2,2,0);
    assert(m.element(2,2) == NULL_TELEM);
    m.modify(1,3,0);
    assert(m.element(1,3)== NULL_TELEM);
}

void functionalityTests(){
    Matrix m1(5,6);
    try {
        m1.setMainDiagonal(2);
        assert(false);
    }
    catch (exception&){
        assert(true);
    }

    Matrix m2(4,4);
    m2.setMainDiagonal(5);

    for(int i=0;i<4;i++)
        assert(m2.element(i,i) == 5);

    std::cout<<"Functionality tests finished!\n";

}