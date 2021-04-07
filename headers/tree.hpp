#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

#include "student.hpp"

int max(int a, int b) {
    return (a >= b) ? a : b;
}

/****************************/
/***** BinarySearchTree *****/
/****************************/
class BinarySearchTree {

/*************** PROTECTED SECTION ************************/
protected:

    /**** NESTED NODE CLASS ****/
    struct Node {
        Node* left;
        Node* right;
        Student* value;
        int height;

        Node(Student* value) {
            this->value = value;
            this->height = 1;
            this->left = nullptr;
            this->right = nullptr;
        }

        ~Node() {
            delete value;
        }

        int get_key() {
            return value->get_key();
        }
    };

    /*** ROOT NODE ***/
    Node* root;

    /*** USING BY get_size() METHOD ***/
    int get_size_recursive(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + get_size_recursive(node->left) + get_size_recursive(node->right);
    }

    /**************** PRINTING STUFF ***************************************/
    void print_node(Node* node) {
        std::cout << node->get_key() << " ";
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

    void display_recursive(Node* node, int level, int blanks) {
        if (node == nullptr) {
            for (int j = 0; j < (1 << level) * blanks; j++) {
                std::cout << "  ";
            }
        }
        else if (level == 0) {
            for (int j = 0; j < blanks; j++) {
                std::cout << " ";
            }
            std::cout << node->get_key();
            for (int j = 0; j < blanks; j++) {
                std::cout << " ";
            }
        }
        else {
            display_recursive(node->left, level - 1, blanks);
            display_recursive(node->right, level - 1, blanks);
        }
    }
    /*************** END OF DISPLAY STUFF ****************************************/

    ///USED BY DISPLAY HEIGHT FUNCTION
    int height_recursive(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        else {
            int lh = height_recursive(node->left);
            int rh = height_recursive(node->right);

            if (lh < rh) {
                return rh + 1;
            }
            else {
                return lh + 1;
            }
        }
    }

    /******************** DELETING NODE STUFF *************************/
    Node* RST(Node* bulwa) {
        while (bulwa->left != nullptr) {
            bulwa = bulwa->left;
        }
        return bulwa;
    }

    Node* LST(Node* bulwa) {
        while (bulwa->left != nullptr) {
            bulwa = bulwa->right;
        }
        return bulwa;
    }

    Node* remove_recursive(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }
        else if (node->get_key() > key) {
            node->left = remove_recursive(node->left, key);
        }
        else if (node->get_key() < key) {
            node->right = remove_recursive(node->right, key);
        }
        else {
            //now we are in the parent of the node to be deleted, we will have to use
            //either LST or RST to find a replacement for it
            //1 CHILD
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                //2 CHILDREN
                //2 choices - LST or RST
                Node* temp = RST(node->right);
                node->value = temp->value;
                node->right = remove_recursive(node->right, temp->get_key());
            }
        }
        return node;
    }
    /************* END OF DELETING STUFF *************************************/

    /**************** ADDING NODE RECURSIVE METHOD ****************/
    Node* insert_recursive(Node* new_node, Node* cur) {
        if (cur == nullptr) {
            cur = new_node;
            return cur;
        }
        else if (cur->get_key() > new_node->get_key()) {
            cur->left = insert_recursive(new_node, cur->left);
        }
        else {
            cur->right = insert_recursive(new_node, cur->right);
        }
        return cur;
    }

    /***** RECURSIVE FUNCTION FOR DESTRUCTOR *****/
    void avalanche_of_node_death(Node* node){
        if (node) {
            avalanche_of_node_death(node->left);
            avalanche_of_node_death(node->right);
            delete node;
        }
    }

