#include "RandomAgent.h"
#include <stdlib.h>
#include <stdio.h>

RandomAgent::RandomAgent()
{
	Agent();
}

Action* RandomAgent::getAction(Tetris *board)
{	
	//Randomly choose a rotation state
	Rotation rot = (Rotation)(rand() % NUM_ROTATIONS);

	//Randomly choose a column
	int playColumn = rand() % (board->highestValidColWithRot(rot) + 1);
	
	//Create an action from the rotation and the column
	Action *a = new Action(rot, playColumn);
	
	//Play the action
	return a;
}

RandomAgent::~RandomAgent()
{}