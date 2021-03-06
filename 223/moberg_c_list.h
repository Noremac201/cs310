#ifndef MOBERG_C_LIST
#define MOBERG_C_LIST
typedef unsigned int uint;

#include <cassert>
#include <sstream>

using namespace std;

/**
 * A simplified generic singly linked list class to illustrate C++ concepts
 * @author Jon Beck
 * @author Modified by Cameron Moberg
 * @version FEB 24, 2017
 */
template< typename Object >
class List
{
private:
    /**
    * A class to store data and provide a link to the next node in the list
    */
    class Node
    {
    public:
        /**
        * The constructor
        * @param data the data to be stored in this node
        */
        explicit Node( const Object & data )
                : data{ data }, next{ nullptr }
        {}

        Object data;
        Node * next;
    };

public:
    /**
    * The constructor for an empty list
    */
    List()
            : op_count{ 0 }, size{ 0 }, first{ nullptr }, last{ nullptr }
    {}

    /**
    * the copy constructor
    */
    List( const List & rhs )
            : op_count{ 0 }, size{ rhs.size }, first{ nullptr }, last{ nullptr }
    {
        size = rhs.size;
        if ( !rhs.is_empty() )
        {
            Node * temp = first = new Node{ rhs.first->data };
            Node * rhs_temp = rhs.first;
            op_count++;
            while ( rhs_temp->next != nullptr )
            {
                rhs_temp = rhs_temp->next;
                temp->next = new Node{ rhs_temp->data };
                temp = temp->next;
                last = temp;
                op_count++;
            }
            last->next = nullptr;
        }
    }

    /**
    * Disallow the rvalue copy constructor.
    */
    List( const List && rhs ) = delete;

    /**
    * the operator= method
    */
    List & operator=( const List & rhs )
    {
        op_count = 0;
        // checks if its talking about same element, or they're both empty.
        if ( this == &rhs || (rhs.is_empty() && is_empty()) )
            return *this;

        copy_nodes( rhs );

        if ( size > rhs.size ) // lhs side is longer.
        {
            uint diff = size - rhs.size;
            Node * iter = first;

            //iterate to last actual element of new lhs.
            for ( uint i = 0; i < rhs.size - 1; i++ )
            {
                iter = iter->next;
            }

            last = iter;

            Node * current = iter->next;
            Node * temp;
            //delete rest of list.
            for ( uint i = 0; i < diff; i++ )
            {
                temp = current;
                current = current->next;
                delete temp;
                op_count++;
            }
            last->next = nullptr;
        }
        else if ( size < rhs.size ) //rhs is longer.
        {
            Node * rhs_iter = rhs.first;
            Node * iter;
            if ( is_empty() )
            {
                first = iter = new Node{ rhs_iter->data };
                op_count++;
                size++;
            }
            else
            {
                iter = first;
                //iterate to last element of lhs
                for ( uint i = 1; i < size; i++ )
                {
                    iter = iter->next;
                    rhs_iter = rhs_iter->next;
                }
            }
            uint diff = rhs.size - size;
            for ( uint i = 0; i < diff; i++ )
            {
                op_count++;
                rhs_iter = rhs_iter->next;
                iter->next = new Node{ rhs_iter->data };
                iter = iter->next;
            }
            last = iter;
            last->next = nullptr;
        }
        size = rhs.size;
        return *this;
    }

    /**
     * Disallow the rvalue operator= constructor.
     */
    List & operator=( const List && rhs ) = delete;

    /**
     * The destructor that gets rid of everything that's in the list and
     * resets it to empty. If the list is already empty, do nothing.
     */
    ~List()
    {
        if ( size != 0 )
        {
            Node * current = first;
            Node * temp;

            while ( current != nullptr )
            {
                temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    /**
    * Copies node data from rhs to lhs.
    * @param rhs List to copy from.
    */
    void copy_nodes( const List & rhs )
    {
        Node * temp = first;
        Node * rhs_temp = rhs.first;
        for ( uint i = 0; i < min( size, rhs.size ); i++ )
        {
            temp->data = rhs_temp->data;
            temp = temp->next;
            rhs_temp = rhs_temp->next;
            op_count++;
        }
    }

    /**
     * Put a new element onto the beginning of the list
     * @param item the data the new element will contain
     */
    void push_front( const Object & item )
    {
        Node * new_node = new Node{ item };

        if ( is_empty() )
        {
            last = new_node;
        }
        else
        {
            new_node->next = first;
        }
        first = new_node;
        size++;
    }

    /**
     * Remove the element that's at the front of the list. Causes an
     * assertion error if the list is empty.
     */
    void pop_front()
    {
        assert( !is_empty() );
        Node * temp = first;

        if ( first == last )
        {
            first = last = nullptr;
        }
        else
        {
            first = first->next;
        }
        delete temp;
        size--;
    }

    /**
     * Accessor to return the data of the element at the front of the list.
     * Causes an assertion error if the list is empty.
     * @return the data in the front element
     */
    const Object & front() const
    {
        assert( !is_empty() );
        return first->data;
    }

    /**
     * Accessor to return the data of the element at the tail of the list.
     * Causes an assertion error if the list is empty.
     * @return the data in the last element
     */
    const Object & tail() const
    {
        assert( !is_empty() );
        return last->data;
    }

    /**
     * Accessor to determine whether the list is empty
     * @return a boolean corresponding to the emptiness of the list
     */
    bool is_empty() const
    {
        return size == 0;
    }

    /**
     * Generate a string representation of the list
     * Requires operator<< to be defined for the list's object type
     * @return string representation of the list
     */

    string to_string() const
    {
        if ( size == 0 )
        {
            return "";
        }
        stringstream buffer;
        for ( auto current = first;
              current != nullptr; current = current->next )
        {
            buffer << current->data << ' ';
        }
        return buffer.str();
    }

    uint get_count()
    {
        return op_count;
    }

private:
    uint op_count;
    uint size;
    Node * first;
    Node * last;
};

#endif
