#include "Tetris.h"
#include <iostream>

using namespace std;

Tetris::Tetris()
{
	clearBoard();
	curPiece = new Piece();
	gameover = false;
	linesCleared = 0;
}

Tetris::Tetris(const int inBoard[TETRIS_COLS][TETRIS_ROWS], int pieceID, int cleared)
{
	clearBoard();
	curPiece = new Piece(pieceID);
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

void Tetris::playAction(Action *a)
{
	curPiece->rotate(a->rotation);
	dropInColumn(a->column);

	//Free the action
	delete a;
}

void Tetris::dropInColumn(int col)
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
	}
	dropRow -= 1;
	placePiece(col, dropRow);

	clearLines();
}

void Tetris::placePiece(int dropCol, int dropRow) {
	bool p[PIECESIZE][PIECESIZE];
	curPiece->copyPiece(p);

	for (int x = 0; x < PIECESIZE; x++) {
		for (int y = 0; y < PIECESIZE; y++) {
			if (p[x][y]) {
				//Check if the board has been lost
				if (y + dropRow < 0) {
					gameover = true;
				} else {
					board[x + dropCol][y + dropRow] = curPiece->getPieceID();
				}
			}
		}
	}

	//Free the old piece and get a new one
	delete curPiece;
	curPiece = new Piece();
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

int Tetris::holesInBoard()
{
	int boardCopy[TETRIS_COLS][TETRIS_ROWS];
	copyBoard(boardCopy);

	for (int x = 0; x < TETRIS_COLS; x++) {
		//Try filling at all of the top spots in case one is blocked
		fillReachableBlanks(x, 0, boardCopy);
	}
	return countBlanks(boardCopy);
}

int Tetris::countBlanks(int boardCopy[TETRIS_COLS][TETRIS_ROWS])
{
	int numHoles = 0;
	for (int x = 0; x < TETRIS_COLS; x++) {
		for (int y = 0; y < TETRIS_ROWS; y++) {
			if (boardCopy[x][y] == EMPTY_SPACE) {
				numHoles++;
			}
		}
	}
	return numHoles;
}

void Tetris::fillReachableBlanks(int x, int y, int boardCopy[TETRIS_COLS][TETRIS_ROWS])
{
	//Make sure that we're on the board
	if (x >= 0 && x < TETRIS_COLS && y >= 0 && y < TETRIS_ROWS) {
		//Only change and recurse on empty spaces
		if (boardCopy[x][y] == EMPTY_SPACE) {
			boardCopy[x][y] = RESERVED;
			fillReachableBlanks(x + 1, y, boardCopy);
			fillReachableBlanks(x - 1, y, boardCopy);
			fillReachableBlanks(x, y + 1, boardCopy);
			fillReachableBlanks(x, y - 1, boardCopy);
		}
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
	return new Tetris(board, curPiece->getPieceID(), linesCleared);
}

Piece* Tetris::currentPiece()
{
	int id = curPiece->getPieceID();
	return new Piece(id);
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
}