#include<iostream>
#include"try_BST.h"

int main(){
    BST<Student> bonzaj;
    bonzaj.add( new Student(" ", " ",4));
    bonzaj.add( new Student(" ", " ",2));
    bonzaj.add( new Student(" ", " ",1));
    bonzaj.add( new Student(" ", " ",3));
    bonzaj.add( new Student(" ", " ",7));
    bonzaj.add( new Student(" ", " ",5));
    bonzaj.add( new Student(" ", " ",9));
    bonzaj.searching(7);
    bonzaj.display();
    bonzaj.deletenode(7);
    //in order jako sprawdzenie czy dzia³a wsm
    bonzaj.display();


return 0;}
