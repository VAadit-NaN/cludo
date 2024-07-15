#include "state.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

GameState
create_game() {
    // this is the concise way to write it
    return (GameState){.move_counter = 0, .positions = {0}};
}

Color
whose_turn_is_it(GameState g) {
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
play(GameState g, Move m) {
    Color curr = whose_turn_is_it(g);
    uint8_t *positions = get_positions(g, curr);

    // what can be played?
    if (m.type == EVICT) {
        for (int a = 0; a < 4; a++) {
            if (get_state_from_position(positions[a]) == HOME) {
                positions[a] = get_offset(curr);
                break;
            }
        }

        // we should not be here
        return;
    }
    // for now there are no transitions out of the OUTER loop so there's no
    // FINAL or ASCENDED states so no state changes after HOME to OUTER

    positions[m.pawn] += m.roll;
}

int
main() {
    return 0;
}
