#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

#include<string>

class Student {

private:
    std::string name, surname;
    int id;

public:
    Student(std::string name, std::string surname, int id) {
        this->name = name;
        this->surname = surname;
        this->id = id;
    }

    std::string get_name() {
        return name;
    }

    std::string get_surname() {
        return surname;
    }

    std::string get_value() {
        return get_name() + " " + get_surname();
    }

    int get_key() {
        return id;
    }

    void display() {
        std::cout << name << " " << surname << " " << id << "\n";
    }
};

#endif // STUDENT_HPP_INCLUDED
