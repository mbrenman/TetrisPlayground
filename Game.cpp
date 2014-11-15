#include <iostream>
#include "Tetris.h"
#include "Piece.h"
#include <unistd.h>

using namespace std;

int main()
{
	srand(time(NULL));

	//Create Simulator with an empty board
	Tetris *board = new Tetris();

	//Create Agent
	
	//Game loop
	while (!board->isLost()) {
		sleep(1);
		board->currentPiece()->printPiece();
		board->printBoard();
		board->dropInColumn(rand() % (board->highestValidCol() + 1));
		
		//Get action from the agent

		//Peform the action

	}
	cout << "highest" << board->highestValidCol() << endl;

	board->printBoard();
	return 0;
}