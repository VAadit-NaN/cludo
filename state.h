
#include <stdint.h>

// fun facts about enums!
// https://kubyshkin.name/posts/c-language-enums-tips-and-tricks/
typedef enum {
    YELLOW_OFFSET = 0,
    GREEN_OFFSET = 11,
    RED_OFFSET = 21,
    BLUE_OFFSET = 35
} Offset;

typedef enum {
    HOME = 1,
    FINAL,
    OUTER,
    ASCENDED
} PawnState;

typedef enum {
    YELLOW,
    GREEN,
    RED,
    BLUE
} Color;

typedef enum {
    EVICT,
    MOVE
} MoveType;

typedef struct {
    uint8_t move_counter;
    uint8_t positions[4 * 4]; // 4 pawns, 4 players
} GameState;

typedef struct {
    MoveType type;
    uint8_t pawn;
    uint8_t roll;
} Move;

// convenience macros -- make them inline functions if you want type safety but
// I don't think it's necessary
#define get_positions(state, color) ((state).positions + (color) * 4)
#define get_states(state, color)    ((state).states + (color) * 4)

inline Offset
get_offset(Color cc) {
    switch (cc) {
    case YELLOW:
        return YELLOW_OFFSET;
    case GREEN:
        return GREEN_OFFSET;
    case RED:
        return RED_OFFSET;
    case BLUE:
        return BLUE_OFFSET;
    }
}

PawnState
get_state_from_position(uint8_t pos) {
    switch (pos) {
    case 0:
        return HOME;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        return FINAL;
    case 6:
        return ASCENDED;
    default:
        return OUTER;
    }
}