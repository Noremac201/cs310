#include <iostream>
#include <sstream>
#include <climits>
#include "moberg_c_list.h"

using namespace std;

typedef unsigned int uint;

int main( int argc, char * argv[] )
{
    if ( argc != 2 )
    {
        cerr << "Usage: " << argv[0] << " n where n is the number of elements"
             << endl;
        return 1;
    }

    stringstream ss( argv[1] ); // get the command line parameter
    uint n = 0;
    ss >> n;

    srand( time( NULL ) );

    cout << "starting to create l1 and l2" << endl;
    List< uint > l1;
    List< uint > l2;
    for ( uint i = 0; i < n; i++ )
    {
        uint value = rand() % 4;
        //l2.push_front( value );
        l1.push_front( value );
    }
    cout << "starting to copy-construct l3 from l1" << endl;
    List< uint > l3{ l1 };
    cout << "starting to operator= l1 onto l2" << endl;
    l2 = l1;
    cerr << n << "\t" << l2.get_count() << "\t" << l3.get_count() << endl;

    return 0;
}
