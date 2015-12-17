#include "Mancala.h"
#include "MancalaState.h"
#include "GLFW\glfw3.h"



Mancala::Mancala() {

}

Mancala::Mancala(MancalaHuman& player1, MancalaAI& player2) {
	Mancala::player2 = player2;
	Mancala::player1 = player1;
	play();
}

bool canSelectMan = true;
bool moveselected = false;
int MoveBin = 0;

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	int width, height;
	double xpos, ypos;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && canSelectMan) {
		glfwGetFramebufferSize(window, &width, &height);
		glfwGetCursorPos(window, &xpos, &ypos);
		//std::cout << xpos << " is the Xposition and " << ypos << " is the Yposition." << std::endl;
		if (ypos > 275 && ypos < 375) {
			if (xpos > 200 && xpos < 300) {
				MoveBin = 0;
				moveselected = true;
			}
			else if (xpos > 300 && xpos < 400) {
				MoveBin = 1;
				moveselected = true;
			}
			else if (xpos > 400 && xpos < 500) {
				MoveBin = 2;
				moveselected = true;
			}
			else if(xpos > 500 && xpos < 600) {
				MoveBin = 3;
				moveselected = true;
			}
			else if (xpos > 600 && xpos < 700) {
				MoveBin = 4;
				moveselected = true;
			}
			else if (xpos > 700 && xpos < 800) {
				MoveBin = 5;
				moveselected = true;
			}

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


void Mancala::play() {
	int term = 0;
	int currentPlayer = 1;
	bool Extra = false;
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(1000, 500, "Mancala", NULL, NULL);
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
		if (moveselected) {
			Extra = currState.Fullmove(MoveBin, 1);
			currState.Display(window);
			moveselected = false;
			term = currState.isTerminal();
			glfwSwapBuffers(window);
			currentPlayer = 2;
			canSelectMan = false;
			if (term == 0 && Extra == false) {
				MoveBin = player2.getmove(currState);
				Extra = currState.Fullmove(MoveBin, 2);
				term = currState.isTerminal();
				currentPlayer = 1;
				canSelectMan = true;
			}
			else {
				canSelectMan = true;	
				currentPlayer = 1;
			}
		}
		currState.Display(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
		if (term != 0) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

}