#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

/****************************/
/***** BinarySearchTree *****/
/****************************/
template <class T>
class BinarySearchTree {

/*************** PROTECTED SECTION ************************/
protected:

    /**** NESTED NODE CLASS ****/
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
    /*************** END OF DISPLAY STUFF ****************************************/

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

    /******************** DELETING NODE STUFF *************************/
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
        if (node == NULL) {
            return node;
        } else if (node->get_key() > ID) {
            node->left = delete_node(node->left, ID);
        } else if (node->get_key() < ID) {
            node->right = delete_node(node->right, ID);
        } else {
            //now we are in the parent of the node to be deleted, we will have to use
            //either LST or RST to find a replacement for it
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
    /************* END OF DELETING STUFF *************************************/

    /**************** ADDING NODE RECURSIVE METHOD ****************/
    Node* add_recursive(Node* newnode, Node* cur) {
        if (cur == nullptr) {
            cur = newnode;
            return cur;
        }
        else if (cur->get_key() > newnode->get_key()) {
            cur->left = add_recursive(newnode, cur-> left);
        }
        else {
            cur->right = add_recursive(newnode, cur->right);
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
    void add(T* value){
        Node* newnode = new Node(value);
        root =add_recursive(newnode, root);
    }

    /***** REMOVING NODE METHOD *****/
    void remove(int ID) {
        delete_node(root, ID);
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

    /************ LOOKING FOR NODE WITH SPECIFIC INDEX ************/
    Node* searching(int ID) {
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

    /**************** PRINTING AND DISPLAYING METHODS ************************/
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
    /************** END OF DISPLAYING METHODS ******************************/
};


/****************************************************/
/*** class template of the AVL Binary Search Tree ***/
/****************************************************/

template <class T>
class BalancedBST : public BinarySearchTree<T> {

private:

    struct Node : public BinarySearchTree<T>::Node {
        using BinarySearchTree<T>::Node::Node;
        int factor;
    };
    Node *root;

    /***** START OF ROTATE METHODS *****/
    auto rotate_rr(auto node) {
        auto child = node->left;
        auto grandchild = child->left;
        node->left = child->right;
        child->right = node;
        return child;
    }

    auto rotate_ll(auto node) {
        auto child = node->right;
        auto grandchild = child->right;
        node->right = child->left;
        child->left = node;
        return child;
    }

    auto rotate_rl(auto node) {
        auto child = node->left;
        auto grandchild = child->right;
        auto temp1 = grandchild->right;
        auto temp2 = grandchild->left;
        child->right = temp2;
        node->left = temp1;
        grandchild->right = node;
        grandchild->left = child;
        return grandchild;
    }

    auto rotate_lr(auto node) {
        auto child = node->right;
        auto grandchild = child->left;
        auto temp2 = grandchild->right;
        auto temp1 = grandchild->left;
        child->left = temp2;
        node->right = temp1;
        grandchild->right = child;
        grandchild->left = node;
        return grandchild;
    }
    /***** END OF ROTATE METHODS *****/

    /***** START OF BALANCING METHODS *****/
    int get_bf(auto root) {
        if (root == nullptr) {
            return 0;
        } else {
            return this->height_recursive(root->left) - this->height_recursive(root->right);
        }
    }

    auto balancing_act(auto root) {
        int bf = this->get_bf(root);
        int bfl = this->get_bf(root->left);
        int bfr = this->get_bf(root->right);
        if (bf > 1 && bfl >= 1) {
            root = rotate_rr(root);
        } else if (bf < -1 && bfr <= 0) {
            root = rotate_ll(root);
        } else if (bf < -1 && bfr >= 0) {
            root = rotate_lr(root);
        } else if (bf > 1 && bfl <= -1) {
            root = rotate_rl(root);
        }
        return root;
    }
    /***** END OF BALANCING METHODS *****/

    /***** ADD RECURSIVE METHOD *****/
    auto add_recursive(auto newnode, auto cur) {
        if (cur == nullptr) {
            cur = newnode;
            return cur;
        } else if(cur->get_key()> newnode->get_key()) {
            cur->left = add_recursive(newnode, cur->left);
        } else {
            cur->right = add_recursive(newnode, cur->right);
        }
        return balancing_act(cur);
    }

    /***** REMOVE RECURSIVE METHOD *****/
    auto remove_recursive(auto node, int ID) {
        if (node == nullptr) {
            return node;
        } else if(node->get_key() > ID) {
            node->left = remove_recursive(node->left, ID);
            if(node->left) {
                node->left = balancing_act(node->left);
            }
        } else if(node->get_key() < ID) {
            node->right = remove_recursive(node->right, ID);
            if(node->right) {
                node->right = balancing_act(node->right);
            }
        } else {
            if (node->left == nullptr) {
                auto pom = node->right;
                delete node;
                return pom;
            } else if(node->right == nullptr) {
                auto pom = node->left;
                delete node;
                return pom;
            } else {
                auto pom = this->RST(node->right);
                node->data = pom->data;
                node->right = remove_recursive(node->right, pom->get_key());
                if(node->right) {
                    node->right = balancing_act(node->right);
                }
            }
        }
        return node;
    }


/************************** PUBLIC SECTION *****************************/
public:
    using BinarySearchTree<T>::BinarySearchTree;

    ///DELETION
    void remove(int ID) {
        BinarySearchTree<T>::root = remove_recursive(BinarySearchTree<T>::root, ID);
        std::cout<<get_bf(BinarySearchTree<T>::root)<<std::endl;
        BinarySearchTree<T>::root = balancing_act(BinarySearchTree<T>::root);
        std::cout<<get_bf(BinarySearchTree<T>::root)<<std::endl;

    }

    ///INSERTION
    auto add(T* data) {
        typename BinarySearchTree<T>::Node* newnode;
        newnode = new (typename BinarySearchTree<T>::Node)(data);
        BinarySearchTree<T>::root =add_recursive(newnode, BinarySearchTree<T>::root);
    }
};

#endif // TREE_HPP_INCLUDED
