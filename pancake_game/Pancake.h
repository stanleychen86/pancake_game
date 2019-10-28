#ifndef PANCAKE_H
#define PANCAKE_H

#include <vector>
#include <iostream>

using namespace std;

struct Pancake {
    vector<int> pStack;

    Pancake() {} // strictly for testing
    Pancake(vector<int> stack);
    Pancake(Pancake* parent, int childMove);
    int at(int index);
    void flip(int flipPos);
    void test_print();
    int getSortedness();
    bool is_sorted();
    int get_stack_size();

    // tests
    bool pancake_flip_test0();
    bool pancake_flip_test1();
    bool pancake_sortedness_test0();
    bool pancake_sortedness_test1();
};

#endif