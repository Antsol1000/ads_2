#ifndef DATA_TYPES_HPP_INCLUDED
#define DATA_TYPES_HPP_INCLUDED

#include<string>
#include<cmath>

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

    std::string get_value() {
        return get_name() + " " + get_surname();
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

template <class T>
class BinarySearchTree{

private:

    struct Node{
        Node* left;
        Node* right;
        T* data;

        Node(T* data) {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
        }

        ~Node() {
            delete data;
        }

        int get_key() {
            return data->get_key();
        }

        std::string get_value() {
            return data->get_value();
        }
    };

    Node* root;

    int get_size_recursive(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + get_size_recursive(node->left) + get_size_recursive(node->right);
    }

    void print_node(Node* node){
        std::cout << node->get_key() << ": ";
    }

    void preorder_recursive(Node* cur) {
        if (cur != nullptr) {
            print_node(cur);
            preorder_recursive(cur->left);
            preorder_recursive(cur->right);
        }
    }

    void inorder_recursive(Node* cur) {
        if(cur != nullptr) {
            inorder_recursive(cur->left);
            print_node(cur);
            inorder_recursive(cur->right);
        }
    }

    void postorder_recursive(Node* cur){
        if(cur != nullptr) {
            postorder_recursive(cur->right);
            print_node(cur);
            postorder_recursive(cur->left);
        }
    }

    void display_recursive(Node* node, int level, int tabs, std::string graph[]) {

        for (int i = 0; i < tabs; i++)
            graph[level] = graph[level] + '\t';

        graph[level] = graph[level] + std::to_string(node->get_key());

        for (int i = 0; i < tabs; i++)
            graph[level] = graph[level] + '\t';

        if (node->left != nullptr)
            display_recursive(node->left, level + 1, tabs / 2, graph);
        if (node->right != nullptr)
            display_recursive(node->right, level + 1, tabs / 2, graph);
    }

public:

    BinarySearchTree(){
        root = nullptr;
    }

    // no akurat destruktor to by sie przydal :-(
    // ale kto to wie jak go zrobic xD
    //destructor BST
    /*~BinarySearchTree(){

    }
    */

    bool is_empty() {
    /// CHECK IF EMPTY
        if (root == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

    void add(T* data){
    ///INSERTING A NODE
        Node* newnode = new Node(data);
        int key = newnode->get_key();

        if (this->is_empty() == true) {
            root = newnode;
        }
        else {
            Node* iterator = root;
            while (iterator != NULL) {
                if (iterator->get_key() > key && iterator->left == nullptr) {
                    iterator->left = newnode;
                    // std::cout<<"Installed to the left"<<std::endl;
                    break;
                }
                else if (iterator->get_key() > key) {
                    iterator = iterator->left;
                    }
                else if(iterator->get_key() < key && iterator->right == nullptr) {
                    iterator->right = newnode;
                    // std::cout<<"Installed to the right"<<std::endl;
                    break;
                }
                else {
                    iterator = iterator->right;
                }
            }
        }
    }


    ///WILL RETURN HEIGHT
    int get_height();

    ///WILL RETURN SIZE
    int get_size() {
        Node* iterator = root;
        if (this->is_empty()) {
            return 0;
        }
        return 1 + get_size_recursive(root->left) + get_size_recursive(root->right);
    }

    Node* searching(int ID){
    ///SEARCHING FOR A PARTICULAR INDEX
        Node* temp = root;
        int key;
        while (temp != nullptr) {
            key = temp->get_key();
            if (key == ID) {
                break;
            }
            else if (key > ID) {
                temp = temp->left;
                }
            else {
                temp = temp->right;
            }
        }
        if (temp == nullptr ) {
            std::cout << "No such element found :(" << std::endl;
        }
        else {
            std::cout << "Searched element is: " << temp->get_value() << std::endl;
        }
        return temp;
    }

    void print_preorder() {
        std::cout << std::endl;
        preorder_recursive(root);
        std::cout << std::endl;
    }

    void print_inorder() {
        std::cout << std::endl;
        inorder_recursive(root);
        std::cout << std::endl;
    }

    void print_postorder() {
        std::cout << std::endl;
        postorder(root);
        std::cout << std::endl;
    }

    // to ma wypisac ladnie w strukturze drzewka ale nie wiem czy dziala :((
    void display() {
        int size = this->get_size();
        std::string graph[size + 1];
        int level = 0, tabs = pow(2, ceil(log2(size)));

        display_recursive(root, level, tabs, graph);

        for (std::string line : graph)
            std::cout << line << std::endl;
    }

    // te trzy pierwsze funkcje chyba mogą być prywante a tylko ostatnia publiczna :)

    ///DELETING A NODE
    //smolest in right
    Node* RST(Node* bulwa){
    while(bulwa->left != nullptr){
        bulwa= bulwa->left;}
    return bulwa;}

    //biggest in left
    Node* LST(Node* bulwa){
    while(bulwa->left != nullptr){
        bulwa= bulwa->right;}
    return bulwa;}

    Node* delete_node(Node* node, int ID){
        if(node== NULL){
            //node is a leaf
            return node;
        }
        else if(node->get_key() > ID){
            node->left = delete_node(node->left, ID);
        }
        else if(node->get_key() < ID){
            node->right = delete_node(node->right, ID);
        }
        else{
            //now we are in the parent of the node to be deleted, we will have to use either LST or RST to find a replacement for it
            //1 CHILD
            if(node->left == nullptr){
                Node* pom = node->right;
                delete node;
                return pom;
            }
            else if(node->right == nullptr){
                Node* pom = node->left;
                delete node;
                return pom;
            }
            else{
                //2 CHILDREN
                //2 choices - LST or RST
                Node* pom = RST(node->right);
                node->data = pom->data;
                node->right = delete_node(node->right, pom->get_key());
            }
        }
        return node;

    }
    void deletenode(int ID){
        delete_node(root, ID);
    }

};



#endif // DATA_TYPES_HPP_INCLUDED
