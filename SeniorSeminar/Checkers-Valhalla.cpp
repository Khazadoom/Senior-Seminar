#include <iostream>
#include "CheckerState.h"
#include "Player.h"
#include "Checkers.h"
#include <vector>

Checkers::Checkers(CheckerHuman player1, CheckerAI player2) {
	terminalStatus = false;
	std::cout << "Thanks for choosing Checkers." << std::endl;
	play();
}

Checkers::Checkers() {

}

CheckerState Checkers::getBoard() {
	return currentState;
}

void Checkers::play() {
	currentPlayer = 1;
	std::vector<int> MoveStart;
	std::vector<int> MoveEnd;
	std::vector<int> AIMove;
	currentState.Display();
	while (terminalStatus != true) {
		//currentState.Display();
		switch (currentPlayer) {
		case 1:
			MoveStart = player1.getmoveStart();
			MoveEnd = player1.getmoveEnd(MoveStart);
			while (!LegalMove(MoveStart, MoveEnd, currentState) && getPiece(MoveStart) == 1 && !checkEmpty(MoveEnd)) {
				MoveStart = player1.getmoveStart();
				//swap values to match how table is laid out
				std::swap(MoveStart[0], MoveStart[1]);
				MoveEnd = player1.getmoveEnd(MoveStart);
				std::swap(MoveEnd[0], MoveEnd[1]);
			}
			currentState.FullMove(MoveStart, MoveEnd);
			//std::cout << MoveStart[0] << " " << MoveStart[1] << " to " << MoveEnd[0] << " " << MoveEnd[1] << std::endl;
			currentPlayer = 2;
			break;
		case 2:
			AIMove = player2.getmove(currentState);
			//swap locations when moving, due to way Move is written to work with human inputs.
			MoveStart = { AIMove[1],AIMove[0] };
			MoveEnd = { AIMove[3],AIMove[2] };
			currentState.FullMove(MoveStart, MoveEnd);
			currentPlayer = 1;
			break; 		
		}
		//std::cout << MoveStart[0] << " " << MoveStart[1] << " to " << MoveEnd[0] << " " << MoveEnd[1] << std::endl;
		//currentState.FullMove(MoveStart, MoveEnd);
	}

}

bool Checkers::checkEmpty(std::vector<int> Location) {
	bool isEmpty = true;
	if (currentState.getPiece(Location) != 0) {
		isEmpty = false;
		std::cout << "You can't move to a location that has a piece in it." << std::endl;
	}
	return isEmpty;
}


int Checkers::getPiece(std::vector<int> Location) {

	int Piece = currentState.getPiece(Location);
	if (currentPlayer == 1) {
		switch (Piece) {
		case 0:
			std::cout << "You have to select a location with a piece!" << std::endl;
			Piece = -1;
			break;
		case 2:
			std::cout << "You can't move an opponents piece!" << std::endl;
			Piece = -1;
			break;
		}
	}
	else if (currentPlayer == 2) {
		switch (Piece) {
		case 0:
			std::cout << "You have to select a location with a piece!" << std::endl;
			Piece = -1;
			break;
		case 1:
			std::cout << "You can't move an opponents piece!" << std::endl;
			Piece = -1;
			break;

		}
	}
	return Piece;
}

