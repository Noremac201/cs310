/**
 * A framework for exhaustive-search discrete knapsack
 * @author originally written by Jon Beck
 * @author modified by Cameron Moberg
 * @version MAR 5 2017
 */
#include <climits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

typedef unsigned int uint;

/**
 * raise an unsigned integer to an unsigned power
 * C++ has pow, but it accepts and returns floating point values
 * @param base the base to be raised to a power
 * @param exp the exponent to which to reaise the base
 * @return base ^ exp
 */
uint ipow( uint base, uint exp )
{
    if ( base == 0 )
        return 1;
    uint result = 1;
    while ( exp > 0 )
    {
        if ( (exp & 1) == 1 )
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

/*
 * standard input must be of the form
 * capacity
 * weight value
 * weight value
 * ...
 */
int main()
{
    uint op_count{ 0 };
    uint capacity;
    cin >> capacity;

    vector< uint > weights;
    vector< uint > values;
    while ( !cin.eof() )
    {
        uint weight;
        uint value;
        cin >> weight >> value;
        if ( !cin.eof() )
        {
            weights.push_back( weight );
            values.push_back( value );
        }
    }

    uint bits_req = values.size();
    uint num_perm = ipow( 2, bits_req );

    for ( uint i = 0; i < num_perm; i++ )
    {
        ostringstream str;
        uint weight_tot{ 0 };
        uint val_tot{ 0 };

        for ( uint j = 0; j < bits_req; j++ )
        {
            op_count++;
            //This bit-shifts the current permutation by 1,2,3,..,bits_req
            //to check all of the bits.
            if ( ((i >> j) & 1) == 1 )
            {
                str << " " << j;
                weight_tot += weights.at( j );
                val_tot += values.at( j );
            }
        }

        cout << left << setw( 20 ) << "{" + str.str() + " }";
        cout << setw( 10 ) << weight_tot;
        cout << (weight_tot > capacity ? "NF" : to_string( val_tot )) << endl;
    }
    cerr << weights.size() << '\t' << op_count << endl;

    return 0;
}
      
