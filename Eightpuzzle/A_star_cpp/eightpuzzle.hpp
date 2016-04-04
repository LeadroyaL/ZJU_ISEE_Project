#ifndef __EIGHTPUZZLE__
#define __EIGHTPUZZLE__

#include<vector>
#include<queue>

using namespace std;

struct EightPuzzleState{
	int state[3][3]; // the 3x3 square state, "blank" is indicated as "-1"
	//int g;double h;  // test for h_v3
	int g, h;	// g is the cost from initial state to this state, h is the value of heuristic function.
	int preMove;	// move trans previous state to this state
	EightPuzzleState* preState;	// Pointer to the father of this state.
	// preMove and preState are used to reverse path.

	bool operator== (EightPuzzleState a){
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				if (a.state[r][c] != state[r][c])
				{
					return false;
				}
			}
		}
		return true;
	}
	bool operator!= (EightPuzzleState a)
	{
		return !(*this == a);
	}
	EightPuzzleState()
	{
		g = 0;
		h = 0;
		preState = NULL;
	}
};

// you don't need to care about this
struct cmpLarge{
	bool operator()(EightPuzzleState* a, EightPuzzleState* b){
		return ((a->g + a->h) > (b->g + b->h)) ;
	}
};


/* Your A* search implementation for 8 puzzle problem
NOTICE:
1. iniState is a 3x3 matrix, the "space" is indicated as -1, for example
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
*/
void AStarSearchFor8Puzzle(EightPuzzleState& iniState, vector<int>& moves);



// You may need the following code, but you may not revise it.

/* Play 8 puzzle game according to "moves" and translate state from "iniState" to  "resultState"
   This function is used to check your AStarSearchFor8Puzzle implementation.
   It will return a state to indicate whether the vector moves will lead the final state.
   return 1 means moves are correct!
   return -1 means moves can not turn iniState to final state
   return -2 means moves violate game rule, see checkMoves();
   You should not revise this function.
*/
int runMoves(const EightPuzzleState* iniState, const vector<int>& moves);

/* Run one move and check whether a move is valid or not. For example, a state like
	1 2 -1
	3 4 5
	6 7 8
	can only move up and right, so move can only be 0 and 3.
	This function return false when the move is not valid. That means your vector of moves
	 violates game rules.
	You should not revise this function.
*/
bool runOneMove(EightPuzzleState* preState, EightPuzzleState* nextState, const int move);

/* Check whether one move is legal
	You should not revise this function.
*/
bool checkMove(const EightPuzzleState* state, const int move,
	int& r_1, int& c_1, int& r_1_move, int& c_1_move);


/* Check whether the resultState is equivalent to the final state
	1 2 3
	4 5 6
	7 8 -1
	It returns true if resultState is the above state.
	You should not revise this function.
*/
bool checkFinalState(const EightPuzzleState* resultState);

/* Randomly generate initial states
	You should not revise this function.
*/
void generateState(EightPuzzleState* state, int nMoves);

/* Print every moves
	You should not revise this function.
*/
void printMoves(EightPuzzleState* state, vector<int>& moves);

/* Print one single move
	You should not revise this function.
*/
void printState(EightPuzzleState* state);
#endif
