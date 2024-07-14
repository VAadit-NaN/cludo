#include "state.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

game_state
create_game() {
    // this is the concise way to write it
    return (game_state){.move_counter = 0, .positions = {0}, .states = {HOME}};
}

Color
whose_turn_is_it(game_state g) {
    return g.move_counter % 4;
}

// this is supposed to be a frontend call which decides whether the
// player has selected HOMEROW (0) or Pawns (anything that's not HOME or
// ASCENDED is a valid selection) pawns are numbered 1 through 4
int
get_selection() {
    return 0;
}

int
getRandomNumber() {
    return 4; // chosen by fair dice roll.
              // guaranteed to be random.
}

void
play(game_state g) {
    Color curr = whose_turn_is_it(g);
    uint8_t roll = rand() % 5 + 1;

    uint8_t *positions = get_positions(g, curr);
    pawn_states *states = get_states(g, curr);

    // what can be played?
    if (roll == 6) {
        int move_p = get_selection();
        if (!move_p) {
            int release_pawn = get_offset(curr); // this is stupid and I can't decide if I hate
                                                 // abstraction more than nesting
            for (int a = 0; a < 4; a++) {
                if (states[a] == HOME) {
                    positions[a] = release_pawn;
                    states[a] = OUTER;
                    break;
                }
            }

            // but what happens if there are no pawns at home?
            // no case to handle a == 4
            // TODO: handle this case
            return;
        }
        // for now there are no transitions out of the OUTER loop so there's no
        // FINAL or ASCENDED states so no state changes after HOME to OUTER

        positions[move_p] += 6;
    }
}

int
main() {
    return 0;
}
