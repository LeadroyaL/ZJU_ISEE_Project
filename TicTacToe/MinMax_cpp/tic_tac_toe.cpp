#include "tic_tac_toe.hpp"
#include "iostream"
#include "string"
#include <vector>
using namespace std;

/*	Search the next step by MinMaxSearch with depth limited strategy.
	currentState is the current state of the game, see structure TicTacToeState for more details.
		WARNING: The search depth is limited to 3, computer uses circles(1).
	r and c are returned row and column index that computer player will draw a circle on. 0<=r<=2, 0<=c<=2
	Your code starts here
*/

void getAssumeState(TicTacToeState state, vector<Action> actions, vector<TicTacToeState>& finalState, int player);
void H_MINIMAX(TicTacToeState currentState, int player, int depth, int& r, int& c);
void getAvailableActions(TicTacToeState currentState, vector<Action>& actions);
int evaluate(TicTacToeState state);
int calc_V(vector<TicTacToeState> state, int depth, int player);

void miniMaxSearchForTicTacToe(const TicTacToeState& currentState, int& r, int& c)
{

	vector<Action> actions;
	vector<TicTacToeState> assum_state;
	vector<TicTacToeState> tp_vector;
	//get every action
	getAvailableActions(currentState, actions);
	getAssumeState(currentState, actions, assum_state,1);
	//actions--->assume_state, pairs
	int very_action_index, very_value = -999;

	for (int i = 0; i < assum_state.size(); i++)
	{
		//???? memory rubbish
		tp_vector.clear();
		tp_vector.push_back(assum_state[i]);
		int tp = calc_V(tp_vector, 2, -1);
		//tp always -50
		//should be -100 0 -100 -100 -100 -100
		//cout << tp << "  ";
		if (very_value < tp)
		{
			very_value = tp;
			very_action_index = i;
		}
	}
	Action final_action = actions[actions.size() -1 - very_action_index];
	very_value;
	r = final_action.row;
	c = final_action.col;
}

int calc_V(vector<TicTacToeState> state, int depth, int player) {
	vector<int> very;
	if (depth == 0)
		for (int i = 0; i < state.size(); i++)
			very.push_back(evaluate(state[i]));
	else {
		vector<Action> actions;
		vector<TicTacToeState> assum_state;
		TicTacToeState tp_state;
		// state is all want to judge condition

		for (int i = 0; i < state.size(); i++)
		{
			//player
			getAvailableActions(state[i], actions);
			getAssumeState(state[i], actions, assum_state, player);
			very.push_back(calc_V(assum_state, depth - 1, -player));
		}
	}

	int r_value = very[0];
	//reverse  12:04
	if (player == -1) {
		//return max
		for (int ii = 0; ii < very.size(); ii++)
			if (r_value < very[ii])
				r_value = very[ii];
	}
	else {
		//return min
		for (int ii = 0; ii < very.size(); ii++)
			if (r_value > very[ii])
				r_value = very[ii];
	}
	return r_value;

}

