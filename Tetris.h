#ifndef __Tetris__
#define __Tetris__

#include "Constants.h"
#include "Piece.h"
#include "Action.h"
#include <assert.h>

const int EMPTY_SPACE = 0;

class Tetris {
	public:
	    Tetris();
	    void printBoard();
	    bool isLost();
	    Piece* currentPiece();
	    void playAction(Action *a);
	    int highestValidCol();
	    int highestValidColWithRot(Rotation rot);
	private:
		int board[TETRIS_COLS][TETRIS_ROWS];
		bool gameover;
		Piece* curPiece;
		void clearBoard();
		bool collision(int dropCol, int dropRow);
		void placePiece(int dropCol, int dropRow);
		void dropInColumn(int col);
};


#endif