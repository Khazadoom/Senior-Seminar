#pragma once
#include <vector>
#include <iostream>
#include <GLFW\glfw3.h>
#include "MancalaState.h"

double twicePi = 2 * 3.142;

MancalaState::MancalaState() {

}

bool MancalaState::Fullmove(int move, int currPlayer) {
	int Tokens;
	int TokensLeft;
	int Bin = move;
	bool ExtraMove = false;
	if (currPlayer == 1) {
		Tokens = Player1Board[(Bin)];
		Player1Board[(Bin)] = 0;
		TokensLeft = Tokens;
		//as long as there are pieces to move keep doing this.
		while (TokensLeft > 0) {
			if (TokensLeft != 0) {
				TokensLeft = p1Move(TokensLeft, currPlayer, Bin+1);
			}
			if (TokensLeft != 0) {
				p1Mancala += 1;
				TokensLeft--;
				if (TokensLeft == 0) {
					ExtraMove = true;
				}
			}
			Bin = 5;
			if (TokensLeft != 0) {
				TokensLeft = p2Move(TokensLeft, currPlayer, Bin);
			}
			Bin = 0;
		}
	}
	else {
		Tokens = Player2Board[(Bin)];
		Player2Board[(Bin)] = 0;
		TokensLeft = Tokens;
		//as long as there are pieces... well you know
		while (TokensLeft > 0) {
			if (TokensLeft != 0) {
				TokensLeft = p2Move(TokensLeft, currPlayer, Bin-1);
			}
			if (TokensLeft != 0) {
				p2Mancala += 1;
				TokensLeft--;
				if (TokensLeft == 0) {
					ExtraMove = true;
				}
			}
			Bin = 0;
			if (TokensLeft != 0) {
				TokensLeft = p1Move(TokensLeft, currPlayer, Bin);
			}
			Bin = 5;
		}
	}

	return ExtraMove;
}

int MancalaState::p1Move(int Tokensleft, int currPlayer, int move) {
	while (Tokensleft > 0 && move < 6) {
		Player1Board[move] += 1;
		Tokensleft--;
		move++;
	}
	if (currPlayer == 1) {
		if (Tokensleft == 0 && Player1Board[move - 1] == 1 && Player2Board[move - 1] != 0) {
			Player1Board[move - 1] = 0;
			p1Mancala += 1;
			p1Mancala += Player2Board[move - 1];
			Player2Board[move - 1] = 0;


		}
	}
	return Tokensleft;
}

int MancalaState::p2Move(int Tokensleft, int currPlayer, int move) {
	while (Tokensleft > 0 && move >= 0) {
		Player2Board[move] += 1;
		Tokensleft--;
		move--;
	}
	if (currPlayer == 2) {
		if (Tokensleft == 0 && Player1Board[move + 1] == 1 && Player2Board[move + 1] != 0) {
			Player2Board[move + 1] = 0;
			p2Mancala += 1;
			p2Mancala += Player1Board[move + 1];
			Player1Board[move + 1] = 0;
		}
	}
	return Tokensleft;
}



void drawPieces(int numPieces, float Centerx, float Centery) {
	float radiusFrom = .15f;
	float radiusCircle = .02f;
	float CircCenX;
	float CircCenY;
	for (int i = 0; i <= numPieces; i++) {
		glColor3f(1.f, 1.f, 0.f);
		CircCenX = (Centerx + (radiusFrom * cos(i * twicePi / numPieces)));
		CircCenY = (Centery + (radiusFrom * sin(i * twicePi / numPieces)));
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(CircCenX, CircCenY);
		for (int j = 0; j <= 10; j++) {
			glVertex3f((CircCenX + (radiusCircle * cos(j * twicePi / 10))), (CircCenY + (radiusCircle * sin(j * twicePi / 10)))
				, 0.f);
		}
		glEnd();
	}
}

