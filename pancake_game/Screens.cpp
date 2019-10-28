#include "Screens.h"
#include <algorithm>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <csignal>
#include <unistd.h>
#include <string.h>
using namespace std;

Screens::Screens() {
    game = Engine();
    done = false;
}

void Screens::setup() {
    read_top_5();
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    splashscreen();
    blink_prompt();
    instructions();
}

void Screens::teardown() {
    endwin();
}

// part 1========================================================================
void Screens::splashscreen() {
    initscr();
    noecho();
    start_color();    
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    mvaddstr(16, 20, "                         |             ");
    mvaddstr(17, 20, " ___  ___  ___  ___  ___ |     ___  ___");
    mvaddstr(18, 20, "|   )|   )|   )|    |   )|___)|___)|___ ");
    mvaddstr(19, 20, "|__/ |__/||  / |__  |__/|| \\  ||__   __/ ");
    mvaddstr(20, 20, "|");
    attroff(COLOR_PAIR(1));
    mvaddstr(23, 33, "Team name: 13");
    mvaddstr(24, 33, "Team members: ");
    mvaddstr(25, 33, "JingChun Qu");
    mvaddstr(26, 33, "Andrew Chin");
    mvaddstr(27, 33, "Alexander Staggs");
    mvaddstr(28, 33, "Zicheng Chen");
    mvaddstr(29, 33, "David Tieding");
}

void Screens::print_state1() {
    mvprintw(6, 34, " +-----+  ");
    mvprintw(7, 34, " |  2  |  ");
    mvprintw(8, 34, " +-----+  ");
    mvprintw(9, 34, "  +---+   ");
    mvprintw(10, 34, "  | 1 |   ");
    mvprintw(11, 34, "  +---+   ");
    mvprintw(12, 34, "+-------+");
    mvprintw(13, 34, "|   3   |");
    mvprintw(14, 34, "+-------+");
}

void Screens::print_state2() {
    mvprintw(6, 34, "  +---+   ");
    mvprintw(7, 34, "  | 1 |   ");
    mvprintw(8, 34, "  +---+   ");
    mvprintw(9, 34, " +-----+  ");
    mvprintw(10, 34, " |  2  |  ");
    mvprintw(11, 34, " +-----+  ");
    mvprintw(12, 34, "+-------+");
    mvprintw(13, 34, "|   3   |");
    mvprintw(14, 34, "+-------+");
}

void Screens::print_empty_state() {
    for (int i = 6; i < 12; ++i)
        mvprintw(i, 34, "                             ");
    mvprintw(12, 34, "+-------+");
    mvprintw(13, 34, "|   3   |");
    mvprintw(14, 34, "+-------+");
}
    
void Screens::animation() {
    print_state1();
    refresh();
    napms(1000);
    for (int i = 0; i < 3; ++i) {
        print_state1();
        refresh();
        napms(500);
        print_empty_state();
        refresh();
        napms(500);
        
    }
    print_state2();
    refresh();
    napms(5000);
}


void Screens::blink_prompt() {
    nodelay(stdscr, TRUE);
    attron(A_BLINK);
    mvwprintw(stdscr, 35, 26, "Press any key to continue!!!");
    attroff(A_BLINK);
    refresh();

    while (1) {
        animation();
        int ch = getch();
        if (ch == ERR || ch != 10) {
            continue;
        }
        else {
            break;
        }
        for (int c = 6; c<12 ; c++) {
            move(c, 20);
            clrtoeol();
            refresh();
             
        }
        refresh();
    }
    nodelay(stdscr, FALSE);
}

