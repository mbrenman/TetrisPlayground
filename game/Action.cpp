#include "Action.h"

Action::Action()
{
	rotation = NONE;
	column = -1;
}

Action::Action(Rotation rot, int col)
{
	rotation = rot;
	column = col;
}
