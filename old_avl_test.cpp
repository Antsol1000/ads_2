#include<iostream>
#include"student.hpp"
#include"tree.hpp"
#include"old_avl.hpp"

int main(){
    AVL<Student> sosna;
    sosna.add( new Student(" ", " ",4));
    sosna.add( new Student(" ", " ",2));
    sosna.add( new Student(" ", " ",1));
    sosna.add( new Student(" ", " ",3));
    sosna.add( new Student("kot", "bonifacy",7));
    sosna.add( new Student("kot", "bonifacy",8));
    sosna.add( new Student("kot", "bonifacy",9));
    sosna.add( new Student("kot", "bonifacy",10));
    sosna.add( new Student("kot", "bonifacy",81));
    sosna.add( new Student("kot", "bonifacy",55));
    sosna.add( new Student("kot", "bonifacy",56));
    /*sosna.add( new Student(" ", " ",5));
    sosna.add( new Student(" ", " ",12));
    sosna.add( new Student("pies", "jamnik",8));
    sosna.add( new Student(" ", " ",6));
    sosna.add( new Student(" ", " ",9));
    sosna.searching(7);*/
    sosna.displayBSF();
    sosna.deletenode(56);
    sosna.displayBSF();
    printf("bobo");
    sosna.deletenode(1);
    sosna.displayBSF();
    sosna.add( new Student("kot", "bonifacy",46));
    sosna.add( new Student("kot", "bonifacy",45));
    sosna.displayBSF();
    sosna.deletenode(3);
    sosna.displayBSF();



return 0;}