void Screens::instructions() {
    erase();
    printw("===============================================================================\n");
    printw("                                  HOW TO PLAY\n");
    printw("===============================================================================\n");
    printw("   Pancakes is simple and fun to play. Your goal is to stack your pancakes in\n");
    printw(" increasing order, with the smallest pancake on top. Additionally, there is an\n");
    printw(" added challenge: you need to stack your pancakes before the AI stacks its own!\n\n");
    printw(" The rules are simple: you may only flip over n pancakes from the top in order\n");
    printw("                              to sort your stack.\n\n\n");
    printw("                      CONTROLS (during stacking gameplay):\n");
    printw("   --------------------------------------------------------------------------\n");
    printw("    -     W : move your cursor up\n");
    printw("    -     S : move your cursor down\n");
    printw("    - ENTER : flip the top n pancakes, starting from your cursor and upwards\n");
    printw("    -     H : display a hint\n\n");
    printw("                                 ______________\n");
    printw("                                |              |\n");
    printw("                                | Good luck!!! |\n");
    printw("                                |______________|\n\n\n\n");
    printw("                           Press any key to continue.");
    getch();
}

bool Screens::test_splashscreen() {
    splashscreen();
    char test1 =mvinch(10, 29);
    char test2 = mvinch(14, 30);
    endwin();
    if(test1 == 'T' && test2 == 'Z') {
        return true;
    }
    else {
        return false;
    }
}
// end of part 1====================================================================

// part 2===========================================================================
void Screens::create_menu() {
    erase();
    int difficulty = 0, num_pancakes = 0;
    move(0, 0);
    clrtoeol();
    printw("Specify the Number of Pancakes You Want: ");
    num_pancakes = check_pancakes();
    game.set_num_pancakes(num_pancakes);
    printw("\n\nStacks will contain %d pancakes.\n\nPress any key to continue.", num_pancakes);
    getch();
    erase();
    move(0, 0);
    clrtoeol();
    printw("Specify the Difficulty of the Game [1-%d]: ", num_pancakes);
    difficulty = check_diff(num_pancakes); 
    game.set_difficulty(difficulty); 
    printw("\n\nGame will be played on difficulty %d.\n\nPress any key to continue.", difficulty); 
    getch(); 
    erase();
}

int Screens::check_pancakes() {
    char c = getch();
    string n = string(1, c);
    while (n.at(0) < 50 || n.at(0) > 57) {
        printw("\nNumber of pancakes must be an integer greater than 1.\n");
        printw("Specify the Number of Pancakes You Want: ");
        c = getch();
        n = string(1, c);
    }
    return stoi(n); 
}

int Screens::check_diff(int num_pancakes) {
    char c = getch();
    string diff = string(1, c);
    int n_ascii = num_pancakes + 48;
    while (diff.at(0) < 49 || diff.at(0) > n_ascii) {
        printw("\nDifficulty must be in the interval.\n");
        printw("Specify the Difficulty of the Game [1-%d]: ", num_pancakes);
        c = getch();
        diff = string(1, c);
    }
    return stoi(diff); 
}

void Screens::print_user_order(vector<int> user_order, int num_pancakes) {
    cout << "Vector order: " << endl;
    for (int i = 0; i < num_pancakes; i++) {
        cout << user_order.at(i) << " ";
    }
    cout << endl;
}

void Screens::print_user_diff(int diff) {
    cout << "User difficulty is: " << diff << endl;
}
// end of part 2==================================================================

/*================================================================================
 * Alex's Part, Parts 3 & 6
 To test, at each screen, try invalid inputs and see if proper error messages appear.
 If it runs successfully with invalid inputs, then try a run without any invalid inputs.
 Invalid inputs should include numbers not expected and random keystrokes (like space or arrows).
 */

void Screens::set_pancake_order() {
    game.set_order(get_user_order(game.get_num_pancakes()));
}

//can't simulate user inputs
vector<int> Screens::get_user_order(int num_pancakes) {
    erase();
    mvprintw(0, 0, "Random or Assign stack order? (Press 1 for random, 2 for assign)");
    refresh();
    int rand_selection;
    while (1) {  //returns break this loop rand_selection = getch();//1 for random, 2 for assign
        rand_selection = getch();  //1 for random, 2 for assign
        if (rand_selection == 49) {  //1 in ascii is 49
            mvprintw(1, 0, "Random order selected.\n");
            printw("Press any key to continue.");
            getch();
            return random_stack_order(num_pancakes);
        }
        else if (rand_selection == 50) {
            return user_stack_order(num_pancakes);
        }
        else {
            move(1, 0);
            mvprintw(1, 0, "Press 1 or 2 for your selection.");
        }
    }
}

