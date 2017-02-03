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
 * @version 1/31/2017
 */
template<typename Object>
class List {
private:
    /**
     * A class to store data and provide a link to the next node in the list
     */
    class Node {
    public:
        /**
         * The constructor
         * @param data the data to be stored in this node
         */
        explicit Node(const Object &data)
                : data{data}, next{nullptr} {}

        Object data;
        Node *next;
    };

public:
    /**
     * The constructor for an empty list
     */
    List()
            : size{0}, first{nullptr}, last{nullptr} {}

    /**
     * the copy constructor
     */
    List(const List &rhs) :
            size{rhs.size}, first{nullptr}, last{nullptr} {
        first = new Node{*rhs.first};
        Node *loc_temp = first;
        Node *rhs_temp = rhs.first;
        last = first;

        while (rhs_temp->next != nullptr)
        {
            loc_temp->next = new Node{*rhs_temp->next};
            loc_temp = loc_temp->next;
            rhs_temp =rhs_temp -> next;
            last = loc_temp->next;
        }

    }


    /**
     * the operator= method
     */
    List &operator=(const List &rhs) {
        size = rhs.size;
        first = rhs.first;
        last = rhs.last;
        return *this;
    }

    /**
     * The destructor that gets rid of everything that's in the list and
     * resets it to empty. If the list is already empty, do nothing.
     */
    ~List() {
        if (size != 0) {
            Node *current = first;
            Node *temp;

            while (current != nullptr) {
                temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    /**
     * Put a new element onto the beginning of the list
     * @param item the data the new element will contain
     */
    void push_front(const Object &item) {
        Node *new_node = new Node(item);
        if (first == nullptr) {
            first = new_node;
            last = new_node;
        } else {
            Node *temp = first;
            first = new_node;
            new_node->next = temp;
        }
        size++;

    }

    /**
     * Remove the element that's at the front of the list. Causes an
     * assertion error if the list is empty.
     */
    void pop_front() {
        assert(!is_empty());
        Node *temp = first;

        if (first == last) {
            first = last = nullptr;
        } else {
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
    const Object &front() const {
        assert(!is_empty());
        return first->data;
    }

    /**
     * Accessor to return the data of the element at the tail of the list.
     * Causes an assertion error if the list is empty.
     * @return the data in the last element
     */
    const Object &tail() const {
        return last->data;
    }

    /**
     * Accessor to determine whether the list is empty
     * @return a boolean corresponding to the emptiness of the list
     */
    bool is_empty() const {
        return size == 0;
    }

    /**
     * Generate a string representation of the list
     * Requires operator<< to be defined for the list's object type
     * @return string representation of the list
     */

    string to_string() const {
        if (size == 0) {
            return "";
        }
        stringstream buffer;
        for (auto current = first; current != nullptr; current = current->next) {
            buffer << current->data << ' ';
        }
        return move(buffer.str());
    }

private:
    uint size;
    Node *first;
    Node *last;
};

#endif
