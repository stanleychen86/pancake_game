#include "Screens.h"

int main() {
    Screens a = Screens();
    a.setup();
    while (a.keep_playing()) {
        a.instructions();
        a.create_menu();
        a.set_pancake_order();
        a.enter_initials();
        a.play_game();
        a.post_game();
    }
    a.teardown();
}
