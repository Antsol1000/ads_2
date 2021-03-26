#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED
#include <typeinfo>
template <class T>
class BinarySearchTree {

private:

    struct Node {
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

    void print_node(Node* node) {
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

    void postorder_recursive(Node* cur) {
        if(cur != nullptr) {
            postorder_recursive(cur->right);
            print_node(cur);
            postorder_recursive(cur->left);
        }
    }

    ///USED BY DISPLAY FUNCTION
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

    ///USED BY DISPLAY HEIGHT FUNCTION
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

    ///DELETING A NODE
    //smolest in right
    Node* RST(Node* bulwa) {
        while(bulwa->left != nullptr) {
            bulwa= bulwa->left;
        }
        return bulwa;
    }

    //biggest in left
    Node* LST(Node* bulwa) {
        while(bulwa->left != nullptr) {
            bulwa= bulwa->right;
        }
        return bulwa;
    }

    Node* delete_node(Node* node, int ID) {
        if(node== NULL) {
            //node is a leaf
            return node;
        } else if(node->get_key() > ID) {
            node->left = delete_node(node->left, ID);
        } else if(node->get_key() < ID) {
            node->right = delete_node(node->right, ID);
        } else {
            //now we are in the parent of the node to be deleted, we will have to use either LST or RST to find a replacement for it
            //1 CHILD
            if(node->left == nullptr) {
                Node* pom = node->right;
                delete node;
                return pom;
            } else if(node->right == nullptr) {
                Node* pom = node->left;
                delete node;
                return pom;
            } else {
                //2 CHILDREN
                //2 choices - LST or RST
                Node* pom = RST(node->right);
                node->data = pom->data;
                node->right = delete_node(node->right, pom->get_key());
            }
        }
        return node;

    }
/*
    Node* add_recursive(Node* newnode, Node* cur){
        if (cur == nullptr || this->is_empty()==true){
            cur = newnode;
            std::cout<<root->get_key()<<std::endl;
            return cur;
            }

        if(cur->get_key()> newnode->get_key()){
                cur->left = add_recursive(newnode,cur-> left);
        }
        else{
            cur->right = add_recursive(newnode,cur->right);
            }

        return cur;}
*/

public:

    BinarySearchTree() {
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
        } else {
            return false;
        }
    }
    //-potrzebne do AVL, wiêc przy porównywaniu czasu tutaj wsm te¿ powinna byæ podobna
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

        return cur;}

    Node* add(T* data){
    ///INSERTING A NODE RECURSIV

        Node* newnode = new Node(data);
        int key = newnode->get_key();
        //std::cout<<key<<std::endl;
        root =add_recursive(newnode, root);
    }

    ///WILL RETURN HEIGHT
    int get_height() {
        return height_recursive(root);
    }

    ///WILL RETURN SIZE
    int get_size() {
        Node* iterator = root;
        if (this->is_empty()) {
            return 0;
        }
        return 1 + get_size_recursive(root->left) + get_size_recursive(root->right);
    }

    Node* searching(int ID) {
    ///SEARCHING FOR A PARTICULAR INDEX
        Node* temp = root;
        int key;
        while (temp != nullptr) {
            key = temp->get_key();
            if (key == ID) {
                break;
            } else if (key > ID) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        if (temp == nullptr ) {
            std::cout << "No such element found :(" << std::endl;
        } else {
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
        postorder_recursive(root);
        std::cout << std::endl;
    }

    // troche nie moglam sie polapac jak dziala, tez nie dziala jakos swietnie, ale wstepnie POWINNO byc w miare ok D:

    ///BFS WYPIS
    void displayBSF() {
        int max_height = this->get_height();
        std::cout<<"max height = "<< max_height<<std::endl;
        for(int h = 0; h<=max_height; h++) {
            int blanks = (2<<(max_height - h))/2;
            bfs_lvl(root, h, blanks);
            std::cout<<""<<std::endl;

        }
    }

    void deletenode(int ID) {
        delete_node(root, ID);
    }
    ///-sekcja rzeczy niepotrzebnych, ale w razie jak rekursja nie bd dzialac to wolê nie spisywaæ tego od razu na straty
    ///nie jest potrzebne
    void add_non_recur(T* data) {
        ///INSERTING A NODE
        Node* newnode = new Node(data);
        int key = newnode->get_key();

        if (this->is_empty() == true) {
            std::cout<<(int)(this->is_empty())<<std::endl;
            root = newnode;
        } else {
            Node* iterator = root;
            while (iterator != NULL) {
                if (iterator->get_key() > key && iterator->left == nullptr) {
                    iterator->left = newnode;
                    // std::cout<<"Installed to the left"<<std::endl;
                    break;
                } else if (iterator->get_key() > key) {
                    iterator = iterator->left;
                } else if(iterator->get_key() < key && iterator->right == nullptr) {
                    iterator->right = newnode;
                    // std::cout<<"Installed to the right"<<std::endl;
                    break;
                } else {
                    iterator = iterator->right;
                }
            }
        }
    }
};

#endif // TREE_HPP_INCLUDED
