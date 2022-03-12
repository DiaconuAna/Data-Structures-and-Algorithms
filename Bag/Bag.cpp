#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <exception>

using namespace std;

//Time Complexity
//BestCase: theta(1), WorstCase: theta(1) => Total Complexity: theta(1)
Bag::Bag() {

	this -> capacity = 20;
	this ->Pcapacity = 20;
    this -> nrElements = 0;
    this -> PositionIndex = 0;
    this -> U = new TElem[this->capacity];
    this -> P = new TElem[this->Pcapacity];

}

//Time Complexity
//BestCase: theta(1), WorstCase: theta(nrElements+PositionIndex)
// => Total Complexity: O(nrElements+PositionIndex)
Bag& Bag::operator=(const Bag &b) {
    this -> capacity = b.capacity;
    this -> Pcapacity = b.Pcapacity;
    this ->nrElements = b.nrElements;
    this ->PositionIndex = b.PositionIndex;
    for(int i=0;i<this->nrElements;i++)
        this->U[i] = b.U[i];
    for(int i=0;i<this->PositionIndex;i++)
        this->P[i] = b.P[i];
    return *this;
}

Bag::Bag(const Bag &b) {
    this -> U = new TElem[20];
    this -> P = new TElem[20];
    this -> capacity = b.capacity;
    this -> Pcapacity = b.Pcapacity;
    this ->nrElements = b.nrElements;
    this ->PositionIndex = b.PositionIndex;
    for(int i=0;i<this->nrElements;i++)
        this->U[i] = b.U[i];
    for(int i=0;i<this->PositionIndex;i++)
        this->P[i] = b.P[i];
}

//Time Complexity
//Best Case:  theta(1) - occurs when adding the 1st element
//Worst Case: theta(2*nrElements + Pcapacity) - occurs when we add a new element(its value in U, its position
//in P), and both DynamicArrays need to be resized
//Total Complexity: O(2*nrElements + Pcapacity)
void Bag::add(TElem elem) {
    int count = 0;
    int index = 0;
    int elem_position = -1;

    while (count < 1 &&  index < this -> nrElements){
        if (this->U[index] == elem){
            count = 1;
            elem_position = index;
        }
        index++;
    }

    if (count == 1)
    {
      if(this ->PositionIndex == this ->Pcapacity)
         this -> resize(this ->P, this->Pcapacity);

      this -> P[this -> PositionIndex] = elem_position;
      this -> PositionIndex ++;
    }

    else
    {   elem_position = this -> nrElements;
        if(this ->nrElements == this ->capacity){
            this -> resize(this -> U,this->capacity);
        }

        this -> U[this -> nrElements] = elem;

        if(this ->PositionIndex == this ->Pcapacity) {
            this->resize(this -> P, this -> Pcapacity);
        }
        this -> P[this -> PositionIndex] = elem_position;
        this -> PositionIndex ++;
        this -> nrElements ++;
    }
}

//Time Complexity
//Best Case:  theta(PositionIndex) - occurs when we want to remove the 1st element from the bag- we have to
//find all of its positions in P (of length PositionIndex)
//Worst Case: theta(nrElements //+ PositionIndex//) - occurs when we want to remove an
//element which appears in the bag only once, so we need to eliminate both its occurence in U and its position in P
//by shifting all elements one element to the left (the order of the elements must be preserved)
//Total Complexity: O(nrElements // + (nrElements - index) + (PositionIndex - first_index)//)
bool Bag::remove(TElem elem) {
	int index = 0;
	int found = false;
	int element_position, j, first_index;
	int nr_of_occurrences = 0;

	index = 0;

	while (index  < this-> nrElements && found == false){
	    if (this -> U[index] == elem){
	        found = true;
	       element_position = this->P[index];
	    }
	    else{
	        index ++;
	    }
	}

	if (found == false){
        return false;
    }
	else{
	    //element_position = this -> P[index];
	    element_position = index;
	    j = 0;
	    for (j=0;j < this ->PositionIndex;j++){
	        if (element_position == this -> P[j]){
	            //printf("el_pos %d P[j] %d \n", element_position, this->P[j]);
	            //if (nr_of_occurrences == 0)
	            first_index = j;
	            nr_of_occurrences ++;
	        }
	    }

	    if (nr_of_occurrences > 1){
	        //we remove the first occurrence
	        for ( j = first_index; j < this ->PositionIndex-1 ; j ++)
	            this -> P[j] = this -> P[j+1];
	        this -> PositionIndex -=1;
	    }
	    else if (nr_of_occurrences == 1){
	        //we remove both the element and its occurrence
	        for ( j = index; j < this-> nrElements -1;j++)
	            this -> U[j] = this -> U[j+1];

            int init_elem;
            init_elem = P[first_index];
            for ( j = first_index; j < this ->PositionIndex-1 ; j ++) {
                 if (this->P[j+1] > init_elem)
                    this -> P[j+1] --;
                this->P[j] = this->P[j + 1];
            }

            this -> PositionIndex -=1;
            this -> nrElements -=1;
	    }
	    return true;}
	}

