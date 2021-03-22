#ifndef DATA_TYPES_HPP_INCLUDED
#define DATA_TYPES_HPP_INCLUDED

#include<string>

class Student {

private:
    std::string name, surname;
    int id;

public:
    Student(std::string name, std::string surname, int id) {
        this->name = name;
        this->surname = surname;
        this->id = id;
    }

    std::string get_name() {
        return name;
    }

    std::string get_surname() {
        return surname;
    }

    int get_key() {
        return id;
    }

    void display() {
        std::cout << name << " " << surname << " " << id << "\n";
    }
};

template <class T>
class OrderedList{
private:
    struct Node{
        Node* next;
        T* data;

        Node(T* data) {
            this->data = data;
            next = nullptr;
        }

        ~Node() {
            delete data;
        }

        int get_key() {
            return (*data).get_key();
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

    void add(T* item) {
        Node* temp = new Node(item);
        temp->next = head;
        head = temp;
    }

    void display() {
        Node* ptr = head;
        while (ptr != nullptr) {
            (ptr->data)->display();
            ptr = ptr->next;
        }
    }

    T* find(int key) {
        Node* ptr = head;
        while (ptr != nullptr) {
            if (ptr->get_key() == key) {
                return ptr->data;
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
            throw "Brak takiego elementu w liœcie lub pusta lista";
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



#endif // DATA_TYPES_HPP_INCLUDED
