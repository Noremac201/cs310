/**
* Program that demonstrates using pointers, pointer-pointers, and references.
* @author Cameron Moberg
* @version 28 January 2017
*/

typedef unsigned int unit;
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
   int* a = new int{5};
   int* b = a;
   int& c = *a;

   int* d = new int{8};
   int** e = new int*{d};
   int*& f = *e; //reference to a pointer.

   (*b)++; //Increment 5 to 6.
   c++; //Increment 6 to 7.
   **e *= 10; //Multiply 8 by 10.

   cout << *a << endl;
   cout << *b << endl;
   cout << c << endl;

   cout << *d << endl;
   cout << **e << endl;
   cout << *f << endl;

   //clean up Heap Memory.
   delete a;
   delete d;
   delete e;
   
   return 0;
}
