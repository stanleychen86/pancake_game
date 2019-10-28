#ifndef NODE_H
#define NODE_H
#include "Pancake.h"

using namespace std;

struct node{
    public:
    Pancake p_stack;
    int sortedness_score;
    int flipped_at;
    node* parent;
    vector<node*> children;
    int level = -1;

    node() {} // strictly for testing
    
    node(Pancake p_stack): p_stack(p_stack), flipped_at(-1), parent(nullptr){
        sortedness_score = p_stack.getSortedness();
    }
    node(node* p, int flip_ind);

    node* get_parent();
    int get_score();
    node* get_child_at(int i);
    void set_child_at(int i, node* s){
        children.at(i) = s;
    }
    Pancake* get_stack();
    int get_flipped_at();
    void set_level(int d);
    int get_level();
    int get_children_size(){return children.size();}

    // tests
    bool node_tester();
};

#endif
