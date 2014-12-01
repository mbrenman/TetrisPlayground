#ifndef __Constants__
#define __Constants__

//Board Sizes
const int TETRIS_ROWS = 20;
const int TETRIS_COLS = 10;

//Piece Constants
const int PIECESIZE = 4;
const int NUMPIECES = 7;

const int NUM_WEIGHTS = 5;

//All of the possible rotations
enum Rotation {NONE, CLOCKWISE, COUNTER_CLOCKWISE, FLIP, NUM_ROTATIONS};

//Best known weights
static double BEST_WEIGHTS[NUM_WEIGHTS] = {0.138531, -0.0323687, -0.702698, -0.0973667, -0.675217};

#endif