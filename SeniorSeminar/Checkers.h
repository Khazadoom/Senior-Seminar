#pragma once
#include "Player.h"
#include "CheckerState.h"
#include <iostream>


class Checkers {
private:
	CheckerHuman player1;
	CheckerAI player2;
	bool terminalStatus;
	CheckerState currentState;
	void play();
	void newPlay();
	bool Checkers::checkEmpty(std::vector<int> Location);
	void drawSelected(GLFWwindow* window);
public:
	Checkers();
	Checkers(CheckerHuman& player1, CheckerAI& player2);
	int currentPlayer;
	int getPiece(std::vector<int> Location);
	CheckerState getBoard();
	
};