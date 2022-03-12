#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

//Time Complexity
//Best Case: theta(n)
//Worst Case: theta(n)
//Total Complexity: theta(n)
SortedMultiMap::SortedMultiMap(Relation r) {


  this->capacity = INIT_CAP;
  this->arr = new BSTNode[this->capacity];
  this->r = r;
  this->ElemCount = 0;
  this->FirstEmpty = 1;
  this->rootPosition = NULL_POS;

  for(int i=1;i<this->capacity-1;i++){
      this->arr[i].parent = -13; //how we mark the position as  free
      this->arr[i].left = i+1;
  }
  this->arr[this->capacity-1].left = -2;

}

//Time Complexity
//Best Case: theta(n) - the element is added at the last level of the tree
//Worst Case: theta(n) -
//Total Complexity: theta(n)
void SortedMultiMap::add(TKey c, TValue v) {
	int current_pos = this->rootPosition;
	int parent_pos = -1;
	bool isLeftChild = false;

    if (this->ElemCount >= this->capacity) //the array is full
    {
       // current_pos = this->capacity;
       //std::cout<<"resize1\n";
        this->resize();
       // this->FirstEmpty = current_pos + 1;
    }

	if(current_pos == -1) //the tree has no nodes in it so we add the root
    {
	    this->addBSTNode(c,v,NULL_POS,isLeftChild,0);

    }
	else{
	    //check if the key is already in the BST. If it is, apppend the value to the corresponding dynamic array, else
	    //add a new node with the corresponding information
	    vector<TValue> elems = this->search(c);
	    if (elems.size() == 0) {
            while (current_pos < this->capacity) {
                //add the new node- find the subtree where it belongs
                if (this->arr[current_pos].parent == -13) { //we can add the node in the current position as a leaf
                    this->addBSTNode(c, v, parent_pos, isLeftChild, current_pos);
                    return;
                }

                //we check if it's a left child
                if (this->r(c, this->arr[current_pos].info.key)) {

                    parent_pos = current_pos;
                    current_pos = this->arr[current_pos].left;
                    isLeftChild = true;
                } else {
                    //it's a right child
                    parent_pos = current_pos;
                    current_pos = this->arr[current_pos].right;
                    isLeftChild = false;
                }

                //if we found the place to add it, we just find the next empty position in the array
                if (current_pos == -1) {
                    if (this->FirstEmpty == -2) //the array is full
                    {
                        current_pos = this->capacity;
                        this->resize();
                        this->FirstEmpty = current_pos + 1; //the previous value of capacity + 1

                    } else {
                        current_pos = this->FirstEmpty;
                        this->FirstEmpty = this->arr[this->FirstEmpty].left;
                    }
                }
            }
        }
	    else{
	        current_pos = this->findKeyPosition(c);

	        int next_elem = this->arr[current_pos].info.current_size;

	        if(next_elem == this->arr[current_pos].info.capacity){
	            SortedMultiMap::resize_TValue(this->arr[current_pos].info.values, this->arr[current_pos].info.capacity);
	        }

	        this->arr[current_pos].info.values[next_elem] = v;
	        this->arr[current_pos].info.current_size++;
            this->ElemCount += 1;

        }
	}
}

//Time Complexity
//Best Case: theta(1)- the element is the root of the tree
//Worst Case: theta(n) - the element is either not in the tree or it is a leaf
//Total Complexity: O(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
	int key_pos = this->findKeyPosition(c);
	vector<TValue> v;
	if(key_pos == -1)
	    return v;
	else{
	    for(int i=0;i<this->arr[key_pos].info.current_size;i++){
	        v.push_back(this->arr[key_pos].info.values[i]);
	    }
	    return v;
	}
}


