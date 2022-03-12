#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(n)
//Total Complexity: theta(n)
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->binaryTree = map.arr;
	this->currentNodePosition = map.rootPosition;

	//if the tree is empty there is no need for an iterator
	if(this->currentNodePosition == -1){
	    this->currentNodePosition = -13; //invalid position
	    return;
	}
	//we begin at the minimum key  of the multimap
    this->currentNodePosition = this->map.findMinimumSubtree(this->currentNodePosition);
	this->DAcurrentindex = 0;
}


//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
void SMMIterator::first(){

    this->currentNodePosition = map.rootPosition;

    //if the tree is empty there is no need for an iterator
    if(this->currentNodePosition == -1){
        this->currentNodePosition = -13; //invalid position
        return;
    }
    //we begin at the minimum key  of the multimap
    this->currentNodePosition = this->map.findMinimumSubtree(this->currentNodePosition);
    this->DAcurrentindex = 0;

}


//Time Complexity
//Best Case: theta(1) - the dynamic array associated to the current key has elements left
//Worst Case: theta(n) - we try finding a bigger value by going up levels
//Total Complexity: O(n)
void SMMIterator::next(){
	if(!this->valid())
	    throw exception();

	//we check to see if the dynamic array associated to the current key has  elements left
	if(this->DAcurrentindex < this->binaryTree[currentNodePosition].info.current_size-1)
	    this->DAcurrentindex += 1;
	else {
        //we check for a right  child
        if (this->binaryTree[this->currentNodePosition].right != -1) {
            //we get the minimum from the right subtree
            this->currentNodePosition = this->map.findMinimumSubtree(this->binaryTree[this->currentNodePosition].right);
            this->DAcurrentindex = 0;
        }

        //if the node doesn't have a right child we need to go up the tree
        //case 1: if the current node is a left child- its parent is the next position (going up a level)
        //case 2: else we need to find a value bigger than the current one
        else{
            if(this->map.isLeftChild(this->currentNodePosition)){
                this->currentNodePosition = this->binaryTree[this->currentNodePosition].parent;
                this->DAcurrentindex = 0;
            }
            else{
            int tmp = this->binaryTree[this->currentNodePosition].parent;

            while(tmp>=0 && this->map.r(this->binaryTree[tmp].info.key, this->binaryTree[this->currentNodePosition].info.key)){
                if (tmp == 0){
                    //maximum element - position becomes invalid
                    this->currentNodePosition = -13;
                    return;
                }
                tmp = this->binaryTree[tmp].parent;
            }
            this->currentNodePosition = tmp;
            this->DAcurrentindex = 0;}
        }

    }
}


//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
bool SMMIterator::valid() const{
//    if(this->binaryTree[this->currentNodePosition].info.key % 2== 0){
//
//    }
	if(this->currentNodePosition == -1 || this->currentNodePosition >= this->map.capacity || this->currentNodePosition == -13){
//        std::cout<<this->binaryTree[this->currentNodePosition].info.key<<" "<<this->binaryTree[this->currentNodePosition].info.current_size<<std::endl;
        return false;}
	if(this->binaryTree[this->currentNodePosition].parent == -13){
 //       std::cout<<this->binaryTree[this->currentNodePosition].info.key<<" "<<this->binaryTree[this->currentNodePosition].info.current_size<<std::endl;
        return false;}
	if(this->DAcurrentindex >= this->binaryTree[this->currentNodePosition].info.current_size){
 //       std::cout<<this->binaryTree[this->currentNodePosition].info.key<<" "<<this->binaryTree[this->currentNodePosition].info.current_size<<std::endl;
        return false;}
	return true;

}


//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
TElem SMMIterator::getCurrent() const{
	if(!this->valid()) {
        throw exception();
    }
	else{
	    TValue elem = this->binaryTree[this->currentNodePosition].info.values[this->DAcurrentindex];
	    TKey key = this->binaryTree[this->currentNodePosition].info.key;
	    TElem pair{key, elem};
	    return pair;
	}
}