//can't simulate inputs, no test
vector<int> Screens::user_stack_order(int num_pancakes) {  //get order helper for user choice
    vector<int> order;
    int x = 0, y = 1;
    y = user_stack_print_prompt(num_pancakes, y, x);  //prints prompt and returns next line
    int user_choice;
    for (int i = 0; i < num_pancakes; i++) {
        move(y, x);
        printw("Input size of Pancake %d. (Press a number 1-%d)", i, num_pancakes);
        user_choice = getch() - 48;  //converts from char to int
        if (user_stack_range_check(user_choice, num_pancakes, y, x) && 
                user_stack_duplicate_check(order, user_choice, y, x)) {  //check inputs
            move(++y, x);
            clrtoeol();
            printw("Size of pancake %d is: %d", i, user_choice);
            order.push_back(user_choice);
            y++;
        }
        else
            i--;  //retry i iter
    }
    y++;
    move(y, x);
    return order;
}

int Screens::user_stack_print_prompt(int num_pancakes, int y, int x) {  //returns next line to move to
    //test would be trivial.
    move(y, x);
    clrtoeol();
    printw("Press numbers 1-%d to assign pancake sizes:", num_pancakes);
    y++;
    move(y, x);
    printw("[Top pancake is Pancake 0.]");
    y++;
    return y;
}

bool Screens::test_user_stack_range_check() {
    bool all_passed = true;
    initscr();
    for (int i = 1; i <= 9; i++) {
        if (!user_stack_range_check(i, 9, 0, 0))
            all_passed = false;
    }
    bool bad_check = user_stack_range_check(5, 4, 0, 0);  //should be false;
    string expected_string = "Press a number 1-4.";
    char actual[100];
    mvinnstr(1, 0, actual, expected_string.length());
    string actual_string = actual;
    if (expected_string.compare(actual_string) != 0 || bad_check)
        all_passed = false;
    endwin();
    return all_passed;
}

bool Screens::user_stack_range_check(int user_choice, int num_pancakes, int y, int x) {
    //checks to see if user input for pancake size is within valid range
    if (!(user_choice > 0 && user_choice <= num_pancakes)) {
        move(y+1, x);
        clrtoeol();
        printw("Press a number 1-%d.", num_pancakes);
        return false;
    }
    return true;
}

bool Screens::test_user_stack_duplicate_check() {
    initscr();
    bool all_passed = true;
    vector<int> order;
    order.push_back(2);
    order.push_back(1);
    bool dup_check = user_stack_duplicate_check(order, 2, 0, 0);  //should be false
    string expected_string = "A pancake of size 2 is already in the stack. Try again.";
    char actual[100];
    mvinnstr(1, 0, actual, expected_string.length());
    string actual_string = actual;
    if (expected_string.compare(actual_string) != 0 || dup_check)
        all_passed = false;
    dup_check = user_stack_duplicate_check(order, 3, 0, 0);  //should be true
    if (!dup_check)
        all_passed = false;
    endwin();
    return all_passed;  //result
}

bool Screens::user_stack_duplicate_check(vector<int> order, int user_choice, int y, int x) {
   //checks to see if user tries to make two pancakes the same size
   //true if no duplicates, false if duplicates
   bool duplicate = false;
   for (int j = 0; j < (int)order.size(); j++) {  //check for duplicate input
       if (order.at(j) == user_choice) {
           duplicate = true;
       }
   }
   if (duplicate) {  //print error message
       move(y+1, x); 
       clrtoeol();
       printw("A pancake of size %d is already in the stack. Try again.", user_choice);
   }
   return !duplicate;
}

bool Screens::test_random_stack_order() {
   bool all_passed = true;
   for (int i = 2; i <=9; i++) {  //each stack size
        bool found;
        bool valid = true;
        vector<int> random_stack = random_stack_order(i);
        for (int j = 0; j < (int)random_stack.size(); j++) {  //each pancake size
            found = false;
            for (int k = 0; k < (int)random_stack.size(); k++) {  //each pancake
                if (j+1 == random_stack.at(k))
                    found = true;
            }
            if (found == false)
                valid = false;
        }
        cout << "Random Stack test " << i;
        if (valid)
            cout << " passed." << endl;
        else {
            cout << " failed." << endl; all_passed = false;
        }
   }
   return all_passed;
}