//Time Complexity
//Best Case: theta(1)- the node has no children, or one child
//Worst Case: theta(n) - the node has 2 children
//Total Complexity: O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
	//we first check if the element exists in the BST
    vector<TValue> elems = this->search(c);
    if (elems.size() == 0){ //there is no node containing the key c
        return false;
    }
    else{
        //for now, just check if the node has no children and remove it as it is
        if(elems.size() == 1) { //the key has exactly  one value associated to it
            //first we check if the value  associated to the key corresponds to the value we want to remove
            if (this->isInDynamicArray(c, v)) {
                int index = this->findKeyPosition(c);
                if (this->arr[index].left == -1 && this->arr[index].right == -1) { //the node has no children/ is a leaf
                    this->removeSingle(index);
                    this->ElemCount -= 1;
                    return true;
                }

                bool hasLeftChild, hasRightChild;

                if(this->arr[index].left != -1)
                    hasLeftChild = true;
                else
                    hasLeftChild = false;

                if(this->arr[index].right != -1)
                    hasRightChild = true;
                else
                    hasRightChild = false;

                if(hasRightChild && hasLeftChild){ //remove a node with two children
                    this->removeWithChildren(index);
                    this->ElemCount -= 1;
                    return true;
                }
                else if(hasRightChild || hasLeftChild){//remove  a node with one child
                    this->removeWithChild(index, hasLeftChild);
                    this->ElemCount -= 1;
                    return true;

                }
            }
            else { //the value cannot be removed as it does not exist
                return false;
            }
        }
        else{ //the key has more than one value associated to it
            bool ok = this->removeFromDynamicArray(c,v);
            int index = this->findKeyPosition(c);

            if(ok){

                this->arr[index].info.current_size = elems.size()-1;
                this->ElemCount -= 1;
            }
            return ok;
        }
    }
  return true;
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
int SortedMultiMap::size() const {
	return this->ElemCount;
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
bool SortedMultiMap::isEmpty() const {
	if(this->ElemCount == 0)
        return true;
    return false;
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
SortedMultiMap::~SortedMultiMap() {

	delete [] this->arr;
}


//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
Info SortedMultiMap::init_key(TKey key, TValue val) {
    Info key_info;

    key_info.key = key;
    key_info.capacity = 5;
    key_info.values = new TValue[key_info.capacity];
    key_info.values[0] = val;
    key_info.current_size++;

    return key_info;

}



//Time Complexity
//Best Case: theta(n)
//Worst Case: theta(n)
//Total Complexity: theta(n)
void SortedMultiMap::resize_TValue(TValue *&DynamicArray1, int &cap) {
    auto* newarr = new TValue[cap*2];
    for(int i=0;i<cap;i++)
        newarr[i] = DynamicArray1[i];
    cap*=2;
    delete[] DynamicArray1;
    DynamicArray1 = newarr;

}



//Time Complexity
//Best Case: theta(1)- element is the root
//Worst Case: theta(n) - element is not in the list or it's a leaf
//Total Complexity: O(n)
int SortedMultiMap::findKeyPosition(TKey key) const {
    int current_pos = this->rootPosition;

    //if the Sorted MultiMap has no elements, we return -1
    if (this->rootPosition == NULL_POS){
        return -1;
    }

    while(current_pos < this->capacity){
        if(this->arr[current_pos].info.key == key){
            return current_pos;
        }
        //we check in the left child(if it exists) if the relation is true
        if(this->r(key, this->arr[current_pos].info.key) && this->arr[current_pos].left != NULL_POS){
            current_pos = this->arr[current_pos].left;
        }
        //else we do the same thing, but for the right child
        else if(!this->r(key, this->arr[current_pos].info.key) && this->arr[current_pos].right != NULL_POS){
            current_pos = this->arr[current_pos].right;
        }
        else
            return -1;
    }

    return -1;
}



//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
bool SortedMultiMap::isLeftChild(int position) const {
    if(position != -1 && position!=this->rootPosition && this->arr[this->arr[position].parent].left == position)
        return true;
    return false;
}


//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
bool SortedMultiMap::isRightChild(int position) const {
    if(position != -1 && position!=this->rootPosition && this->arr[this->arr[position].parent].right == position)
        return true;
    return false;
}



//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
BSTNode SortedMultiMap::init_node(Info info, int parent) {
   BSTNode node;
   node.info = info;
   node.right = -1;
   node.left = -1;
   node.parent = parent;

    return node;
}



//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
void SortedMultiMap::addBSTNode(TKey c, TValue v, int parent, bool isLeftChild, int add_position) {
    Info BSTNodeInfo = this->init_key(c, v);
    BSTNode node = this->init_node(BSTNodeInfo, parent);

    if(this->FirstEmpty == this->arr[add_position].left){
        this->FirstEmpty = this->arr[this->arr[add_position].left].left;
    }

    this->arr[add_position] = node;
    this->ElemCount += 1;

    //we check if it is the root
    if(parent == NULL_POS){
        this->rootPosition = add_position;
    }
    else{
        if(isLeftChild){
            this->arr[parent].left = add_position;
        }
        else{
            this->arr[parent].right = add_position;
        }
    }
}



//Time Complexity
//Best Case: theta(n)
//Worst Case: theta(n)
//Total Complexity: theta(n)
void SortedMultiMap::resize_BSTNode(BSTNode *&DynamicArray1, int &cap) {
    BSTNode *newArray1;
    newArray1 = new BSTNode[cap * 2];

    for (int i=0; i < cap; i++) {
        newArray1[i] = DynamicArray1[i];
    }


    delete[] DynamicArray1;
    DynamicArray1 = newArray1;
    cap*=2;
}



//Time Complexity
//Best Case: theta(n)
//Worst Case: theta(n)
//Total Complexity: theta(n)
void SortedMultiMap::resize() {

    this->resize_BSTNode(this->arr, this->capacity);

    for(int i=this->capacity/2;i<this->capacity-1;i++){
        this->arr[i].left = i+1;
    }
    this->arr[this->capacity-1].left = -2;
}



//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
BSTNode SortedMultiMap::deleteNodeData(BSTNode node) {
    node.parent = -13;
    node.left = -1;
    node.right = -1;
    delete [] node.info.values;

    return node;
}



//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
void SortedMultiMap::removeSingle(int position) {

    //we check if it's the left child
    if(this->isLeftChild(position)){
        this->arr[this->arr[position].parent].left = -1;
        int nextEmpty = this->arr[this->FirstEmpty].left;
        this->arr[position].left = nextEmpty;
        this->arr[this->FirstEmpty].left = position;
    }
    else if(this->isRightChild(position)){
        this->arr[this->arr[position].parent].right = -1;
        int nextEmpty = this->arr[this->FirstEmpty].left;
        this->arr[position].left = nextEmpty;
        this->arr[this->FirstEmpty].left = position;
    }
    else{ //if it's  no left or right child, it must be the root
        this->rootPosition = -1;
        int nextEmpty = this->arr[this->FirstEmpty].left;
        this->arr[position].left = nextEmpty;
        this->arr[this->FirstEmpty].left = position;
    }
    this->arr[position] = this->deleteNodeData(this->arr[position]);

}


//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
void SortedMultiMap::removeWithChild(int position, bool hasLeftChild) {
    //we check if it's the left child
    if(this->isLeftChild(position)) {
        if (hasLeftChild) {
            this->arr[this->arr[position].parent].left = this->arr[position].left;
            this->arr[this->arr[position].left].parent = this->arr[position].parent;
            int nextEmpty = this->arr[this->FirstEmpty].left;
            this->arr[position].left = nextEmpty;
            this->arr[this->FirstEmpty].left = position;
        } else {
            this->arr[this->arr[position].parent].left = this->arr[position].right;
            this->arr[this->arr[position].right].parent = this->arr[position].parent;
            int nextEmpty = this->arr[this->FirstEmpty].left;
            this->arr[position].left = nextEmpty;
            this->arr[this->FirstEmpty].left = position;
        }
    }
    else if(this->isRightChild(position)){
        if (hasLeftChild) {
            this->arr[this->arr[position].parent].right = this->arr[position].left;
            this->arr[this->arr[position].left].parent = this->arr[position].parent;
            int nextEmpty = this->arr[this->FirstEmpty].left;
            this->arr[position].left = nextEmpty;
            this->arr[this->FirstEmpty].left = position;
        } else {
            this->arr[this->arr[position].parent].right = this->arr[position].right;
            this->arr[this->arr[position].right].parent = this->arr[position].parent;
            int nextEmpty = this->arr[this->FirstEmpty].left;
            this->arr[position].left = nextEmpty;
            this->arr[this->FirstEmpty].left = position;
        }
    }
    else{ //if it's  no left or right child, it must be the root
        int tmp = this->rootPosition;
        if(hasLeftChild){
            this->rootPosition = this->arr[tmp].left;
            this->arr[this->arr[tmp].left].parent = -1;
        }
        else{
            this->rootPosition = this->arr[tmp].right;
            this->arr[this->arr[tmp].right].parent = -1;
        }
    }

    this->arr[position] = this->deleteNodeData(this->arr[position]);

}

/*
 * Find the maximum of the left subtree, move it to the node to
be deleted, and delete the maximum
OR
Find the minimum of the right subtree, move it to the node to
be deleted, and delete the minimum
 */

//Time Complexity
//Best Case: theta(n) - because we need to find the maximum left subtree
//Worst Case: theta(n)
//Total Complexity: theta(n)
void SortedMultiMap::removeWithChildren(int position) {
    //both left and right children exist
    int maxPosition = this->findMaximumSubtree(this->arr[position].left); //the maximum of the left subtree
    this->arr[position] = this->arr[maxPosition]; //move it to the node to be deleted

    //now delete the maximum
    int nextEmpty = this->arr[this->FirstEmpty].left;
    this->arr[maxPosition].left = nextEmpty;
    this->arr[this->FirstEmpty].left = position;

    //in order to remove the leaf, we have to check whether it is a left or a right child
    if(this->isLeftChild(maxPosition)){
        this->arr[this->arr[maxPosition].parent].left = -1;
    }
    else if(this->isRightChild(maxPosition)){
        this->arr[this->arr[maxPosition].parent].right = -1;
    }
    this->arr[maxPosition] = this->deleteNodeData(this->arr[maxPosition]);

}


//Time Complexity
//Best Case: theta(n) - elements need to be shifted one position to the left
//Worst Case: theta(n) - same
//Total Complexity: theta(1)
bool SortedMultiMap::removeFromDynamicArray(TKey c, TValue val) const {
    int index = this->findKeyPosition(c);
    int ok = 1, pos;

    for(int i=0;i<this->arr[index].info.current_size && ok;i++){
        if(this->arr[index].info.values[i] == val){
            pos = i;
            ok = 0;
        }
    }

    if(ok == 1)
        return false; //the value is not part of the dynamic array
    else{
        for(int i=pos;i<this->arr[index].info.current_size-1;i++)
            this->arr[index].info.values[i] = this->arr[index].info.values[i+1];
            return true;
        }
}



//Time Complexity
//Best Case: theta(1)- the maximum node is at the root
//Worst Case: theta(n) - when all the elements are connected ( like a chain)
//Total Complexity: O(n)
int SortedMultiMap::findMaximumSubtree(int rootPosition) const{
    //we keep going to the right,  as long as there are positions
    while(rootPosition < this->capacity && this->arr[rootPosition].right != -1){
        rootPosition = this->arr[rootPosition].right;
    }

    return rootPosition;
}

//Time Complexity
//Best Case: theta(1)- the minimum node is at the root
//Worst Case: theta(n) - when all the elements are connected ( like a chain)
//Total Complexity: O(n)
int SortedMultiMap::findMinimumSubtree(int rootPosition) const{
    //we keep going to the left,  as long as there are positions
    while(rootPosition < this->capacity && this->arr[rootPosition].left != -1){
        rootPosition = this->arr[rootPosition].left;
    }

    return rootPosition;
}


//Time Complexity
//Best Case: theta(1)- element is on the 1st position
//Worst Case: theta(n) - element is either on the last position, or not in the array
//Total Complexity: O(n)
bool SortedMultiMap::isInDynamicArray(TKey c, TValue val) const {
    vector<TValue> values = this->search(c);

    int ok = 1, pos;
    for(int i=0;i<values.size() && ok;i++){
        if(values[i] == val){
            pos = i;
            ok = 0;
        }
    }

    if(ok == 0)
        return true; //the value is not part of the dynamic array
    else{
        return false;
    }
}


//Time Complexity
//Best Case: theta(n)- no values need to be removed from any keys
//Worst Case: theta(n^2) - for each key at least a value must be removed
//Total Complexity: 0(n^2)
int SortedMultiMap::trimValues(int maxSize) {
    int nr_removed = 0;
    SMMIterator it = this->iterator();
    it.first();
    while (it.valid()){
        int key = it.getCurrent().first;
        int value = it.getCurrent().second;
        int key_position = this->findKeyPosition(key);
       // std::cout<<key<<" "<<value<<" "<<this->arr[key_position].info.current_size<<std::endl;
        if(this->arr[key_position].info.current_size > maxSize){
            this->remove(key, value);
                nr_removed += 1;
               // std::cout<<"Removed "<<key<<" "<<value<<std::endl;

        }
        else{
        it.next();
        }
    }
    return nr_removed;
}
