#ifndef __Tetris__
#define __Tetris__

#include "Constants.h"
#include "Piece.h"
#include "Action.h"
#include <assert.h>
#include <unistd.h>

const int EMPTY_SPACE =  0;
const int RESERVED    = -1;

const int ANIM_DELAY = 5000;

class Tetris {
	public:
	    Tetris(bool official);
	  	Tetris(const int board[TETRIS_COLS][TETRIS_ROWS], int pieceID, int nextPieceID, int cleared);
	    void printBoard();
	    bool isLost();
	    Piece* currentPiece();
	    void setPiece(int id);
	    void playAction(Action *a, bool animated);
	    int highestValidCol();
	    int highestValidColWithRot(Rotation rot);
	    Tetris* gameCopy();
	    int getLinesCleared();
	    int maxBoardHeight();
	    void copyBoard(int dest[TETRIS_COLS][TETRIS_ROWS]);
	    ~Tetris();
	private:
		int board[TETRIS_COLS][TETRIS_ROWS];
		int linesCleared;
		bool gameover;
		const bool officialGame;
		Piece* curPiece;
		Piece* nextPiece;
		void clearBoard();
		bool collision(int dropCol, int dropRow);
		void placePiece(int dropCol, int dropRow, int inBoard[TETRIS_COLS][TETRIS_ROWS], bool activeBoard);
		void dropInColumn(int col, bool animated);
		void clearLines();
		bool lineIsFull(int y);
		void clearLine(int startCol);
		void printSpecial(int inBoard[TETRIS_COLS][TETRIS_ROWS]);
		void printBoardWithDroppingPiece(int col, int dropRow);
		void clearScreen();
};


#endif