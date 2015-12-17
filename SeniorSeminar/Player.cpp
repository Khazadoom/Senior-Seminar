#include <iostream>
#include <string>
#include <array>
#include "Player.h"
#include "Checkers.h"

int currentPlayer;

CheckerHuman::CheckerHuman() {
}

CheckerAI::CheckerAI() {

}

MancalaHuman::MancalaHuman() {

}

MancalaAI::MancalaAI() {

}


MancalaAI::MancalaAI(int turn, int difficulty) {
	currentPlayer = turn;
	MancalaAI::Difficulty = difficulty;
	switch (Difficulty){
	case 1:
		setDepth(4);
		break;
	case 2:
		setDepth(10);
		break;
	case 3:
		setDepth(10);
		break;
	case 4:
		setDepth(20);
		break;
	}
}

void MancalaAI::setDepth(int depth) {
	MancalaAI::currentDepth = depth;
}


CheckerHuman::CheckerHuman(int Turn) {

	currentPlayer = Turn;
}

void CheckerAI::setDepth(int depth) {
	CheckerAI::currentDepth = depth;
}



CheckerAI::CheckerAI(int Turn, int challenge) {
	currentPlayer = Turn;
	CheckerAI::Difficulty = challenge;
	switch (Difficulty) {
	case 1://easy
		setDepth(2);
		break;
	case 2://normal
		setDepth(5);
		break;
	case 3: //hard
		setDepth(5);
		break;
	case 4:
		setDepth(7);
		break;
	}
}

int MancalaAI::getmove(MancalaState State) {
	int max = -100;
	int move = 0;
	int bin = 1;
	MancalaState copy = State;

	std::vector<MancalaState> expanded = expand(copy,2);

	for (int i = 0; i < expanded.size(); i++) {
		if (expanded[i].legal) {
			copy = expanded[i];
		}
		if (Difficulty <= 2) {
			move = MiniMax(copy, currentDepth, 2);
		}
		else
			move = MiniMaxAlphaBeta(copy, currentDepth, 2,max, 100);
		if (move > max) {
			max = move;
			bin = i;
		}
	}
	return bin;
}

std::vector<MancalaState> MancalaAI::expand(MancalaState state,int player) {
	
	std::vector<MancalaState> expanded;
	MancalaState copy = state;
	for (int i = 0; i < 6; i++) {
		if (copy.getTokenAmount(player, i) == 0) {
			expanded.push_back(copy);
			expanded[i].legal = false;
		}
		else {
			copy.Fullmove(i, player);
			expanded.push_back(copy);
			copy = state;
		}
	}
	return expanded;
}


int MancalaAI::MiniMax(MancalaState state, int depth, int player) {
	int bestVal;
	int val;
	if (depth == 0 || state.isTerminal() > 0) {
		return eval(state);
	}
	if (player == 2) {
		bestVal = -100;
		std::vector<MancalaState> expanded = expand(state, 2);
		for (int i = 0; i < expanded.size(); i++) {
			if (expanded[i].legal) {
				val = MiniMax(expanded[i], depth - 1, 1);
				if (val == 0 || val > bestVal) {
					bestVal = val;
				}
			}
		}
		return bestVal;
	}
	else {
		bestVal = 100;
		std::vector<MancalaState> expanded = expand(state, 1);
		for (int i = 0; i < expanded.size(); i++) {
			if (expanded[i].legal) {
				val = MiniMax(expanded[i], depth - 1, 2);
				if (val < bestVal) {
					bestVal = val;
				}
			}
		}
		return bestVal;
	}
}


int MancalaAI::eval(MancalaState state) {
	int score = 0;

	score += (state.getscore(2) * 2);
	score -=(state.getscore(1) * 2);
	for (int i = 0; i < 6; i++) {
		score += state.getTokenAmount(2, i);
		score -= state.getTokenAmount(1, i);
		if (state.getTokenAmount(2, i) == 0)
			score -= 10;
	}
	return score;
}


