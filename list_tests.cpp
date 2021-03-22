#include<iostream>
#include"data_types.hpp"

int main() {
    OrderedList<Student> lista;
    lista.add(new Student("a", "b", 1));
    lista.add(new Student("antek", "sysol", 2));
    std::cout << "\n";
    lista.display();
    std::cout << lista.size() << "\n\n";
    Student* s = lista.find(1);
    s->display();
    lista.remove(1);
    std::cout << "\n";
    lista.display();
    std::cout << lista.size() << "\n";

   // Student* ptr = lista.find(1);
   // std::cout << (*ptr).get_name();
}
