#include <iostream>
#include "Tetris.h"
#include "Piece.h"
#include "Agent.h"
#include "RandomAgent.h"
#include "RolloutAgent.h"
#include "HeuristicAgent.h"
#include "NextPieceAgent.h"
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

using namespace std;

void playGame(Tetris *board, Agent *player, bool animated);

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	//Create Simulator with an empty board -- official game
	Tetris *board = new Tetris(true);

	Agent *player = new NextPieceAgent();

	playGame(board, player, true);

	delete board;
	delete player;
	return 0;
}

void playGame(Tetris *board, Agent *player, bool animated)
{
	int count = 0;
	//Game loop
	while (!board->isLost() && count++ < 1) {
		//Get action from the agent
		Action *a = player->getAction(board);

		//Peform the action
		board->playAction(a, animated);
	}

	if (animated) {
		board->printBoard();
		cout << "Finished with #lines: " << board->getLinesCleared() << endl;
	}
}