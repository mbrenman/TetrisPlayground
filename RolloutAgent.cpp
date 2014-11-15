#include "RolloutAgent.h"

RolloutAgent::RolloutAgent()
{
	Agent();
}

Action* RolloutAgent::getAction(Tetris *board)
{		
	int maxLinesCleared = -1;
	int minHeightGained = PIECESIZE; //Max possible
	Rotation bestRot = NUM_ROTATIONS; //If not overwritten, this is crash when played
	int bestColumn = -1;

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
			int prevLines = sim->getLinesCleared();
			int prevHeight = sim->maxBoardHeight();

			//Play the action
			sim->playAction(a);

			//Observe new stats
			int linesCleared = sim->getLinesCleared() - prevLines;
			int heightGain = prevHeight - sim->maxBoardHeight();

			//More lines are better
			if (linesCleared > maxLinesCleared) {
				maxLinesCleared = linesCleared;
				minHeightGained = heightGain;
				bestRot = rot;
				bestColumn = col;
			} else if (linesCleared == maxLinesCleared) {
				if (heightGain <= minHeightGained) {
					maxLinesCleared = linesCleared;
					minHeightGained = heightGain;
					bestRot = rot;
					bestColumn = col;	
				}
			}
			delete sim;
		}
	}

	//Create the best action
	Action *a = new Action(bestRot, bestColumn);

	//Play the action
	return a;
}