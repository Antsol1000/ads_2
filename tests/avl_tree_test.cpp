#include<iostream>
#include"../headers/student.hpp"
#include"../headers/tree.hpp"

int main(){
    BalancedBST *drzewko = new BalancedBST();
    drzewko->insert(new Student("rybka", "nemo", 9));
    drzewko->insert(new Student("kot", "bonifacy", 2));
    drzewko->insert(new Student("pies", "jamnik", 8));
    drzewko->insert(new Student("kot", "filemon", 6));
    drzewko->insert(new Student("papuga", "gustaw", 1));
    drzewko->insert(new Student("owczarek", "czarek", 3));
    drzewko->insert(new Student("krowa", "wiktoria", 7));
    drzewko->insert(new Student("lama", "nina", 5));
    drzewko->insert(new Student("swinka", "antek", 4));

    std::cout << "znalazlem: ";
    drzewko->find(6)->display();

    drzewko->display();

    std::cout << "\nwypisuje inorder\n";
    drzewko->print_inorder();
    std::cout << "\nwyswietlam\n";
    drzewko->display();
    std::cout << "\n\nusuwam\n";
    drzewko->remove(2);
    std::cout << "\nwyswietlam\n";
    drzewko->display();
    std::cout << "wypisuje preorder\n";
    drzewko->print_preorder();

    return 0;
}
