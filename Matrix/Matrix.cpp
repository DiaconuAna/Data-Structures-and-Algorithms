#include "Matrix.h"
#include <exception>
#include <iostream>
using namespace std;

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->head = NULL;
	this->noCols = nrCols;
	this->noLines = nrLines;
	this->elemCount = 0;
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
int Matrix::nrLines() const {
	return this->noLines;
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
int Matrix::nrColumns() const {
	return this->noCols;
}

//Time Complexity
//Best Case: theta(1) - the element we are looking for is in the first position of the list
//Worst Case: theta(n) - we may need to verify every node in order to find our element
//Total complexity: O(n)
TElem Matrix::element(int i, int j) const {

    if (i>=this->noLines || i<0 || j>=this->noCols || j<0)
        throw exception();
    else{
        SLLNode *current = this->head;
        while (current != NULL){
            if (current->column == j && current->line == i)
                return current->elem;
            else
                current = current->next;
        }
    }
	return NULL_TELEM;
}


//Time Complexity
//Best Case: theta(1)- the element we want to modify (identified by its coordinates in
//the matrix) is on the 1st position on the matrix and depending on its value, we either delete it or insert it in the list
//Worst Case: theta(n) - we either want to insert or remove an element found at the end of our data structure so we iterate
//through the SLL once to see which case we found ourselves in (theta(n) -we assume the element we want to modify either is not in the list,
//or it's in the last position), and another theta(n) for adding/removing the said element
//Total Complexity: O(n)
TElem Matrix::modify(int i, int j, TElem e) {
	if (this->check_validity(i,j) == 0)
	    throw exception();
	else{
	    TElem current_element;
	    current_element = this->element(i,j);

	    if (current_element == NULL_TELEM){
	        if (e == 0)
	            return current_element;
	        else
            {
                if (this->elemCount == 0) {
                    this->insertAtPosition(0,i,j,e);
                }
                else{
                SLLNode *current = this->head;
                int position = 0, add = 0;
                while (current != NULL){
                 if((current->line==i && current->column>j) || (current->line>i)){
                     this->insertAtPosition(position,i,j,e);
                     add = 1;
                     break;}
                 position++;
                 current=current->next;}
                if (add==0){
                    this->insertAtPosition(position,i,j,e);
                }
                }

            }
	    }
	    else
        {
        if (e==0 || e==NULL_TELEM){
            this->deleteNode(i,j);
        }
        else{
            SLLNode *current = this->head;

            while (current != NULL){
                if (current->column == j && current->line == i)
                {current->elem = e;
                    break;}
                else{
                    current = current->next;}
            }
        }
        }
        return current_element;
	}
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
int Matrix::position_check(int i1, int i2, int j1, int j2) {
    if (i1<i2)
        return 1;
    else if (i1 == i2 && j1 < j2)
        return 1;
    return 0;
}

//Time Complexity
//Best Case: theta(1)
//Worst Case: theta(1)
//Total Complexity: theta(1)
int Matrix::check_validity(int i, int j) const {
    if (i>=this->noLines || i<0)
        return 0;
    if (j>=this->noCols || j<0)
        return 0;
    return 1;
}

//Time Complexity
//Best Case: theta(1)- element can be added on the 1st position
//Worst Case: theta(n)- element is added on the last position of the list
//Total Complexity: O(n)
void Matrix::insertAtPosition(int pos, int i, int j, TElem elem) {
    if (pos<0)
        return;
    else if (pos==0)
    {
        auto *new_node = new SLLNode;
        new_node->elem = elem;
        new_node->line = i;
        new_node->column = j;
        new_node->next = this->head;
        this->head = new_node;
        this->elemCount++;
    }
    else{
        SLLNode *current_node = this->head;
        int current_position = 0;
        while (current_position< pos-1 && current_node!=NULL){
            current_node = current_node->next;
            current_position+=1;
        }

        if (current_node!=NULL){
            auto *new_node = new SLLNode;
            new_node->elem = elem;
            new_node->line = i;
            new_node->column = j;
            new_node->next = current_node->next;
            current_node->next = new_node;
            this->elemCount++;
        }
        else {
        return;}
    }
}

//Time Complexity
//Best Case: theta(1)- the element that is deleted is on the 1st position
//Worst Case: theta(n)- the element that is deleted  is on the last position
//Total Complexity: O(n)
void Matrix::deleteNode(int i, int j) {
    SLLNode *current_node = this->head;
    SLLNode *prev_node = NULL;

    while (current_node!=NULL && (current_node->line !=i || current_node->column!=j)){
        prev_node = current_node;
        current_node=current_node->next;
    }
    if (current_node!=NULL && prev_node==NULL)
        this->head=this->head->next;
    else if(current_node!=NULL){
        prev_node->next = current_node->next;
        current_node->next = NULL;
    }
    delete current_node;
}


//Time Complexity
//Best Case: theta(n)- deleting the list, n is its length
//Worst Case: theta(n)- deleting the whole list
//Total Complexity: theta(n)
Matrix::~Matrix() {

    SLLNode *previous_node = NULL;
    SLLNode *current_node = this->head;

    while (current_node!=NULL){
        previous_node = current_node;
        current_node = current_node->next;
        delete previous_node;
    }

    this->elemCount = 0;
    this->head = NULL;
}

//Time Complexity
//Best Case: theta(n*lines) -
//Worst Case: theta(n*lines) -the complexity required for adding an element in the matrix is theta(n) and we have 'lines' elements
//Total complexity: O(n*lines)
void Matrix::setMainDiagonal(TElem elem) {
    int column, lines;
    column = this->nrColumns();
    lines = this->nrLines();

    if (column != lines)
        throw exception();
    else {
        for (int i = 0; i < lines; i++) {
            this->modify(i,i,elem);
        }
    }
}
