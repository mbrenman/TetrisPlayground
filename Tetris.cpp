#include "Tetris.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

Tetris::Tetris(bool official) : officialGame(official)
{
	clearBoard();
	curPiece = new Piece();
	nextPiece = new Piece();
	gameover = false;
	linesCleared = 0;
}

//If we're setting the board, then it is not an official game
Tetris::Tetris(const int inBoard[TETRIS_COLS][TETRIS_ROWS], int pieceID, int nextPieceID, int cleared) : officialGame(false)
{
	clearBoard();
	curPiece = new Piece(pieceID);
	nextPiece = new Piece(nextPieceID);
	gameover = false;
	linesCleared = cleared;

	for (int x = 0; x < TETRIS_COLS; x++) {
		for (int y = 0; y < TETRIS_ROWS; y++) {
			//Nothing marked
			board[x][y] = inBoard[x][y];
		}
	}
}

void Tetris::clearBoard()
{
	for (int x = 0; x < TETRIS_COLS; x++) {
		for (int y = 0; y < TETRIS_ROWS; y++) {
			//Nothing marked
			board[x][y] = EMPTY_SPACE;
		}
	}
}

int Tetris::highestValidCol()
{
	return TETRIS_COLS - curPiece->pieceWidth() - 1;
}

int Tetris::highestValidColWithRot(Rotation rot)
{
	//Make a copy of the current piece
	Piece *p = new Piece(curPiece->getPieceID());

	//Rotate the new piece
	p->rotate(rot);

	//Save the width
	int width = p->pieceWidth();

	//Delete the piece
	delete p;

	//Give the highestValidCol based on the new piece's width
	return TETRIS_COLS - width - 1;
}

void Tetris::playAction(Action *a, bool animated)
{
	curPiece->rotate(a->rotation);
	dropInColumn(a->column, animated);

	if (animated) {
		printBoard();
	}
	
	//Free the action
	delete a;
}

void Tetris::dropInColumn(int col, bool animated)
{
	assert(col >= 0);
	if (col > highestValidCol()){
		cerr << "Highest col: " << col << endl;
	}
	assert(col <= highestValidCol());
	assert(col < TETRIS_COLS);

	int dropRow = -PIECESIZE; //Start above the board
	while (!collision(col, dropRow)) {
		dropRow += 1;
		if (animated && dropRow > 0) {
			printBoardWithDroppingPiece(col, dropRow - 1);
			usleep(ANIM_DELAY);
		}
	}
	dropRow -= 1;
	placePiece(col, dropRow, board, true);
	clearLines();
}

void Tetris::placePiece(int dropCol, int dropRow, int inBoard[TETRIS_COLS][TETRIS_ROWS], bool activeBoard) {
	bool p[PIECESIZE][PIECESIZE];
	curPiece->copyPiece(p);

	for (int x = 0; x < PIECESIZE; x++) {
		for (int y = 0; y < PIECESIZE; y++) {
			if (p[x][y]) {
				//Check if the board has been lost
				if (y + dropRow < 0 && activeBoard) {
					gameover = true;
				} else {
					inBoard[x + dropCol][y + dropRow] = curPiece->getPieceID();
				}
			}
		}
	}

	//Free the old piece and get a new one only if this isn't the temp animation board
	if (activeBoard) {
		delete curPiece;
		curPiece = nextPiece;
		nextPiece = new Piece();
	}
}

