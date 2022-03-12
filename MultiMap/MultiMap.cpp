#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	this->emptyPositionHead = nullptr;

	this->ElemCount = 0;

	this->arr.position = 0; //first empty position
	this->arr.capacity = 10;
	this->arr.left = new int[this->arr.capacity];
    this->arr.right = new int[this->arr.capacity];
    this->arr.parent = new int[this->arr.capacity];
    this->arr.info = new Info[this->arr.capacity];

    for(int i=0;i<this->arr.capacity;i++){
        this->addNode(i);
    }

    print_empty_positions();

}


void MultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
}


bool MultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	return  false;
}


vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> values;
	Info root = this->findRoot();
	bool found = false;


	return vector<TValue>();
}


int MultiMap::size() const {
	return this->ElemCount;
}


bool MultiMap::isEmpty() const {
	if(this->ElemCount == 0)
	    return true;
	else
	    return false;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	//TODO - Implementation
}

void MultiMap::print_empty_positions() {
    BSTNode* node;
    node = this->emptyPositionHead;

    while(node->next!=NULL)
    {
        std::cout<<node->empty_pos<<" ";
        node = node->next;
    }
    std::cout<<node->empty_pos<<" ";
}

void MultiMap::addNode(int info) {
    BSTNode *aux = new BSTNode ;
    aux->empty_pos = info;
    aux->next = nullptr;

    if(this->emptyPositionHead == NULL){
        this->emptyPositionHead = aux;
    }
    else{
        BSTNode *tmp = this->emptyPositionHead ;
        while(tmp->next!= nullptr)
            tmp = tmp->next;
        tmp->next = aux;
    }
}

Info MultiMap::init_key(TKey key, TValue val) {
    Info key_info;

    key_info.key = key;
    key_info.capacity = 5;
    key_info.values = new TValue[key_info.capacity];
    key_info.values[0] = val;
    key_info.current_size++;

    return key_info;

}

void MultiMap::resize_int(int *&DynamicArray1, int capacity) {

        int *newArray1;
        newArray1 = new int[capacity*2];

        for (int i=0; i<capacity;i++) {
            newArray1[i] = DynamicArray1[i];
        }


        delete[] DynamicArray1;
        DynamicArray1 = newArray1;

}

void MultiMap::resize_info(Info *DynamicArray1, int capacity) {
    Info *newArray1;
    newArray1 = new Info[capacity*2];

    for (int i=0; i<capacity;i++) {
        newArray1[i] = DynamicArray1[i];
    }


    delete[] DynamicArray1;
    DynamicArray1 = newArray1;
}

void MultiMap::resize_TValue(TValue *DynamicArray1, int &capacity) {
    TValue *newArray1;
    newArray1 = new TValue [capacity*2];

    for (int i=0; i<capacity;i++) {
        newArray1[i] = DynamicArray1[i];
    }


    delete[] DynamicArray1;
    DynamicArray1 = newArray1;
    capacity*=2;
}

Info MultiMap::findRoot() const {
    for(int i=0;i<this->arr.capacity;i++){
        if(this->arr.parent[i] == -1)
            return this->arr.info[i];
    }
}

int MultiMap::getLeft(TKey key) {
    for(int i=0;i<this->arr.capacity;i++){
        if(this->arr.info[i].key == key)
            return this->arr.left[i];
    }
    return -1;
}

int MultiMap::getRight(TKey key) {
    for(int i=0;i<this->arr.capacity;i++){
        if(this->arr.info[i].key == key)
            return this->arr.right[i];
    }
    return -1;
}

int MultiMap::getParent(TKey key) {
    for(int i=0;i<this->arr.capacity;i++){
        if(this->arr.info[i].key == key)
            return this->arr.parent[i];
    }
    return -1;
}

Info MultiMap::getInfo(TKey key) {
    for(int i=0;i<this->arr.capacity;i++){
        if(this->arr.info[i].key == key)
            return this->arr.info[i];
    }

}


