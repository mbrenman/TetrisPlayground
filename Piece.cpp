#include "Piece.h"
#include <iostream>

using namespace std;

Piece::Piece()
{
	piece[0][0] = 1;
	piece[1][0] = 0;
	piece[0][1] = 1;
	piece[1][1] = 1;

	//Pick a random number between 0 and 8
	pieceID = rand() % 8;
}

Piece::Piece(int id)
{
	piece[0][0] = 1;
	piece[1][0] = 0;
	piece[0][1] = 1;
	piece[1][1] = 0;

	pieceID = id;
}

int Piece::getPieceID()
{
	return pieceID;
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