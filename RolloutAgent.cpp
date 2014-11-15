#include "RolloutAgent.h"

RolloutAgent::RolloutAgent()
{
	Agent();
}

Action* RolloutAgent::getAction(Tetris *board)
{		
	int maxLinesCleared = -1;
	Rotation bestRot = NUM_ROTATIONS; //If not overwritten, this is crash when played
	int bestColumn = -1;

	//For all valid rotations
	for (int r = 0; r < NUM_ROTATIONS; r++) {
		Rotation rot = (Rotation) r;
		//For all valid columns for each rotation
		int maxColumn = board->highestValidColWithRot(rot) + 1;
		// cout << "MAX COL: " << maxColumn << endl;
		for (int col = 0; col < maxColumn; col++) {
			Action *a = new Action(rot, col);
			Tetris *sim = board->gameCopy();
			int prevLines = sim->getLinesCleared();
			sim->playAction(a);
			int linesCleared = sim->getLinesCleared() - prevLines;
			if (linesCleared >= maxLinesCleared) {
				// cout << "Found better with col " << col << " and lines " << linesCleared << endl;
				maxLinesCleared = linesCleared;
				bestRot = rot;
				bestColumn = col;
			}
			delete sim;
		}
	}

	//If we can't expect to gain any lines, play randomly
	if (maxLinesCleared == 0) {
		// //Randomly choose a rotation state
		bestRot = (Rotation)(rand() % NUM_ROTATIONS);

		// //Randomly choose a column
		bestColumn = rand() % (board->highestValidColWithRot(bestRot) + 1);
	}

	//Create the best action
	Action *a = new Action(bestRot, bestColumn);

	//Play the action
	return a;
}