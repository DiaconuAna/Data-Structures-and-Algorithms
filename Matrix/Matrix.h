#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

typedef struct Node{
    int line,  column;
    TElem elem;
    Node* next;
} SLLNode;

class Matrix {

private:
	SLLNode* head;
	int noLines;
	int noCols;
	int elemCount;

	//checks if the element found at position i1,j1 is before the element found at position i2,j2 in the matrix
	int position_check(int i1, int i2, int j1, int j2);

    //checks if the coordinates are valid wrt the dimensions of the matrix
    int check_validity(int i, int j) const;

    //A node is inserted at a given position
    void insertAtPosition(int pos, int i, int j,TElem elem);

    //Delete a node with a given information
    void deleteNode(int i, int j);

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//sets all the values from the main diagonal to the value elem.
	//throws an exception if it is not a square matrix
    void setMainDiagonal(TElem elem);

	//matrix destructor
    ~Matrix();

};
