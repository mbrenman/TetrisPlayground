#include "Piece.h"
#include <iostream>
#include "assert.h"

using namespace std;

Piece::Piece()
{
	pieceID = (rand() % NUMPIECES) + 1;
	setPiece(pieceID);
}

Piece::Piece(int id)
{
	pieceID = id;
	setPiece(id);
}

void Piece::setPiece(int id)
{
	//Reserved id for empty spaces
	assert(id != 0);

	switch(pieceID){
		case 1:
			// . . . .
			// . . . .
			// X X . .
			// X X . .
				piece[0][0] = 0;
				piece[1][0] = 0;
				piece[2][0] = 0;
				piece[3][0] = 0;
				piece[0][1] = 0;
				piece[1][1] = 0;
				piece[2][1] = 0;
				piece[3][1] = 0;
				piece[0][2] = 1;
				piece[1][2] = 1;
				piece[2][2] = 0;
				piece[3][2] = 0;
				piece[0][3] = 1;
				piece[1][3] = 1;
				piece[2][3] = 0;
				piece[3][3] = 0;
			break;
		case 2:
			// . . . .
			// . . . .
			// X . . .
			// X X X .
				piece[0][0] = 0;
				piece[1][0] = 0;
				piece[2][0] = 0;
				piece[3][0] = 0;
				piece[0][1] = 0;
				piece[1][1] = 0;
				piece[2][1] = 0;
				piece[3][1] = 0;
				piece[0][2] = 1;
				piece[1][2] = 0;
				piece[2][2] = 0;
				piece[3][2] = 0;
				piece[0][3] = 1;
				piece[1][3] = 1;
				piece[2][3] = 1;
				piece[3][3] = 0;
			break;
		case 3:
			// . . . .
			// . . . .
			// . . X .
			// X X X .
				piece[0][0] = 0;
				piece[1][0] = 0;
				piece[2][0] = 0;
				piece[3][0] = 0;
				piece[0][1] = 0;
				piece[1][1] = 0;
				piece[2][1] = 0;
				piece[3][1] = 0;
				piece[0][2] = 0;
				piece[1][2] = 0;
				piece[2][2] = 1;
				piece[3][2] = 0;
				piece[0][3] = 1;
				piece[1][3] = 1;
				piece[2][3] = 1;
				piece[3][3] = 0;
			break;
		case 4:
			// . . . .
			// . . . .
			// . . . .
			// X X X X
				piece[0][0] = 0;
				piece[1][0] = 0;
				piece[2][0] = 0;
				piece[3][0] = 0;
				piece[0][1] = 0;
				piece[1][1] = 0;
				piece[2][1] = 0;
				piece[3][1] = 0;
				piece[0][2] = 0;
				piece[1][2] = 0;
				piece[2][2] = 0;
				piece[3][2] = 0;
				piece[0][3] = 1;
				piece[1][3] = 1;
				piece[2][3] = 1;
				piece[3][3] = 1;
			break;
		case 5:
			// . . . .
			// . . . .
			// . X X .
			// X X . .
				piece[0][0] = 0;
				piece[1][0] = 0;
				piece[2][0] = 0;
				piece[3][0] = 0;
				piece[0][1] = 0;
				piece[1][1] = 0;
				piece[2][1] = 0;
				piece[3][1] = 0;
				piece[0][2] = 0;
				piece[1][2] = 1;
				piece[2][2] = 1;
				piece[3][2] = 0;
				piece[0][3] = 1;
				piece[1][3] = 1;
				piece[2][3] = 0;
				piece[3][3] = 0;
			break;
		case 6:
			// . . . .
			// . . . .
			// X X . .
			// . X X .
				piece[0][0] = 0;
				piece[1][0] = 0;
				piece[2][0] = 0;
				piece[3][0] = 0;
				piece[0][1] = 0;
				piece[1][1] = 0;
				piece[2][1] = 0;
				piece[3][1] = 0;
				piece[0][2] = 1;
				piece[1][2] = 1;
				piece[2][2] = 0;
				piece[3][2] = 0;
				piece[0][3] = 0;
				piece[1][3] = 1;
				piece[2][3] = 1;
				piece[3][3] = 0;
			break;
		case 7:
			// . . . .
			// . . . .
			// X X . .
			// . X X .
				piece[0][0] = 0;
				piece[1][0] = 0;
				piece[2][0] = 0;
				piece[3][0] = 0;
				piece[0][1] = 0;
				piece[1][1] = 0;
				piece[2][1] = 0;
				piece[3][1] = 0;
				piece[0][2] = 0;
				piece[1][2] = 1;
				piece[2][2] = 0;
				piece[3][2] = 0;
				piece[0][3] = 1;
				piece[1][3] = 1;
				piece[2][3] = 1;
				piece[3][3] = 0;
			break;
		default:
			cerr << "BAD PIECE ID " << pieceID;
			exit(1);
	}
}

