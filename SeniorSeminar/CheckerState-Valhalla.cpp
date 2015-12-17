#include <iostream>
#include <vector>
#include "CheckerState.h"
#include "GL/glew.h"
#include "GL/freeglut.h"




CheckerState::CheckerState() {
	//std::cout << initialize[0][0] << std::endl;
	//std::cout << CheckerState::board[0][0]<<"CheckerStateD" << std::endl;

}

int CheckerState::isTerminal() {
	int count1 = 0;
	int count2 = 0;
	for each(std::vector<int> x in board) {
		for each(int y in x) {
			if (y == 1) {
				count1++;
			}
			else if (y == 2) {
				count2++;
			}
		}
	}
	if (count1 == 1 && count2 == 0) {
		return 1;
	}
	else if (count1 == 0 && count2 == 1) {
		return 2;
	}
	else {
		return 0;
	}

}

CheckerState::CheckerState(bool instance) {
	CheckerState::board = {};
}

int CheckerState::getPiece(std::vector<int> Location) {
	return CheckerState::board[Location[0]][Location[1]];
}

std::vector<std::vector<int>> CheckerState::getBoard() {
	return CheckerState::board;
}

CheckerState::CheckerState(std::vector<std::vector<int>> Copy) {
	CheckerState::board = Copy;
}

void CheckerState::RemovePiece(std::vector<int> Location) {
	CheckerState::board[Location[0]][Location[1]] = 0;
}


std::string CheckerState::Display() {
/**
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if ((i + j) % 2 == 0) // if i + j is even
				glColor3f(0.4, 0.2, 0.6);
			else
				glColor3f(0.2, 0.3, 0.4);
			glRecti(i*32, j*32, (i + 1)*32, (j + 1)*32);    // draw the rectangle
		}
	}
	glutPostRedisplay();**/


	std::cout << "  A|B|C|D|E|F|G|H" << std::endl;

	for (int i = 0; i < 8; i++) {
		std::cout << i + 1;
		std::cout << "|";
		for (int j = 0; j < 8; j++) {

			if (CheckerState::board[i][j] == 2) {
				std::cout << "B|";
			}
			else if (CheckerState::board[i][j] == 1) {
				std::cout << "R|";
			}
			else {
				std::cout << " |";
			}
		}
		std::cout << std::endl;
		std::cout << " -----------------" << std::endl;
	}
	return "Hello Display";
}


void CheckerState::FullMove(std::vector<int> Start, std::vector<int> End) {
	int Start1 = Start[1];
	int Start0 = Start[0];
	int End1 = End[1];
	int End0 = End[0];
	std::cout << "swapping: " << Start0 << " " << Start1 << " and " << End0 << " " << End1 << std::endl;
	std::swap(CheckerState::board[Start1][Start0], CheckerState::board[End1][End0]);
	if (std::abs(Start1 - End1) == 2 && std::abs(Start0 - End0) == 2) {
		RemovePiece({ ((Start1 + End1) / 2),((Start0 + End0) / 2) });
	}
	Display();
}

void CheckerState::move(std::vector<int> MoveStart, std::vector<int> MoveEnd) {
	int Start1 = MoveStart[1];
	int Start0 = MoveStart[0];
	int End1 = MoveEnd[1];
	int End0 = MoveEnd[0];
	std::swap(CheckerState::board[Start1][Start0], CheckerState::board[End1][End0]);
}


