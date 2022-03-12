#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


const int INIT_CAP = 255; // 8 levels
const int NULL_POS = -1;

typedef struct{
    TKey key;
    TValue *values;
    int capacity;
    int current_size;
} Info;

typedef struct{
    Info info;
    int left;
    int right;
    int parent;
} BSTNode;


class SortedMultiMap {
	friend class SMMIterator;
    private:

    BSTNode* arr;
    int capacity;
    int ElemCount;
    int FirstEmpty;
    Relation r;
    int rootPosition;

    //Initialize a new key alongside its dynamic array of associated values
    Info init_key(TKey key, TValue val);
    static BSTNode init_node(Info info, int parent);

    void resize_BSTNode(BSTNode*& DynamicArray1, int &cap);
    static void resize_TValue(TValue*& DynamicArray1, int& cap);
    void resize();

    //find the position of the node containing a given key
    //returns -1 if the key does not exist in the BST
    int findKeyPosition(TKey key) const;

    //add a new node to the BST
    void addBSTNode(TKey c, TValue v, int parent, bool isLeftChild, int add_position);

    bool isLeftChild(int position) const;
    bool isRightChild(int position) const;

    //checks if a given position is empty
    bool isEmptyPosition(int position) const;

    //Removes a node with no children
    void removeSingle(int position);

    //Removes a node with one child (either right or  left depending on the truth value of hasLeftChild)
    void removeWithChild(int position, bool hasLeftChild);

    //Removes a node with two children
    void removeWithChildren(int position);

    //Remove a given value from a Dynamic Array
    //Returns true if the removal was successful, else false
    bool removeFromDynamicArray(TKey c, TValue val) const;

    //Check if a given value is in the dynamic array associated to the key
    bool isInDynamicArray(TKey c, TValue val) const;

    //delete the data from a node once it has been removed
    BSTNode deleteNodeData(BSTNode node);

    //Find the position of the maximum element in a subtree, given by its root
    int findMaximumSubtree(int rootPosition) const;

    //Find the position of the minimum element in a subtree, given by its root
    int findMinimumSubtree(int rootPosition) const;


public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();

//limits the number of values for a key to maxSize. From the keys with more
// than maxSize values, some values (does not matter which ones) will be removed
// until the number of associated values will be equal to maxSize. If a key has
// less than maxSize values, they will not be changed. The limitation does not have
// to be respected after the call to the function (so new pairs can be added).
// Returns the total number of removed values.
     int trimValues(int maxSize);
};
