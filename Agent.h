#ifndef __TetrisAgent__
#define __TetrisAgent__

#include "Constants.h"
#include "Tetris.h"
#include "Action.h"
#include <vector>
#include <assert.h>

using namespace std;

class Agent {
	public:
		Agent();
		virtual Action* getAction(Tetris *board);
	protected:
		Action* pickRandomAction(vector<Action*> &actions);
		void clearActionList(vector<Action*> &actions);
		void foundNewBestAction(vector<Action*> &actions, Rotation rot, int col);
		void foundTiedAction(vector<Action*> &actions, Rotation rot, int col);	
};

#endif