#include "Piece.h"
#include <iostream>
#include "assert.h"

using namespace std;

Piece::Piece()
{
	pieceID = (rand() % 4) + 1;
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
			// X.
			// XX
			piece[0][0] = 1;
			piece[1][0] = 0;
			piece[0][1] = 1;
			piece[1][1] = 1;
			break;
		case 2:
			// XX
			// XX
			piece[0][0] = 1;
			piece[1][0] = 1;
			piece[0][1] = 1;
			piece[1][1] = 1;
			break;
		case 3:
			// XX
			// .X
			piece[0][0] = 1;
			piece[1][0] = 1;
			piece[0][1] = 0;
			piece[1][1] = 1;
			break;
		case 4:
			// X.
			// X.
			piece[0][0] = 1;
			piece[1][0] = 0;
			piece[0][1] = 1;
			piece[1][1] = 0;
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

//Fix this logic
void Piece::rotate(Rotation rot)
{
	bool buf[PIECESIZE][PIECESIZE];
	copyPiece(buf);
	printPiece();
	switch(rot){
		case NONE:
			cout << "About to rotate NONE " << endl;
			break;
		case CLOCKWISE:
			cout << "About to rotate CLOCKWISE " << endl;
			for (int x = 0; x < PIECESIZE; x++) {
				for (int y = 0; y < PIECESIZE; y++) {
					buf[PIECESIZE - y - 1][x] = piece[x][y];
				}
			}
			cout << "Done." << endl;
			break;
		case COUNTER_CLOCKWISE:
			cout << "About to rotate COUNTER_CLOCKWISE " << endl;
			break;
		case FLIP:
			cout << "About to rotate FLIP " << endl;
			break;
		default:
			exit(1);
	}
	printPiece();
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

//Fix this logic
void Piece::pullLeft()
{
	printPiece();
	while (emptyLeft()){
		cout << "PULLING LEFT" << endl;
		printPiece();
		for (int y = 0; y < PIECESIZE; y++) {
			for (int x = 0; x < PIECESIZE - 1; x++) {
				piece[x][y] = piece[x + 1][y];
			}
			piece[PIECESIZE - 1][y] = 0;
		}
		cout << "Done." << endl;
		printPiece();
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