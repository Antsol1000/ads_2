#include<iostream>
#include<algorithm>
#include<ctime>
#include"../headers/tree.hpp"

int main(){
    srand(time(0));
    const int size = 20;
    BalancedBST *drzewko = new BalancedBST();
    int t[size] =  {15,17,6,20,8,11,14,19,13,2,12,9,18,10,55,7,16,4,1,3};

    for (int i = 0; i < size; i++) {
        drzewko->display();
        drzewko->insert(new Student("", "", t[i]));
    }

    drzewko->insert(new Student("", "", 5));
    drzewko->display();
    std::random_shuffle(t, t+size);

    for (int i = 0; i < size; i++) {
        drzewko->remove(t[i]);
    }
    delete &drzewko;

    return 0;
}