vector<int> Screens::random_stack_order(int num_pancakes) {  //get order helper for rand order
    vector<int> order;
    for (int i = 0; i < num_pancakes; i++) {  //random order
        order.push_back(i+1);
    }
    srand(time(0));  //time seed to make truly random
    random_shuffle(order.begin(), order.end());
    move(2, 0);
    return order;
}
// end of part 3=====================================================================

//===================================================================================
// Part 6, user move, AI blink, flip printing
bool Screens::test_arrow_move() {
    bool all_passed = true;
    initscr();
    string expected = "->";
    int move_output = arrow_move(0, 0, 1, 3, 1);  //test going above limit
    char actual_cstr[2];
    mvinnstr(1, 0, actual_cstr, expected.length());
    string actual = actual_cstr;
    if (expected.compare(actual) != 0 || move_output != 1) {
        all_passed = false;
        cout << "test 1 failed";
    }
    move_output = arrow_move(0, 0, 3, 3, -1);  //test going above limit
    mvinnstr(7, 0, actual_cstr, expected.length());
    actual = actual_cstr;
    if (expected.compare(actual) != 0 || move_output != 3) {
        all_passed = false;
        cout << "test 2 failed";
    }
    move_output = arrow_move(0, 0, 3, 3, 0);
    if (move_output != 0) {
        all_passed = false;
        cout << "test 3 failed";
    }
    endwin();
    return all_passed;
}

//no way to simulate key presses, so second optional arguments for testing
int Screens::arrow_move(int y, int x, int cursor_pos, int num_pancakes, int move) {
    //move int determines move, -1 = down, 1 = up, 0 = enter
    //return pos if enter, 0 if move cursor
    for(int i = y; i < y+num_pancakes*3; i++) {  //clear old arrow
        mvprintw(i, x, "  ");
    }
    if(move == 0) {  //skip if enter key pressed
        return 0;
    }
    else if(move == 1 || move == -1) {
        if((move == 1 && cursor_pos == 1) || (move == -1 && cursor_pos == num_pancakes-1))
            move = 0;  //handle arrow boundaries
        int new_y = y+1+3*(cursor_pos-1-move);
        mvprintw(new_y, x, "->");
        return cursor_pos-move;
    }
    else {
        cout << "Unexpected Error Occurred.";
        return -1;
    }
}

void Screens::arrow_init(int y, int x, int cursor_pos) {
    mvprintw(y+1+3*(cursor_pos-1), x, "->");
}

void Screens::test_player_selection() {
    //can't simulate user input, manual test
    initscr();
    vector<int> order;
    order.push_back(4);
    order.push_back(2);
    order.push_back(1);
    order.push_back(3);
    game.set_order(order);
        int sel = player_selection(0, 0);
        endwin();
        cout << "player selection was: " << sel << endl;
}

int Screens::player_selection(int y, int x) {
    noecho();
    keypad(stdscr, TRUE);
    int num_pancakes = game.get_num_pancakes();
    int cursor_pos = 1;  //cursor position
    arrow_init(y, x, cursor_pos);
    int key_input, output_pos, move;
    while (true) {  //cursor_pos == 0 means select location
        key_input = getch();
        if (key_input == 104)  // hint
            mvprintw(1, 0, "Try flipping the top %d pancakes.", game.get_hint());
        else if (key_input == 10 || key_input == 'w' || key_input == 's') {  //enter, w, s
            if (key_input == 'w') move = 1;
            else if (key_input == 's') move = -1;
            else if (key_input == 10) move = 0;  //can be optimized to return at move = 0
            output_pos = arrow_move(y, x, cursor_pos, num_pancakes, move);
            if (output_pos == 0) {
                return cursor_pos;
            }
            else
                cursor_pos = output_pos;
        }
    }
}

