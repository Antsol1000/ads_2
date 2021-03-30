#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

#include<string>
#include"student.hpp"

/****************************/
/**** ORDERED LIST CLASS ****/
/****************************/
class OrderedList {

protected:

    struct Node {
        Node* next;
        Student* value;

        Node(Student* value) {
            this->value = value;
            next = nullptr;
        }

        ~Node() {
            delete value;
        }

        int get_key() {
            return (*value).get_key();
        }
    };

    Node* head;

    void push_front(Student* value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
    }

public:

    OrderedList() {
        head = nullptr;
    }

    ~OrderedList() {
        Node* ptr = head;
        while (ptr != nullptr) {
            Node* temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }

    void display() {
        Node* ptr = head;
        while (ptr != nullptr) {
            (ptr->value)->display();
            ptr = ptr->next;
        }
    }

    void print() {
        std::string result = "";
        Node* iterator = head;
        while (iterator != nullptr) {
            result = result + std::to_string(iterator->get_key()) + " ";
            iterator = iterator->next;
        }
        std::cout << result << std::endl;
    }

    Student* find(int key) {
        Node* ptr = head;
        while (ptr != nullptr) {
            if (ptr->get_key() == key) {
                return ptr->value;
            }
            ptr = ptr->next;
        }
        return nullptr;
    }

    void remove(int key) {
        Node* ptr = head;
        Node* prev = nullptr;
        while (ptr != nullptr && ptr->get_key() != key) {
            prev = ptr;
            ptr = ptr->next;
        }
        if (ptr == nullptr) {
            throw "Brak takiego elementu w liscie lub pusta lista";
        }
        prev->next = ptr->next;
        delete ptr;
    };

    void insert(Student* value) {
        push_front(value);
    }

    int size() {
        Node *ptr = head;
        int counter = 0;
        while (ptr != nullptr) {
            counter++;
            ptr = ptr->next;
        }
        return counter;
    }
};


/**********************************/
/******** SORTED LIST CLASS *******/
/**********************************/
class SortedList : public OrderedList {

private:

    /*** FIND POSITION FOR ELEMENT ***/
    Node* find_position(int key) {
        if (head == nullptr) {
            return nullptr;
        }
        if (head->get_key() > key)
            return nullptr;
        auto iterator = head;
        while (iterator->next != nullptr && iterator->next->get_key() < key) {
            iterator = iterator->next;
        }
        return iterator;
    }

public:
    using OrderedList::OrderedList;

    /*** ADDING ELEMENT AND KEEP LIST SORTED ***/
    void insert(Student* value) {
        Node *position = find_position(value->get_key());
        if (position == nullptr) {
            this->push_front(value);
        }
        else {
            Node *new_node = new Node(value);
            Node *temp = position->next;
            position->next = new_node;
            new_node->next = temp;
        }
    }
};

#endif // LIST_HPP_INCLUDED
