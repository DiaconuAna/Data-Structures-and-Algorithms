#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
typedef bool (*Condition)(TComp);
#define NULL_TELEM -11111
class SortedSetIterator;

typedef struct sll{
    TComp* elems;
    int* next;
    int capacity;
    int head;
    int firstEmpty;
}SLLA;

class SortedSet {
	friend class SortedSetIterator;
private:
	SLLA list;
	Relation rel;
	int _size;

	void insertFirst(TComp e);
	int searchPosition(TComp elem);
	void insertAtPosition(int pos, TComp elem);

	//void print();

public:
	//constructor
	SortedSet(Relation r);

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	
	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;


	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

    //keeps in the sortedset only those elements that respect the given condition
    // where Condition is a function which takes as parameter an element and returns true or
    // false depending on whether the element respects the condition. Obs. add the following typedef
    // to the beginning of SortedSet.h  typedef bool (*Condition)(TComp);
    void filter(Condition cond);

	// destructor
	~SortedSet();





};
