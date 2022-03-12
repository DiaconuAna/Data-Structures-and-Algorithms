#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;

//Time Complexity
//Best Case: theta(1) - first element is on the 1st free position of the hashtable
//Worst Case: theta(n) - the hashtable is empty (we keep looking for an element until we reach the end of the table)
//Total Complexity: O(n)
MapIterator::MapIterator(const Map& d) : map(d)
{
	this->HashTable = d.hash_table;
	this->currentPosition = 0;


	while(this->currentPosition < d.hash_table.m && d.hash_table.hashtable[this->currentPosition].next == nullptr)
	    this->currentPosition++;
	if(this->currentPosition < d.hash_table.m)
	    this->currentNode = d.hash_table.hashtable[this->currentPosition].next;
	else
	    this->currentNode = nullptr;
}

//Time Complexity
//Best Case: theta(1) - first element is on the 1st free position of the hashtable
//Worst Case: theta(n) - the hashtable is empty (we keep looking for an element until we reach the end of the table)
//Total Complexity: O(n)
void MapIterator::first() {
    this->currentPosition = 0;


    while(this->currentPosition < this->HashTable.m && this->HashTable.hashtable[this->currentPosition].next == nullptr)
        this->currentPosition++;
    if(this->currentPosition < this->HashTable.m)
        this->currentNode = this->HashTable.hashtable[this->currentPosition].next;
    else
        this->currentNode = nullptr;
}

//Time Complexity
//Best Case: theta(1) - the node we are currently at has a successor
//Worst Case: theta(n) - we keep looking for a non null element until we reach the end of the table
//Total Complexity: O(n)
void MapIterator::next() {

	if(this->valid()){

        // this->currentNode = this->HashTable.hashtable[this->currentPosition].next;
        if(this->currentNode->next == nullptr){
	    //if(this->HashTable.hashtable[this->currentPosition].next->next == nullptr) {
	        this->currentPosition++;
            while (this->currentPosition < this->HashTable.m &&
                   this->HashTable.hashtable[this->currentPosition].next == nullptr)
                this->currentPosition++;
            this->currentNode = this->HashTable.hashtable[this->currentPosition].next;
        }
	    else
	        //this->currentNode = this->HashTable.hashtable[this->currentPosition].next->next;
	        this->currentNode = this->currentNode->next;

	}
	else
	throw exception();

}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
TElem MapIterator::getCurrent(){
    if(this->valid())
        return this->currentNode->elem;
    else
        throw exception();
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
bool MapIterator::valid() const {
    if(this->currentPosition < this->HashTable.m)
        return true;
    else
        return false;
}



