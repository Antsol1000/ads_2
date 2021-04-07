#include<iostream>
#include"../headers/student.hpp"
#include"../headers/list.hpp"

int main() {
    SortedList *lista = new SortedList();
    lista->insert(new Student("rybka", "nemo", 9));
    lista->insert(new Student("kot", "bonifacy", 2));
    lista->insert(new Student("pies", "jamnik", 8));
    lista->insert(new Student("kot", "filemon", 6));
    lista->insert(new Student("papuga", "gustaw", 1));
    lista->insert(new Student("owczarek", "czarek", 3));
    lista->insert(new Student("krowa", "wiktoria", 7));
    lista->insert(new Student("lama", "nina", 5));
    lista->insert(new Student("swinka", "antek", 4));

    lista->print_keys();
    lista->print_students();
    std::cout << std::endl;

    lista->remove(6);

    lista->print_keys();
    lista->print_students();
    std::cout << std::endl;

    delete lista;

    return 0;
}
