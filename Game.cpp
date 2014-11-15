#include <iostream>
#include "Tetris.h"
#include "Piece.h"
#include "Agent.h"
#include <unistd.h>

using namespace std;

int main()
{
	srand(time(NULL));

	//Create Simulator with an empty board
	Tetris *board = new Tetris();

	//Create Agent
	Agent *player = new Agent();

	//Game loop
	while (!board->isLost()) {
		usleep(50000);
		// board->currentPiece()->printPiece();
		board->printBoard();
		Action *a = player->getAction(board);
		board->dropInColumn(a->column);
		
		//Get action from the agent

		//Peform the action

	}
	cout << "highest" << board->highestValidCol() << endl;

	board->printBoard();
	return 0;
}