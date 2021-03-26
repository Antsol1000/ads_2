#include<iostream>
#include"data_types.hpp"

int main(){
    BinarySearchTree<Student> bonzaj;
    bonzaj.add( new Student(" ", " ",4));
    bonzaj.add( new Student(" ", " ",2));
    bonzaj.add( new Student(" ", " ",1));
    bonzaj.add( new Student(" ", " ",3));
    bonzaj.add( new Student("kot", "bonifacy",7));
    bonzaj.add( new Student(" ", " ",5));
    bonzaj.add( new Student(" ", " ",12));
    bonzaj.add( new Student("pies", "jamnik",8));
    bonzaj.add( new Student(" ", " ",6));
    bonzaj.add( new Student(" ", " ",9));
    bonzaj.searching(7);
    bonzaj.print_inorder();
    bonzaj.displayBSF();
    bonzaj.deletenode(4);
    //in order jako sprawdzenie czy dzia³a wsm
    bonzaj.print_inorder();
    bonzaj.displayBSF();
    bonzaj.deletenode(7);
    bonzaj.displayBSF();
    bonzaj.print_postorder();

return 0;}
