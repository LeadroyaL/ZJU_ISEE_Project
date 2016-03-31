#include "tic_tac_toe.hpp"
#include <iostream>

using namespace std;


int main()
{
	GameJudge judge;
	int player = -1; // You move first
	int status = 2; // Game is going on
	judge.printStatus(-2, status);
	while(status == 2)
	{
		// Your turn
		int r_human, c_human;
		judge.humanInput(r_human, c_human);
		judge.makeAMove(r_human, c_human, player);
		status = judge.checkGameStatus();
		judge.printStatus(player, status);
		player *= - 1;
		if (status !=2 )
		{
			break;
		}
		// Computer's turn
		int r_computer, c_computer;
		miniMaxSearchForTicTacToe(judge.getGameStatus(), r_computer, c_computer);
		judge.makeAMove(r_computer, c_computer, player);
		status = judge.checkGameStatus();
		judge.printStatus(player, status);
		player *= - 1;
	}
	getchar();
	getchar();
}