int Piece::getPieceID()
{
	return pieceID;
}

void Piece::rotate(Rotation rot)
{
	bool buf[PIECESIZE][PIECESIZE];
	copyPiece(buf);

	switch(rot){
		case NONE:
			// cout << "About to rotate NONE " << endl;
			break;
		case CLOCKWISE:
			// cout << "About to rotate CLOCKWISE " << endl;
			for (int x = 0; x < PIECESIZE; x++) {
				for (int y = 0; y < PIECESIZE; y++) {
					buf[PIECESIZE - y - 1][x] = piece[x][y];
				}
			}
			break;
		case COUNTER_CLOCKWISE:
			// cout << "About to rotate COUNTER_CLOCKWISE " << endl;
			for (int x = 0; x < PIECESIZE; x++) {
				for (int y = 0; y < PIECESIZE; y++) {
					buf[y][PIECESIZE - x - 1] = piece[x][y];
				}
			}
			break;
		case FLIP:
			// cout << "About to rotate FLIP " << endl;
			for (int x = 0; x < PIECESIZE; x++) {
				for (int y = 0; y < PIECESIZE; y++) {
					buf[PIECESIZE - x - 1][PIECESIZE - y - 1] = piece[x][y];
				}
			}
			break;
		default:
			exit(1);
	}

	replacePiece(buf);
	pullLeft();
}

void Piece::replacePiece(bool buf[PIECESIZE][PIECESIZE])
{

	for (int x = 0; x < PIECESIZE; x++) {
		for (int y = 0; y < PIECESIZE; y++) {
			piece[x][y] = buf[x][y];
			assert(piece[x][y] == buf[x][y]);
		}
	}
}

void Piece::pullLeft()
{
	while (emptyLeft()){
		for (int y = 0; y < PIECESIZE; y++) {
			for (int x = 0; x < PIECESIZE - 1; x++) {
				piece[x][y] = piece[x + 1][y];
			}
			piece[PIECESIZE - 1][y] = 0;
		}
	}
}

bool Piece::emptyLeft()
{
	for (int y = 0; y < PIECESIZE; y++) {
		if (piece[0][y]){
			return false;
		}
	}
	return true;
}

void Piece::pullDown()
{
	while (emptyBottom()){
		for (int x = 0; x < PIECESIZE; x++) {
			for (int y = PIECESIZE - 1; y > 0; y--) {		
				piece[x][y] = piece[x][y - 1];
			}
			piece[x][0] = 0;
		}
	}
}

bool Piece::emptyBottom()
{
	for (int x = 0; x < PIECESIZE; x++) {
		if (piece[x][PIECESIZE - 1]){
			return false;
		}
	}
	return true;
}

void Piece::copyPiece(bool buf[PIECESIZE][PIECESIZE])
{
	for (int x = 0; x < PIECESIZE; x++) {
		for (int y = 0; y < PIECESIZE; y++) {
			buf[x][y] = piece[x][y];
		}
	}
}

int Piece::pieceWidth()
{
	int width = 0;
	for (int x = 0; x < PIECESIZE; x++) {
		for (int y = 0; y < PIECESIZE; y++) {
			if (piece[x][y]) {
				width = x;
			}
		}
	}
	return width;
}

void Piece::printPiece()
{
	for (int y = 0; y < PIECESIZE; y++) {
		for (int x = 0; x < PIECESIZE; x++) {
			cout << piece[x][y];
		}
		cout << endl;
	}
}