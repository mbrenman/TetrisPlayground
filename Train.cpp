#include <iostream>
#include "Tetris.h"
#include "Piece.h"
#include "Agent.h"
#include "RandomAgent.h"
#include "RolloutAgent.h"
#include "HeuristicAgent.h"
#include "NextPieceAgent.h"
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>

using namespace std;

const int NUM_GAMES = 5;
const int POPULATION_SIZE = 10;
const int NUM_GENERATIONS = 3;
const double MUTATION_RATE = 0.02;
const int RAND_NEW = 15;

//TODO: Diversity criterion?

struct playerWithScore
{
	playerWithScore() : player(NULL), score(-1) {};
	playerWithScore(HeuristicAgent *p, double s, int t) : player(p), score(s), numTrials(t) {};
	void addMoreTrials(double s, int num) {
		score = ((double)(numTrials)/(double)(numTrials + num)) * score
			  + ((double)(num)/(double)(numTrials + num)) 		* s;
		numTrials += num;
	};
	HeuristicAgent *player;
	double score;
	int numTrials;
};

HeuristicAgent *randomPlayer();
playerWithScore *randomPopulation();
void printPopulationData(playerWithScore population[POPULATION_SIZE]);
void evolvePopulation(playerWithScore *population);
HeuristicAgent *getCrossoverPlayer(playerWithScore population[POPULATION_SIZE]);
HeuristicAgent *getMutatedPlayer(playerWithScore population[POPULATION_SIZE]);
HeuristicAgent *randomMutatedPlayer(playerWithScore population[POPULATION_SIZE]);
void mutateWeights(double weights[NUM_WEIGHTS]);
double evaluatePlayer(Agent *player);
void playGame(Tetris *board, Agent *player, bool animated);
double randomNegOneToOne();
int playerComp(const void *a, const void *b);

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	//Create Simulator with an empty board -- official game
	Tetris *board = new Tetris(true);

	//Create a population
	playerWithScore *population = randomPopulation();

	cout << "Initial Population: " << endl;
	printPopulationData(population);

	for (int i = 0; i < NUM_GENERATIONS; i++) {
		evolvePopulation(population);
		cout << "Generation " << (i + 1) << ": " << endl;
		printPopulationData(population);
	}

	cout << "\n\nPress Enter to see best agent play!\n\n";
	cin.get();

	//Create Agent -- first in list is best
	Agent *player = population[0].player;

	double score = evaluatePlayer(player);

	playGame(board, player, true);

	cout << "Avg score: " << score << endl;
	cout << "With weights: [";
	double *weights = ((HeuristicAgent *)player)->weights;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		cout << weights[i];
		if (i < NUM_WEIGHTS - 1) {
			cout << ", ";
		}
	}
	cout << "]" << endl;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		delete population[i].player;
	}

	delete[] population;
	delete board;	
	return 0;
}

void printPopulationData(playerWithScore population[POPULATION_SIZE])
{
	qsort(population, POPULATION_SIZE, sizeof(population[0]), &playerComp);
	for (int i = 0; i < POPULATION_SIZE; i++) {
		cout << setw(10) << setprecision(6) << population[i].score;
		cout << setw(10) << setprecision(6) << population[i].numTrials;
		
		double *weights = ((HeuristicAgent *)population[i].player)->weights;
		cout << "   [";
		for (int i = 0; i < NUM_WEIGHTS; i++) {
			cout << setw(10) << setprecision(4) << weights[i];
			if (i < NUM_WEIGHTS - 1) {
				cout << ", ";
			}
		}
		cout << "]" << endl;
	}
}

void evolvePopulation(playerWithScore population[POPULATION_SIZE])
{
	cout << "EVOLUTION" << endl;
	//Naive approach is take the top pop_size / 2 -- should change later

	//Sort the population according to avg score
	qsort(population, POPULATION_SIZE, sizeof(population[0]), &playerComp);

	//Reevaluate the better half
	for (int i = 0; i < POPULATION_SIZE / 2; i++) {
		HeuristicAgent *player = population[i].player;
		double score = evaluatePlayer(player);
		population[i].addMoreTrials(score, NUM_GAMES);
	}

	//Replace the worse half
	for (int i = POPULATION_SIZE / 2; i < POPULATION_SIZE; i++) {
		delete population[i].player;
		population[i].player = NULL;

		HeuristicAgent *player;

		bool randNew = rand() % 100 < RAND_NEW;
		if (randNew) {
			player = randomMutatedPlayer(population);
			cout << "RAND" << endl;
		} else {
			//Randomly either mutate or crossover
			bool mutate = rand() % 2; //0 or 1

			if (mutate) {
				player = getMutatedPlayer(population);
			} else {
				player = getCrossoverPlayer(population);
			}
		}

		//Evaluate and save the new player
		double score = evaluatePlayer(player);
		population[i] = playerWithScore(player, score, NUM_GAMES);
	}
}

