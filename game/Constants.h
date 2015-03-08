#ifndef __Constants__
#define __Constants__

//Board Sizes
const int TETRIS_ROWS = 20;
const int TETRIS_COLS = 10;

//Piece Constants
const int PIECESIZE = 4;
const int NUMPIECES = 7;

const int NUM_WEIGHTS = 6;

//All of the possible rotations
enum Rotation {NONE, CLOCKWISE, COUNTER_CLOCKWISE, FLIP, NUM_ROTATIONS};

//Best known weights
static double BEST_WEIGHTS[NUM_WEIGHTS] = {0.5114, 0.06141, -0.4613, -0.5912, 0.3666, -0.1948};

#endif
