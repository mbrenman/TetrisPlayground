#include <iostream>
#include "Tetris.h"
#include "Piece.h"
#include "Agent.h"
#include "RandomAgent.h"
#include "RolloutAgent.h"
#include <unistd.h>

using namespace std;

void clearScreen();

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	//Create Simulator with an empty board
	Tetris *board = new Tetris();

	//Create Agent
	Agent *player = new RolloutAgent();

	//Game loop
	while (!board->isLost()) {
		usleep(750000);
		board->printBoard();

		//Get action from the agent
		Action *a = player->getAction(board);

		//Peform the action
		board->playAction(a);

		clearScreen();
	}

	board->printBoard();

	cout << "Finished with #lines: " << board->getLinesCleared() << endl;

	delete board;
	delete player;
	return 0;
}

void clearScreen()
{
	cout << "\n\n\n\n\n\n";
}