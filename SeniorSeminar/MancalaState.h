#pragma once
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>

class MancalaState {
private:
	std::vector<int> Player1Board = { 4,4,4,4,4,4 };
	std::vector<int> Player2Board = { 4,4,4,4,4,4 };
	int p1Mancala = 0;
	int p2Mancala = 0;
	int p1Move(int TokensLeft, int currPlayer, int move);
	int p2Move(int TokensLeft, int currPlayer, int move);
public:
	bool legal = true;
	int getTokenAmount(int player, int bin);
	int getscore(int player);
	MancalaState();
	//MancalaState(std::vector<int> p1, int p1Man, std::vector<int> p2, int p2Man);
	bool MancalaState::Fullmove(int move, int currPlayer);
	GLFWwindow* MancalaState::Display(GLFWwindow* window);
	int isTerminal();
};