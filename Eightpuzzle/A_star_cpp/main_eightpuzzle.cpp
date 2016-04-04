#include "eightpuzzle.hpp"
#include <vector>
#include <iostream>
using namespace std;
int main()
{

	EightPuzzleState iniState;
	generateState(&iniState,150); // randomly generate a initial state, the second variable indicates how 
								// far the initial state is from final state, for debugging, choose 10.
								// For testing, you may choose 50 - 150. 
	vector<int> moves;
	AStarSearchFor8Puzzle(iniState, moves);
	//-----output the w/a/s/d route to debug
	//for (int i = 0; i < moves.size(); i++)
	//	switch (moves[i])
	//	{
	//	case 0: cout << "w" << ' '; break;
	//	case 1: cout << "s" << ' '; break;
	//	case 2: cout << "a" << ' '; break;
	//	case 3: cout << "d" << ' '; break;
	//	}
	int status = runMoves(&iniState, moves);
	switch (status)
	{
	case 1:
		cout << " Your solution is correct ! " << endl;
		break;
	case -1:
		cout << " Your solution can not turn initial state to final state !" << endl;
		break;
	case -2:
		cout << " Your solution violates game rule (move blocks out of boundary)!";
	}
	printMoves(&iniState, moves);
	getchar();
}