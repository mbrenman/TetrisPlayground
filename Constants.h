#ifndef __Constants__
#define __Constants__

//Board Sizes
const int TETRIS_ROWS = 20;
const int TETRIS_COLS = 10;

//Piece Constants
const int PIECESIZE = 4;
const int NUMPIECES = 7;

//All of the possible rotations
enum Rotation {NONE, CLOCKWISE, COUNTER_CLOCKWISE, FLIP, NUM_ROTATIONS};

#endif