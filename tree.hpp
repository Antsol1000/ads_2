#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

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
        int balance_factor;

        Node(Student* value) {
            this->value = value;
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
    Node* rotate_rr(Node* node) {
        Node* child = node->left;
        Node* grandchild = child->left;
        node->left = child->right;
        child->right = node;
        return child;
    }

    Node* rotate_ll(Node* node) {
        Node* child = node->right;
        Node* grandchild = child->right;
        node->right = child->left;
        child->left = node;
        return child;
    }

    Node* rotate_rl(Node* node) {
        Node* child = node->left;
        Node* grandchild = child->right;
        Node* temp1 = grandchild->right;
        Node* temp2 = grandchild->left;
        child->right = temp2;
        node->left = temp1;
        grandchild->right = node;
        grandchild->left = child;
        return grandchild;
    }

    Node* rotate_lr(Node* node) {
        Node* child = node->right;
        Node* grandchild = child->left;
        Node* temp2 = grandchild->right;
        Node* temp1 = grandchild->left;
        child->left = temp2;
        node->right = temp1;
        grandchild->right = child;
        grandchild->left = node;
        return grandchild;
    }
    /***** END OF ROTATE METHODS *****/

    /***** START OF BALANCING METHODS *****/
    int get_bf(Node* bulwa) {
        if (bulwa == nullptr) {
            return 0;
        } else {
            return height_recursive(bulwa->left) - height_recursive(bulwa->right);
        }
    }

    Node* balancing_act(Node* bulwa) {
        int bf = this->get_bf(bulwa);
        int bfl = this->get_bf(bulwa->left);
        int bfr = this->get_bf(bulwa->right);
        if (bf > 1 && bfl >= 1) {
            bulwa = rotate_rr(bulwa);
        }
        else if (bf < -1 && bfr <= 0) {
            bulwa = rotate_ll(bulwa);
        }
        else if (bf < -1 && bfr >= 0) {
            bulwa = rotate_lr(bulwa);
        }
        else if (bf > 1 && bfl <= -1) {
            bulwa = rotate_rl(bulwa);
        }
        return bulwa;
    }
    /***** END OF BALANCING METHODS *****/

    /***** ADD RECURSIVE METHOD *****/
    Node* add_recursive(Node* newnode, Node* cur) {
        if (cur == nullptr) {
            cur = newnode;
            return cur;
        }
        else if (cur->get_key() > newnode->get_key()) {
            cur->left = add_recursive(newnode, cur->left);
        }
        else {
            cur->right = add_recursive(newnode, cur->right);
        }
        return balancing_act(cur);
    }

    /***** REMOVE RECURSIVE METHOD *****/
    Node* remove_recursive(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }
        else if (node->get_key() > key) {
            node->left = remove_recursive(node->left, key);
            if (node->left) {
                node->left = balancing_act(node->left);
            }
        }
        else if (node->get_key() < key) {
            node->right = remove_recursive(node->right, key);
            if (node->right) {
                node->right = balancing_act(node->right);
            }
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if(node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* temp = this->RST(node->right);
                node->value = temp->value;
                node->right = remove_recursive(node->right, temp->get_key());
                if(node->right) {
                    node->right = balancing_act(node->right);
                }
            }
        }
        return node;
    }


/************************** PUBLIC SECTION *****************************/
public:
    using BinarySearchTree::BinarySearchTree;

    ///REMOVING
    void remove(int key) {
        this->root = remove_recursive(this->root, key);
        this->root = balancing_act(root);
    }

    ///INSERTION
    auto insert(Student* value) {
        Node* new_node = new Node(value);
        this->root = add_recursive(new_node, this->root);
    }
};

#endif // TREE_HPP_INCLUDED
