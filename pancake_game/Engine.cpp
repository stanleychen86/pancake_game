#include "Engine.h"

using namespace std;

Engine::Engine(){
    initials = "";
    user_stack = nullptr;
    ai_stack = nullptr;
    curr_difficulty = 0;
    num_pancakes = 0;
    winner = -1; // 0 - player, 1 - ai , 2 tie
}

Engine::~Engine(){
    delete user_stack;
    delete ai_stack;
}

void Engine::flip_user(int pos){
    user_stack->flip(pos);
}

void Engine::flip_ai(int pos){
    ai_stack->flip(pos);
}

bool Engine::test_game_over(){
    bool all_passed = true;
    vector<int> not_sorted;
    not_sorted.push_back(4);
    not_sorted.push_back(2);
    not_sorted.push_back(3);
    not_sorted.push_back(1);
    vector<int> sorted;
    for(int i = 0; i < 4; i++)
        sorted.push_back(i+1);
    Pancake* sorted_pancake = new Pancake(sorted);
    Pancake* not_sorted_pancake = new Pancake(not_sorted);
    user_stack = not_sorted_pancake;
    ai_stack = not_sorted_pancake;
    if(game_over()) all_passed = false;
    user_stack = sorted_pancake;
    if(!game_over()) all_passed = false;
    ai_stack = sorted_pancake;
    if(!game_over()) all_passed = false;
    user_stack = not_sorted_pancake;
    if(!game_over()) all_passed = false;
    delete sorted_pancake;
    delete not_sorted_pancake;
    return all_passed;
}

bool Engine::game_over(){
    return check_is_over();
}
void Engine::set_order(vector<int> permutation){
    user_stack = new Pancake(permutation);
    ai_stack = new Pancake(permutation);
}

int Engine::get_ai_move(){
    ai_tree* ai1 = new ai_tree(*ai_stack, curr_difficulty);
    int ai_move = ai1->get_next_move();
    delete ai1;
    return ai_move;
}

bool Engine::check_is_over(){
    if(check_user_stack()){
        if(check_ai_stack()){
            winner = 2;
        }
        else{
            winner = 0;
        }
        return true;
    }
    else if(check_ai_stack()){
        winner = 1;
        return true;
    }
    else{
        return false;
    }
}

bool Engine::check_user_stack(){
    return user_stack->is_sorted();
}

bool Engine::check_ai_stack(){
    return ai_stack->is_sorted();
}

int Engine::calculate_score(int num_pancakes) {
    if(winner == 1){
        return num_pancakes;
    }
    else if(winner == 2){
        return num_pancakes*(curr_difficulty+1);
    }
    else if(winner == 0){
        return 2*num_pancakes*(curr_difficulty + 1);
    }
    return -1;
}

void Engine::set_user_order(vector<int> _user_order){
    user_order = _user_order;
}

vector<int> Engine::get_user_order(){
    return user_stack->pStack;
}

vector<int> Engine::get_ai_order(){
    return ai_stack->pStack;
}

int Engine::get_num_pancakes() {
    return num_pancakes;
}

int Engine::get_difficulty() {
    return curr_difficulty;
}

string Engine::get_initials() {
    return initials;
}

vector<tuple<string, int, int>> Engine::get_top_5() {
    return high_scores;
}

void Engine::set_num_pancakes(int pancakes) {
    num_pancakes = pancakes;
}

void Engine::set_difficulty(int d) {
    curr_difficulty = d;
}

void Engine::set_initials(string i) {
    initials = i;
} 

void Engine::set_high_scores(vector<tuple<string, int, int>> v) {
    high_scores = v;
}

int Engine::get_hint(){
    vector<int>* ans = find_solution(user_stack->pStack);
    int next = ans->at(0);
    delete ans;
    return next;;
}

int Engine::get_min_moves() {
    vector<int>* ans = find_solution(user_stack->pStack);
    int min_moves = ans->size();
    delete ans;
    return min_moves;
}

string Engine::get_winner() {
    if (winner == 0)
        return "You beat the computer!!!";
    if (winner == 1)
        return "You lost...";
    return "It was a tie!";
}