void Screens::player_move() {
    int y = 5;
    int x = 10;
    int flip_location = player_selection(y+3, x);
    vector<int> user_order = game.get_user_order();
    vector<int> sub_stack;
    for (int i = 0; i <= flip_location; i++) {
        sub_stack.push_back(user_order.at(i));
    }
    blink_stack(y, x, sub_stack);
    refresh();
    game.flip_user(flip_location);
    erase_pancakes(y, x, 30, game.get_num_pancakes());
    draw_pancakes(game.get_user_order(), y, x);
    refresh();

}

void Screens::erase_pancakes(int top_side, int left_side, int num_cols, int num_pancakes) {
    for (int i = top_side; i < 3*num_pancakes+top_side; i++) {
        for (int j = left_side; j < num_cols+left_side; j++) {
            mvprintw(i, j, " ");
        }
    }
}

void Screens::test_blink_stack() {
    initscr();
    vector<int> test_vec;
    test_vec.push_back(2);
    test_vec.push_back(1);
    test_vec.push_back(3);
    blink_stack(0, 0, test_vec);
    endwin();
}

void Screens::blink_stack(int y, int x, vector<int> sub_stack) {
    //mvprintw(30, 0, "Blink Called");
    refresh();
    for (int i = 0; i < 3; i++) {
        erase_pancakes(y, x, 30, sub_stack.size());
        refresh();
        napms(500);
        draw_pancakes(sub_stack, y, x);
        refresh();
        napms(500);
    }
}

void Screens::ai_move() {
    //mvprintw(29, 0, "ai move called");
    refresh();
    int y = 5;
    int x = 40;
    int ai_move = game.get_ai_move();
    //mvprintw(31, 0, "get_ai_move terminated");
    refresh();
    vector<int> ai_order = game.get_ai_order();
    vector<int> sub_stack;
    for (int i = 0; i <= ai_move; i++) {
        sub_stack.push_back(ai_order.at(i));
    }
    blink_stack(y, x, sub_stack);
    refresh();
    game.flip_ai(ai_move);
    erase_pancakes(y, x, 30, game.get_num_pancakes());
    draw_pancakes(game.get_ai_order(), y, x);
}
//end of part 6
//==============================================================================================

// part 4 and 8===================================================================================
void Screens::enter_initials() {
    erase();
    string initials;
    char str[80];
    echo();
    while (true) {
        printw("Please enter your initials: ");
        getstr(str);
        initials = string(str);
        if (initials.length() == 3)
            break;
        printw("Invalid initials (must be 3 characters).\n");
    }
    noecho();
    game.set_initials(initials);
    display_top_5();
    printw("\n%s (Lv.%d) %d\n", initials.c_str(), game.get_difficulty(), 0);
    printw("\nPress any key to continue.");
    getch();
    refresh();
}

void Screens::post_game() {
    erase();
    move(0, 0);
    int curr_score = game.calculate_score(game.get_num_pancakes());
    int curr_difficulty = game.get_difficulty();
    string initials = game.get_initials();
    int pos = in_top_5(curr_score);
    printw("%s\n[%s] On difficulty %d, you scored %d pts.\n\n", game.get_winner().c_str(), initials.c_str(), curr_difficulty, curr_score);
    if (pos == -1) {
        printw("Sorry, your score is not one of the top 5 highest scores.\n\n");
        display_top_5();
        printw("\n%s (%d) %d\n", initials.c_str(), curr_difficulty, curr_score);
    }
    else {
        printw("You made it onto the leaderboard!\n\n");
        add_score(make_tuple(initials, curr_difficulty, curr_score));
        display_top_5();
        write_top_5();
    }
    play_again();
}

void Screens::display_top_5() {
    vector<tuple<string, int, int>> high_scores = game.get_top_5();
    printw("Top 5 High Scores\n");
    printw("-----------------\n");
    for (auto t : high_scores) {
        printw("%s (%d) %d\n", get<0>(t).c_str(), get<1>(t), get<2>(t));
    }
}

