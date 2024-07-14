
#include <stdint.h>

typedef enum {
    YELLOW_OFFSET = 0,
    GREEN_OFFSET = 11,
    RED_OFFSET = 21,
    BLUE_OFFSET = 35
} Offset;

// fun facts about enums!
// https://kubyshkin.name/posts/c-language-enums-tips-and-tricks/
typedef enum {
    HOME = 1,
    FINAL,
    OUTER,
    ASCENDED
} pawn_states;

typedef enum {
    Yellow,
    Green,
    Red,
    Blue
} Color;

typedef struct {
    uint8_t move_counter;
    uint8_t positions[4 * 4]; // 4 pawns, 4 players
    pawn_states states[4]
} game_state; // same here, PascalCase

// convenience macros -- make them inline functions if you want type safety but
// I don't think it's necessary
#define get_positions(state, color) ((state).positions + (color) * 4)
#define get_states(state, color)    ((state).states + (color) * 4)

inline Offset
get_offset(Color cc) {
    switch (cc) {
    case Yellow:
        return YELLOW_OFFSET;
    case Green:
        return GREEN_OFFSET;
    case Red:
        return RED_OFFSET;
    case Blue:
        return BLUE_OFFSET;
    }
}
