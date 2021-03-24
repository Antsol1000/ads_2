#pragma once
#include<string>
#include<iostream>

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
class BST{
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
            return (*data).get_key();
        }
        std::string get_name(){
        std::string bigolstr = (*data).get_name() + " " + (*data).get_surname();
        return bigolstr;}
    };
    Node* root;
public:
    BST(){
        root = nullptr;
    }

    //destructor BST
    /*~BST(){

    }
    */
    /// CHECK IF EMPTY, FOR ANOTHER FUNCTION
    bool is_empty(){
        if(root== nullptr){return true;}
        else{return false;}
    }
    ///INSERTING A NODE
    void add(T* data){
        Node* newnode = new Node(data);
        //insertion_r(newnode, root);
        int key = newnode->get_key();
        if(this->is_empty() == true){root = newnode;}
        else{
            Node* iterator = root;
            while(iterator != NULL){
                if(iterator->get_key() > key && iterator->left == nullptr)
                {   iterator->left = newnode;
                    std::cout<<"Installed to the left"<<std::endl;
                    break;}
                else if(iterator->get_key() > key){
                    iterator = iterator->left;}
                else if(iterator->get_key() < key && iterator->right == nullptr)
                {   iterator->right = newnode;
                    std::cout<<"Installed to the right"<<std::endl;
                    break;}
                else{iterator = iterator->right;}
                }
            }
        }


    ///WILL RETURN HEIGHT
    int height(){

    }

    ///SEARCHING FOR A PARTICULAR INDEX
    Node* searching(int ID){
        Node* temp = root;
        int key;
        while(temp != nullptr){
            key = temp->get_key();
            if(key == ID){break;}
            else if(key > ID){temp = temp->left;}
            else{temp = temp->right;}
        }
        if(temp == nullptr ){
            std::cout<<"No such element found :("<<std::endl;
        }else{
        std::cout<<"Searched element is: "<<temp->get_name()<<std::endl;}
        return temp;
        }


    ///ORDER BY WHICH TO DISPLAY
    void print_node(Node* node){
        std::cout<<node->get_key()<<": ";
    }
    void preorder(Node* cur){
        if(cur != nullptr){
        print_node(cur);
        preorder(cur->left);
        preorder(cur->right);}
        }
    void inorder(Node* cur){
        if(cur != nullptr){
        inorder(cur->left);
        print_node(cur);
        inorder(cur->right);}
        }
    void postorder(Node* cur){
        if(cur != nullptr){
        postorder(cur->right);
        print_node(cur);
        postorder(cur->left);}
        }

    void display(){
        std::cout<<"\n";
        inorder(root);
        std::cout<<"\n";


    }

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