std::vector<int> CheckerHuman::getmoveStart() {
	std::vector<int> StartCoord = { 0,0 };
	std::cout << "Choose a piece to move:";
	std::cin >> MovePiece;
	MovePiece = trim(MovePiece);
	for (char& c : MovePiece) {
		c = toupper(c);
	}
	//std::cout << MovePiece << std::endl;
	switch (MovePiece.at(0)) {
	case 'A':
		StartCoord[0] = 0;
		break;
	case 'B':
		StartCoord[0] = 1;
		break;
	case 'C':
		StartCoord[0] = 2;
		break;
	case 'D':
		StartCoord[0] = 3;
		break;
	case 'E':
		StartCoord[0] = 4;
		break;
	case 'F':
		StartCoord[0] = 5;
		break;
	case 'G':
		StartCoord[0] = 6;
		break;
	case 'H':
		StartCoord[0] = 7;
		break;
	}

	switch (MovePiece.at(1)) {
	case '1':
		StartCoord[1] = 0;
		break;
	case '2':
		StartCoord[1] = 1;
		break;
	case '3':
		StartCoord[1] = 2;
		break;
	case '4':
		StartCoord[1] = 3;
		break;
	case '5':
		StartCoord[1] = 4;
		break;
	case '6':
		StartCoord[1] = 5;
		break;
	case '7':
		StartCoord[1] = 6;
		break;
	case '8':
		StartCoord[1] = 7;
		break;
	}


	if (StartCoord[0] > 7 || StartCoord[0] < 0){
		std::cout << "Invalid Column, Please try again." << std::endl;
		return getmoveStart();
	}
	else if (StartCoord[1] > 7 || StartCoord[1] < 0) {
		std::cout << "Invalid Row, Please try again." << std::endl;
		return getmoveStart();
	}
	else {
		return StartCoord;
	}
}

std::vector<int> CheckerHuman::getmoveEnd(std::vector<int> MoveStart) {
	std::string MoveEnd;
	std::cout << "Choose where to Move:";
	std::cin >> MoveEnd;
	MoveEnd = trim(MoveEnd);
	std::vector<int> EndCoord = { 0,0 };
	for (char& c : MoveEnd) {
		c = toupper(c);
	}
	
	switch (MoveEnd.at(0)) {
	case 'A':
		EndCoord[0] = 0;
		break;
	case 'B':
		EndCoord[0] = 1;
		break;
	case 'C':
		EndCoord[0] = 2;
		break;
	case 'D':
		EndCoord[0] = 3;
		break;
	case 'E':
		EndCoord[0] = 4;
		break;
	case 'F':
		EndCoord[0] = 5;
		break;
	case 'G':
		EndCoord[0] = 6;
		break;
	case 'H':
		EndCoord[0] = 7;
		break;
	}

	switch (MoveEnd.at(1)) {
	case '1':
		EndCoord[1] = 0;
		break;
	case '2':
		EndCoord[1] = 1;
		break;
	case '3':
		EndCoord[1] = 2;
		break;
	case '4':
		EndCoord[1] = 3;
		break;
	case '5':
		EndCoord[1] = 4;
		break;
	case '6':
		EndCoord[1] = 5;
		break;
	case '7':
		EndCoord[1] = 6;
		break;
	case '8':
		EndCoord[1] = 7;
		break;
	}


	return EndCoord;
};

std::string CheckerHuman::trim( const std::string& str, const std::string& whitespace)
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

int eval(CheckerState State) {
	std::vector<std::vector<int>> datBoard = State.getBoard();
	int score = 0;
	//std::cout << "Evaluating!" << std::endl;
	for each(std::vector<int> x in datBoard) {
		for each(int y in x) {
			if (y == 2) {
				score++;
			}
			else if (y == 1)
			{
				score--;
			}
		}
	}
	
	return score;
}

int CheckerAI::miniMax(CheckerState State,int depth, int choicePlayer) {
	int bestVal = -100;
	int val;
	int NotPlayer;
	if (choicePlayer == 2) {
		NotPlayer = 1;
	}
	else {
		NotPlayer = 2;
	}
	int temp;
	std::vector<std::vector<std::vector<CheckerState>>> expanded = expand(State,choicePlayer);
	//std::cout << depth << "MINIMAX" << std::endl;
	if (depth == 0 || State.isTerminal()) {
		if (choicePlayer == 2) {
			return eval(State);
		}
		else {
			int negate = eval(State);
			negate = negate * -1;
			return negate;
		}	
	}
		
	for each(std::vector<std::vector<CheckerState>> x in expanded) {
		for each(std::vector<CheckerState> y in x) {
			for each(CheckerState z in y) {
				temp = miniMax(z, depth - 1, NotPlayer);
				val = -temp;
				if (val < bestVal) {
					bestVal = val;
				}
			}
		}
	}
	return bestVal;
}

int MancalaAI::MiniMaxAlphaBeta(MancalaState state, int depth, int player, int alpha, int beta) {
	int bestVal;
	if (depth == 0 || state.isTerminal() > 0) {
		return eval(state);
	}
	if (player == 2) {
		bestVal = -100;
		std::vector<MancalaState> expanded = expand(state, 2);
		for (int i = 0; i < expanded.size(); i++) {
			if (expanded[i].legal) {
				bestVal = std::max(bestVal, MiniMaxAlphaBeta(state, depth - 1, 1, alpha, beta));
				alpha = std::max(bestVal, alpha);
				if (beta <= alpha)
					break;
			}
		}
		return bestVal;
	}
	else {
		bestVal = 100;
		std::vector<MancalaState> expanded = expand(state, 1);
		for (int i = 0; i < expanded.size(); i++) {
			if (expanded[i].legal) {
				bestVal = std::min(bestVal, MiniMaxAlphaBeta(state, depth - 1, 2, alpha, beta));
				beta = std::min(bestVal, beta);
				if (beta <= alpha) {
					break;
				}
			}
		}
		return bestVal;
	}
}


