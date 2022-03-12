#include "Map.h"
#include "MapIterator.h"

//Time Complexity
//Best Case: theta(n), where n is the initial size of the hashtable
//Worst Case: theta(n) - ""
//Total Complexity: theta(n)
Map::Map() {
	this->hash_table.m = 5;
	this->hash_table.hashtable = new HNode[hash_table.m];
	this->current_size = 0;

	for(int i=0; i<this->hash_table.m;i++){
	    this->hash_table.hashtable[i].next = nullptr;
	}
}

//Time Complexity
//Best Case: theta(n)
//Worst Case: theta(n)
//Total Complexity: theta(n)
Map::~Map() {

    for(int i=0;i<this->hash_table.m;i++){
        HNode* tmp;
        while(this->hash_table.hashtable[i].next != nullptr){
            tmp = this->hash_table.hashtable[i].next->next;
            delete this->hash_table.hashtable[i].next;
            this->hash_table.hashtable[i].next = tmp;
        }
    }
    delete [] this->hash_table.hashtable;
}


//Time Complexity
//Best Case: theta(1) - the element to be added needs to actually be replaced and is found on the 1st position of the
//correspoding sll
//Worst Case: theta(n) - the element to be added is not in the list (search+insert take theta(n))
//Total Complexity: O(n)
TValue Map::add(TKey c, TValue v){
	if(this->search(c)!= NULL_TVALUE){
	    int old_value = this->search(c);
	    auto* ht = this->createHashNode(c,v);
	    this->insertHT(ht);
	    return  old_value;
	}
	else{
        auto* ht = this->createHashNode(c,v);
        this->insertHT(ht);

	return NULL_TVALUE;}
}

//Time Complexity
//Best Case: theta(1) - element is on the first position
//Worst Case: theta(n) - element is on the last position of the hash table, at the end of sll
//Total Complexity: O(n)
TValue Map::search(TKey c) const{
	int h = HashFunction(c, this->hash_table.m);
	HNode *p = this->hash_table.hashtable[h].next; //.next

	while(p != nullptr){
	    if(p->elem.first == c)
	        return p->elem.second;
	    p= p->next;
	}
	return NULL_TVALUE;
}

//Time Complexity
//Best Case: theta(1) - element is not in the list
//Worst Case: theta(n) - element is on the last position of the table, at the far end of the list- m, number
//of elements
//Total Complexity: O(n)
TValue Map::remove(TKey c){
	if(this->search(c) == NULL_TVALUE)
        return NULL_TVALUE;
	else{
	    TValue elem = this->search(c);
	    TElem pair(c,elem);
	    int hash_index = HashFunction(c, this->hash_table.m);
	    HNode* tmp = this->hash_table.hashtable[hash_index].next;
	    HNode* prev = nullptr;

	    while(tmp){
	        if(tmp->elem == pair){
	            if(prev!= nullptr){
	                prev->next = tmp->next;
	            }
	            else{ //first element in the chain
	                this->hash_table.hashtable[hash_index].next = tmp->next;
	            }
	            delete tmp; //free the memory
	            this->current_size--;
                return elem;
	        }

	    prev = tmp;
	    tmp = tmp->next;}
	}
    return NULL_TVALUE;
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
int Map::size() const {

	return this->current_size;
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
bool Map::isEmpty() const{
	if(this->current_size == 0)
        return true;
    else
        return false;
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
MapIterator Map::iterator() const {
	return MapIterator(*this);
}


//Time Complexity
//Best Case: theta(1) - element can be added on a free position of the table
//Worst Case: theta(n) - replacing the key of an already existing element (found at the end of a sll)
//Total Complexity: O(n)
void Map::insertHT(HNode *newNode) {
    int hash_index = HashFunction(newNode->elem.first,this->hash_table.m);

    if(this->search(newNode->elem.first) == NULL_TVALUE){ //element is to be added on a free position of the table

    if(this->hash_table.hashtable[hash_index].next == nullptr){
        this->hash_table.hashtable[hash_index].next = newNode;
    }
    else{
        newNode->next = this->hash_table.hashtable[hash_index].next;
        this->hash_table.hashtable[hash_index].next = newNode;
    }
    this->current_size++;}

    else{ //element is already in the list- we just need to replace the old value with the new one
        int c = newNode->elem.first;
       // HNode *p = this->hash_table.hashtable[c].next;
        HNode *p = this->hash_table.hashtable[hash_index].next;

        while(p){
            if(p->elem.first == c){
                p->elem.second = newNode->elem.second;
            break;}
            p=p->next;}

    }

    if(this->current_size > this->hash_table.m * LOAD_FACTOR)
        rehash();

}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
HNode *Map::createHashNode(TKey c, TValue v) {

    auto *newNode = new HNode;

    newNode->elem = TElem(c,v);
    newNode->next = nullptr;

    return newNode;
}

//Time Complexity
//Best Case: theta(n)
//Worst Case: theta(n)
//Total Complexity: theta(n)
void Map::rehash() {
    int new_size = this->hash_table.m*2;
    int old_size = this->hash_table.m;

    auto* ht = new HNode[new_size];

    for(int i=0;i<new_size;i++)
        ht[i].next = nullptr;

    for(int i=0;i<old_size;i++)
    {
        HNode *current = this->hash_table.hashtable[i].next;
        HNode *prev;
        HNode *tmp;

        while(current != nullptr){

            int index = HashFunction(current->elem.first, new_size);
            prev = current; current = current->next;
//            tmp = this->hash_table.hashtable[i].next->next;
//            delete this->hash_table.hashtable[i].next;
//            this->hash_table.hashtable[i].next = tmp;

            if(ht[index].next != nullptr){
                prev->next = ht[index].next;
                ht[index].next = prev;
            }
            else{
                ht[index].next = prev;
                prev->next = nullptr;
            }
        }
    }


//    for(int i=0;i<old_size;i++){
//        HNode* tmp;
//        while(this->hash_table.hashtable[i].next != nullptr){
//            tmp = this->hash_table.hashtable[i].next->next;
//            delete this->hash_table.hashtable[i].next;
//            this->hash_table.hashtable[i].next = tmp;
//        }
//    }
    delete [] this->hash_table.hashtable;
    this->hash_table.hashtable = new HNode[new_size];
    this->hash_table.hashtable = ht;
    this->hash_table.m = new_size;

}



//Time Complexity
//Best Case: theta(n^2) - where n is the number of elements in the hashtable
//Worst Case: theta(n^2) - where n is the number of elements in the hashtable
//Total Complexity: theta(n^2)
TValue Map::mostFrequent() const {
    if(this->size() == 0)
        return NULL_TVALUE;
    else{
        int max = 0;
        auto* val_arr = new TValue [this->size()];
        int current_index = 0;
        TValue most_frequent_value, aux;

        MapIterator it = this->iterator();

        while (it.valid()) {

            val_arr[current_index++] = it.getCurrent().second;
            it.next();
        }

        for(int i=0;i<current_index-1;i++)
            for(int j=0;j<current_index;j++)
                if(val_arr[i] > val_arr[j]){
                    aux = val_arr[i];
                    val_arr[i] = val_arr[j];
                    val_arr[j] = aux;
                }

        int no_occ = 0;

        for(int i=0;i<current_index-1;i++){
            if(val_arr[i] == val_arr[i+1])
                no_occ++;
            else{
                if(no_occ>max){
                    max = no_occ;
                    most_frequent_value = val_arr[i];
                }
                no_occ = 1;
            }
        }

        delete [] val_arr;
        return most_frequent_value;
    }
}