/******************** PUBLIC SECTION **********************/
public:

    /*** CONSTRUCTOR AND DESTRUCTOR ***/
    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        avalanche_of_node_death(root);
    }
    /**********************************/

    /*** CHECK IF TREE IS EMPTY ***/
    bool is_empty() {
        if (root == nullptr) {
            return true;
        } else {
            return false;
        }
    }

    /***** ADDING NODE METHOD *****/
    void insert(Student* value){
        Node* newnode = new Node(value);
        root = insert_recursive(newnode, root);
    }

    /***** REMOVING NODE METHOD *****/
    void remove(int key) {
        remove_recursive(root, key);
    }

    /***** RETURN HEIGHT OF TREE *****/
    int get_height() {
        return height_recursive(root);
    }

    /***** RETURN NUMBER OF NODES *****/
    int get_size() {
        Node* iterator = root;
        if (this->is_empty()) {
            return 0;
        }
        return 1 + get_size_recursive(root->left) + get_size_recursive(root->right);
    }

    /************ LOOKING FOR NODE WITH SPECIFIC KEY ************/
    Student* find(int key) {
        Node* iterator = root;
        int it_key;
        while (iterator != nullptr) {
            it_key = iterator->get_key();
            if (it_key == key) {
                return iterator->value;
            }
            else if (it_key > key) {
                iterator = iterator->left;
            }
            else {
                iterator = iterator->right;
            }
        }
        return nullptr;
    }

    /**************** PRINTING AND DISPLAYING METHODS ************************/
    void print_preorder() {
        preorder_recursive(root);
    }

    void print_inorder() {
        inorder_recursive(root);
    }

    void print_postorder() {
        postorder_recursive(root);
    }

    void display() {
        int max_height = this->get_height();
        for (int h = 0; h <= max_height; h++) {
            int blanks = 1 << (max_height - h);
            display_recursive(root, h, blanks);
            std::cout << std::endl;
        }
    }
    /************** END OF DISPLAYING METHODS ******************************/
};


/******************************************/
/**** BALANCED BINARY SEARCH TRE (AVL) ****/
/******************************************/
class BalancedBST : public BinarySearchTree {

private:

    /***** START OF ROTATE METHODS *****/
    Node* rotate_right(Node* node) {
        Node* child = node->left;
        Node* temp = child->right;
        child->right = node;
        node->left = temp;
        child->height = max(get_height(child->left), get_height(child->right)) + 1;
        node->height = max(get_height(node->left), get_height(node->right)) + 1;
        return child;
    }

    Node* rotate_left(Node* node) {
        Node* child = node->right;
        Node* temp = child->left;
        child->left = node;
        node->right = temp;
        node->height = max(get_height(node->left), get_height(node->right)) + 1;
        child->height = max(get_height(child->left), get_height(child->right)) + 1;
        return child;
    }
    /***** END OF ROTATE METHODS *****/

    /***** START OF BALANCING METHODS *****/
    int get_height(Node* node) {
        if (node != nullptr)
            return node->height;
        return 0;
    }

    int get_bf(Node* node) {
        if (node == nullptr) {
            return 0;
        } else {
            return get_height(node->right) - get_height(node->left);
        }
    }
    /***** END OF BALANCING METHODS *****/

    /***** ADD RECURSIVE METHOD *****/
    Node* insert_recursive(Node* newnode, Node* cur) {
        if (cur == nullptr) {
            cur = newnode;
            return cur;
        }
        else if (cur->get_key() > newnode->get_key()) {
            cur->left = insert_recursive(newnode, cur->left);
        }
        else {
            cur->right = insert_recursive(newnode, cur->right);
        }
        cur->height = max(get_height(cur->left), get_height(cur->right)) + 1;
        int bf = get_bf(cur);
        int key = newnode->get_key();
        if (bf < -1 && key < cur->left->get_key())
            return rotate_right(cur);
        if (bf > 1 && key > cur->right->get_key())
            return rotate_left(cur);
        if (bf < -1 && key > cur->left->get_key()) {
            cur->left = rotate_left(cur->left);
            return rotate_right(cur);
        }
        if (bf > 1 && key < cur->right->get_key()) {
            cur->right = rotate_right(cur->right);
            return rotate_left(cur);
        }
        return cur;
    }

    /***** REMOVE RECURSIVE METHOD *****/
    Node* remove_recursive(Node* node, int key) {
        if (node == nullptr)
            return node;

        if (node->get_key() > key) {
            node->left = remove_recursive(node->left, key);
        }
        else if (node->get_key() < key) {
            node->right = remove_recursive(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if(node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* temp = this->RST(node->right);
                node->value = temp->value;
                node->right = remove_recursive(node->right, temp->get_key());
            }
        }
        if (node == nullptr)
            return node;
        node->height = 1 + max(get_height(node->left), get_height(node->right));
        int bf = get_bf(node);
        if (bf < -1 && get_bf(node->left) <= 0)
            return rotate_right(node);
        if (bf < -1 && get_bf(node->left) > 0) {
            node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        if (bf > 1 && get_bf(node->right) >= 0)
            return rotate_left(node);
        if (bf > 1 && get_bf(node->right) < 0) {
            node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        return node;
    }


/************************** PUBLIC SECTION *****************************/
public:
    using BinarySearchTree::BinarySearchTree;

    ///REMOVING
    void remove(int key) {
        this->root = remove_recursive(this->root, key);
    }

    ///INSERTION
    void insert(Student* value) {
        Node* new_node = new Node(value);
        this->root = insert_recursive(new_node, this->root);
    }
};

#endif // TREE_HPP_INCLUDED
