#ifndef __HeuristicAgent__
#define __HeuristicAgent__

#include "Agent.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

const int HEURISTIC_HEIGHT = 2;

class HeuristicAgent : public Agent {
	public:
		HeuristicAgent();
		Action* getAction(Tetris *board);
		~HeuristicAgent();
	private:
		vector<Action *> getBestActions(Tetris *board);
		Action* pickRandomAction(vector<Action*> &actions);
		void clearActionList(vector<Action*> &actions);
		void foundNewBestAction(vector<Action*> &actions, Rotation rot, int col);
		void foundTiedAction(vector<Action*> &actions, Rotation rot, int col);		
		float valueOfAction(int linesCleared, int heightGain, int newHoles, int topDownBlocked, int aggTopBlocked, bool lost);
		float valueOfActionOnBoard(Action *a, Tetris *sim);
		float valueBetweenBoards(Tetris *board1, Tetris *board2);
};

#endif