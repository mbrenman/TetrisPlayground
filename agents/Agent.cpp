#include "Agent.h"
#include <stdlib.h>
#include <stdio.h>

Agent::Agent()
{
	//Initialize Agent
}

Action Agent::getAction(Tetris *board)
{
	//NULL Action (not playable)
	return Action();
}

Action Agent::pickRandomAction(vector<Action> &actions)
{
	assert(actions.size() > 0);
	
	//Randomly pick an index and get the action
	int actIndex = rand() % actions.size();
	Action a = actions.at(actIndex);

	//Make a copy since all of the values in the vector will be cleaned up
	return Action(a.rotation, a.column);
}

void Agent::clearActionList(vector<Action> &actions)
{
	// for(vector<Action>::iterator it = actions.begin(); it != actions.end(); it++) {
	// 	Action a = (*it);
	// 	delete a;
	// }
	actions.clear();
}

void Agent::foundNewBestAction(vector<Action> &actions, Rotation rot, int col)
{
	clearActionList(actions);
	Action a = Action(rot, col);
	actions.push_back(a);
}

void Agent::foundTiedAction(vector<Action> &actions, Rotation rot, int col)
{
	Action a = Action(rot, col);
	actions.push_back(a);
}

Agent::~Agent()
{}
