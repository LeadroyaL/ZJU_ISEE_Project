#include "eightpuzzle.hpp"
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using std::random_shuffle;
using namespace std;
/* Your A* search implementation for 8 puzzle problem
NOTICE:
1. iniState.state is a 3x3 matrix, the "space" is indicated as -1, for example
	1 2 -1              1 2
	3 4 5   stands for  3 4 5
	6 7 8               6 7 8
2. moves contains directions that transform initial state to final state. Here
	0 stands for up
	1 stands for down
	2 stands for left
	3 stands for right
   There might be several ways to understand "moving up/down/left/right". Here we define
   that "moving up" means to move other numbers up, not move "space" up. For example
	1 2 -1              1 2 5
	3 4 5   move up =>  3 4 -1
	6 7 8               6 7 8
   This definition is actually consistent with where your finger moves to
	when you are playing 8 puzzle game.
	Your code start here
*/
int g_mat_v2[9][9] = {
	{0,1,2,1,2,3,2,3,4},
	{1,0,1,2,1,2,3,2,3},
	{2,1,0,3,2,1,4,3,2},
	{1,2,3,0,1,2,1,2,3},
	{2,1,2,1,0,1,2,1,2},
	{3,2,1,2,1,0,3,2,1},
	{2,3,4,1,2,3,0,1,2},
	{3,2,3,2,1,2,1,0,1},
	{4,3,2,3,2,1,2,1,0}
};
double g_mat_v3[9][9] = {
	{ 0,1,2,1,1.414,2.236,2,2.236,2.828},
	{ 1,0,1,1.414,1,1.414,2.236,2,2.236 },
	{ 2,1,0,2.236,1.414,1,2.828,2.236,2 },
	{ 1,1.414,2.236,0,1,2,1,1.414,2.236 },
	{ 1.414,1,1.414,1,0,1,1.414,1,1.414 },
	{ 2.236,1.414,1,2,1,0,2.236,1.414,1 },
	{ 2,2.236,2.828,1,1.414,2.236,0,1,2 },
	{ 2.236,2,2.236,1.414,1,1.414,1,0,1 },
	{ 2.828,2.236,2,2.236,1.414,1,2,1,0 }
};
EightPuzzleState* current;
EightPuzzleState* startPos;
EightPuzzleState* successors[4];

void AStarSearchFor8Puzzle(EightPuzzleState& iniState, vector<int>& moves)
{
	priority_queue<EightPuzzleState*, vector<EightPuzzleState*>, cmpLarge> openlist;
	priority_queue<EightPuzzleState*, vector<EightPuzzleState*>, cmpLarge> store_openlist;
	vector<EightPuzzleState*> closelist;
	int success_count;
	int loop_c = 0;
	openlist.push(&iniState);
	startPos = &iniState;
	void reverse_moves(vector<int>& moves);
	while (!openlist.empty())
	{
		loop_c++;
		if (loop_c % 10 == 0)
		cout << "next Round!" << loop_c << endl;
		// get game state
		current = openlist.top();
		//check success and return
		if (checkFinalState(current)) {
			////???????????? return the int moves[]
			reverse_moves(moves);
			cout << "Yeah!!Success!" << endl;
			return;
		}
		openlist.pop();
		closelist.push_back(current);
		//annouce and create getSuccessors function
		int getSuccessors(EightPuzzleState*);
		success_count = getSuccessors(current);
		for (int i = 0; i < success_count; i++)
		{
			//whether in closelist
			bool flag = true;
			for (unsigned j = 0; j < closelist.size(); j++)
				if (closelist[j] == successors[i])
				{
					flag = false;
					break;
				}
			if (!flag) continue;

			//whether in openlist
			flag = true;
			while (!openlist.empty())
			{
				EightPuzzleState* tp;
				store_openlist.push(openlist.top());
				tp = openlist.top();
				openlist.pop();
				if (tp->state == successors[i]->state)
				{
					flag = false;
					break;
				}
			}
			//resume openlist
			while (!store_openlist.empty()) {
				openlist.push(store_openlist.top());
				store_openlist.pop();
			}
			//not in openlist
			if (flag) {
				openlist.push(successors[i]);
			}
			//in openlist
			else {
				if (successors[i]->g <= current->g)
					openlist.push(successors[i]);
			}
		}
	}
}

int getSuccessors(EightPuzzleState* current) {
	int calc_h(EightPuzzleState* state);
	int calc_h_v2(EightPuzzleState* state);
	double calc_h_v3(EightPuzzleState* state);
	int r_1, r_2, c_1, c_2;
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (checkMove(current, i, r_1, c_1, r_2, c_2))
		{
			EightPuzzleState* tp = (EightPuzzleState*)malloc(sizeof(EightPuzzleState));
			successors[count] = tp;
			count++;
			tp->preState = current;
			tp->preMove = i;
			for (int j = 0; j < 3; j++)
				for (int k = 0; k < 3; k++)
					tp->state[j][k] = current->state[j][k];
			tp->state[r_1][c_1] = tp->state[r_2][c_2];
			tp->state[r_2][c_2] = -1;
			tp->g = current->g + 1;
			tp->h = calc_h_v2(tp);
		}
		else
			continue;
	}
	return count;
}

int calc_h(EightPuzzleState* state) {
	int value = 0;
	for (int j = 0; j < 3; j++)
		for (int k = 0; k < 3; k++)
			value += state->state[j][k] != (j * 3 + k + 1);
	value -= state->state[2][2] == -1;
	return value;
}