int evaluate(TicTacToeState state) {
	//pre dealing
	int a[8] = { 0,0,0,0,0,0,0,0 };
	int player = 0;
	//012 for --  345 for ||  67forX
	for (int i = 0; i < 3; i++)
	{
		a[0] += state.state[0][i];
		a[1] += state.state[1][i];
		a[2] += state.state[2][i];
		a[3] += state.state[i][0];
		a[4] += state.state[i][1];
		a[5] += state.state[i][2];
		//a[0] += state.state[i][0];
		//a[1] += state.state[i][1];
		//a[2] += state.state[i][2];
		//a[3] += state.state[0][i];
		//a[4] += state.state[1][i];
		//a[5] += state.state[2][i];
		a[6] += state.state[i][i];
		a[7] += state.state[i][2 - i];
	}

	//judge kill
	for (int i = 0; i < 9; i++)
		if (a[i] == -3) return -100;
		else if (a[i] == 3) return 100;
		else;

		//player 1--AI turn  0--human turn
		for (int i = 0; i < 9; i++)
			player += state.state[i / 3][i % 3];

		//first kill then be kill then KO then be KO
		if (player == -1)
			//AI turn, -2 is very danger
		{
			for (int i = 0; i < 9; i++)
				if (a[i] == 2) return 50;
			for (int i = 0; i < 9; i++)
				if (a[i] == -2) return -50;
			//judge KO
			for (int i = 0; i < 3; i++)
				for (int j = 3; j < 6; j++)
					if (a[i] == 2 && a[j] == 2)
						if (state.state[i][j - 3] != 1)
							return 50;
			for (int i = 0; i < 5; i++)
				for (int j = 6; j < 7; j++)
				{
					if (a[i] == 2 && a[j] == 2)
						if (j == 6)
							if (state.state[i % 3][i % 3] == 2)
								return 50;
							else;
						else if (j == 7)
							if (state.state[(2 - i + 3) % 3][i % 3] == 2)
								return 50;
							else;
						else;
					else;
				}
			return 0;
		}
		else {
			for (int i = 0; i < 9; i++)
				if (a[i] == -2) return -50;
			for (int i = 0; i < 9; i++)
				if (a[i] == 2) return 50;
			//judge KO
			for (int i = 0; i < 3; i++)
				for (int j = 3; j < 6; j++)
					if (a[i] == -2 && a[j] == -2)
						if (state.state[i][j - 3] != -1)
							return -50;
			for (int i = 0; i < 5; i++)
				for (int j = 6; j < 7; j++)
				{
					if (a[i] == 2 && a[j] == 2)
						if (j == 6)
							if (state.state[i % 3][i % 3] == -2)
								return -50;
							else;
						else if (j == 7)
							if (state.state[(2 - i + 3) % 3][i % 3] == -2)
								return -50;
							else;
						else;
					else;
				}
			return 0;
		}

		return 0;
}

void getAvailableActions(TicTacToeState currentState, vector<Action>& actions) {
	actions.clear();
	int chess_count = 0;
	int a[8] = { 0,0,0,0,0,0,0,0 };
	for (int i = 0; i < 3;i++)
		for (int j = 0; j < 3; j++)
			if (currentState.state[i][j] == 0) {
				Action* _new = (Action*)malloc(sizeof(Action));
				_new->row = i; _new->col = j;
				actions.push_back(*_new);
			}
			else
				chess_count++;
	for (int i = 0; i < 3; i++)
	{
		a[0] += currentState.state[0][i];
		a[1] += currentState.state[1][i];
		a[2] += currentState.state[2][i];
		a[3] += currentState.state[i][0];
		a[4] += currentState.state[i][1];
		a[5] += currentState.state[i][2];
		a[6] += currentState.state[i][i];
		a[7] += currentState.state[i][2 - i];
	}
	for (int i = 0; i < 8; i++)
		if (fabs(a[i]) == 3) {
			actions.clear();
			return;
		}
	if (chess_count==1){
		actions.clear();
		Action* _new = (Action*)malloc(sizeof(Action));
		if (currentState.state[1][1] == 0)
		{
			_new->row = 1; _new->col = 1;
		}
		else {
			_new->row = 0; _new->col = 0;
		}
		actions.push_back(*_new);
	}
}
void H_MINIMAX(TicTacToeState currentState, int player, int depth, int& r, int& c) {
	vector<Action> actions;
	if (depth == 0)
		return;
	else
	{
		depth--;
		player = -player;
		getAvailableActions(currentState, actions);
		if(player==1)
		{
			//get MAX for AI
						
		}
		else
		{ 
			//get MIN for human
		}
	}
}

void getAssumeState(TicTacToeState state, vector<Action> actions, vector<TicTacToeState>& finalState, int player)
{
	finalState.clear();
	for (int i = actions.size() - 1; i >= 0; i--)
	{
		TicTacToeState* p = (TicTacToeState*)malloc(sizeof(TicTacToeState));
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
			{
				p->state[j][k] = state.state[j][k];
			}
		p->state[actions[i].row][actions[i].col] = player;
		finalState.push_back(*p);
	}
	if (actions.size() == 0)
	{
		TicTacToeState* p = (TicTacToeState*)malloc(sizeof(TicTacToeState));
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				p->state[j][k] = state.state[j][k];
		finalState.push_back(*p);
	}

}