HeuristicAgent *getMutatedPlayer(playerWithScore population[POPULATION_SIZE])
{
	//Pick a random player
	int playerIndex = rand() % (POPULATION_SIZE / 2);
	HeuristicAgent *toMutate = population[playerIndex].player;

	//Mutate their weights
	double *weights = toMutate->weights;
	mutateWeights(weights);

	//Make the new agent with the updated weights
	return new HeuristicAgent(weights);	
}

HeuristicAgent *randomMutatedPlayer(playerWithScore population[POPULATION_SIZE])
{
	//Pick a random player
	int playerIndex = rand() % (POPULATION_SIZE / 2);
	HeuristicAgent *toMutate = population[playerIndex].player;

	//Randomly change some weights to random numbers
	double *weights = toMutate->weights;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		bool change = rand() % 2; //0 or 1
		if (change) {
			weights[i] = randomNegOneToOne();
		}
	}

	//Make the new agent with the updated weights
	return new HeuristicAgent(weights);	
}

HeuristicAgent *getCrossoverPlayer(playerWithScore population[POPULATION_SIZE])
{
	double weights[NUM_WEIGHTS];
	
	//Pick two random surviving players
	int firstParentInd = rand() % (POPULATION_SIZE / 2);
	HeuristicAgent *parent1 = population[firstParentInd].player;
	int secondParentInd = rand() % (POPULATION_SIZE / 2);
	HeuristicAgent *parent2 = population[secondParentInd].player;
	
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		//Randomly pick each weight between the two parents
		bool fromFirstParent = rand() % 2; //0 or 1
		if (fromFirstParent) {
			weights[i] = parent1->weights[i];
		} else {
			weights[i] = parent2->weights[i];
		}
	}

	//Make the new agent with the updated weights
	return new HeuristicAgent(weights);	
}

void mutateWeights(double weights[NUM_WEIGHTS])
{
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		double maxChange = weights[i] * MUTATION_RATE;

		//Find the amount that it will change (up or down MUTATION_RATE percent)
		double realChange = maxChange * randomNegOneToOne();

		weights[i] += realChange;
	}
}

playerWithScore *randomPopulation()
{
	playerWithScore *population = new playerWithScore[POPULATION_SIZE];
	for (int i = 0; i < POPULATION_SIZE; i++) {
		HeuristicAgent *player = randomPlayer();
		double score = evaluatePlayer(player);
		population[i] = playerWithScore(player, score, NUM_GAMES);
	}
	return population;
}

HeuristicAgent *randomPlayer()
{
	//Create agent
	double weights[NUM_WEIGHTS];
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		weights[i] = randomNegOneToOne();
	}

	return new HeuristicAgent(weights);
}

double evaluatePlayer(Agent *player)
{
	int totalLines = 0;

	//Play some games
	for (int i = 0; i < NUM_GAMES; i++) {
		//Create Simulator with an empty board -- official game
		Tetris *board = new Tetris(true);
	
		playGame(board, player, false);
		// cout << "Finished with #lines: " << board->getLinesCleared() << endl;

		totalLines += board->getLinesCleared();

		delete board;
	}

	return (double)totalLines / (double)NUM_GAMES;
}

void playGame(Tetris *board, Agent *player, bool animated)
{
	//Game loop
	while (!board->isLost()) {
		//Get action from the agent
		Action a = player->getAction(board);

		//Peform the action
		board->playAction(a, animated);
	}

	if (animated) {
		board->printBoard();
		cout << "Finished with #lines: " << board->getLinesCleared() << endl;
	}
}

double randomNegOneToOne()
{
	return (2 * (rand() / double(RAND_MAX)) - 1);
}

int playerComp(const void *a, const void *b)
{
	playerWithScore pa = *(playerWithScore *)a;
	playerWithScore pb = *(playerWithScore *)b;
	
	if (pb.score > pa.score) {
		return 1;
	} else if (pb.score < pa.score) {
		return -1;
	}
	return 0;
}
