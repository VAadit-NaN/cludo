#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define YELLOW_OFFSET 0
#define GREEN_OFFSET 11
#define RED_OFFSET 21
#define BLUE_OFFSET 35


// https://stackoverflow.com/a/4024086
// Yes, I know how it works
// No, I could not have figured it out by myself :(
//
// I'm realizing it's not the best idea to have stuff which changes size constantly
// for sake of avoiding future headaches. no stack for home
//
// PAWN STATES- at home, final row, outer loop, finished
//
// #define push(sp, n) (*((sp)++) = (n))
// #define pop(sp) (*--(sp))


// fun facts about enums! https://kubyshkin.name/posts/c-language-enums-tips-and-tricks/
typedef enum 
{
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
} COLOR;

typedef struct 
{
    int p1;
    int p2;
    int p3;
    int p4;
}
pawn_pos;

typedef struct 
{
    uint8_t move_counter;
    pawn_pos *Y_pos, *G_pos, *R_pos, *B_pos;
    pawn_states *Y_pawns, *R_pawns, *G_pawns, *B_pawns;
} 
game_state;

typedef struct 
{
    pawn_pos *curr_positions;
    pawn_states *curr_pawns;
    COLOR cc;
}
turn;

void
init_board(game_state x)
{
    x.move_counter = 0;
    x.Y_pos = (pawn_pos *)malloc(sizeof(pawn_pos));
    x.R_pos = (pawn_pos *)malloc(sizeof(pawn_pos));
    x.G_pos = (pawn_pos *)malloc(sizeof(pawn_pos));
    x.B_pos = (pawn_pos *)malloc(sizeof(pawn_pos));
    // there has to be a more concise way to write this part
    pawn_states init_stack[4] = {HOME, HOME, HOME, HOME};
    x.Y_pawns = memcpy(x.Y_pawns, init_stack, sizeof(init_stack));
    x.R_pawns = memcpy(x.R_pawns, init_stack, sizeof(init_stack));
    x.G_pawns = memcpy(x.G_pawns, init_stack, sizeof(init_stack));
    x.B_pawns = memcpy(x.B_pawns, init_stack, sizeof(init_stack));
}

turn 
whose_turn_is_it(game_state l)
{
    turn *out = NULL;
    switch(l.move_counter % 4)
    {
        case 0:
            out->curr_pawns = l.Y_pawns;
            out->curr_positions = l.Y_pos;
            out->cc = Yellow;
            break;
        case 1:
            out->curr_pawns = l.R_pawns;
            out->curr_positions = l.R_pos;
            out->cc = Green;
            break;

        case 2:
            out->curr_pawns = l.G_pawns;
            out->curr_positions = l.G_pos;
            out->cc = Red;
            break;

        case 3:
            out->curr_pawns = l.B_pawns;
            out->curr_positions = l.B_pos;
            out->cc = Blue;
            break;
    }
    return *out;
}

int get_offset(COLOR cc) 
{
    switch(cc) 
    {
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


// this is supposed to be a frontend call which decides whether the 
// player has selected HOMEROW (0) or Pawns (anything that's not HOME or ASCENDED is a valid selection)
// pawns are numbered 1 through 4
int
get_selection()
{
    return 0;
}

void
play(game_state l)
{
    turn curr = whose_turn_is_it(l);
    int roll = rand() % 5 + 1;
    // what can be played?
    // 
    if (roll == 6) {
        int move_p = get_selection();
        if (!move_p) {
            int release_pawn = get_offset(curr.cc); // this is stupid and I can't decide if I hate abstraction more than nesting
            int a = 0;
            for (; a < 4; a++) 
            {
                if (curr.curr_pawns[a] == 1) break; //first home pawn is released
            }
            // release pawn and also change it's state from HOME to OUTER
            switch(a) 
            {
                case 0: curr.curr_positions->p1 = release_pawn; curr.curr_pawns[0] = OUTER; break;
                case 1: curr.curr_positions->p2 = release_pawn; curr.curr_pawns[1] = OUTER; break;
                case 2: curr.curr_positions->p3 = release_pawn; curr.curr_pawns[2] = OUTER; break;
                case 3: curr.curr_positions->p4 = release_pawn; curr.curr_pawns[3] = OUTER; break;
            }
        }
        else 
        {
            // for now there are no transitions out of the OUTER loop so there's no FINAL or ASCENDED states
            // so no state changes after HOME to OUTER
            switch(move_p)
            {
                case 0: curr.curr_positions->p1 += 6; break;
                case 1: curr.curr_positions->p2 += 6; break;
                case 2: curr.curr_positions->p3 += 6; break;
                case 3: curr.curr_positions->p4 += 6; break;
            }
        }
    }
}



int main() {
    return 0;
}
