#ifndef AVL_HPP_INCLUDED
#define AVL_HPP_INCLUDED
#include"student.hpp"


template <class T>
class AVL{
private:
        struct Node{
        Node* left;
        Node* right;
        T* data;
        //int bf;

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


    ///ROTATION FUNCTIONS

    Node* rotaterr(Node* node) {
        Node* child;
        child = node->left;
        Node* grandchild;
        grandchild = child->left;
        node->left = child->right;
        child->right = node;
        return child;}

    Node* rotatell(Node* node) {
        Node* child;
        child = node->right;
        Node* grandchild;
        grandchild = child->right;
        node->right = child->left;
        child->left = node;

        return child;}

    Node* rotaterl(Node* node) {
        Node* child;
        child = node->left;
        Node* grandchild;
        grandchild = child->right;
        Node* temp1;
        Node* temp2;
        temp1 = grandchild->right;
        temp2 = grandchild->left;
        child->right = temp2;
        node->left = temp1;
        grandchild->right = node;
        grandchild->left = child;
        return grandchild;}

    Node* rotatelr(Node* node) {
        Node* child;
        child = node->right;
        Node* grandchild;
        grandchild = child->left;
        Node* temp1;
        Node* temp2;
        temp2 = grandchild->right;
        temp1 = grandchild->left;
        child->left = temp2;
        node->right = temp1;
        grandchild->right = child;
        grandchild->left = node;
        return grandchild;}

    void bfs_lvl(Node* node, int lvl, int blanks) {
        if(node == nullptr) {
            for(int j = 0; j <(1<<lvl)*blanks; j++) {
                std::cout<<"  ";
            }
        } else if(lvl == 0) {
            for(int j = 0; j <blanks; j++) {
                std::cout<<" ";
            }
            std::cout<<node->get_key();
            for(int j = 0; j <blanks; j++) {
                std::cout<<" ";
            }
        } else {
            bfs_lvl(node->left, lvl-1, blanks);
            bfs_lvl(node->right, lvl-1, blanks);
        }
    }

    int height_recursive(Node* node) {
        if(node == nullptr) {
            return 0;
        } else {
            int lh = height_recursive(node->left);
            int rh = height_recursive(node->right);

            if(lh<rh) {
                return rh + 1;
            } else {
                return lh +1;
            }
        }
    }
    //gdy lewa odnoga d³u¿sza to na plusie - prawa - prawa-wtedy na minusie
    int get_bf(Node* root){
        if(root == nullptr){return 0;}
        else{return this->height_recursive(root->left) - this->height_recursive(root->right);}
    }

    Node* balancing_act(Node* root){
         int bf = this->get_bf(root);
         int bfl = this->get_bf(root->left);
         int bfr = this->get_bf(root->right);
         if(bf>1 && bfl>=1){root = rotaterr(root);}
         else if(bf<-1 && bfr<=0){root = rotatell(root);}
         else if(bf<-1 && bfr>=0){root = rotatelr(root);}
         else if(bf>1 && bfl<=-1){root = rotaterl(root);}
         return root;}

    Node* add_recursive(Node* newnode, Node* cur) {
            if (cur == nullptr){
            cur = newnode;
            return cur;
            }
            else if(cur->get_key()> newnode->get_key())
            {
            cur->left = add_recursive(newnode,cur-> left);
            }
            else{
            cur->right = add_recursive(newnode,cur->right);
            }
        return balancing_act(cur);}


    Node* RST(Node* bulwa) {
        while(bulwa->left != nullptr) {
            bulwa= bulwa->left;
        }
        return bulwa;
    }

    Node* LST(Node* bulwa) {
        while(bulwa->left != nullptr) {
            bulwa= bulwa->right;
        }
        return bulwa;
    }

    Node* delete_node(Node* node, int ID) {
        if(node== NULL) {
            return node;
        } else if(node->get_key() > ID) {
            node->left = delete_node(node->left, ID);
            if(node->left){node->left = balancing_act(node->left);}
        } else if(node->get_key() < ID) {
            node->right = delete_node(node->right, ID);
            if(node->right){node->right =balancing_act(node->right);}
        } else {
            if(node->left == nullptr) {
                Node* pom = node->right;
                delete node;
                return pom;
            } else if(node->right == nullptr) {
                Node* pom = node->left;
                delete node;
                return pom;
            } else {
                Node* pom = RST(node->right);
                node->data = pom->data;
                node->right = delete_node(node->right, pom->get_key());
                if(node->right){node->right =balancing_act(node->right);}
            }
        }
        return node;}
public:
    AVL(){
        root = nullptr;
    }
    ///DELETION
    void deletenode(int ID) {
        root = delete_node(root, ID);
        std::cout<<get_bf(root)<<std::endl;
        root = balancing_act(root);
        std::cout<<get_bf(root)<<std::endl;

    }
    ///BFS WYPIS
    void displayBSF() {
        int max_height = this->height_recursive(root);
        std::cout<<"max height = "<< max_height<<std::endl;
        for(int h = 0; h<=max_height; h++) {
            int blanks = (2<<(max_height - h))/2;
            bfs_lvl(root, h, blanks);
            std::cout<<""<<std::endl;

        }
    }
    ///INSERTION
    Node* add(T* data){
        Node* newnode = new Node(data);
        root =add_recursive(newnode, root);
    }



};
#endif // AVL_HPP_INCLUDED
