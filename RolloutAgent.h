#ifndef __TetrisRolloutAgent__
#define __TetrisRolloutAgent__

#include "Agent.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

const int K = 0;
const int W = 1;
const float GAMMA = 0.9;

class RolloutAgent : public Agent {
	public:
		RolloutAgent();
		Action* getAction(Tetris *board);
	private:
		Action* getActionHeuristic(Tetris *board);
		Action* pickRandomAction(vector<Action*> &actions);
		void clearActionList(vector<Action*> &actions);
		void foundNewBestAction(vector<Action*> &actions, Rotation rot, int col);
		void foundTiedAction(vector<Action*> &actions, Rotation rot, int col);		
		float valueOfAction(int linesCleared, int heightGain, int newHoles, int topDownBlocked, int aggTopBlocked, bool lost);
		float valueOfActionOnBoard(Action *a, Tetris *sim);
		float valueBetweenBoards(Tetris *board1, Tetris *board2);
};

#endif