#include "Agent.h"

Agent::Agent()
{
	//Initialize Agent
}

Action* Agent::getAction(Tetris *board)
{
	int playColumn = rand() % (board->highestValidCol() + 1);
	Action *a = new Action(NONE, playColumn);
	return a;
}