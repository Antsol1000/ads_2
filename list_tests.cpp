#include<iostream>
#include"data_types.hpp"

int main() {
    OrderedList<Student> lista;
    lista.add(new Student("a", "b", 1));
    lista.add(new Student("antek", "sysol", 2));
    lista.add(new Student("kot", "bonifacy", 3));
    lista.add(new Student("pies", "jamnik", 4));

    lista.display();
    lista.print();
    std::cout << std::endl;

    lista.remove(3);

    lista.display();
    lista.print();
    std::cout << std::endl;
}
