#include <iostream>
#include <vector>
#include "CheckerState.h"
#include<GLFW/glfw3.h>



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
	if (count2 == 0) {
		return 1;
	}
	else if (count1 == 0) {
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
	//std::cout<<"Piece is: " << CheckerState::board[Location[0]][Location[1]] << std::endl;
	return CheckerState::board[Location[1]][Location[0]];
	
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

GLFWwindow* CheckerState::Display(GLFWwindow* window) {
	double twicePi = 2.0 * 3.142;
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int pieceSpotY;
	int color = 1;
	int RAndC = 4; //half of the rows and columns for the board
	float Centerx;
	float Centery;
	double radius = .1;
	float TopLeft[] = { 0.f,0.f };
	float TopRight[] = { 0.f,0.f };
	float BottomRight[] = { 0.f,0.f };
	float BottomLeft[] = { 0.f,0.f };
	//glRotatef(-90.0, 0.f, 0.f, 1.f);
	//glRotatef(180.0, 0.f, 1.f, 0.f);
	for (int x = -RAndC; x < RAndC; x++) {
		TopLeft[0] = (x / (float)RAndC);
		TopRight[0] = ((x + 1) / (float)RAndC);
		BottomRight[0] = ((x + 1) / (float)RAndC);
		BottomLeft[0] = (x / (float)RAndC);
		Centerx = TopRight[0] + BottomLeft[0];
		Centerx = Centerx / 2.f;
		pieceSpotY = 0;
		for (int y = RAndC-1; y >= -RAndC; y--) {
			TopLeft[1] = (y / (float)RAndC);
			TopRight[1] = (y / (float)RAndC);
			BottomRight[1] = ((y + 1) / (float)RAndC);
			BottomLeft[1] = ((y + 1) / (float)RAndC);
			Centery = TopLeft[1] + BottomLeft[1];
			Centery = Centery / 2.f;
			glBegin(GL_QUADS);
			if (color == 1) {
				glColor3f(0.f, 0.f, 0.f);
				if (y != -RAndC) {
					color = 2;
				}
			}
			else {
				glColor3f(1.f, 1.f, 1.f);
				if (y != -RAndC) {
					color = 1;
				}
			}
			glVertex3f((float)x / RAndC, (float)y / RAndC, 0.f);
			glVertex3f((float)x / RAndC, (y + 1) / (float)RAndC, 0.f);
			glVertex3f((x + 1) / (float)RAndC, (y + 1) / (float)RAndC, 0.f);
			glVertex3f((x + 1) / (float)RAndC, y / (float)RAndC, 0.f);
			glEnd();
			//std::cout << "Checking: " << y + 4 << " and " << x + 4 << std::endl;
			
			if (CheckerState::board[pieceSpotY][x+4] == 2) {
				glBegin(GL_TRIANGLE_FAN);
				glColor3f(0.f, 0.f, 0.f);
				//Central Vertex of cirlce
				glVertex3f(Centerx, Centery, 0.f);
				for (int i = 0; i <= 20; i++) {
					glVertex3f((Centerx + (radius * cos(i * twicePi / 20))), (Centery + (radius * sin(i * twicePi / 20)))
						, 0.f);
				}
				glEnd();

			}
			else if (CheckerState::board[pieceSpotY][x+4] == 1) {
				glBegin(GL_TRIANGLE_FAN);
				glColor3f(1.f, 0.f, 0.f);
				//Central Vertex of cirlce
				glVertex3f(Centerx, Centery, 0.f);
				for (int i = 0; i <= 20; i++) {
					glVertex3f((Centerx + (radius * cos(i * twicePi / 20))), (Centery + (radius * sin(i * twicePi / 20)))
						, 0.f);
				}
				glEnd();
			}
			pieceSpotY++;

		}
	}


	return window;
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
	//Display();
}

void CheckerState::move(std::vector<int> MoveStart, std::vector<int> MoveEnd) {
	int Start1 = MoveStart[1];
	int Start0 = MoveStart[0];
	int End1 = MoveEnd[1];
	int End0 = MoveEnd[0];
	std::swap(CheckerState::board[Start1][Start0], CheckerState::board[End1][End0]);
}


