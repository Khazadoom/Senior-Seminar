#pragma once
#include <string>
#include <vector>
#include <iostream>

char getPiece(std::vector<int> Location);

class CheckerState {

	std::vector<int> row1 = { 0, 2, 0, 2, 0, 2, 0, 2 };
	std::vector<int> row2 = { 2, 0, 2, 0, 2, 0, 2, 0 };
	std::vector<int> row3 = { 0, 2, 0, 2, 0, 2, 0, 2 };
	std::vector<int> row4 = { 0, 0, 0, 0, 0, 0, 0, 0 };
	std::vector<int> row5 = { 0, 0, 0, 0, 0, 0, 0, 0 };
	std::vector<int> row6 = { 1, 0, 1, 0, 1, 0, 1, 0 };
	std::vector<int> row7 = { 0, 1, 0, 1, 0, 1, 0, 1 };
	std::vector<int> row8 = { 1, 0, 1, 0, 1, 0, 1, 0 };

	std::vector<std::vector<int>> board = {row1,row2,row3,row4,row5,row6,row7,row8};


	/**int board[8][8] = { 2, 0, 2, 0, 2, 0, 2, 0,
	0, 2, 0, 2, 0, 2, 0, 2,
		2, 0, 2, 0, 2, 0, 2, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 1, 0, 1, 0, 1, 0,
		0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0 };
		**/
public:
	void CheckerState::FullMove(std::vector<int> Start, std::vector<int> End);
	std::vector<int> Start;
	std::vector<int> End;
	std::vector<std::vector<int>> CheckerState::getBoard();
	void move(std::vector<int> MoveStart, std::vector<int> MoveEnd);
	CheckerState(bool instance);
	CheckerState();
	CheckerState(std::vector<std::vector<int>> Copy);
	std::string Display();
	int getPiece(std::vector<int> Location);
	int isTerminal();
private:
	void RemovePiece(std::vector<int> Location);

};