
#include <stdint.h>

// #define YELLOW_OFFSET   0
// #define GREEN_OFFSET    11
// #define RED_OFFSET      21
// #define BLUE_OFFSET     35

// this is fine, but I'd rather use an enum for this

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
} pawn_states; // as far as naming conventions go, I'd rather use PascalCase
               // for types

typedef enum {
    // also inconsistent casing in your enums; the ones above are CAPS and this
    // one is PascalCase
    Yellow,
    Green,
    Red,
    Blue
} Color;

// unnecessary abstraction -- you are indexing them anyway and this way you
// can't use a for loop (that would otherwise be unrolled by the compiler)
/*
typedef struct
{
    int p1;
    int p2;
    int p3;
    int p4;
}
pawn_pos;
*/

typedef struct {
    uint8_t move_counter;
    uint8_t positions[4 * 4]; // 4 pawns, 4 players
    pawn_states states[4]
} game_state; // same here, PascalCase

// unnecessary abstraction 2: electric boogaloo
/*
typedef struct
{
    uint8_t curr_positions[4];
    pawn_states *curr_pawns;
    COLOR cc;
}
turn;
*/

// convenience macros -- make them inline functions if you want type safety but
// I don't think it's necessary
#define get_positions(state, color) ((state).positions + (color)*4)
#define get_states(state, color)    ((state).states + (color)*4)

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