int calc_h_v2(EightPuzzleState* state) {
	int value = 0;
	for (int j = 0; j < 3; j++)
		for (int k = 0; k < 3; k++)
			//value += state->state[j][k] != (j * 3 + k + 1);
			if (state->state[j][k]>0)
				value += g_mat_v2[state->state[j][k] - 1][j * 3 + k];
	return value;
}

double calc_h_v3(EightPuzzleState* state) {
	double value = 0;
	for (int j = 0; j < 3; j++)
		for (int k = 0; k < 3; k++)
			//value += state->state[j][k] != (j * 3 + k + 1);
			if (state->state[j][k]>0)
				value += g_mat_v2[state->state[j][k] - 1][j * 3 + k];
	return value;
}
void reverse_moves(vector<int>& moves){
	EightPuzzleState* p;
	p = current;
	while(*p!=*startPos)
	{
		moves.insert(moves.begin(), p->preMove);
		//moves.push_back(p->preMove);
		p = p->preState;
	}
	return;
}
// You may need the following code, but you may not revise it

/* Play 8 puzzle game according to "moves" and translate state from "iniState" to  "resultState"
   This function is used to check your AStarSearchFor8Puzzle implementation.
   It will return a state to indicate whether the vector moves will lead the final state.
   return 1 means moves are correct!
   return -1 means moves can not turn iniState to final state
   return -2 means moves violate game rule, see runOneMove();
   You should not revise this function.
*/
int runMoves(const EightPuzzleState* iniState, const vector<int>& moves)
{
	if (moves.size() == 0)
	{
		return -1;
	}
	//memcpy(&resultState[0][0], &iniState[0][0], sizeof(*iniState));
	EightPuzzleState currentState = *iniState;
	EightPuzzleState nextState;
	for (int i = 0; i < (int)moves.size(); ++i)
	{
		if (!runOneMove(&currentState, &nextState, moves[i]))
		{
			return -2;
		}
		currentState = nextState;
	}
	if (checkFinalState(&nextState))
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

bool checkMove(const EightPuzzleState* state, const int move,
	int& r_1, int& c_1, int& r_1_move, int& c_1_move)
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (state->state[r][c] == -1)
			{
				r_1 = r;
				c_1 = c;
			}
		}
	}

	switch (move)
	{
		//up
	case 0:
		r_1_move = r_1 + 1;
		c_1_move = c_1;
		break;
		//down
	case 1:
		r_1_move = r_1 - 1;
		c_1_move = c_1;
		break;
		//left
	case 2:
		c_1_move = c_1 + 1;
		r_1_move = r_1;
		break;
		//right
	case 3:
		c_1_move = c_1 - 1;
		r_1_move = r_1;
	}

	// if move out of boundary
	if (r_1_move < 0 || r_1_move > 2 || c_1_move < 0 || c_1_move > 2)
	{
		return false;
	}
	return true;
}

bool runOneMove(EightPuzzleState* preState, EightPuzzleState* nextState, const int move)
{
	// find the position of -1
	int r_1, c_1, r_1_move, c_1_move;
	*nextState = *preState;
	bool flag = checkMove(nextState, move, r_1, c_1, r_1_move, c_1_move);

	// if move out of boundary
	if (r_1_move < 0 || r_1_move > 2 || c_1_move < 0 || c_1_move > 2)
	{
		return false;
	}
	int v = nextState->state[r_1_move][c_1_move];
	nextState->state[r_1][c_1] = v;
	nextState->state[r_1_move][c_1_move] = -1;
	nextState->preState = preState;
	nextState->preMove = move;
	return true;
}

bool checkFinalState(const EightPuzzleState* resultState)
{
	const int finalState[3][3] = { {1,2,3},{4,5,6},{7,8,-1} };

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (finalState[i][j] != resultState->state[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

void generateState(EightPuzzleState* state, int nMoves)
{
	EightPuzzleState finalState;
	for (int i = 1; i < 10; ++i)
	{
		finalState.state[(i - 1) / 3][(i - 1) % 3] = i;
	}
	finalState.state[2][2] = -1;
	EightPuzzleState preState, nextState;
	preState = finalState;
	srand((int)time(0));
	for (int i = 0; i < nMoves; ++i)
	{
		int rdmove = rand() % 4;
		runOneMove(&preState, &nextState, rdmove);
		preState = nextState;
	}
	*state = nextState;
}

void printMoves(EightPuzzleState* state, vector<int>& moves)
{
	cout << "Initial state " << endl;
	printState(state);
	EightPuzzleState preState, nextState;
	preState = *state;
	for (int i = 0; i < (int)moves.size(); ++i)
	{
		switch (moves[i])
		{
		case 0:
			cout << " The " << i << "-th move goes up" << endl;
			break;
		case 1:
			cout << " The " << i << "-th move goes down" << endl;
			break;
		case 2:
			cout << " The " << i << "-th move goes left" << endl;
			break;
		case 3:
			cout << " The " << i << "-th move goes right" << endl;
		}

		runOneMove(&preState, &nextState, moves[i]);
		printState(&nextState);
		preState = nextState;
	}
}

void printState(EightPuzzleState* state)
{

	for (int i = 0; i < 3; ++i)
	{
		cout << state->state[i][0] << " " << state->state[i][1] << " " << state->state[i][2] << endl;
	}
	cout << "---------------" << endl;
}
