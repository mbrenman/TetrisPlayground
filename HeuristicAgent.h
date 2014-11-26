#ifndef __HeuristicAgent__
#define __HeuristicAgent__

#include "Agent.h"
#include <vector>
#include <map>
#include <iostream>
#include <math.h>

using namespace std;

const int HEURISTIC_HEIGHT = 2;

//TODO: Move board heuristics into this file

class HeuristicAgent : public Agent {
	public:
		HeuristicAgent();
		HeuristicAgent(double ws[NUM_WEIGHTS]);
		Action* getAction(Tetris *board);
		float valueBetweenBoards(Tetris *board1, Tetris *board2);
		double weights[NUM_WEIGHTS];
		~HeuristicAgent();
	private:
		vector<Action *> getBestActions(Tetris *board);
		string getBoardDesc(Tetris *board);
		float valueOfAction(int linesCleared, int heightGain, int newHoles, int topDownBlocked, int aggTopBlocked, bool lost);
		float valueOfActionOnBoard(Action *a, Tetris *sim);
		map<string, vector<Action *> > computedActions;
};

#endif