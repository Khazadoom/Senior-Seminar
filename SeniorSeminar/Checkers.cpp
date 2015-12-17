#include <iostream>
#include "CheckerState.h"
#include "Player.h"
#include "Checkers.h"
#include <vector>
#include <GLFW\glfw3.h>

bool canSelect = true;
bool pieceSelected=false;
bool spotSelected = false;
std::vector<int> MoveStart = { 0,0 };
std::vector<int> MoveEnd = { 0,0 };
std::vector<int> AIMove;
CheckerState thing;

Checkers::Checkers() {

}

Checkers::Checkers(CheckerHuman& player1, CheckerAI& player2) {
	Checkers::player1 = player1;
	Checkers::player2 = player2;
	terminalStatus = false;
	std::cout << "Thanks for choosing Checkers." << std::endl;
	play();
}

CheckerState Checkers::getBoard() {
	return currentState;
}



static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	double xpos, ypos;
	int width, height;
	if (canSelect == true && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetFramebufferSize(window, &width, &height);
		//std::cout << width << std::endl;
		//std::cout << height << std::endl;
		glfwGetCursorPos(window, &xpos, &ypos);
		//std::cout << xpos << std::endl;
		//std::cout << ypos << std::endl;
		if (pieceSelected == false) {
			MoveStart[0] = (double)(xpos / width) * 8;
			MoveStart[1] = (double)(ypos / height) * 8;
			std::cout << MoveStart[0] << std::endl;
			std::cout << MoveStart[1] << std::endl;
			if (thing.getPiece(MoveStart) == 1) {
				pieceSelected = true;
			}
		}
		else {
			MoveEnd[0] = (double)(xpos / width) * 8;
			MoveEnd[1] = (double)(ypos / height) * 8;
			spotSelected = true;
		}
	}



}

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void Checkers::drawSelected(GLFWwindow* window) {
	currentState.Display(window);
	//radius is always .1
	//twicePi.. do i really need to explain what this is? come on.
	double radius = .1;
	double twicePi = 2.0 * 3.142;


	//CoordStartx takes the index of the piece that should be checked before being passed
	// subtracts 4 and then divides by 4. this converts it to working in the GLFW Coordinate system of -1 to 1
	float CoordStartx = MoveStart[0] - 4.f;
	CoordStartx = CoordStartx / 4.f;
	float CoordStartx2 = MoveStart[0] - 3.f;
	CoordStartx2 = CoordStartx2 / 4.f;
	//Centerx will end up being the equivalent square on the GLFW coord plane that the piece is on.
	//averages this the right bound of the square to get the center X coordinate between -1 and 1.
	float Centerx = CoordStartx + CoordStartx2;
	Centerx = Centerx / 2.f;

	//same thing with Y coordinates.
	float CoordStarty = 4.f - MoveStart[1];
	CoordStarty = CoordStarty / 4.f;
	float CoordStarty2 = 3.f - MoveStart[1];
	CoordStarty2 = CoordStarty2 / 4.f;
	float Centery = CoordStarty + CoordStarty2;
	Centery = Centery / 2.f;


	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.f, 1.f, 0.f);
	//Central Vertex of cirlce
	glVertex3f(Centerx, Centery, 0.f);
	for (int i = 0; i <= 20; i++) {
		glVertex3f((Centerx + (radius * cos(i * twicePi / 20))), (Centery + (radius * sin(i * twicePi / 20)))
			, 0.f);
	}
	glEnd();
}


int CheckTerminal(CheckerState currState) {
	return currState.isTerminal();
}


void Checkers::newPlay() {
	
	int term;
	currentPlayer = 1;
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(800, 800, "Checkers", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	while (!glfwWindowShouldClose(window)) {
		thing = currentState;
		if (pieceSelected) {
			drawSelected(window);
		}
		else
			currentState.Display(window);

		if (spotSelected) {
			spotSelected = false;
			if (player1.LegalMove(MoveStart, MoveEnd, currentState)) {
				canSelect = false;
				pieceSelected = false;
				currentState.FullMove(MoveStart, MoveEnd);
				currentState.Display(window);
				term = CheckTerminal(currentState);
				glfwSwapBuffers(window);
				currentPlayer = 2;
				//as soon as player moves, AI makes a move.
				if (term == 0) {
					AIMove = player2.getmove(currentState);
					MoveStart = { AIMove[0],AIMove[1] };
					MoveEnd = { AIMove[2],AIMove[3] };
					currentState.FullMove(MoveStart, MoveEnd);
					term = CheckTerminal(currentState);
					currentPlayer = 1;
					canSelect = true;
				}
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
		if (term != 0) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}


	}
}

void Checkers::play() {
	newPlay();

	//currentPlayer = 1;
	//std::vector<int> MoveStart;
	//std::vector<int> MoveEnd;
	//std::vector<int> AIMove;
	//GLFWwindow* window;
	//glfwSetErrorCallback(error_callback);
	//if (!glfwInit())
	//	exit(EXIT_FAILURE);
	//window = glfwCreateWindow(1000, 1000, "Simple example", NULL, NULL);
	//if (!window)
	//{
	//	glfwTerminate();
	//	exit(EXIT_FAILURE);
	//}
	//glfwMakeContextCurrent(window);
	//glfwSwapInterval(1);
	//glfwSetKeyCallback(window, key_callback);
	//currentState.Display(window);
	//while (!glfwWindowShouldClose(window)) {
	//	//currentState.Display();
	//	switch (currentPlayer) {
	//	case 1:
	//		MoveStart = player1.getmoveStart();
	//		MoveEnd = player1.getmoveEnd(MoveStart);
	//		while (!LegalMove(MoveStart, MoveEnd, currentState) && getPiece(MoveStart) == 1 && !checkEmpty(MoveEnd)) {
	//			MoveStart = player1.getmoveStart();
	//			//swap values to match how table is laid out
	//			std::swap(MoveStart[0], MoveStart[1]);
	//			MoveEnd = player1.getmoveEnd(MoveStart);
	//			std::swap(MoveEnd[0], MoveEnd[1]);
	//		}
	//		currentState.FullMove(MoveStart, MoveEnd);
	//		window = currentState.Display(window);
	//		glfwPollEvents();
	//		//std::cout << MoveStart[0] << " " << MoveStart[1] << " to " << MoveEnd[0] << " " << MoveEnd[1] << std::endl;
	//		currentPlayer = 2;
	//		break;
	//	case 2:
	//		AIMove = player2.getmove(currentState);
	//		//swap locations when moving, due to way Move is written to work with human inputs.
	//		MoveStart = { AIMove[1],AIMove[0] };
	//		MoveEnd = { AIMove[3],AIMove[2] };
	//		currentState.FullMove(MoveStart, MoveEnd);
	//		currentState.Display(window);
	//		currentPlayer = 1;
	//		break; 		
	//	}
	//	//std::cout << MoveStart[0] << " " << MoveStart[1] << " to " << MoveEnd[0] << " " << MoveEnd[1] << std::endl;
	//	//currentState.FullMove(MoveStart, MoveEnd);
	//}

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