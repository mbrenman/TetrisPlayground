#ifndef __Tetris__
#define __Tetris__

#include "Constants.h"
#include "Piece.h"
#include "Action.h"
#include <assert.h>

const int EMPTY_SPACE =  0;
const int RESERVED    = -1;

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
	    int maxBoardHeight();
	    int holesInBoard();
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
		int countBlanks(int boardCopy[TETRIS_COLS][TETRIS_ROWS]);
		void fillReachableBlanks(int x, int y, int boardCopy[TETRIS_COLS][TETRIS_ROWS]);
		void copyBoard(int dest[TETRIS_COLS][TETRIS_ROWS]);
};


#endif