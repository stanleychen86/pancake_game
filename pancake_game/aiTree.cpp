#include "aiTree.h"

using namespace std;
void ai_tree::recursive_create(node* ptr, int lv_left){ // recursive algorithm for making the tree
    int num_children = get_to_be_num_children(ptr);
    if(num_children == 0){
        leaves.push_back(ptr);
        ptr->set_level(lv_left);
        return;
    }
    if(lv_left <= 0){
        leaves.push_back(ptr);
        return;
    }
    for(int i = 1; i <= num_children; i++){
        node* temp = new node(ptr, i);
        ptr->children.push_back(temp);
        recursive_create(temp, lv_left - 1);
    }
}

int ai_tree::get_to_be_num_children(node* ptr){ // prevents unwanted children
    int num_child = ptr->get_stack()->get_stack_size();
    num_child -- ;
    int top = num_child;
    for(int i = top ; i > 0; i--){
        int max_index = -1;
        int max = -1;
        for(int j = 0; j < i+1; j++){
            if(ptr->get_stack()->at(j) > max){
                max = ptr->get_stack()->at(j);
                max_index = j;
            }
        }
        if(max_index == i){
            num_child--;
        }
        else{
            break;
        }
    }
    if(num_child < 0){
        num_child = 0;
    }
    return num_child;
}


ai_tree::ai_tree(Pancake p_stack, int difficulty){ 
    source_node = new node(p_stack);
    depth = difficulty;
    recursive_create(source_node, difficulty);
}

ai_tree::~ai_tree(){
    dfs_clear(source_node);
    delete source_node;
    source_node = nullptr;
}

void ai_tree::dfs_clear(node* ptr){
    if(ptr == nullptr){
        return;
    }
    for(int i = 0; i < ptr->get_children_size(); i++){
        dfs_clear(ptr->get_child_at(i));
        delete ptr->get_child_at(i);
        ptr->set_child_at(i, nullptr);
    }
}

int ai_tree::get_depth(){
    return depth;
}

node* ai_tree::get_source(){
    return source_node;
}

int ai_tree::get_next_move(){
    int best_index = get_best_leaf();
    if(best_index == -1){
        return -1;
    }
    node* ptr = leaves.at(best_index);
    while((ptr->get_parent() != source_node)&&(ptr->get_parent() != nullptr)){
        ptr = ptr->get_parent();
    }

    return ptr->get_flipped_at();
}

int ai_tree::get_best_leaf(){
    int best_sortedness = 999;
    int best_index = -1;
    int best_level = -1;

    for(int i = 0 ; i < (int)leaves.size(); i++){
        int curr_sortedness = leaves.at(i)->get_score();
        int curr_level = leaves.at(i)->get_level();

        if(curr_sortedness < best_sortedness){
            best_sortedness = curr_sortedness;
            best_index = i;
            best_level = curr_level;
        }
        else if((curr_level != -1)&&(curr_level > best_level)){
            best_sortedness = curr_sortedness;
            best_index = i;
            best_level = curr_level;
        }
    }
    if(best_index == -1){
        return -1;
    }
    return best_index;
}

// tests
bool ai_tree::get_to_be_num_children_test0(){
    vector<int> p_stack1;
    for(int i = 0; i < 9; i++){
        p_stack1.push_back(i+1);
    }
    Pancake p1(p_stack1);
    node node1(p1);
    ai_tree ai1;
    int test1 = ai1.get_to_be_num_children(&node1);
    if(test1 == 0){
        return true;
    }
    return false;
}

bool ai_tree::get_to_be_num_children_test1(){
    vector<int> p_stack1;
    p_stack1.push_back(7);
    p_stack1.push_back(6);
    p_stack1.push_back(5);
    p_stack1.push_back(4);
    p_stack1.push_back(3);
    p_stack1.push_back(2);
    p_stack1.push_back(1);
    p_stack1.push_back(8);
    p_stack1.push_back(9);
    Pancake p1(p_stack1);
    node node1(p1);
    ai_tree ai1;
    int test1 = ai1.get_to_be_num_children(&node1);
    if(test1 == 6){
        return true;
    }
    return false;
}

bool ai_tree::get_to_be_num_children_test2(){
    vector<int> p_stack1;
    p_stack1.push_back(9);
    p_stack1.push_back(8);
    p_stack1.push_back(7);
    p_stack1.push_back(6);
    p_stack1.push_back(5);
    p_stack1.push_back(4);
    p_stack1.push_back(3);
    p_stack1.push_back(2);
    p_stack1.push_back(1);
    Pancake p1(p_stack1);
    node node1(p1);
    ai_tree ai1;
    int test1 = ai1.get_to_be_num_children(&node1);
    if(test1 == 8){
        return true;
    }
    return false;
}

bool ai_tree::get_next_move_test0(){
    vector<int> p_stack1;
    p_stack1.push_back(1);
    p_stack1.push_back(2);
    p_stack1.push_back(3);
    p_stack1.push_back(4);
    p_stack1.push_back(5);
    p_stack1.push_back(6);
    p_stack1.push_back(7);
    p_stack1.push_back(8);
    p_stack1.push_back(9);
    Pancake p1(p_stack1);
    node node1(p1);
    ai_tree ai1(p1, 5);
    int next_move = ai1.get_next_move();
    if(next_move == -1){
        return true;
    }
    cout << next_move << " ";
    return false;
}

bool ai_tree::get_next_move_test1(){
    vector<int> p_stack1;
    p_stack1.push_back(8);
    p_stack1.push_back(7);
    p_stack1.push_back(6);
    p_stack1.push_back(5);
    p_stack1.push_back(4);
    p_stack1.push_back(3);
    p_stack1.push_back(2);
    p_stack1.push_back(1);
    p_stack1.push_back(9);
    Pancake p1(p_stack1);
    node node1(p1);
    ai_tree ai1(p1, 5);
    int next_move = ai1.get_next_move();
    if(next_move == 7){
        return true;
    }
    cout << next_move << " ";
    return false;
}

bool ai_tree::get_next_move_test2(){
    vector<int> p_stack1;
    p_stack1.push_back(2);
    p_stack1.push_back(3);
    p_stack1.push_back(4);
    p_stack1.push_back(5);
    p_stack1.push_back(6);
    p_stack1.push_back(7);
    p_stack1.push_back(8);
    p_stack1.push_back(1);
    p_stack1.push_back(9);
    Pancake p1(p_stack1);
    node node1(p1);
    ai_tree ai1(p1, 5);
    int next_move = ai1.get_next_move();
    if(next_move == 6){
        return true;
    }
    cout << next_move << " ";
    return false;
}

bool ai_tree::get_next_move_test3(){
    vector<int> p_stack1;
    p_stack1.push_back(9);
    p_stack1.push_back(8);
    p_stack1.push_back(7);
    p_stack1.push_back(6);
    p_stack1.push_back(5);
    p_stack1.push_back(4);
    p_stack1.push_back(3);
    p_stack1.push_back(2);
    p_stack1.push_back(1);
    Pancake p1(p_stack1);
    node node1(p1);
    ai_tree ai1(p1, 5);
    int next_move = ai1.get_next_move();
    if(next_move == 8){
        return true;
    }
    cout << next_move << " ";
    return false;
}