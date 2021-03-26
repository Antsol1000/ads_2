#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

#include<string>

template <class T>
class OrderedList {

private:

    struct Node {
        Node* next;
        T* value;

        Node(T* value) {
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

    void add(T* value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
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

    T* find(int key) {
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

#endif // LIST_HPP_INCLUDED
