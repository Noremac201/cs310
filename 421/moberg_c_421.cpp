/**
 * calculate the longest subsequence between two strings
 * @author Jon Beck
 * @author modified by Cameron Moberg
 * @version 20 April 2017
 */
#include <climits>
#include <iomanip>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "matrix.h"

using namespace std;
typedef unsigned int uint;

// set infinity to one less than the maximum so we can add one to
// infinity and not overflow around to zero
const uint INFTY = UINT_MAX - 1;

/**
 * the recursive, memoized optimum function for computing the edit distance
 * between two strings
 * @param s the first string
 * @param i the index of the first string
 * @param t the second string
 * @param j the index of the second string
 * @param memo the memo table
 */
uint opt( const string & s, uint i, const string & t, uint j,
          Matrix< uint > & memo )
{
    // base cases are built into the memo table with entries of INFTY
    if ( memo.at( i, j ) == INFTY )
    {
        if ( s.at( i ) == t.at( j ) )
            memo.at( i, j ) = opt( s, i - 1, t, j - 1, memo ) + 1;
        else
            memo.at( i, j ) = max( opt( s, i - 1, t, j, memo ),
                                   opt( s, i, t, j - 1, memo ) );
    }
    return memo.at( i, j );
}

/**
 * Recursive algorithm to find structure of the problem.
 * @param s the first string
 * @param i the index of the first string
 * @param t the second string
 * @param j the index of the second string
 * @param memo the memo table
 * @param answ passed by reference, this is the answer (should be an empty str).
 */
void find_struct( const string & s, uint i, const string & t, uint j,
                  const Matrix< uint > & memo, string & answ )
{
    if ( i != 0 && j != 0 )
    {
        if ( memo.at( i, j ) == memo.at( i, j - 1 ) )
        {
            find_struct( s, i, t, j - 1, memo, answ );
        }
        else if ( memo.at( i, j ) == memo.at( i - 1, j ) )
        {
            find_struct( s, i - 1, t, j, memo, answ );
        }
        else
        {
            find_struct( s, i - 1, t, j - 1, memo, answ );
            answ += t.at( j );
        }
    }
    return;
}

/**
 * get the two strings from the command line
 * set up the memo table
 * print the results
 */
int main( int argc, char * argv[] )
{
    if ( argc != 3 )
    {
        cerr << "Usage: " << argv[0] << " s1 s2 where s1 and s2 are the strings"
             << endl;
        return 1;
    }

    // add a space to the beginning of each string so the string indices
    // will match the memo indices
    string s = argv[1];
    s = ' ' + s;
    string t = argv[2];
    t = ' ' + t;

    // fill the memo table with infinities
    Matrix< uint > memo( s.size() + 1, t.size() + 1 );
    for ( uint row = 1; row <= s.size(); row++ )
        for ( uint col = 1; col <= t.size(); col++ )
            memo.at( row, col ) = INFTY;

    // hard-code the base cases
    for ( uint row = 0; row <= s.size(); row++ )
        memo.at( row, 0 ) = 0;
    for ( uint col = 0; col <= t.size(); col++ )
        memo.at( 0, col ) = 0;
    memo.at( 0, 0 ) = 1;
    uint result = opt( s, s.size() - 1, t, t.size() - 1, memo );

    cout << "The LCS has length " << result << endl;

    string answer;
    find_struct( s, s.size() - 1, t, t.size() - 1, memo, answer );

    cout << "The LCS is " << answer << endl;

    return 0;
}
