#include "Action.h"

Action::Action()
{
	//Inital null action, invalid to play
	rotation = NONE;
	column = -1;
}

Action::Action(Rotation rot, int col)
{
	rotation = rot;
	column = col;
}
