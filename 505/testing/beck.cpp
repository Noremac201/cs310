/**
 * A program that implements branch-and-bound for the job assignment problem
 * @author originally written by Jon Beck
 * @author modified by Your Name Here
 * @version date last modified here
 */

#include <iostream>
#include <climits>
#include <queue>
#include <vector>
#include "matrix.h"

using namespace std;

typedef unsigned int uint;

struct Node
{
    uint label;
    uint level; // this is equivalent to the worker
    vector< uint > jobpath;
    vector< bool > jobsused;
    uint lower_bound;
    static uint next_label;

    explicit Node( uint level ) : level{ level }
    {
        label = next_label++;
    }

    string get_label() const
    {
        return std::to_string( label );
    }

    string to_string() const
    {
        string result = "label:" + std::to_string( label ) + ";level:" +
                        std::to_string( level ) + ";jobs:";
        for ( auto job : jobpath )
            result += std::to_string( job ) + ",";
        result.pop_back();
        result += ";lower_bound:" + std::to_string( lower_bound );
        return result;
    }

    void calculate_lower_bound( const Matrix< uint > & cost, uint & op_count )
    {
        lower_bound = 0;
        for ( uint i = 0; i < jobpath.size(); i++ )
        {
            lower_bound += cost.at( i, jobpath.at( i ) );
        }

        for ( uint row = jobpath.size(); row < cost.numrows(); row++ )
        {
            uint smallest = UINT_MAX;
            for ( uint job = 1; job < cost.numrows(); job++ )
            {
                op_count++;
                if ( cost.at( row, job ) < smallest )
                    smallest = cost.at( row, job );
            }
            lower_bound += smallest;
        }
    }
};

uint Node::next_label; // allocate storage for class member

/**
 * a class simply to provide a less-than for priority queue Nodes
 * the less-than is reversed to greater-than because STL priority queue
 * is a max-heap
 */
struct LBLessThan
{
    bool operator()( const Node & lhs, const Node & rhs )
    {
        if ( lhs.lower_bound == rhs.lower_bound )
            return lhs.label > rhs.label;
        return lhs.lower_bound > rhs.lower_bound;
    }
};

int main()
{
    // read n on std input
    uint n;
    cin >> n;
    uint op_count{ 0 };
    Matrix< uint > cost( n + 1, n + 1 );

    // read the cost matrix from stdin
    for ( uint column = 0; column < n + 1; column++ )
    {
        cost.at( 0, column ) = 0;
    }

    for ( uint row = 1; row < n + 1; row++ )
    {
        cost.at( row, 0 ) = 0;
        for ( uint column = 1; column < n + 1; column++ )
        {
            cin >> cost.at( row, column );
        }
    }

    priority_queue< Node, vector< Node >, LBLessThan > node_pq;

    Node node{ 0 };
    node.jobpath.push_back( 0 );
    node.calculate_lower_bound( cost, op_count );
    for ( uint i = 0; i <= n; i++ )
        node.jobsused.push_back( false );
    node_pq.push( node );

    uint best_solution = UINT_MAX;

    //cout << "starting node: " << node.to_string() << endl;

    uint count{ 0 };
    while ( !node_pq.empty() )
    {
        Node curnode = node_pq.top();
        node_pq.pop();
        //cout << "considering: " << curnode.get_label() << endl;
        if ( curnode.level == n )
        {
            if ( curnode.lower_bound < best_solution )
            {
                best_solution = curnode.lower_bound;
                //cout << "new best solution: " << best_solution << endl;
                count++;
            }
            else
            {
                //cout << "discarding" << endl;
            }
        }
        else
        {
            for ( uint i = 1; i <= n; i++ )
            {
                if ( !curnode.jobsused.at( i ) )
                {
                    Node newnode{ curnode.level + 1 };
                    newnode.jobpath = curnode.jobpath;
                    newnode.jobpath.push_back( i );
                    newnode.calculate_lower_bound( cost, op_count );
                    if ( newnode.lower_bound < best_solution )
                    {
                        newnode.jobsused = curnode.jobsused;
                        newnode.jobsused.at( i ) = true;
                        node_pq.push( newnode );
                        //cout << "new node: " << newnode.to_string() << endl;
                    }
                }
            }
        }
    }
    cout << count << endl;
    return 0;
}
