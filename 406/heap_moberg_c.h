#ifndef HEAP_MOBERG_C
#define HEAP_MOBERG_C

#include <climits>
#include <vector>
#include <cassert>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

typedef unsigned int uint;

/**
 * a generic heap class for use in analyzing build_heap and heap_sort algorithms
 * @author Jon Beck
 * @author modified by Cameron Moberg
 * @version 6 April 2017
 */
template< typename Comparable >
class Heap
{
public:
    /**
     * The constructor for an empty heap
     */
    Heap()
            : build_count{ 0 }, sort_count{ 0 }
    {}

    /**
     * The constructor that takes in an array and builds them into a heap
     * @param items a vector of items to go into the heap
     */
    explicit Heap( const vector< Comparable > & items )
            : build_count{ 0 }, sort_count{ 0 }, array{ items }
    {
        build_heap();
    }

    /* since there are no dynamically allocated fields, all the rest of the big six
       do not need to be implemented */

    /**
     * accessor to determine whether there are any elements on the heap
     * @return true if the heap is empty; false otherwise
     */
    bool is_empty() const
    {
        return array.size() == 0;
    }

    /**
     * accessor to determine how many basic operations were performed the last time
     * heap_sort was called. this would not be in a production heap class
     * @return the count of the basic operations
     */
    uint heap_sort_count() const
    {
        return sort_count;
    }

    /**
     * accessor to determine how many basic operations were performed the last time
     * build_heap was called. this would not be in a production heap class
     * @return the count of the basic operations
     */
    uint build_heap_count() const
    {
        return build_count;
    }

    /**
     * insert an element into the heap
     * @param value the value to be inserted
     */
    void insert( const Comparable & value )
    {
        array.push_back( value );
        bubble_up( array.size() - 1 );
    }

    /**
     * delete the maximum element from the heap. should be called "delete" but that's
     * a reserved word in C++
     * @return the element with the largest value in the heap
     */
    Comparable delete_max()
    {
        assert( !is_empty() );

        Comparable to_ret = array.at( 0 );
        swap( array.at( 0 ), array.back() );
        array.pop_back();

        //uses sort_count, because that is the only thing that calls this.
        percolate_down( 0, sort_count );

        return to_ret;
    }

    /**
     * uses the heap_sort algorithm as described in Levitin 3rd pp 231 et seq
     * sets the sort_count field. fills result vector with the elements in order
     * @param result a vector that will be filled with the items in ascending order
     */
    void heap_sort( vector< Comparable > & result )
    {
        sort_count = 0;
        /*
         * To preface this, understand that this is an odd implementation of
         * heap sort purely because heap_sort is in the Heap class, and this
         * method assumes that we are modifying an array that will have all of
         * the same elements of the heap array.
         */
        result.resize( array.size() ); //n
        Heap h = *this;

        uint size = result.size();
        for ( uint i = size - 1; i != UINT_MAX; i-- )
        {
            result.at( i ) = h.delete_max();
        }
        /*
        * Since the basic operation for sort is inside of another method called
        * by delete max, percolate_down(), we only want the operations
        * made by the h Heap.
        */
        sort_count = h.sort_count;
    }
//    void heap_sort( vector< Comparable > & result )
//    {
//        sort_count = 0;
//
//        vector<Comparable> temp = result = array;
//        /*
//         * To preface this, understand that this is an odd implementation of
//         * heap sort purely because heap_sort is in the Heap class, and this
//         * method assumes that we are modifying an array that will have all of
//         * the same elements of the heap array.
//         */
//
//        uint size = result.size();
//        for ( uint i = size - 1; i != UINT_MAX; i-- )
//        {
//            result.at( i ) = delete_max();
//        }
//        /*
//        * Since the basic operation for sort is inside of another method called
//        * by delete max, percolate_down(), we only want the operations
//        * made by the h Heap.
//        */
//        array = temp;
//    }

    /**
     * generate a string representation of the array in its current state
     * requires the heap elements to implement the << operator
     * this is for debugging purposes; it would not be included in a production
     * class
     * @return string representation of the heap value in their current order
     */
    string to_string() const
    {
        if ( is_empty() )
        {
            return "";
        }
        stringstream buffer;
        for ( auto value : array )
        {
            buffer << value << ' ';
        }
        return buffer.str();
    }

private:
    uint build_count;
    uint sort_count;
    vector< Comparable > array;

    /**
     * establish a valid heap from an arbitrary arrangement of items
     */
    void build_heap()
    {
        for ( uint i = (array.size() / 2) - 1; i != UINT_MAX; i-- )
            percolate_down( i, build_count );
    }

    void bubble_up( uint index )
    {
        if ( index != 0 )
        {
            uint par_idx = (index - 1) / 2;
            if ( array.at( par_idx ) < array.at( index ) )
            {
                swap( array.at( par_idx ), array.at( index ) );
                bubble_up( par_idx );
            }
        }
    }

    void percolate_down( uint index, uint & op_count )
    {
        uint l_chld_idx = index * 2 + 1;
        uint r_chld_idx = l_chld_idx + 1;
        Comparable lg_chld;

        if ( l_chld_idx >= array.size() )
            return;
        else if ( r_chld_idx < array.size() )
        {
            op_count++;
            lg_chld = max( array.at( l_chld_idx ), array.at( r_chld_idx ) );
        }
        else
            lg_chld = array.at( l_chld_idx );

        //op_count increments on every comparison between large child and
        //root node.
        op_count++;
        if ( lg_chld > array.at( index ) )
        {
            if ( lg_chld == array.at( l_chld_idx ) )
            {
                swap( array.at( index ), array.at( l_chld_idx ) );
                percolate_down( l_chld_idx, op_count );
            }
            else if ( r_chld_idx < array.size() )
            {
                swap( array.at( index ), array.at( (r_chld_idx) ) );
                percolate_down( r_chld_idx, op_count );
            }
        }
    }
};

#endif
