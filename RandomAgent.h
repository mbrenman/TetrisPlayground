#ifndef __TetrisRandomAgent__
#define __TetrisRandomAgent__

#include "Agent.h"

class RandomAgent : public Agent {
	public:
		RandomAgent();
		Action* getAction(Tetris *board);
	private:
};

#endif