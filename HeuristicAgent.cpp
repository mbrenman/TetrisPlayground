#include "HeuristicAgent.h"

HeuristicAgent::HeuristicAgent()
{
	Agent();
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		weights[i] = 0;
	}
}

HeuristicAgent::HeuristicAgent(double ws[NUM_WEIGHTS])
{
	Agent();

	//Normalize weights
	double vectorLength = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		vectorLength += ws[i] * ws[i];
	}
	vectorLength = sqrt(vectorLength);
	
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		weights[i] = ws[i] / vectorLength;
	}
}

Action* HeuristicAgent::getAction(Tetris *board)
{
	vector<Action *> bestActions;
	string boardDesc = getBoardDesc(board);

	//Check if the action has been seen before
	if (computedActions.count(boardDesc) > 0 && false) {

		//Pull actions from the map
		bestActions = computedActions.at(boardDesc);
	} else {
		//Calculate best actions
		bestActions = getBestActions(board);

		//Save those actions
		computedActions[boardDesc] = bestActions;
	}

	//Choose the best action
	Action *a = pickRandomAction(bestActions);

	//Play the action
	return a;
}

string HeuristicAgent::getBoardDesc(Tetris *board)
{
	//Get a local copy of the board
	int copy[TETRIS_COLS][TETRIS_ROWS];
	board->copyBoard(copy);



	return "test";
}

vector<Action *> HeuristicAgent::getBestActions(Tetris *board)
{
	float bestValue = -99999999;

	vector<Action*> bestActions;

	//For all valid rotations
	for (int r = 0; r < NUM_ROTATIONS; r++) {
		Rotation rot = (Rotation) r;

		//Make sure that we only check valid columns
		int maxColumn = board->highestValidColWithRot(rot) + 1;

		//For all valid columns for each rotation
		for (int col = 0; col < maxColumn; col++) {
			//Create the action for this move (will be cleaned up by playing it)
			Action *a = new Action(rot, col);

			//Copy the board
			Tetris *sim = board->gameCopy();

			float value = valueOfActionOnBoard(a, sim);

			if (value > bestValue) {
				bestValue = value;
				foundNewBestAction(bestActions, rot, col);
			} else if (value == bestValue) {
				foundTiedAction(bestActions, rot, col);
			}

			delete sim;
		}
	}

	return bestActions;
}

float HeuristicAgent::valueOfActionOnBoard(Action *a, Tetris *sim)
{
			//Save current game stats
			int prevLines      = sim->getLinesCleared();
			int prevHeight     = sim->maxBoardHeight();
			int prevHoles      = sim->holesInBoard();
			int prevBlocked    = sim->topDownBlocked();
			int prevAggBlocked = sim->aggregateTopDownBlocked();

			//Play the action
			sim->playAction(a, false);

			//Observe new stats
			int linesCleared    = sim->getLinesCleared() - prevLines;
			int heightGain      = prevHeight - sim->maxBoardHeight();
			int newHoles        = sim->holesInBoard() - prevHoles;
			int topBlocked      = sim->topDownBlocked() - prevBlocked;
			int aggTopBlocked   = sim->aggregateTopDownBlocked() - prevAggBlocked;
			bool lost		    = sim->isLost();

			return valueOfAction(linesCleared, heightGain, newHoles, topBlocked, aggTopBlocked, lost);
}

float HeuristicAgent::valueBetweenBoards(Tetris *board1, Tetris *board2)
{
	int linesCleared    = board2->getLinesCleared() - board1->getLinesCleared();
	int heightGain      = board1->maxBoardHeight() - board2->maxBoardHeight();
	int newHoles        = board2->holesInBoard() - board1->holesInBoard();
	int topBlocked      = board2->topDownBlocked() - board1->topDownBlocked();
	int aggTopBlocked   = board2->aggregateTopDownBlocked() - board1->aggregateTopDownBlocked();
	bool lost		    = board2->isLost();

	return valueOfAction(linesCleared, heightGain, newHoles, topBlocked, aggTopBlocked, lost);
}

float HeuristicAgent::valueOfAction(int linesCleared, int heightGain, int newHoles, int topDownBlocked, int aggTopBlocked, bool lost)
{
	if (lost) {
		return -10000;
	} else {
		return (weights[0] * linesCleared) + (weights[1] * newHoles) + (weights[2] * topDownBlocked) + (weights[3] * aggTopBlocked) + (weights[4] * heightGain);
	}
}

HeuristicAgent::~HeuristicAgent()
{
	//TODO: clean up all of the memory in the map -- use clearActionList(...) on all values;
}