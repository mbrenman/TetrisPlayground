#ifndef __Piece__
#define __Piece__

#include "Constants.h"

class Piece {
	public:
		Piece();
		Piece(int id);
		void copyPiece(bool buf[PIECESIZE][PIECESIZE]);
		void printPiece();
		int pieceWidth();
		int getPieceID();
	private:
		bool piece[PIECESIZE][PIECESIZE];
		int pieceID;
};

#endif