#include "Pancake.h"

Pancake::Pancake(vector<int> stack): pStack(stack){} // index 0 - top


Pancake::Pancake(Pancake* parent, int childMove){
    for(int i = 0; i < (int)parent->pStack.size(); i++){
        pStack.push_back(parent->pStack.at(i));
    }
    flip(childMove);
}

int Pancake::at(int index){
    return pStack.at(index);
}

void Pancake::flip(int flipPos){ //flips the pancake at position flipPos
    if(flipPos >= (int)pStack.size()){
        cout << "Invalid flip position" << endl;
        return;
    }
    int index = 0;
    while(flipPos > index){
        int temp = pStack.at(index);
        pStack.at(index) = pStack.at(flipPos);
        pStack.at(flipPos) = temp;
        index ++;
        flipPos --;
    }
}

void Pancake::test_print(){ // not the real pancake print function
    cout << "Stack: ";
    for(int i = 0; i < (int)pStack.size(); i++){
        cout << pStack.at(i) << ", ";
    }
    cout << endl;
}

int Pancake::getSortedness(){ //get the number of reversals
    int reversals = 0;
    int comparison = -1; // 0: < , 1: > 
    for(int i = 1; i < (int)pStack.size(); i++){
        int j = i -1;
        int tempComp = -1;
        if(pStack.at(j) > pStack.at(i)){
            tempComp = 1;
        }
        else{
            tempComp = 0;
        }
        if(comparison == -1){
            comparison = tempComp;
        }
        else{
            if(comparison != tempComp){
                reversals ++;
            }
            comparison = tempComp;
        }
    }
    return reversals;
}

bool Pancake::is_sorted(){
    for(int i = 0; i < (int)pStack.size(); i ++){
        if(pStack.at(i) != (i+1)){
            return false;
        }
    }
    return true;
}

int Pancake::get_stack_size(){
    return pStack.size();
}

// tests
bool Pancake::pancake_flip_test0(){
    vector<int> p_stack;
    for(int i = 0; i < 9; i++){
        p_stack.push_back(i);
    }
    Pancake p(p_stack);
    p.flip(5);
    vector<int> compare_stack;
    compare_stack.push_back(5);
    compare_stack.push_back(4);
    compare_stack.push_back(3);
    compare_stack.push_back(2);
    compare_stack.push_back(1);
    compare_stack.push_back(0);
    compare_stack.push_back(6);
    compare_stack.push_back(7);
    compare_stack.push_back(8);
    for(int i = 0; i < 9; i++){
        if(p.at(i) != compare_stack.at(i)){
            //cout << "pancake_flip_test0 failed: " << p.at(i) << " != " << compare_stack.at(i) << ", at index: " << i << endl;
            return false;
        }
    }
    return true;
}

bool Pancake::pancake_flip_test1(){//test on flipping one pancake
    vector<int> p_stack;
    for(int i = 0; i < 9; i++){
        p_stack.push_back(i);
    }
    vector<int> compare_stack;
    for(int i = 0; i < 9; i++){
        compare_stack.push_back(i);
    }
    Pancake p(p_stack);
    p.flip(0);
    for(int i = 0; i < 9; i++){
        if(p.at(i) != compare_stack.at(i)){
            //cout << "pancake_flip_test1 failed: " << p.at(i) << " != " << compare_stack.at(i) << ", at index: " << i << endl;
            return false;
        }
    }
    return true;
}

bool Pancake::pancake_sortedness_test0(){
    vector<int> p_stack;
    p_stack.push_back(1);
    p_stack.push_back(2);
    p_stack.push_back(4);
    p_stack.push_back(3);
    p_stack.push_back(5);
    p_stack.push_back(6);
    p_stack.push_back(7);
    p_stack.push_back(8);
    p_stack.push_back(9);
    Pancake p(p_stack);
    int s = p.getSortedness();
    if(s == 2){
        return true;
    }
    return false;
}

bool Pancake::pancake_sortedness_test1(){
    vector<int> p_stack;
    p_stack.push_back(1);
    p_stack.push_back(2);
    p_stack.push_back(3);
    p_stack.push_back(4);
    p_stack.push_back(5);
    p_stack.push_back(6);
    p_stack.push_back(7);
    p_stack.push_back(8);
    p_stack.push_back(9);
    Pancake p(p_stack);
    int s = p.getSortedness();
    if(s == 0){
        return true;
    }
    return false;
}