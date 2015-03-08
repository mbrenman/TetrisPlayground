#ifndef __HeuristicAgent__
#define __HeuristicAgent__

#include "Agent.h"
#include <vector>
#include <map>
#include <iostream>
#include <math.h>

using namespace std;

const int HEURISTIC_HEIGHT = 2;
const double LOSE_PENALTY  = 1000;

//TODO: Add more heuristics
//			-- smoothness
//			-- total height (not the different) -- INTEGRATE IN
//			-- max difference between col heights
//			-- count blockades (maybe instead of aggtopblocked)

class HeuristicAgent : public Agent {
	public:
		HeuristicAgent();
		HeuristicAgent(double ws[NUM_WEIGHTS]);
		Action getAction(Tetris *board);
		float valueBetweenBoards(Tetris *board1, Tetris *board2);
		float valueOfActionOnBoard(Action a, Tetris *sim);
		double weights[NUM_WEIGHTS];
		virtual ~HeuristicAgent();
	private:
		vector<Action > getBestActions(Tetris *board);
		float valueOfAction(int linesCleared, int heightGain, int newHoles, int topDownBlocked, int aggTopBlocked, int aggHeight, bool lost);

		//Heuristic Measurements
		int aggHeight(Tetris *board);
		int holesInBoard(Tetris *board);
		void fillReachableBlanks(int x, int y, int boardCopy[TETRIS_COLS][TETRIS_ROWS]);
		int countBlanks(int boardCopy[TETRIS_COLS][TETRIS_ROWS]);
		int topDownBlocked(Tetris *board);
		int aggregateTopDownBlocked(Tetris *board);
		void fillTopDown(int boardCopy[TETRIS_COLS][TETRIS_ROWS]);
};

#endif
