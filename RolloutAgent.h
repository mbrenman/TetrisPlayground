#ifndef __TetrisRolloutAgent__
#define __TetrisRolloutAgent__

#include "Agent.h"
#include "HeuristicAgent.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

const int K = 2;
const int W = 10;
const float GAMMA = 0.9;

class RolloutAgent : public Agent {
	public:
		RolloutAgent();
		Action* getAction(Tetris *board);
		~RolloutAgent();
	private:
		HeuristicAgent *heurAgent;
		Action* pickRandomAction(vector<Action*> &actions);
		void clearActionList(vector<Action*> &actions);
		void foundNewBestAction(vector<Action*> &actions, Rotation rot, int col);
		void foundTiedAction(vector<Action*> &actions, Rotation rot, int col);		
};

#endif