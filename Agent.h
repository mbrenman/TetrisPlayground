#ifndef __TetrisAgent__
#define __TetrisAgent__

#include "Constants.h"
#include "Tetris.h"
#include "Action.h"
#include <assert.h>

class Agent {
	public:
		Agent();
		virtual Action* getAction(Tetris *board);
	private:
};

#endif