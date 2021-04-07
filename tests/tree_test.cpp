#include<iostream>
#include"../headers/student.hpp"
#include"../headers/tree.hpp"

int main(){
    BinarySearchTree *bonzaj = new BinarySearchTree();
    bonzaj->insert(new Student("rybka", "nemo", 9));
    bonzaj->insert(new Student("kot", "bonifacy", 2));
    bonzaj->insert(new Student("pies", "jamnik", 8));
    bonzaj->insert(new Student("kot", "filemon", 6));
    bonzaj->insert(new Student("papuga", "gustaw", 1));
    bonzaj->insert(new Student("owczarek", "czarek", 3));
    bonzaj->insert(new Student("krowa", "wiktoria", 7));
    bonzaj->insert(new Student("lama", "nina", 5));
    bonzaj->insert(new Student("swinka", "antek", 4));

    std::cout << "znalaz³em: ";
    bonzaj->find(6)->display();

    std::cout << "\nwypisuje inorder\n";
    bonzaj->print_inorder();
    std::cout << "\nwyswietlam\n";
    bonzaj->display();
    std::cout << "\n\nusuwam\n";
    bonzaj->remove(6);
    std::cout << "wypisuje preorder\n";
    bonzaj->print_preorder();

    return 0;
}
