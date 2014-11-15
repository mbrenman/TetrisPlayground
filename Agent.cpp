#include "Agent.h"

Agent::Agent()
{
	//Initialize Agent
}

Action* Agent::getAction(Tetris *board)
{
	int playColumn = rand() % (board->highestValidColWithRot(CLOCKWISE) + 1);
	Action *a = new Action(CLOCKWISE, playColumn);
	return a;
}