void DrawMancala(int p1Pieces, int p2Pieces) {
	float radiusCircle = .02f;
	float CircCenX = 1.5f;
	float CircCenY = .45f;
	glColor3f(1.f, 1.f, 1.f);
	for (int i = 0; i < p1Pieces; i++) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(CircCenX, CircCenY);
		for (int j = 0; j <= 10; j++) {
			glVertex3f((CircCenX + (radiusCircle * cos(j * twicePi / 10))), (CircCenY + (radiusCircle * sin(j * twicePi / 10)))
				, 0.f);
		}
		glEnd();
		CircCenY = CircCenY - .05f;
		if (CircCenY < -.5) {
			CircCenY = .4f;
			CircCenX -= .075f;
		}
	}
	CircCenX = -1.35f;
	CircCenY = .45f;
	for (int z = 0; z < p2Pieces; z++) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(CircCenX, CircCenY);
		for (int j = 0; j <= 10; j++) {
			glVertex3f((CircCenX + (radiusCircle * cos(j * twicePi / 10))), (CircCenY + (radiusCircle * sin(j * twicePi / 10)))
				, 0.f);
		}
		glEnd();
		CircCenY = CircCenY - .05f;
		if (CircCenY < -.5) {
			CircCenY = .4f;
			CircCenX -= .075f;
		}
	}
}


GLFWwindow* MancalaState::Display(GLFWwindow* window) {
	int width, height;
	float ratio;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.35f, 0.05f);
	glVertex2f(-1.6f, .6f);
	glVertex2f(-1.6f, -.6f);
	glVertex2f(1.6f, -.6f);
	glVertex2f(1.6f, .6f);
	glEnd();
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_QUADS);
	glVertex2f(-1.55f, .5f);
	glVertex2f(-1.55f, -.5f);
	glVertex2f(-1.3f, -.5f);
	glVertex2f(-1.3f, .5f);
	glEnd();
	glColor3f(1.f, 0.f, 0.f);
	float Centerx = -1.f;
	float Centery = .3;
	
	//drawing AI(player2) Mancala bins
	for (int x = 0; x < 6; x++) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(Centerx, Centery);
		for (int i = 0; i <= 20; i++) {
			glVertex3f((Centerx + (.2f * cos(i * twicePi / 20))), (Centery + (.2f * sin(i * twicePi / 20)))
				, 0.f);
		}
		glEnd();
		drawPieces(Player2Board[x], Centerx, Centery);
		glColor3f(1.f, 0.f, 0.f);
		Centerx = Centerx + .4f;
	}
	glColor3f(0.f, 0.f, 0.f);
	glBegin(GL_QUADS);
	glVertex2f(1.3f, .5f);
	glVertex2f(1.3f, -.5f);
	glVertex2f(1.55f, -.5f);
	glVertex2f(1.55f, .5f);
	glEnd();
	Centerx = -1.f;
	Centery = -.3;
	//drawing Human(player1) bins
	for (int x = 0; x < 6; x++) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(Centerx, Centery);
		for (int i = 0; i <= 20; i++) {
			glVertex3f((Centerx + (.2f * cos(i * twicePi / 20))), (Centery + (.2f * sin(i * twicePi / 20)))
				, 0.f);
		}
		glEnd();
		drawPieces(Player1Board[x], Centerx, Centery);
		glColor3f(0.f, 0.f, 0.f);
		Centerx = Centerx + .4f;
	}
	DrawMancala(p1Mancala, p2Mancala);

	return window;
}

int MancalaState::getTokenAmount(int player, int bin) {
	if (player == 1) {
		return Player1Board[bin];
	}
	else
		return Player2Board[bin];
}

int MancalaState::getscore(int player) {
	if (player == 1) {
		return p1Mancala;
	}
	else
		return p2Mancala;
}


int MancalaState::isTerminal() {
	int p1Emptied = 0;
	int p2Emptied = 0;
	for (int x = 0; x < 6; x++) {
		if (Player1Board[x] == 0) {
			p1Emptied++;
		}
		if (Player2Board[x] == 0) {
			p2Emptied++;
		}
	}
	if (p1Emptied == 6) {
		for each (int x in Player2Board) {
			p2Mancala += x;
		}
		return 2;
	}
	if (p2Emptied == 6) {
		for each (int x in Player1Board) {
			p1Mancala += x;
		}
		return 1;
	}
	return 0;
}