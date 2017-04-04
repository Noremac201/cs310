#include <vector>
#include "heap_moberg_c.h"

using namespace std;

int main ()
{
    vector<unsigned int> values{ 81, 6, 30, 4, 100, 38, 2, 13, 35, 1 };
    Heap< unsigned int > h( values );

    cout << h.to_string() << endl;
    // output after build_heap should be:
    // 100 81 38 35 6 30 2 13 4 1
    uint build_count = h.build_heap_count();

    while( !h.is_empty() )
    {
        cout << h.delete_max() << ' ';
    }
    cout << endl;
    // output of repeated deletes should be in order:
    // 100 81 38 35 30 13 6 4 2 1

    for( auto value : values )
    {
        h.insert( value );
    }
    cout << h.to_string() << endl;
    // output after repeated inserts should be:
    // 100 81 38 35 6 30 2 4 13 1

    vector< uint > sorted;
    h.heap_sort( sorted );
    for( auto value : sorted )
    {
        cout << value << ' ';
    }
    cout << endl;
    // output should be in order:
    // 1 2 4 6 13 30 35 38 81 100

    cerr << values.size() << "\t" << build_count
         << "\t" << h.heap_sort_count() << endl;

    return 0;
}