//Time Complexity
//BestCase: theta(1) -occurs when elem is on 1st position in the list
//WorstCase: theta(nrElements) -occurs when elem is on the last position or doesn't exist in the list
//Total Complexity: O(nrElements)
bool Bag::search(TElem elem) const {
	int index;
	index = 0;

	while (index < this -> nrElements)
    {
	    if (elem == this -> U[index])
	        return true;
	    index ++;
    }
	return false; 
}


//Time Complexity
//BestCase: theta(1) - element is not in the list
//WorstCase: theta(nrElements + PositionIndex) -element is on the last position in the list and we need to iterate through
//the entire P(osition array) of length PositionIndex so we can count its occurrences
//Total Complexity: O(nrElements + PositionIndex)
int Bag::nrOccurrences(TElem elem) const {
    int index = 0;
    int nr_of_occurrences = 0;
    int found = false;

    while (index  < this-> nrElements && found == false){
        if (this -> U[index] == elem){
            found = true;
        }
        else
            index++;
        }
    if (found == false)
        return 0;
    else{
        index = 0;
        while (index < this->PositionIndex) {
            if (this->U[this->P[index]] == elem)
                nr_of_occurrences++;
            index++;
        }
        return nr_of_occurrences;
        }
    }

//BC: theta(nrocc*T(n)) where BT(n)- best complexity of remove
//WC: theta(nr*T(n)) -WT(n) -worst complexity of remove
//Total complexity: O(nr*T(n))
int Bag::removeOccurrences(int nr, TElem elem) {
    int nrocc;
    nrocc = this->nrOccurrences(elem);
    if (nr<0)
        throw "Invalid data. Please try again!";
    else{
        if (nrocc<nr){
            for (int i=0;i<nrocc;i++)
                this->remove(elem);
        return nrocc;}
        else{
            for (int i=0;i<nr;i++)
                this->remove(elem);
            return nr;
        }

    }
}

//Time Complexity
//BestCase: theta(1), WorstCase: theta(1) => Total Complexity: theta(1)
int Bag::size() const {
	return this -> PositionIndex;
}

//Time Complexity
//BestCase: theta(1), WorstCase: theta(1) => Total Complexity: theta(1)
bool Bag::isEmpty() const {
    if (this -> PositionIndex == 0)
        return true;
    else
        return false;
}

//Time Complexity
//BestCase = WorstCase = theta(cap)
//Total Complexity: theta(cap)
void Bag::resize(TElem* &DynamicArray1, int &cap) {
    TElem *newArray1;
    newArray1 = new TElem[cap*2];

    for (int i=0; i<cap;i++) {
        newArray1[i] = DynamicArray1[i];
    }


    delete[] DynamicArray1;
    DynamicArray1 = newArray1;
    cap *=2;

}

//Time Complexity
//BestCase: theta(1), WorstCase: theta(1) => Total Complexity: theta(1)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


//destructor
//Time Complexity
//BestCase: theta(1), WorstCase: theta(1) => Total Complexity: theta(1)
Bag::~Bag() {

	//cout<<"\nHello !\n";
	//cout << this->U;
	delete[] this -> U;
	delete[] this -> P;
}


