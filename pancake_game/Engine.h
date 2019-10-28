#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include <vector>
#include <tuple>
#include <ncurses.h>
#include <string>
#include "aiTree.h"
#include "find_solution.h"

using namespace std;

struct Engine{
    private:
    vector<tuple<string, int, int>> high_scores; // local storage of top 5 scores
    vector<int> user_order;
    string initials; // current player's initials
    Pancake* user_stack;
    Pancake* ai_stack;
    int curr_difficulty; // current game's difficulty level
    int num_pancakes; // current game's pancake stack size
    int winner; // 0 - player, 1 - ai , 2 tie

    public:
    Engine();
    ~Engine();
    
    // return true if check_is_over() returns true
    bool game_over();
    bool test_game_over();
    // set the order of both pancake stacks - call at beginning of gameplay
    void set_order(vector<int> permutation);
    // use the minimax tree to determine the AI's next move
    int get_ai_move();
    // set winner and check if the game is over - one or both stacks are sorted
    bool check_is_over();
    // check if the user's pancake stack is sorted
    bool check_user_stack();
    // check if the AI's pancake stack is sorted
    bool check_ai_stack();
    // calculate the score when the game is over
    int calculate_score(int pancakes);
    // perform a flip operation on the user's pancake stack
    void flip_user(int pos);
    // perform a flip operation on the AI's pancake stack
    void flip_ai(int pos);
    // set the vector representing the user's pancake stack
    void set_user_order(vector<int> _user_order);
    // get a vector representing the user's pancake stack
    vector<int> get_user_order();
    // get a vector represetnting the AI's pancake stack
    vector<int> get_ai_order();
    // return the size of a pancake stack for the current game
    int get_num_pancakes();
    // return the selected difficulty of the current game
    int get_difficulty();
    // return the player's initials
    string get_initials();
    // return the current top 5 scores
    vector<tuple<string, int, int>> get_top_5();
    // set the number of pancakes in a stack for the current game
    void set_num_pancakes(int pancakes);
    // set the difficulty of the current game
    void set_difficulty(int d);
    // set the player's initials
    void set_initials(string i);
    // set the high_scores vector (use after adding a)
    void set_high_scores(vector<tuple<string, int, int>> v);
    // give the index of the best next flip based on the current stack
    int get_hint();
    // get the minimum number of moves to solve given the current stack
    int get_min_moves();
    // return a message displaying who won
    string get_winner();
};

#endif
