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
	  	Tetris(const int board[TETRIS_COLS][TETRIS_ROWS], int pieceID, int cleared);
	    void printBoard();
	    bool isLost();
	    Piece* currentPiece();
	    void playAction(Action *a);
	    int highestValidCol();
	    int highestValidColWithRot(Rotation rot);
	    Tetris* gameCopy();
	    int getLinesCleared();
	    ~Tetris();
	private:
		int board[TETRIS_COLS][TETRIS_ROWS];
		int linesCleared;
		bool gameover;
		Piece* curPiece;
		void clearBoard();
		bool collision(int dropCol, int dropRow);
		void placePiece(int dropCol, int dropRow);
		void dropInColumn(int col);
		void clearLines();
		bool lineIsFull(int y);
		void clearLine(int startCol);
};


#endif