bool Tetris::collision(int dropCol, int dropRow)
{
	bool p[PIECESIZE][PIECESIZE];
	curPiece->copyPiece(p);

	for (int x = 0; x < PIECESIZE; x++) {
		for (int y = 0; y < PIECESIZE; y++) {
			//Only check when the piece is there and the piece is on the board
			if (p[x][y] && y + dropRow >= 0) {
				//Check if piece is off the board
				if (x + dropCol >= TETRIS_COLS) {
					// cout << "Off the board X" << endl;
					return true;
				}
				//Check if piece is falling through the bottom
				if (y + dropRow >= TETRIS_ROWS) {
					// cout << "Off the board Y" << endl;
					return true;
				}
				//Check if piece is colliding with already placed pieces
				if (board[x + dropCol][y + dropRow] != EMPTY_SPACE) {
					// cout << "COLLISION" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

void Tetris::printBoard()
{
	clearScreen();
	for (int y = 0; y < TETRIS_ROWS; y++) {
		for (int x = 0; x < TETRIS_COLS; x++) {
			if (board[x][y] != EMPTY_SPACE) {
				printf("%c[%d;%d;%dm",27,1,37,40 + board[x][y]);
				cout << "  ";
				printf("%c[%dm", 0x1B, 0);
			} else {
				cout << " .";
			}
		}
		cout << endl;
	}
	printData();
	cout << endl << endl;
}

void Tetris::printBoardWithDroppingPiece(int col, int dropRow)
{
	int boardCopy[TETRIS_COLS][TETRIS_ROWS];
	copyBoard(boardCopy);

	//Place piece on a temporary board
	placePiece(col, dropRow, boardCopy, false);

	//Print the temp board
	printSpecial(boardCopy);
}

void Tetris::printSpecial(int inBoard[TETRIS_COLS][TETRIS_ROWS])
{
	clearScreen();
	for (int y = 0; y < TETRIS_ROWS; y++) {
		for (int x = 0; x < TETRIS_COLS; x++) {
			if (inBoard[x][y] == RESERVED){
				cout << " X";
			} else if (inBoard[x][y] != EMPTY_SPACE) {
				printf("%c[%d;%d;%dm",27,1,37,40 + inBoard[x][y]);
				cout << "  ";
				printf("%c[%dm", 0x1B, 0);
			} else {
				cout << " .";
			}
		}
		cout << endl;
	}
	printData();
	cout << endl << endl;
}

void Tetris::printData()
{
	cout << endl << "Lines Cleared: " << linesCleared << endl;

	cout << endl << "Current Piece: " << endl;
	curPiece->printPiece();

	cout << endl << "Next Piece: " << endl;
	nextPiece->printPiece();
}

void Tetris::clearScreen()
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int Tetris::maxBoardHeight()
{
	for (int y = 0; y < TETRIS_ROWS; y++) {
		for (int x = 0; x < TETRIS_COLS; x++) {
			if (board[x][y] != EMPTY_SPACE) {
				return y;
			}
		}
	}
	return 0;
}

void Tetris::clearLines()
{
	for (int y = TETRIS_ROWS - 1; y >= 0; y--) {
		if (lineIsFull(y)) {
			clearLine(y);
			linesCleared += 1;
			y++; //In case there are multiple lines that are cleared
		}
	}
}

bool Tetris::lineIsFull(int y)
{
	assert(y >= 0);
	assert(y < TETRIS_ROWS);

	for (int x = 0; x < TETRIS_COLS; x++) {
		if (board[x][y] == EMPTY_SPACE) {
			return false;
		}
	}
	return true;
}

void Tetris::clearLine(int startCol)
{
	assert(startCol >= 0);
	assert(startCol < TETRIS_ROWS);

	//Pull down all rows above
	for (int y = startCol; y > 0; y--) {
		for (int x = 0; x < TETRIS_COLS; x++) {
			board[x][y] = board[x][y - 1];
		}
	}

	//Clear the top row
	for (int x = 0; x < TETRIS_COLS; x++) {
		board[x][0] = EMPTY_SPACE;
	}
}

void Tetris::copyBoard(int dest[TETRIS_COLS][TETRIS_ROWS])
{
	for (int x = 0; x < TETRIS_COLS; x++) {
		for (int y = 0; y < TETRIS_ROWS; y++) {
			dest[x][y] = board[x][y];
		}
	}
}

Tetris* Tetris::gameCopy()
{
	return new Tetris(board, curPiece->getPieceID(), nextPiece->getPieceID(), linesCleared);
}

Piece* Tetris::currentPiece()
{
	int id = curPiece->getPieceID();
	return new Piece(id);
}

void Tetris::setPiece(int id)
{
	assert(id > 0 && id <= NUMPIECES);

	//Only change non-official games, but let people try
	if (officialGame) {
		cerr << "Illegal Action: Trying to change to official game piece." << endl;
	} else {
		delete curPiece;
		curPiece = new Piece(id);
	} 
}

bool Tetris::isLost()
{
	return gameover;
}

int Tetris::getLinesCleared()
{
	return linesCleared;
}

Tetris::~Tetris()
{
	delete curPiece;
	delete nextPiece;
}