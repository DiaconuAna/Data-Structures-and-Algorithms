#pragma once
//DO NOT INCLUDE BAGITERATOR
// #include <iostream>

//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator; 
class Bag {

private:
	//TODO - Representation
    TElem* U;
	TElem* P;
	int capacity; // maximum number of elements that can be stored in U
	int Pcapacity; // maximum number of elements that can be stored in P
	int nrElements; //the  current number of elements stored in the container
	int PositionIndex; //the index of the current  element in P

	//DO NOT CHANGE THIS PART

	friend class BagIterator;

	//assignment operator
	Bag& operator=(const Bag& b);

	//copy constructor
	Bag (const Bag& b);

    void resize(TElem* &DynamicArray1, int &capacity);

public:
	//constructor
	Bag();

	//adds an element to the bag - in U and mark its position in P
	//if the element has already been added to the U array we just mark its
	//position in P
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	//if the element we want to delete appears in the array for several  times, we just delete one occurrence from P
	bool remove(TElem e);

	//checks if an element appears in the bag
	// an element appears in the bag if it's in U
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//for the laboratory requirement
    //removes nr occurrences of elem. If the element appears less than nr times, all occurrences will be removed.
    // returns the number of times the element was removed.
    // throws an exception if nr is negative
    int removeOccurrences(int nr, TElem elem);

	void contents();

	//destructor
	~Bag();
};