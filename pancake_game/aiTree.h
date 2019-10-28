#ifndef AI_TREE_H
#define AI_TREE_H

#include "node.h"

using namespace std;

struct ai_tree{
    private:
    node* source_node = nullptr;
    int depth;
    vector<node*> leaves;
    vector<node*> id_path;
    public:
    void recursive_create(node* ptr, int lv_left);
    int get_to_be_num_children(node* ptr);

    ai_tree(){}; // strictly for testing
    ai_tree(Pancake p_stack, int difficulty);
    ~ai_tree();
    void dfs_clear(node* ptr);

    int get_depth();
    node* get_source();
    int get_next_move();
    int get_best_leaf();

    // tests
    bool get_to_be_num_children_test0();
    bool get_to_be_num_children_test1();
    bool get_to_be_num_children_test2();
    bool get_next_move_test0();
    bool get_next_move_test1();
    bool get_next_move_test2();
    bool get_next_move_test3();
};

#endif
