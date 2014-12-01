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
		float valueOfAction(int linesCleared, int heightGain, int newHoles, int topDownBlocked, int aggTopBlocked, bool lost);
		float valueOfActionOnBoard(Action *a, Tetris *sim);

		//Heuristic Measurements
		int holesInBoard(Tetris *board);
		void fillReachableBlanks(int x, int y, int boardCopy[TETRIS_COLS][TETRIS_ROWS]);
		int countBlanks(int boardCopy[TETRIS_COLS][TETRIS_ROWS]);
		int topDownBlocked(Tetris *board);
		int aggregateTopDownBlocked(Tetris *board);
		void fillTopDown(int boardCopy[TETRIS_COLS][TETRIS_ROWS]);
};

#endif