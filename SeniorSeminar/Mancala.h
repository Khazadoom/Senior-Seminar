#pragma once
#include "MancalaState.h"
#include "Player.h"
#include <GLFW\glfw3.h>

class Mancala {
private:
	MancalaState currState;
	int terminalStatus;
	MancalaAI player2;
	MancalaHuman player1;
public:
	void play();
	Mancala();
	Mancala(MancalaHuman& player1, MancalaAI& player2);

};
