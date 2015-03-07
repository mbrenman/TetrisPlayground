#ifndef __TetrisNextPieceAgent__
#define __TetrisNextPieceAgent__

#include "Agent.h"
#include "HeuristicAgent.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

const bool testPoss = false;

class NextPieceAgent : public Agent {
	public:
		NextPieceAgent();
		Action* getAction(Tetris *board);
		virtual ~NextPieceAgent();
	private:
		HeuristicAgent *heurAgent;
};

#endif