// You do not need the following code and do not revise it.
GameJudge::GameJudge()
{
	this->gameState = TicTacToeState();
}

void GameJudge::makeAMove(const int& r, const int& c, const int player)
{
	//player = 1 for computer, play = -1 for human
	//1 stands for circle, -1 stands for cross, 0 stands for empty space
	// computer uses circle, human uses cross
	this->gameState.state[r][c] = player;
}

/*	Return game status
	1 for computer wins
	-1 for human wins
	0 for draw
	2 in the play
*/
int GameJudge::checkGameStatus()
{



	// somebody wins
	for (int r = 0; r < 3; r++)
	{
		int sum_row = this->gameState.state[r][0] +
			this->gameState.state[r][1]+ this->gameState.state[r][2];
		if (sum_row == 3)
		{
			return 1;
		}
		if (sum_row == -3)
		{
			return -1;
		}
	}
	for (int c = 0; c < 3; c++)
	{
		int sum_col = this->gameState.state[0][c] +
			this->gameState.state[1][c]+ this->gameState.state[2][c];
		if (sum_col == 3)
		{
			return 1;
		}
		if (sum_col == -3)
		{
			return -1;
		}
	}
	int sum_diag = this->gameState.state[0][0] +
		this->gameState.state[1][1]+this->gameState.state[2][2];
	if (sum_diag == 3)
	{
		return 1;
	}
	if (sum_diag == -3)
	{
		return -1;
	}
	sum_diag = this->gameState.state[0][2] +
		this->gameState.state[1][1]+this->gameState.state[2][0];
	if (sum_diag == 3)
	{
		return 1;
	}
	if (sum_diag == -3)
	{
		return -1;
	}
	// All spaces are occupied but nobody wins
	int numSpaces = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; j++)
		{
			if (this->gameState.state[i][j] == 0)
			{
				numSpaces ++;
			}
		}
	}
	if (numSpaces == 0)
	{
		return 0;
	}
	// in the play
	return 2;
}

void GameJudge::humanInput(int& r, int& c)
{
	cout << "Input the row and column index of your move " << endl;
	cout << "1,0 means draw a cross on the row 1, col 0" << endl;
	string str;
	bool succ = false;
	while(!succ)
	{
		cin >> str;
		sscanf(str.c_str(), "%d,%d", &r, &c);
		if (r < 0 || r > 2 || c < 0 || c > 2)
		{
			succ = false;
			cout << " Invalidate input, the two numbers should >> 0 and << 2" << endl;
		}
		else if (this->gameState.state[r][c] != 0)
		{
			succ = false;
			cout << " You can not put cross on this place " << endl;
		}
		else
		{
			succ = true;
		}
	}
}

void GameJudge::printStatus(const int player, const int status)
{
	cout << "------------------------------" << endl;
	for (int r= 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (this->gameState.state[r][c] == 1)
			{
				cout << "[O]";
			}
			if (this->gameState.state[r][c] == -1)
			{
				cout << "[X]";
			}
			else if(this->gameState.state[r][c] == 0)
			{
				cout << "[ ]";
			}

		}
		cout << endl;
	}
	if (player == 1)
	{
		cout << "Last move was conducted by computer " << endl;
	}
	else if (player == -1)
	{
		cout << "Last move was conducted by you " << endl;
	}
	if (status == 1)
	{
		cout << "Computer wins " << endl;
	}
	else if (status == -1)
	{
		cout << " You win " << endl;
	}
	else if (status == 2)
	{
		cout << " Game going on " << endl;
	}
	else if (status == 0)
	{
		cout << " Draw " << endl;
	}
}
TicTacToeState GameJudge::getGameStatus()
{
	return this->gameState;
}