void Screens::read_top_5() {
    vector<tuple<string, int, int>> top5;
    string initials;
    int difficulty, score;
    ifstream file("highscores.txt");
    if (!file) {
        init_high_score_file();
        file.open("highscores.txt");
    }
    while (file >> initials >> difficulty >> score) {
        top5.push_back(make_tuple(initials, difficulty, score));
    }
    file.close();
    game.set_high_scores(top5);
}

void Screens::write_top_5() {
    vector<tuple<string, int, int>> high_scores = game.get_top_5();
    ofstream file("highscores.txt");
    for (int i = 0; i < 5; ++i) {
        file << get<0>(high_scores.at(i)) << " " << get<1>(high_scores.at(i)) << " " << get<2>(high_scores.at(i)) << endl;
    }
    file.close();
}

int Screens::in_top_5(int score) {
    vector<tuple<string, int, int>> high_scores = game.get_top_5();
    if (!high_scores.empty()) {
        for (int i = 0; i < 5; ++i) {
            if (score > get<2>(high_scores.at(i)))
                return i;
        }
        return -1;
    }
    return 0;
}
void Screens::add_score(tuple<string, int, int> score) {
    vector<tuple<string, int, int>> high_scores = game.get_top_5();
    if (!high_scores.empty()) {
        int pos = in_top_5(get<2>(score));
        if (pos != -1) {
            for (int i = 4; i > pos; --i) {
                high_scores.at(i) = high_scores.at(i - 1);
            }
            high_scores.at(pos) = score;
        }
    }
    game.set_high_scores(high_scores);
}

void Screens::init_high_score_file() {
    ofstream file("highscores.txt");
    for (int i = 0; i < 5; ++i) {
        file << "--- 0 0" << endl;
    }
    file.close();
}

void Screens::play_again() {
    cbreak();
    printw("\nKeep playing? (y/n): ");
    char ans = getch();
    while (true) {
        if (ans == 110) {
            done = true;
            return;
        }
        else if (ans == 121) {
            erase();
            return;
        }
        else {
            move(14, 0);
            printw("Enter y or n: ");
            ans = getch();
        }
    }
}

bool Screens::keep_playing() {
    return !done;
}

bool Screens::test_file_read() {
    vector<tuple<string, int, int>> save = save_file_contents();
    ofstream file("highscores.txt");
    file << "AAA 4 10000" << endl << "BBB 5 9000" << endl << "CCC 8 5500" << endl << "DDD 7 4000" << endl << "EEE 3 100" << endl;
    file.close();
    read_top_5();
    vector<tuple<string, int, int>> expected = make_test_vector();
    for (int i = 0; i < 5; ++i) {
        vector<tuple<string, int, int>> v = game.get_top_5();
        if (get<0>(v.at(i)) != get<0>(expected.at(i)) || get<1>(v.at(i)) != get<1>(expected.at(i)) || get<2>(v.at(i)) != get<2>(expected.at(i))) {
            restore_file_contents(save);
            return false;
        }
    }
    restore_file_contents(save);
    return true;
}

bool Screens::test_file_write() {
    vector<tuple<string, int, int>> save = save_file_contents();
    vector<tuple<string, int, int>> test = make_test_vector();
    game.set_high_scores(test);
    write_top_5();
    vector<string> expected = {"AAA 4 10000", "BBB 5 9000", "CCC 8 5500", "DDD 7 4000", "EEE 3 100"};
    ifstream file("highscores.txt");
    string line;
    for (int i = 0; i < 5; ++i) {
        getline(file, line);
        if (line != expected.at(i)) {
            restore_file_contents(save);
            return false;
        }
    }
    restore_file_contents(save);
    return true;
}

