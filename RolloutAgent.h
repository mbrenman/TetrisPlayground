#ifndef __TetrisRolloutAgent__
#define __TetrisRolloutAgent__

#include "Agent.h"
#include <iostream>

using namespace std;

class RolloutAgent : public Agent {
	public:
		RolloutAgent();
		Action* getAction(Tetris *board);
	private:
};

#endif