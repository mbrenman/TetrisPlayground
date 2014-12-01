#include "RolloutAgent.h"

RolloutAgent::RolloutAgent()
{
	Agent();
	double *ws = BEST_WEIGHTS;
	heurAgent = new HeuristicAgent(ws);
}

Action* RolloutAgent::getAction(Tetris *board)
{
	vector<Action*> bestActions;
	float bestValue = -99999999;

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

			for (int w = 0; w < W; w++) {
				Action *a = new Action(rot, col);

				//Copy the board -- this makes it have random next pieces
				Tetris *trajectorySim = board->gameCopy();

				trajectorySim->playAction(a, false);

				for (int k = 0; k < K; k++) {
					// trajectorySim->setPiece(1);
					// trajectorySim->printBoard();
					Action *heuristicAct = heurAgent->getAction(trajectorySim);
					trajectorySim->playAction(heuristicAct, false);
				}

				actVal += heurAgent->valueBetweenBoards(board, trajectorySim);
				// trajectorySim->printBoard();
			}
			
			//Average over the W K-length trajectories
			actVal /= (float)W;
			// actionSim->printBoard();
			// cout << "PLAY WITH ROW: " << r << " AND COL: " << col << endl;
			// cout << "SCORE: " << actVal << endl << endl;
			// exit(1);
			if (actVal > bestValue) {
				bestValue = actVal;
				foundNewBestAction(bestActions, rot, col);
			} else if (actVal == bestValue) {
				foundTiedAction(bestActions, rot, col);
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

RolloutAgent::~RolloutAgent()
{
	delete heurAgent;
}