int CheckerAI::miniMaxAlphaBeta(CheckerState State, int depth, int choicePlayer,int alpha, int beta) {
	int bestVal = -100;

	int NotPlayer;
	if (choicePlayer == 2) {
		NotPlayer = 1;
	}
	else {
		NotPlayer = 2;
	}

	std::vector<std::vector<std::vector<CheckerState>>> expanded = expand(State, choicePlayer);
	//std::cout << depth << "MINIMAXAB" << std::endl;
	if (depth == 0 || State.isTerminal()) {
		if (choicePlayer == 2) {
			return eval(State);
		}
		else {
			int negate = eval(State);
			negate = negate * -1;
			return negate;
		}
	}
	if (choicePlayer == 2) {
		for each(std::vector<std::vector<CheckerState>> x in expanded) {
			for each(std::vector<CheckerState> y in x) {
				for each(CheckerState z in y) {
					bestVal = std::max(bestVal,miniMaxAlphaBeta(z, depth - 1, NotPlayer, alpha, beta));
					alpha = std::max(bestVal, alpha);
					if (beta <= alpha)
						break;
					
				}
			}
		}
	}
	else {
		for each(std::vector<std::vector<CheckerState>> x in expanded) {
			for each(std::vector<CheckerState> y in x) {
				for each(CheckerState z in y) {
					bestVal = std::min(bestVal,miniMaxAlphaBeta(z, depth - 1, NotPlayer, alpha, beta));
					beta = std::min(bestVal, beta);
					if (beta <= alpha) {
						break;
					}
				}
			}
		}
	}
	return bestVal;
}

std::vector<int> CheckerAI::getmove(CheckerState State) {
	int max = -100;
	int move;
	int temp;
	std::vector<int> choiceStart = {};
	std::vector<int> choiceEnd = {};
	int depth = currentDepth;

	std::vector<std::vector<std::vector<CheckerState>>> MOVES = CheckerAI::expand(State,2);
	CheckerState tempBoard;
	for each(std::vector<std::vector<CheckerState>> x in MOVES) {
		for each(std::vector<CheckerState> y in x) {
			for each(CheckerState z in y) {
				tempBoard = z;
				if (Difficulty <= 2) {
					temp = (miniMax(z, depth - 1, 1));
				}
				else {
					temp = miniMaxAlphaBeta(z, depth - 1, 1, max, 100);
				}
					move = temp;
					if (move >= max) {
						max = move;
						choiceStart = z.Start;
						choiceEnd = z.End;
					}
					else {
						choiceStart = tempBoard.Start;
						choiceEnd = tempBoard.End;
					}
			}
		}
	}
	std::vector<int> OhSHIT = { choiceStart[0],choiceStart[1],choiceEnd[0],choiceEnd[1] };
	return OhSHIT;

}

std::vector<std::vector<std::vector<CheckerState>>> CheckerAI::expand(CheckerState State,int choicePlayer) {
	//bool moveApplied;
	std::vector<int> pos;
	//std::cout << "Expanding" << std::endl;
	std::vector<std::vector<std::vector<CheckerState>>> fuck;
				std::vector<std::vector<CheckerState>> tempRow;
							std::vector<CheckerState> PositionMoves;
	CheckerState Copy = State;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			pos = { i,j };
			if (State.getPiece(pos) == choicePlayer) {
				PositionMoves = moves(Copy, pos);
				tempRow.push_back(PositionMoves);
			}
		}
		bool test = tempRow.empty();
		if (!tempRow.empty()) {
			fuck.push_back(tempRow);
			tempRow.clear();
		}
	}

	return fuck;
}

