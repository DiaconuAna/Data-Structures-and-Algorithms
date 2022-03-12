#pragma once
#include <utility>
//DO NOT INCLUDE MAPITERATOR


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111)

#define LOAD_FACTOR 7.5

class MapIterator;

typedef struct Node{
    TElem elem;
    Node* next;
} HNode;


typedef struct hashTable{
    int m; //table capacity
    HNode *hashtable;
}HT;


class Map {
	//DO NOT CHANGE THIS PART
	friend class MapIterator;

	private:
		HT hash_table;
        int current_size; //number of elements currently stored in the hash table

    int HashFunction(TKey key, int cap) const {
        if(key<0)
            key = -key;
        return key%cap;
    }

    void rehash();
    void insertHT(HNode* newNode);
    HNode* createHashNode(TKey c, TValue v);



	public:

	// implicit constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator() const;

    //returns the TValue that appears most frequently in the Map. If multiple TValues appear most frequently,
    // it returns any of them.
    // if the Map is empty, the operation returns NULL_TVALUE
    TValue mostFrequent() const;


	// destructor
	~Map();

};



