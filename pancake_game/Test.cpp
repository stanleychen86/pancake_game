#include "Screens.h"
#include "aiTree.h"
#include "node.h"
#include "Pancake.h"
#include <iostream>
#include <assert.h> 
#include <unistd.h>
using namespace std;


int main() {
    Screens s = Screens();

    cout << "Testing File Read...";
    assert(s.test_file_read());
    cout << "Passed" << endl;

    cout << "Testing File Write...";
    assert(s.test_file_write());
    cout << "Passed" << endl;

    cout << "Testing Score Add...";
    assert(s.test_add_score());
    cout << "Passed" << endl;
    
    //cout << "Testing splash screen...";
    //assert(s.test_splashscreen());
    //cout << "Passed" << endl;
    
    //cout << "Testing Random Stack Order..." << endl;
    //assert(s.test_random_stack_order());
    //cout << "Passed" << endl;
    
    //cout << "Testing duplicate check" << endl;
    //assert(s.test_user_stack_duplicate_check());
    //cout << "Passed" << endl;

    //cout << "Testing user range check" << endl;
    //assert(s.test_user_stack_range_check());
    //cout << "Passed" << endl;

    //cout << "Testing arrow move" << endl;
    //assert(s.test_arrow_move());
    //cout << "Passed" << endl;

    //cout << "Testing game over" << endl;
    //assert(e.test_game_over());
    //cout << "Passed" << endl;
    
    /*cout << "Testing Box Order...";
    assert(s.determine_box_order_test());
    cout << "Passed" << endl;
    
    cout << "Testing Center Output...";
    assert(s.center_output_test());
    cout << "Passed << endl;
    */
    
    //s.test_player_selection(0,0);
    //s.test_blink_stack();

    //-------------------------------------------------
    Pancake p = Pancake();

    cout << "Testing Pancake Flip 1...";
    assert(p.pancake_flip_test0());
    cout << "Passed" << endl;

    cout << "Testing Pancake Flip 2...";
    assert(p.pancake_flip_test1());
    cout << "Passed" << endl;

    cout << "Testing Pancake Sortedness 1...";
    assert(p.pancake_sortedness_test0());
    cout << "Passed" << endl;

    cout << "Testing Pancake Sortedness 2...";
    assert(p.pancake_sortedness_test1());
    cout << "Passed" << endl;

    //-------------------------------------------------
    
    node n = node();

    cout << "Testing Node operations...";
    assert(n.node_tester());
    cout << "Passed" << endl;

    ai_tree a = ai_tree();
    cout << "Testing AI get_next_move 1...";
    assert(a.get_next_move_test0());
    cout << "Passed" << endl;

    cout << "Testing AI get_next_move 2...";
    assert(a.get_next_move_test1());
    cout << "Passed" << endl;

    cout << "Testing AI get_next_move 3...";
    assert(a.get_next_move_test2());
    cout << "Passed" << endl;

    cout << "Testing AI get_next_move 4...";
    assert(a.get_next_move_test3());
    cout << "Passed" << endl;

    cout << "Testing AI get_to_be_num_children 1...";
    assert(a.get_to_be_num_children_test0());
    cout << "Passed" << endl;

    cout << "Testing AI get_to_be_num_children 2...";
    assert(a.get_to_be_num_children_test1());
    cout << "Passed" << endl;

    cout << "Testing AI get_to_be_num_children 3...";
    assert(a.get_to_be_num_children_test2());
    cout << "Passed" << endl;
    
    cout << "All Tests Passed!" << endl;
}