bool Screens::test_add_score() {
    vector<tuple<string, int, int>> save = save_file_contents();
    vector<tuple<string, int, int>> test = make_test_vector();
    game.set_high_scores(test);
    add_score(make_tuple("NEW", 5, 6500));
    add_score(make_tuple("BAD", 8, 0));
    test = game.get_top_5();
    vector<tuple<string, int, int>> expected;
    expected.push_back(make_tuple("AAA", 4, 10000));
    expected.push_back(make_tuple("BBB", 5, 9000));
    expected.push_back(make_tuple("NEW", 5, 6500));
    expected.push_back(make_tuple("CCC", 8, 5500));
    expected.push_back(make_tuple("DDD", 7, 4000));
    for (int i = 0; i < 5; ++i) {
        if (expected.at(i) != test.at(i)) {
            restore_file_contents(save);
            return false;
        }
    }
    restore_file_contents(save);
    return true;
}

vector<tuple<string, int, int>> Screens::save_file_contents() {
    read_top_5();
    return game.get_top_5();
}

void Screens::restore_file_contents(vector<tuple<string, int, int>> v) {
    game.set_high_scores(v);
    write_top_5();
}

vector<tuple<string, int, int>> Screens::make_test_vector() {
    vector<tuple<string, int, int>> test;
    test.push_back(make_tuple("AAA", 4, 10000));
    test.push_back(make_tuple("BBB", 5, 9000));
    test.push_back(make_tuple("CCC", 8, 5500));
    test.push_back(make_tuple("DDD", 7, 4000));
    test.push_back(make_tuple("EEE", 3, 100));
    return test;
}
// end of parts 4 and 8================================================================

// part 7==============================================================================
void Screens::play_game() {
    echo();
    erase();
    label_user_stack(3, 10);
    label_ai_stack(3, 40);
    draw_pancakes(game.get_user_order(), 5, 10);
    draw_pancakes(game.get_user_order(), 5, 40);
    noecho();
    while (!game.game_over()) {
        mvprintw(0, 0, "Minimum Number of Steps to Solve: %d", game.get_min_moves());
        mvprintw(1, 0, "[Need a hint? Press 'h']             ");
        player_move();
        mvprintw(1, 0, "Opponent is thinking...               ");
        ai_move();
        refresh();
    }
    printw("\n\n                   Game finished. Press any key to continue.");
    getch();
}
// end of part 7========================================================

// part 5==============================================================================
void Screens::center_output(string str, int num_cols) { //Allows the pancakes to be displayed appropriately
    int padding_left = (num_cols/ 2) - (str.size() / 2); //Makes sure the pancakes are centered relative to one another
    
    for(int i = 0; i < padding_left; i++) {
        printw(" ");
    }

    printw(str.c_str());
}

bool Screens::center_output_test() { //Tests to ensure that the pancakes are actually being centered relative to one another
    int top_side = 0;
    vector<string> test_string = box_1_wrapper();
    
    move(top_side, 0);
    
    for(int i = 0; i < 3; i++) {
        center_output(test_string[i], 30);
        move(top_side += 1, 0);
    }
    
    char test1 = mvinch(0, 0);
    char test2 = mvinch(0, 2);
    char test3 = mvinch(0, 4);
    char test4 = mvinch(1, 0);
    char test5 = mvinch(1, 2);
    char test6 = mvinch(1, 4);
    endwin();
    if(test1 == '+' && test2 == '-' && test3 == '+' && test4 == '|' && test5 == '1' && test6 == '|') {
        return true;
    }
    else {
        return false;
    }
}

//Wrappers that contain vectors of strings comprised of the individual elements of the pancakes
vector<string> Screens::box_9_wrapper() {
    vector<string> box_9 = {
    "+-------------------+", 
    "|         9         |", 
    "+-------------------+"
    };
    return box_9;
}

vector<string> Screens::box_8_wrapper() {
    vector<string> box_8 = {
    "+-----------------+", 
    "|        8        |", 
    "+-----------------+"
    };
    return box_8;
}


vector<string> Screens::box_7_wrapper() {
    vector<string> box_7 = {
    "+---------------+", 
    "|       7       |",  
    "+---------------+"
    };
    return box_7;
}

vector<string> Screens::box_6_wrapper() {
    vector<string> box_6 = {
    "+-------------+", 
    "|      6      |",  
    "+-------------+"
    };
    return box_6;
}

vector<string> Screens::box_5_wrapper() {
    vector<string> box_5 = {
    "+-----------+", 
    "|     5     |", 
    "+-----------+"
    };
    return box_5;
}

