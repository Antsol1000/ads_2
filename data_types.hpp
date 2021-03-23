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
        Node* temp = new Node(value);
        temp->next = head;
        head = temp;
    }

    void display() {
        Node* ptr = head;
        while (ptr != nullptr) {
            (ptr->value)->display();
            ptr = ptr->next;
        }
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

template<class T>
class BinarySearchTree{

private:

    struct Node{
        Node* left_child, right_child, parent;
        T* value;

        Node(T* value) {
            this->value = value;
            this->left_child = nullptr;
            this->right_child = nullptr;
            this->parent = nullptr;
        }

        ~Node() {
            delete value;
        }

        int get_key() {
            return (*value).get_key();
        }
    };

    Node* root;

public:

    BinarySearchTree();

    ~BinarySearchTree();

    void add(T* item);

    void remove(int key);

    void display();

    void find(int key);

    int size();
};



#endif // DATA_TYPES_HPP_INCLUDED
