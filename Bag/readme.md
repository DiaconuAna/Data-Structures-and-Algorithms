Implement in C++ the given container (ADT) using a given representation and a dynamic array as a data structure. You are not allowed to use the vector from STL or from any other library.

Obs:

- Since your implementation will use dynamic allocation, it is a good practice to implement a destructor, copy constructor and assignment operator as well (even if they are not on the interface).

- You are not allowed to use the functions memcpy and realloc, because it is not safe to use memcpy and realloc on memory that was allocated with new. Also, if the memory location contains objects, undefined behavior can occur. The implementation might still work with these functions, but it is not a good practice to use them.

-  If you need auxiliary functions, fell free to add them to the interface of the ADT, but make them private.

ADT  Bag – represented as a dynamic array of unique elements (U) and a dynamic array of positions (P) in U of the elements from the Bag. For example, the bag [5, 10, -1, 2, 3, 10, 5, 5, -5] will be represented as:
U = [5, 10, -1, 2, 3, -5]
P = [0, 1, 2, 3,4, 1, 0, 0, 5]