vector<string> Screens::box_4_wrapper() {
    vector<string> box_4 = {
    "+---------+", 
    "|    4    |", 
    "+---------+"
    };
    return box_4;
}

vector<string> Screens::box_3_wrapper() {
    vector<string> box_3 = {
    "+-------+", 
    "|   3   |",  
    "+-------+"
    };
    return box_3;
}

vector<string> Screens::box_2_wrapper() {
    vector<string> box_2 = {
    "+-----+", 
    "|  2  |", 
    "+-----+"
    };
    return box_2;
}

vector<string> Screens::box_1_wrapper() {
    vector<string> box_1 = {
    "+---+", 
    "| 1 |",  
    "+---+"
    };
    return box_1;
}
    
void Screens::label_user_stack(int top_side, int left_side) { //Indicates which stack is the users
    move(top_side, left_side);
    center_output("PLAYER", 30);
}
    
void Screens::label_ai_stack(int top_side, int left_side) { //Indicates which stack is the AIs
    move(top_side, left_side);
    center_output("AI", 30);
}
    
void Screens::draw_pancakes(vector<int> stack, int top_side, int left_side) { //draws the appropriate pancakes in the appropriate places
    int num_cols = 30;
    move(top_side, left_side); //Allows us to print the pancakes anywhere on the screen that we wish
    vector<vector<string>> boxes = determine_box_order(stack); //Determines which pancakes and which order those pancakes should be displayed in
    
    for (int i = 0; i < (int)boxes.size(); i++) { //Prints the pancakes appropriately
        for (int j = 0; j < 3; j++) {
            center_output(boxes[i][j], num_cols);
            move(top_side+=1, left_side);
        }
    }
}
    
vector<vector<string>> Screens::determine_box_order(vector<int> stack) { //Determines the correct order for the pancakes to be displayed in
    //Brad said leaving it as 34 lines was ok because breaking up a switch statement is gross
    vector<vector<string>> boxes;
    for(int i = 0; i < (int)stack.size(); i++) {
        switch(stack[i]) {
            case 1:
                boxes.push_back(box_1_wrapper());
                break;
            case 2:
                boxes.push_back(box_2_wrapper());
                break;
            case 3:
                boxes.push_back(box_3_wrapper());
                break;
            case 4:
                boxes.push_back(box_4_wrapper());
                break;
            case 5:
                boxes.push_back(box_5_wrapper());
                break;
            case 6:
                boxes.push_back(box_6_wrapper());
                break;
            case 7:
                boxes.push_back(box_7_wrapper());
                break;
            case 8:
                boxes.push_back(box_8_wrapper());
                break;
            case 9:
                boxes.push_back(box_9_wrapper());
                break;
            default:
                break;
        }
    }
    return boxes;
}
    
    
bool Screens::determine_box_order_test() { //Ensures that the order being the pancakes are being displayed in is the correct order
    vector<int> actual = box_order_test_vector();
    vector<vector<string>> compare = box_order_test_comparison_vector();
     
    vector<vector<string>> boxes = determine_box_order(actual);
    bool box_order = true;
    for(int i = 0; i < (int)boxes.size(); i++) {
        for(int j = 0; j < (int)boxes[0].size(); j++) {
            if(boxes[i][j] != compare[i][j]) {
                box_order = false;
            }
        }
    }
    return box_order;
}

vector<vector<string>> Screens::box_order_test_comparison_vector() { //Provides a test pancakes stack to compare to
    vector<vector<string>> compare;
    compare.push_back(box_1_wrapper());
    compare.push_back(box_2_wrapper());
    compare.push_back(box_3_wrapper()); 
    compare.push_back(box_4_wrapper());
    
    return compare;
}

vector<int> Screens::box_order_test_vector() {//Provides a vector that should yield the same order of pancakes as the function above.
    vector<int> actual;
    actual.push_back(1);
    actual.push_back(2);
    actual.push_back(3);
    actual.push_back(4);
    
    return actual;
}
// end of part 5==========================================================================
