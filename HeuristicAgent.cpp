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
	vector<Action *> bestActions = getBestActions(board);;

	//Choose the best action
	Action *a = pickRandomAction(bestActions);

	//Play the action
	return a;
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
			int prevHoles      = holesInBoard(sim);
			int prevBlocked    = topDownBlocked(sim);
			int prevAggBlocked = aggregateTopDownBlocked(sim);

			//Play the action
			sim->playAction(a, false);

			//Observe new stats
			int linesCleared    = sim->getLinesCleared() - prevLines;
			int heightGain      = prevHeight - sim->maxBoardHeight();
			int newHoles        = holesInBoard(sim) - prevHoles;
			int topBlocked      = topDownBlocked(sim) - prevBlocked;
			int aggTopBlocked   = aggregateTopDownBlocked(sim) - prevAggBlocked;
			bool lost		    = sim->isLost();

			return valueOfAction(linesCleared, heightGain, newHoles, topBlocked, aggTopBlocked, lost);
}

float HeuristicAgent::valueBetweenBoards(Tetris *board1, Tetris *board2)
{
	int linesCleared    = board2->getLinesCleared() - board1->getLinesCleared();
	int heightGain      = board1->maxBoardHeight() - board2->maxBoardHeight();
	int newHoles        = holesInBoard(board2) - holesInBoard(board1);
	int topBlocked      = topDownBlocked(board2) - topDownBlocked(board1);
	int aggTopBlocked   = aggregateTopDownBlocked(board2) - aggregateTopDownBlocked(board1);
	bool lost		    = board2->isLost();

	return valueOfAction(linesCleared, heightGain, newHoles, topBlocked, aggTopBlocked, lost);
}

float HeuristicAgent::valueOfAction(int linesCleared, int heightGain, int newHoles, int topDownBlocked, int aggTopBlocked, bool lost)
{
	if (lost) {
		return -100000;
	} else {
		return (weights[0] * linesCleared) + (weights[1] * newHoles) + (weights[2] * topDownBlocked) + (weights[3] * aggTopBlocked) + (weights[4] * heightGain);
	}
}

// Measurement Heuristics
int HeuristicAgent::holesInBoard(Tetris *board)
{
	int boardCopy[TETRIS_COLS][TETRIS_ROWS];
	board->copyBoard(boardCopy);

	for (int x = 0; x < TETRIS_COLS; x++) {
		//Try filling at all of the top spots in case one is blocked
		fillReachableBlanks(x, 0, boardCopy);
	}
	return countBlanks(boardCopy);
}

void HeuristicAgent::fillReachableBlanks(int x, int y, int boardCopy[TETRIS_COLS][TETRIS_ROWS])
{
	//Make sure that we're on the board
	if (x >= 0 && x < TETRIS_COLS && y >= 0 && y < TETRIS_ROWS) {
		//Only change and recurse on empty spaces
		if (boardCopy[x][y] == EMPTY_SPACE) {
			boardCopy[x][y] = RESERVED;
			fillReachableBlanks(x + 1, y, boardCopy);
			fillReachableBlanks(x - 1, y, boardCopy);
			fillReachableBlanks(x, y + 1, boardCopy);
			fillReachableBlanks(x, y - 1, boardCopy);
		}
	}
}

int HeuristicAgent::countBlanks(int boardCopy[TETRIS_COLS][TETRIS_ROWS])
{
	int numHoles = 0;
	for (int x = 0; x < TETRIS_COLS; x++) {
		for (int y = 0; y < TETRIS_ROWS; y++) {
			if (boardCopy[x][y] == EMPTY_SPACE) {
				numHoles++;
			}
		}
	}
	return numHoles;
}

int HeuristicAgent::topDownBlocked(Tetris *board)
{
	int boardCopy[TETRIS_COLS][TETRIS_ROWS];
	board->copyBoard(boardCopy);

	fillTopDown(boardCopy);
	return countBlanks(boardCopy);
}

int HeuristicAgent::aggregateTopDownBlocked(Tetris *board)
{
	int boardCopy[TETRIS_COLS][TETRIS_ROWS];
	board->copyBoard(boardCopy);

	int blockCount = 0;

	for (int x = 0; x < TETRIS_COLS; x++) {
		for (int y = 0; y < TETRIS_ROWS; y++) {
			if (boardCopy[x][y] == EMPTY_SPACE) {
				//Go back up, counting how many are blocking this piece
				for (int yprime = y; yprime >= 0; yprime--) {
					if (boardCopy[x][yprime] != EMPTY_SPACE) {
						blockCount++;
					}
				}
			}
		}
	}
	return blockCount;
}

void HeuristicAgent::fillTopDown(int boardCopy[TETRIS_COLS][TETRIS_ROWS])
{
	for (int x = 0; x < TETRIS_COLS; x++) {
		int y = 0;
		//While we're on the board and at an empty space
		while ((x >= 0 && x < TETRIS_COLS && y >= 0 && y < TETRIS_ROWS) && boardCopy[x][y] == EMPTY_SPACE) {
			boardCopy[x][y] = RESERVED;
			y++;
		}
	}
}

HeuristicAgent::~HeuristicAgent()
{
}