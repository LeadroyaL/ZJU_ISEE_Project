#ifndef __TIC_TAC_TOE__
#define __TIC_TAC_TOE__
#include <vector>
#include <iostream>

using namespace std;
/* =============ReadMe==============
	You will write a tic tac toc player and play game with this computer player.
	You will use MiniMaxSearch with depth limited strategy. For simplicity, Alpha-Beta Pruning
	is not considered.
	Let's make some assumptions.
	1. The computer player use circle and you use cross.
	2. The computer player is MAX user and you are MIN user.
	3. The miniMaxSearch depth is 3, so that the computer predict one step further. It first
	predicts what you will do if it makes a move and choose a move that maximize its gain.
	4. You play first
*/

struct TicTacToeState
{
	int state[3][3]; // 1 stands for circle, -1 stands for cross, 0 stands for empty space
	TicTacToeState()
	{
		for (int i = 0; i < 9; ++i)
		{
			state[i/3][i%3] = 0;
		}
	}
};

struct Action
{
	int row, col;
	Action()
	{
		row = -1;
		col = -1;
	}
	Action(int r, int c)
	{
		row = r;
		col = c;
	}
};

/*	Search the next step by MinMaxSearch with depth limited strategy.
	currentState is the current state of the game, see structure TicTacToeState for more details.
		WARNING: The search depth is limited to 3, computer uses circles(1).
	r and c are returned row and column index that computer player will draw a circle on. 0<=r<=2, 0<=c<=2
	Your code starts here
*/
void miniMaxSearchForTicTacToe(const TicTacToeState& currentState, int& r, int& c);




// Do not care about the following code.
class GameJudge{
public:

	GameJudge();

	void makeAMove(const int& r, const int& c, const int player);	//player = 1 for computer, play = -1 for human

	/*	Return game status
		1 for computer wins
		-1 for human wins
		0 for draw
		2 in the play
	*/
	int checkGameStatus();
	void humanInput(int& r, int& c);
	void printStatus(const int player, const int status);
	TicTacToeState getGameStatus();
private:
	TicTacToeState gameState;
};

#endif