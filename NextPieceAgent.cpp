#include "NextPieceAgent.h"

NextPieceAgent::NextPieceAgent()
{
	Agent();
	double *ws = BEST_WEIGHTS;
	heurAgent = new HeuristicAgent(ws);
}

Action* NextPieceAgent::getAction(Tetris *board)
{
	vector<Action*> bestActions;
	float bestValue = -999999;
	foundNewBestAction(bestActions, (Rotation) 0, 0);

	//For all valid rotations
	for (int r = 0; r < NUM_ROTATIONS; r++) {
		Rotation rot = (Rotation) r;

		//Make sure that we only check valid columns
		int maxColumn = board->highestValidColWithRot(rot) + 1;

		//For all valid columns for each rotation
		for (int col = 0; col < maxColumn; col++) {
			//Create the action for this move (will be cleaned up by playing it)
			
			float actVal = 0;
			
			//TODO: Look at all possible next pieces instead of random sampling
			Action *a = new Action(rot, col);

			//Copy the board -- this makes it have random next pieces
			Tetris *firstPlayed = board->gameCopy();

			firstPlayed->playAction(a, false);

			//We don't want to keep looking if we've lost
			if (!firstPlayed->isLost()) {

				//Now look at the best for the next piece
				//For all valid rotations
				for (int nextr = 0; nextr < NUM_ROTATIONS; nextr++) {
					Rotation nextrot = (Rotation) nextr;

					//Make sure that we only check valid columns
					int nextMaxColumn = firstPlayed->highestValidColWithRot(nextrot) + 1;

					//For all valid columns for each rotation
					for (int nextcol = 0; nextcol < nextMaxColumn; nextcol++) {
						//Create the action for this move (will be cleaned up by playing it)

						Tetris *nextPieceBoard = firstPlayed->gameCopy();

						Action *nexta = new Action(nextrot, nextcol);
						nextPieceBoard->playAction(nexta, false);

						actVal = heurAgent->valueBetweenBoards(board, nextPieceBoard);

						if (actVal > bestValue) {
							bestValue = actVal;
							foundNewBestAction(bestActions, rot, col);
						} else if (actVal == bestValue) {
							foundTiedAction(bestActions, rot, col);
						}
					}
				}
			}	
		}
	}

	//Choose the best action
	Action *a = pickRandomAction(bestActions);

	//Clean up the actions
	clearActionList(bestActions);

	//Play the action
	return a;
}

NextPieceAgent::~NextPieceAgent()
{
	delete heurAgent;
}