#include<fstream>
#include<iostream>
#include<ctime>
#include<string>
#include<algorithm>
#include"../headers/tree.hpp"

const int SIZE_STEP = 2000;
const int MAX_SIZE = 100000;
const int NUM_OF_TESTS = MAX_SIZE / SIZE_STEP;

int main() {
    srand(time(0));

    // open file with results of trials
    std::ofstream wyniki;
    wyniki.open("avl_bst_results.csv");
    wyniki << "test_number;number_of_records;add_time;search_time;remove_time" << std::endl;


    for (int test_number = 1; test_number <= NUM_OF_TESTS; test_number++) {

        // create an ARRAY with records from data file
        int SIZE = SIZE_STEP * test_number;
        std::string *ARRAY = new std::string[SIZE];
        std::ifstream file;
        file.open("..//data.csv");
        for (int i = 0; i < SIZE; i++) {
            file >> ARRAY[i];
        }
        file.close();

        // create data structure
        BalancedBST tree;
        clock_t start_t, end_t;

        // add all elements and measure time
        double add_time;
        start_t = clock();
        for (int i = 0; i < SIZE; i++) {
            tree.insert(new Student(ARRAY[i].substr(8, 12), ARRAY[i].substr(21, 12), std::stoi(ARRAY[i].substr(0, 7))));
        }
        end_t = clock();
        add_time = (double) (end_t - start_t);

        // shuffle the array and measure time of finding elements
        std::random_shuffle(ARRAY, ARRAY + SIZE);
        double search_time;
        start_t = clock();
        for (int i = 0; i < SIZE; i++) {
            tree.find(std::stoi(ARRAY[i].substr(0, 7)));
        }
        end_t = clock();
        search_time = (double) (end_t - start_t);

        // shuffle the array and measure time of removing elements
        std::random_shuffle(ARRAY, ARRAY + SIZE);
        double remove_time;
        start_t = clock();
        for (int i = 0; i < SIZE; i++) {
            tree.remove(std::stoi(ARRAY[i].substr(0, 7)));
        }
        end_t = clock();
        remove_time = (double) (end_t - start_t);

        // delete data structure and ARRAY with records
        delete &tree;
        delete []ARRAY;

        // print results to the file
        wyniki << test_number  << ";" << SIZE << ";" << add_time << ";" << search_time << ";" << remove_time << std::endl;

        std::cout << "test nr" << test_number << " zakonczony\n";
    }

    // close results file
    wyniki.close();

    return 0;
}
