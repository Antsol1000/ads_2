#include<iostream>
#include"data_types.hpp"

int main(){
    BinarySearchTree<Student> bonzaj;
    bonzaj.add( new Student(" ", " ",4));
    bonzaj.add( new Student(" ", " ",2));
    bonzaj.add( new Student(" ", " ",1));
    bonzaj.add( new Student(" ", " ",3));
    bonzaj.add( new Student(" ", " ",7));
    bonzaj.add( new Student(" ", " ",5));
    bonzaj.add( new Student(" ", " ",9));
    bonzaj.searching(7);
    bonzaj.print_inorder();
    bonzaj.display();
    bonzaj.deletenode(7);
    //in order jako sprawdzenie czy dzia³a wsm
    bonzaj.print_inorder();
    bonzaj.display();


return 0;}
