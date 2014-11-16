#include "RolloutAgent.h"

RolloutAgent::RolloutAgent()
{
	Agent();
}

Action* RolloutAgent::getAction(Tetris *board)
{		
	// int maxLinesCleared = -1;
	// int minHeightGained = PIECESIZE; //Max possible
	int bestValue = -99999999;

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

			//Save current game stats
			int prevLines  = sim->getLinesCleared();
			int prevHeight = sim->maxBoardHeight();
			int prevHoles  = sim->holesInBoard();

			//Play the action
			sim->playAction(a);

			//Observe new stats
			int linesCleared = sim->getLinesCleared() - prevLines;
			int heightGain   = prevHeight - sim->maxBoardHeight();
			int newHoles     = sim->holesInBoard() - prevHoles;
			bool lost		 = sim->isLost();

			int value = valueOfAction(linesCleared, heightGain, newHoles, lost);

			if (value > bestValue) {
				bestValue = value;
				foundNewBestAction(bestActions, rot, col);
			} else if (value == bestValue) {
				foundTiedAction(bestActions, rot, col);
			}

			//More lines are better
			// if (linesCleared > maxLinesCleared) {
			// 	maxLinesCleared = linesCleared;
			// 	minHeightGained = heightGain;
			// 	bestRot = rot;
			// 	bestColumn = col;
			// 	foundNewBestAction(bestActions, rot, col);
			// } else if (linesCleared == maxLinesCleared) {
			// 	//Minimize height gain if lines cannot be cleared
			// 	if (heightGain < minHeightGained) {
			// 		maxLinesCleared = linesCleared;
			// 		minHeightGained = heightGain;
			// 		bestRot = rot;
			// 		bestColumn = col;
			// 		foundNewBestAction(bestActions, rot, col);
			// 	} else if (heightGain == minHeightGained) {
			// 		foundTiedAction(bestActions, rot, col);
			// 	}
			// }
			delete sim;
		}
	}

	//Choose the best action
	Action *a = pickRandomAction(bestActions);

	//Clean up the actions
	clearActionList(bestActions);

	//Play the action
	return a;
}

int RolloutAgent::valueOfAction(int linesCleared, int heightGain, int newHoles, bool lost)
{
	if (lost) {
		return -10000;
	} else {
		return (100 * linesCleared) + (-3 * newHoles) + (-50 * heightGain);
	}
}

Action* RolloutAgent::pickRandomAction(vector<Action*> &actions)
{
	assert(actions.size() > 0);
	
	//Randomly pick an index and get the action
	int actIndex = rand() % actions.size();
	Action *a = actions.at(actIndex);

	//Make a copy since all of the values in the vector will be cleaned up
	return new Action(a->rotation, a->column);
}

void RolloutAgent::clearActionList(vector<Action*> &actions)
{
	for(vector<Action*>::iterator it = actions.begin(); it != actions.end(); it++) {
		Action *a = (*it);
		delete a;
	}
	actions.clear();
}

void RolloutAgent::foundNewBestAction(vector<Action*> &actions, Rotation rot, int col)
{
	clearActionList(actions);
	Action *a = new Action(rot, col);
	actions.push_back(a);
}

void RolloutAgent::foundTiedAction(vector<Action*> &actions, Rotation rot, int col)
{
	Action *a = new Action(rot, col);
	actions.push_back(a);
}