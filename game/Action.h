#ifndef __Action__
#define __Action__

#include "Constants.h"

class Action {
	public:
		Action();
		Action(Rotation rot, int col);
		Rotation rotation;
		int column;
};

#endif
