#include "Action.h"

Action::Action()
{
	rotation = -1;
	column = -1;
}

Action::Action(int rot, int col)
{
	rotation = rot;
	column = col;
}