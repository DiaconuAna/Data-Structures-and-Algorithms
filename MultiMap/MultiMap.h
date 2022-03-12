#pragma once
#include<vector>
#include<utility>
#include<iostream>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

typedef struct{
    TKey key;
    TValue *values;
    int capacity;
    int current_size;
} Info;

typedef struct{
    Info *info;
    int* left;
    int* right;
    int* parent;
    int position;
    int capacity;
} Array;

typedef struct Node{
    int empty_pos;
    Node* next;
} BSTNode;

class MultiMap
{
	friend class MultiMapIterator;

private:
	BSTNode* emptyPositionHead;
	Array arr;
	int ElemCount;

	Info init_key(TKey key, TValue val);
    void resize_int(int* &DynamicArray1, int capacity);
    void resize_info(Info* DynamicArray1, int capacity);
    void resize_TValue(TValue* DynamicArray1, int& capacity);

    void print_empty_positions();

    //adds a new empty position at the end of the list
    void addNode(int info);

    //removes a position once it's been occupied as it's not empty anymore
    void removeNode(int info);

    //returns the information corresponding to the root of the tree whose parent is -1
    Info findRoot() const;
    int getLeft(TKey key);
    int getRight(TKey key);
    int getParent(TKey key);
    Info getInfo(TKey key);


public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//descturctor
	~MultiMap();


};

