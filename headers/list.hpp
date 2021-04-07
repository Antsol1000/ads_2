#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

#include<string>
#include"student.hpp"

/****************************/
/**** ORDERED LIST CLASS ****/
/****************************/
class OrderedList {

protected:

    /*************************************/
    /**** NODE STRUCTURE WITH STUDENT ****/
    /*************************************/
    struct Node {
        /// POINTER TO NEXT NODE
        Node* next;
        Student* value;

        Node(Student* value) {
            this->value = value;
            next = nullptr;
        }

        ~Node() {
            // this->value->display();
            delete value;
        }

        int get_key() {
            return (*value).get_key();
        }
    };

    /*** HEAD OF THE LIST ***/
    Node* head;

    /***** PUSHES NEW NODE AT THE FRONT OF THE LIST *****/
    void push_front(Student* value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
    }

public:

    /**** CONSTRUCTOR AND DESTRUCTOR *****/
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
    /**** END OF THE CONSTRUCTOR AND DESTRUCTOR ****/

    /***** INSERT AND REMOVING METHODS *****/
    void insert(Student* value) {
        push_front(value);
    }

    void remove(int key) {
        if (head->get_key() == key) {
            Node* temp = head->next;
            delete head;
            head = temp;
            return;
        }
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
    /***** END OF IN/OUT METHODS *****/

    /***** DISPLAY LIST OF THE STUDENTS *****/
    void print_students() {
        Node* ptr = head;
        while (ptr != nullptr) {
            (ptr->value)->display();
            ptr = ptr->next;
        }
    }

    /***** DISPLAY LIST OF KEYS *****/
    void print_keys() {
        std::string result = "";
        Node* iterator = head;
        while (iterator != nullptr) {
            result = result + std::to_string(iterator->get_key()) + " ";
            iterator = iterator->next;
        }
        std::cout << result << std::endl;
    }

    /**** FIND NODE WITH STUDENT WITH GIVEN INDEX ****/
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

    /**** CALCULATE THE LENGHT OF THE LIST ****/
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
    /*** return left neighbor of the inserting node ***/
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