std::vector<CheckerState> CheckerAI::moves(CheckerState State, std::vector<int> Position) {
	std::vector<std::vector<CheckerState>> results;
	std::vector<CheckerState> tempRow;
	CheckerState Copy = CheckerState(State.getBoard());
	//CheckerState Empty = CheckerState(false);
	std::vector<std::vector<int>> moveEnds = {};
	//look at positions in leftmost column
	switch (Position[1]) {
		//left most position cannot move left.
	case 0:
		//if position is not in the bottom row look to move one diagonal
		if (Position[0] < 7) {
			moveEnds.push_back({ Position[0] + 1,Position[1] + 1 });
		}
		//if position is higher than bottom two rows, look to potentially jump a piece.
		if (Position[0] < 6) {
			moveEnds.push_back({ Position[0] + 2,Position[1] + 2 });
		}
		break;
		//second left most position can look to the right all the way, and one to the left.
	case 1:
		//if position is not in the bottom row look to move one diagonal
		if (Position[0] < 7) {
			moveEnds.push_back({ Position[0] + 1,Position[1] + 1 });
			moveEnds.push_back({ Position[0] + 1,Position[1] - 1 });
		}
		//if position is higher than bottom two rows, look to potentially jump a piece.
		if (Position[0] < 6) {
			moveEnds.push_back({ Position[0] + 2,Position[1] + 2 });
		}
		break;

		//second right most positions can look to the left all the way, and one to the right.
	case 6:
		//if position is not in the bottom row look to move one diagonal
		if (Position[0] < 7) {
			moveEnds.push_back({ Position[0] + 1,Position[1] + 1 });
			moveEnds.push_back({ Position[0] + 1,Position[1] - 1 });
		}
		//if position is higher than bottom two rows, look to potentially jump a piece.
		if (Position[0] < 6) {
			moveEnds.push_back({ Position[0] + 2,Position[1] - 2 });
		}
		break;
		
		//right most positions can look to the left all the way.
	case 7:
		//if position is not in the bottom row look to move one diagonal
		if (Position[0] < 7) {
			moveEnds.push_back({ Position[0] + 1,Position[1] - 1 });
		}
		//if position is higher than bottom two rows, look to potentially jump a piece.
		if (Position[0] < 6) {
			moveEnds.push_back({ Position[0] + 2,Position[1] - 2 });
		}
		break;
	default:
		//if position is not in the bottom row look to move one diagonal
		if (Position[0] < 7) {
			moveEnds.push_back({ Position[0] + 1,Position[1] + 1 });
			moveEnds.push_back({ Position[0] + 1,Position[1] - 1 });
		}
		//if position is higher than bottom two rows, look to potentially jump a piece.
		if (Position[0] < 6) {
			moveEnds.push_back({ Position[0] + 2,Position[1] + 2 });
			moveEnds.push_back({ Position[0] + 2,Position[1] - 2 });
		}
		break;

	}

	for each(std::vector<int> x in moveEnds) {
		if (AILegalMove(Position, x, State)) {
			Copy.move(Position, x);
			Copy.End = x;
			Copy.Start = Position;
			tempRow.push_back(Copy);
			Copy = State;
		}
	}
	return tempRow;
}

bool CheckerAI::AILegalMove(std::vector<int> MoveStart, std::vector<int> MoveEnd, CheckerState Board) {

	bool MovePossible = true;
	
	int MoveSpot = Board.getPiece(MoveEnd);

	double startToEnd0 = (MoveStart[0] - MoveEnd[0]); //
	double startToEnd1 = (MoveStart[1] - MoveEnd[1]);
	
	//if statement nest to determine if the computer is looking at 2 squares away
	if (std::abs(startToEnd0) == 2 && std::abs(startToEnd1) == 2) { //checks to make sure it is two spaces from start to End
		int Piece = Board.getPiece({ (MoveEnd[0] + MoveStart[0]) / 2, (MoveEnd[1] + MoveStart[1]) / 2 });
		if (Piece != 1) {
			MovePossible = false;
		}
	}
	else if (std::abs(startToEnd0/2.0) != .5 || std::abs(startToEnd1/2.0) != .5) {
		MovePossible = false;
	}
	else {
		if (MoveSpot != 0) {
			MovePossible = false;
		}

	}
	if (MoveStart[0] == 2) {
		MovePossible = MovePossible;
	}

	return MovePossible;
}


bool CheckerHuman::LegalMove(std::vector<int> MoveStart, std::vector<int> MoveEnd,CheckerState Board) {

	int startToEnd0 = MoveEnd[0] - MoveStart[0];
	int startToEnd1 = MoveEnd[1] - MoveStart[1];
	std::vector<int> JumpSpace;

		if ((startToEnd1 == 1 || startToEnd1 == -1) && std::abs(startToEnd0 == 1)) {
			if (Board.getPiece(MoveEnd) != 0) {
				std::cout << "You can't move on top of another peice!" << std::endl;
				return false;
			}
		}
		else if ((startToEnd1 == 2 || startToEnd1 == -2) && std::abs(startToEnd0 == 2)) {

			if (startToEnd0 == 2) {
				JumpSpace = { MoveEnd[1] - 1, MoveEnd[0] + 1 };
			}
			else if (startToEnd0 == -2) {
				JumpSpace = { MoveEnd[1] - 1,MoveEnd[0] - 1 };
			}
			if (Board.getPiece(JumpSpace) == 1) {
				std::cout << "You can't jump your own peice." << std::endl;
				return false;
			}
			else if (Board.getPiece(JumpSpace) == 0) {
				std::cout << "You have to jump a peice to move there" << std::endl;
				return false;
			}
		}
		else
			return false;

	return true;
}