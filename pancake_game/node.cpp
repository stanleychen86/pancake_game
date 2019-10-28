#include "node.h"

using namespace std;

node::node(node* p, int flip_ind): p_stack(*(p->get_stack())){
    parent = p;
    p_stack.flip(flip_ind);
    sortedness_score = p_stack.getSortedness();
    flipped_at = flip_ind;
}

node* node::get_parent(){
    return parent;
}

int node::get_score(){
    return sortedness_score;
}

node* node::get_child_at(int i){
    if((i+1) > (int)children.size()){
        return nullptr;
    }
    return children.at(i);
}

Pancake* node::get_stack(){
    return &p_stack;
}

int node::get_flipped_at(){return flipped_at;}

void node::set_level(int d){
    level = d;
}

int node::get_level(){
    return level;
}

// tests
bool node::node_tester(){
    vector<int> p_stack;
    for(int i = 8; i >=0; i --){ //8,7,6,5,4,3,2,1,0
        p_stack.push_back(i);
    }
    Pancake p(p_stack);
    node n(p);
    if(n.sortedness_score != 0)
        return false;
    node n1(&n, 5);
    if(n1.get_score() != 1)
        return false;
    if(n1.get_flipped_at() != 5)
        return false;

    return true;
}