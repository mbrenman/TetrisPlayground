#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

//Game components
#include "Tetris.h"
#include "Piece.h"

//Agent components (add any agents that you make here)
#include "Agent.h"
#include "RandomAgent.h"
#include "RolloutAgent.h"
#include "HeuristicAgent.h"
#include "NextPieceAgent.h"

using namespace std;

void playGame(Tetris *board, Agent *player, bool animated);

int main(int argc, char const *argv[])
{
	//Seed the RNG
	srand(time(NULL));

	//Create Simulator with an empty board -- official game
	Tetris *board = new Tetris(true);

	//Create the Agent (This is where you instantiate your custom agent)
	Agent *player = new NextPieceAgent();

	//Play the game!
	playGame(board, player, true);

	delete board;
	delete player;
	return 0;
}

void playGame(Tetris *board, Agent *player, bool animated)
{
	//Game loop
	while (!board->isLost()) {
		//Get action from the agent
		Action a = player->getAction(board);

		//Peform the action
		board->playAction(a, animated);
	}

	//After the game, reprint board and statistics
	if (animated) {
		board->printBoard();
		cout << "Finished with #lines: " << board->getLinesCleared() << endl;
	}
}
