#pragma once
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "MancalaState.h"
#include "CheckerState.h"

class MancalaHuman {
public:
	MancalaHuman();
	MancalaHuman(int Turn);
	//int LegalMove(int bin);
};

class MancalaAI {
public:
	int currentDepth;
	int Difficulty;
	MancalaAI();
	MancalaAI(int Turn, int difficulty);
	int MiniMax(MancalaState State, int depth, int choicePlayer);
	int MiniMaxAlphaBeta(MancalaState State, int depth, int choicePlayer,int alpha,int beta);
	int getmove(MancalaState State);
private:
	std::vector<MancalaState> expand(MancalaState State, int currentPlayer);
	int eval(MancalaState state);
	void setDepth(int depth);
};


bool LegalMove(std::vector<int> MoveStart, std::vector<int> MoveEnd,CheckerState Board);
int eval(CheckerState State);

class CheckerHuman {
public:
	bool LegalMove(std::vector<int> MoveStart, std::vector<int> MoveEnd, CheckerState Board);
	CheckerHuman();
	CheckerHuman(int Turn);
	std::vector<int> getmoveStart();
	std::vector<int> getmoveEnd(std::vector<int> MoveStart);
private:
	std::string MovePiece;
	std::string trim(const std::string& str, const std::string& whitespace = " \t");
};

class CheckerAI {
public:
	CheckerAI();
	CheckerAI(int Turn,int Depth);
	std::vector<int> getmove(CheckerState State);
private:
	void setDepth(int depth);
	int Difficulty = 0;
	bool AILegalMove(std::vector<int> MoveStart, std::vector<int> MoveEnd, CheckerState Board);
	int currentPlayer = 2;
	int currentDepth;
	int miniMax(CheckerState State,int depth, int choicePlayer);
	int miniMaxAlphaBeta(CheckerState State, int depth, int choicePlayer,int alpha,int beta);
	//std::vector<int> minValue(CheckerState State);
	//std::vector<int> maxValue(CheckerState State);
	std::vector<CheckerState> moves(CheckerState State, std::vector<int> Position);
	std::vector<std::vector<std::vector<CheckerState>>> expand(CheckerState State,int currentPlayer);

};