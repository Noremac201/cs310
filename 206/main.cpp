/**
 * Driver program to test and exercise the list class. You should expand this
 * program to test every single method, all boundary cases, everything you can
 * think of.
 * @author Jon Beck
 * @version 20 January 2017
 */

typedef unsigned int uint;

#include <iostream>
#include "moberg_c_list.h"

using namespace std;

int main()
{

    List< uint > uint_list;

    uint_list.push_front( 1 );
    uint_list.push_front( 3 );
    uint_list.push_front( 5 );
    uint_list.push_front( 4 );
    uint_list.push_front( 2 );

    cout << uint_list.to_string() << endl;
    cout << endl << endl;

    cout << "The end element is: " << uint_list.tail() << endl;

    List< string > string_list;

    string_list.push_front( "Ali" );
    string_list.push_front( "Bec" );
    string_list.push_front( "Cai" );
    string_list.push_front( "Dov" );
    cout << "The front element is: " << string_list.front() << endl;
    cout << "The entire list is" << endl;
    cout << string_list.to_string() << endl;
    cout << endl;

    string_list.pop_front();
    cout << "After removing the first element" << endl;
    cout << "the last element is: " << string_list.tail() << endl;
    cout << string_list.to_string() << endl;
    cout << endl;

    List< string > copy{ string_list };
    cout << "a copy of the previous list is: " << endl;
    cout << copy.to_string() << endl;
    cout << endl;

    List< string > second_copy;
    cout << "about to make the second copy" << endl;
    second_copy = copy;
    cout << "a second copy of the copy appears as: " << endl;
    cout << second_copy.to_string() << endl;
    cout << endl;

    return 0;
}
