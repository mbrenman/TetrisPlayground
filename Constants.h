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
static double BEST_WEIGHTS[NUM_WEIGHTS] = {0.2196, 0.02566, -0.483, -0.1131, 0.5441, -0.6395};

#endif