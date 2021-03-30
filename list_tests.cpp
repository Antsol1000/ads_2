#include<iostream>
#include"student.hpp"
#include"list.hpp"

int main() {
    OrderedList lista;
    lista.insert(new Student("a", "b", 1));
    lista.insert(new Student("antek", "sysol", 2));
    lista.insert(new Student("kot", "bonifacy", 3));
    lista.insert(new Student("pies", "jamnik", 4));

    lista.display();
    lista.print();
    std::cout << std::endl;

    lista.remove(3);

    lista.display();
    lista.print();
    std::cout << std::endl;
    delete &lista;

    SortedList lista2;
    lista2.insert(new Student("a", "b", 1));
    lista2.insert(new Student("antek", "sysol", 2));
    lista2.insert(new Student("kot", "bonifacy", 3));
    lista2.insert(new Student("pies", "jamnik", 4));


    lista2.display();
    lista2.print();
    std::cout << std::endl;

    lista2.remove(3);

    lista2.display();
    lista2.print();
    std::cout << "\n\nkoniec" << std::endl;
    delete &lista2;
}
