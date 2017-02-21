#ifndef MOBERG_C_LIST
#define MOBERG_C_LIST
typedef unsigned int uint;

#include <cassert>
#include <sstream>

using namespace std;

/**
 * a simplified generic singly linked list class to illustrate C++ concepts
 * @author Jon Beck
 * @author modified by Cameron Moberg
 * @version FEB 17, 2017
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
            : size{ 0 }, first{ nullptr }, last{ nullptr }
    {}

    /**
    * the copy constructor
    */
    List( const List & rhs )
            : size{ rhs.size }, first{ nullptr }, last{ nullptr }
    {
        size = rhs.size;
        if ( !rhs.is_empty() )
        {

            Node * temp = first = new Node{ rhs.first->data };
            Node * rhs_temp = rhs.first;

            while ( rhs_temp->next != nullptr )
            {
                rhs_temp = rhs_temp->next;
                temp->next = new Node{ rhs_temp->data };
                temp = temp->next;
                last = temp;
            }
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
                rhs_iter = rhs_iter->next;
                size++;
            }
            else
            {
                iter = first;
                for ( uint i = 1; i < size; i++ )
                {
                    iter = iter->next;
                    rhs_iter = rhs_iter->next;
                }
            }
            uint diff = rhs.size - size;
            for ( uint i = 0; i < diff; i++ )
            {
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
        }
    }

    /**
     * Delete nodes after start_node, helper method for operator=.
     * @param start_node Position of last node you want to stay.
     */
    void delete_end()
    {
        if ( !is_empty() )
        {
            Node * iter = first;

            for ( uint i = 1; i < size - 1; i++ )
            {
                iter = iter->next;
            }
            last = iter;
            Node * temp = iter->next;
            last->next = nullptr;
            delete temp;

            size--;
        }
    }

    /**
     * Pushes a new element to end of list.
     * @param item
     */
    void push_end( const Object & item )
    {
        if ( is_empty() )
        {
            first = last = new Node{ item };
        }
        else
        {
            Node * iter = first;
            for ( uint i = 0; i < size - 1; i++ )
            {
                iter = iter->next;
            }
            iter->next = new Node{ item };
            last = iter->next;
            last->next = nullptr;
        }
        size++;
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

