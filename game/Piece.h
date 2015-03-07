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
		void rotate(Rotation rot);
	private:
		bool piece[PIECESIZE][PIECESIZE];
		int pieceID;
		void setPiece(int id);
		void pullLeft();
		void pullDown();
		void replacePiece(bool buf[PIECESIZE][PIECESIZE]);
		bool emptyLeft();
		bool emptyBottom();
};

#endif