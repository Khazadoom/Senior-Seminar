#include "stdafx.h"
#include <iostream>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "Checkers.h"
#include "CheckerState.h"
#include "Player.h"
#include <string>
#include <array>

Checkers Launched;


void Displaything() {
	Launched.getBoard().Display();
}

int main(int argc, char* argv[]) {
	int GameChoice;
	int difficulty;
	/**CheckerHuman Player1(1);
	CheckerAI Player2(2);**/
	std::cout << "Please Choose a Checkers to play. (Enter the Number next to the Checkers name)" << std::endl;
	std::cout << "1: Checkers." << std::endl;
	std::cout << "2: Mancala." << std::endl;
	std::cin >> GameChoice;
	std::cout << "Please Select a Dificulty to play." << std::endl;
	std::cout << "1: Easy" << std::endl;
	std::cout << "2: Normal" << std::endl;
	std::cout << "3: Hard" << std::endl;
	std::cin >> difficulty;

	if (GameChoice == 1) {
		CheckerHuman Player1(1);
		CheckerAI Player2(2, difficulty);
		Launched = Checkers(Player1, Player2);
	}
	else if (GameChoice == 2) {
		std::cout << "You chose a not game. lol" << std::endl;
	}
}
