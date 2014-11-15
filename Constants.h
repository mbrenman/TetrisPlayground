#ifndef __Constants__
#define __Constants__

//Board Sizes
const int TETRIS_ROWS = 40;
const int TETRIS_COLS = 8;

const int PIECESIZE = 2;

//All of the possible rotations
enum Rotation {NONE, CLOCKWISE, COUNTER_CLOCKWISE, FLIP, NUM_ROTATIONS};

#endif