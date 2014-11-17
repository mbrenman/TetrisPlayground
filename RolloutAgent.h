#ifndef __TetrisRolloutAgent__
#define __TetrisRolloutAgent__

#include "Agent.h"
#include <vector>
#include <iostream>

using namespace std;

class RolloutAgent : public Agent {
	public:
		RolloutAgent();
		Action* getAction(Tetris *board);
	private:
		Action* pickRandomAction(vector<Action*> &actions);
		void clearActionList(vector<Action*> &actions);
		void foundNewBestAction(vector<Action*> &actions, Rotation rot, int col);
		void foundTiedAction(vector<Action*> &actions, Rotation rot, int col);		
		int valueOfAction(int linesCleared, int heightGain, int newHoles, int topDownBlocked, bool lost);
};

#endif