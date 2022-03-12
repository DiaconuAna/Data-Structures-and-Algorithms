#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {

   // Bag b1, b2;

    //b2 = b1;

	testAll();
	cout << "Short tests over" << endl;
	testLabFunction();
	testAllExtended();

	cout << "All test over" << endl;
	return 0;
}