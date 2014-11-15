#include <iostream>
#include "Tetris.h"
#include "Piece.h"
#include "Agent.h"
#include "RandomAgent.h"
#include <unistd.h>

using namespace std;

void clearScreen();

int main()
{
	srand(time(NULL));

	//Create Simulator with an empty board
	Tetris *board = new Tetris();
	Tetris *board2 = new Tetris();

	//Create Agent
	Agent *player = new RandomAgent();

	//Game loop
	while (!board->isLost() && !board2->isLost()) {
		usleep(75000);
		board->printBoard();
		cout << endl << endl;
		board2->printBoard();

		//Get action from the agent
		Action *a = player->getAction(board);
		Action *a2 = player->getAction(board2);

		//Peform the action
		board->playAction(a);
		board2->playAction(a2);

		clearScreen();
	}

	board->printBoard();
	cout << endl << endl;
	board2->printBoard();

	delete board;
	delete player;
	return 0;
}

void clearScreen()
{
	cout << "\n\n\n\n\n\n";
}