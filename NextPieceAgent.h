#ifndef __TetrisNextPieceAgent__
#define __TetrisNextPieceAgent__

#include "Agent.h"
#include "HeuristicAgent.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class NextPieceAgent : public Agent {
	public:
		NextPieceAgent();
		Action* getAction(Tetris *board);
		~NextPieceAgent();
	private:
		HeuristicAgent *heurAgent;	
};

#endif