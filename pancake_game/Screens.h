#ifndef SCREENS_H
#define SCREENS_H

#include <fstream>
#include "Engine.h"

using namespace std;

class Screens {
    public:
        // create Game object
        Screens();
        // init ncurses and show splashscreen (called at init)
        void setup();
        // destroy the game window and return to std in/out (called at termination)
        void teardown();

        //===========================================================================================
        // Parts 1 & extra credit 1 (splash screen + demo gameplay & instructions)
        // display the splash screen and the blinking prompt
        void splashscreen();
        //display the initial state of the game demo
        void print_state1();
        //display the blinking prompt of the game demo
        void print_state2();
        //display the final state of the game demo
        void print_empty_state();
        //display the animation of the game demo on the splash screen
        void animation();
        // prompt the user to press enter to start the game
        void blink_prompt();
        // screen displaying instructions for how to play the game
        void instructions();
        // verify splash screen displays correctly
        bool test_splashscreen();

        //===========================================================================================
        // Parts 2 (setting pancake stack size and game difficulty)
        // prompt user to configure size and difficulty
        void create_menu();
        
        //===========================================================================================
        //Part 3 (random or assigning stack order)
        //sets order of pancake stack in engine object
        void set_pancake_order();
        //Stack order selection tests.
        bool test_random_stack_order();
        bool test_user_stack_duplicate_check();
        bool test_user_stack_range_check();

        //===========================================================================================
        // Parts 4 & 8 (FILE I/O & TOP SCORES)
        // prompt user to enter their initials and then display top 5 scores
        void enter_initials();
        // screen for actual gameplay
        void play_game();
        // calculate game score, display results, and update highscores.txt
        void post_game();
        // prompt user to play another game or end the program
        bool keep_playing();
        // verify reading top scores from a file
        bool test_file_read();
        // verify writing high scores to a file
        bool test_file_write();
        // verify adding 2 scores to a list of top scores
        // one score should be added to position 3,
        // and the other score should not be added
        bool test_add_score();

        //===========================================================================================
        //Part 6 tests
        bool test_arrow_move();
        // TEST FUNCTIONS
        void test_player_selection();
        void test_player_move();
        void test_blink_stack();
        bool determine_box_order_test();
        bool center_output_test();

    private:
        Engine game; // the game engine controlling gameplay
        bool done; // signals if the user is ready to terminate the game

        //====================================================================================
        // Part 2 Helper functions
        // sanitize input for selecting pancake stack size
        int check_pancakes();
        // sanitize input for selecting game difficulty
        int check_diff(int num_pancakes);
        // print the order of the vector to the terminal std out
        void print_user_order(vector<int> user_order, int num_pancakes);
        // print selected difficulty to the terminal std out
        void print_user_diff(int diff);

        //=====================================================================================
        //Part 3 Helper functions
        //asks user for random or assigned pancake stack order
        vector<int> get_user_order(int num_pancakes);
        //returns a random order of pancakes given number of pancakes
        vector<int> random_stack_order(int num_pancakes);
        //takes user input for order of pancake stack
        vector<int> user_stack_order(int num_pancakes);
        //checks that user's input is not a duplicate pancake
        bool user_stack_duplicate_check(vector<int> order, int user_choice, int y, int x);
        //checks that user's input is within valid pancake sizes
        bool user_stack_range_check(int user_choice, int num_pancakes, int y, int x);
        //prints prompt for user assignment
        int user_stack_print_prompt(int num_pancakes, int y, int x);

        //==========================================================================================
        //  Parts 4 & 8 Helper functions
        // display the top 5 scores to the screen
        void display_top_5();
        // read top 5 scores from file and store them locally in a vector
        void read_top_5();
        // write high_scores into the file highscores.txt
        void write_top_5();
        // return index where score should be added into vector high_scores
        // return -1 if the score should not be added
        int in_top_5(int score);
        // add score to vector high_scores if in_top_5 returns true
        void add_score(tuple<string, int, int> score);
        // create the highscore.txt and fill with '--- 0 0'
        void init_high_score_file();
        // on game completion ask the user if they would like to play again
        // consequently changes the variable done
        void play_again();
        // save the contents of highscores.txt to a vector and return it
        vector<tuple<string, int, int>> save_file_contents();
        // restore highscores.txt with scores from a vector
        void restore_file_contents(vector<tuple<string, int, int>> v);
        // create and return a test vector with sample data, used for testing
        vector<tuple<string, int, int>> make_test_vector();

        //====================================================================================
        //Part 6 & 7 (controls for gameplay & calling minimax tree functions in class aiTree)
        //handles individual moves of user cursor
        int arrow_move(int y, int x, int cursor_pos, int num_pancakes, int move);
        //handles user's moving of arrow and selection of a pancake to flip
        int player_selection(int y, int x);
        //handles user's move input, flipping of stack in engine, and reprinting of user's stack
        void player_move();
        //handles ai output for move selection, flipping of ai stack in engine, and reprinting of ai stack
        void ai_move();
        //blinks the portion of the pancake stack for a given move
        void blink_stack(int y, int x, vector<int> sub_stack);
        //prints first arrow on screen
        void arrow_init(int y, int x, int cursor_pos);
        //clears a portion of the screen for a new pancake stack printing
        void erase_pancakes(int top_side, int left_side, int num_cols, int num_pancakes);
        
        //=================================================================================
        //Part 5 (draw centered pancakes)
        //Wrappers to create vectors that have strings representing pancakes
        vector<string> box_1_wrapper();
        vector<string> box_2_wrapper();
        vector<string> box_3_wrapper();
        vector<string> box_4_wrapper();
        vector<string> box_5_wrapper();
        vector<string> box_6_wrapper();
        vector<string> box_7_wrapper();
        vector<string> box_8_wrapper();
        vector<string> box_9_wrapper();
        // pad a string str with spaces to center it within num_cols
        void center_output(string str, int num_cols);
        // draw pancakes given a stack and a top-left coordinate point
        void draw_pancakes(vector<int> stack, int top_side, int left_side);
        
        vector<vector<string> > determine_box_order(vector<int> stack);
        // print 'PLAYER' on top of player's pancake stack
        void label_user_stack(int top_side, int left_side);
        // print 'AI' on top of AI's pancake stack
        void label_ai_stack(int top_side, int left_side);
        //Part 5 Test Helpers
        vector<vector<string> > box_order_test_comparison_vector();
        vector<int> box_order_test_vector();
                
};

#endif
