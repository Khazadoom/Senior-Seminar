#define ILUT_USE_OPENGL
#include <IL\config.h>
#include <IL\il.h>
#include <IL\ilu.h>
#include <IL\ilut_config.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include "Checkers.h"
#include "CheckerState.h"
#include "Player.h"
#include "Mancala.h"
#include <map>
#include <iostream>
#include <IL\devil_cpp_wrapper.hpp>


#pragma comment(lib,"DevIL.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib, "opengl32.lib")// and this too     figured

//
//
//
//
//#define ILUT_USE_OPENGL
//#include <IL\config.h>
//#include <IL\il.h>
//#include <IL\ilu.h>
//#include <IL\ilut_config.h>
//
//#include "stdafx.h"
//#include <iostream>
//#include "GL\glew.h"
//#include "GL\freeglut.h"
//#include "Checkers.h"
//#include "CheckerState.h"
//#include "Player.h"
//#include <string>
//#include <array>
//#include <IL\devil_cpp_wrapper.hpp>
//
//
//#pragma comment(lib,"DevIL.lib")
//#pragma comment(lib,"glu32.lib")
//#pragma comment(lib, "opengl32.lib")// and this too     figured

Checkers Launched;
int MenuPage = 1;
int GameChoice;
int difficulty = 0;
GLuint textname;
int width, height;
float buttonTopX;
float buttonTopY;
float buttonBottomX;
float buttonBottomY;

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	double xpos, ypos;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetFramebufferSize(window, &width, &height);
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << xpos << " is the Xposition and " << ypos << " is the Yposition." << std::endl;
		if (MenuPage == 1) {
			if (xpos >= 200 && xpos <= 600) {
				if (ypos >= 80 && ypos <= 160) {
					MenuPage = 2;
					GameChoice = 1;
				}
				else if (ypos >= 240 && ypos <= 320) {
					MenuPage = 2;
					GameChoice = 2;
				}
				else if (ypos >= 400 && ypos <= 480) {
					glfwSetWindowShouldClose(window, GL_TRUE);
				}
			}
		}
		else if (MenuPage == 2) {
			if (xpos >= 200 && xpos <= 600) {
				if (ypos >= 80 && ypos <= 160) {
					difficulty = 1;
					glfwSetWindowShouldClose(window, GL_TRUE);
				}
				else if (ypos >= 240 && ypos <= 320) {
					difficulty = 2;
					glfwSetWindowShouldClose(window, GL_TRUE);
				}
				else if (ypos >= 400 && ypos <= 480) {
					difficulty = 3;
					glfwSetWindowShouldClose(window, GL_TRUE);
				}
				else if (ypos >= 560 && ypos <= 640) {
					difficulty = 4;
					glfwSetWindowShouldClose(window, GL_TRUE);
				}
				else if (ypos >= 720 && ypos <= 800) {
					MenuPage = 1;
				}
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

static void createMenu(GLFWwindow* window) {
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
	if (MenuPage == 1) {

		textname = ilutGLLoadImage("Checkers button.png");
		glBindTexture(GL_TEXTURE_2D, textname);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(-.5f, .8f);
		glTexCoord2f(0, 0);
		glVertex2f(-.5f, .6f);
		glTexCoord2f(1, 0);
		glVertex2f(.5f, .6f);
		glTexCoord2f(1, 1);
		glVertex2f(.5f, .8f);
		glEnd();

		textname = ilutGLLoadImage("Mancala button.png");
		glBindTexture(GL_TEXTURE_2D, textname);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(-.5f, .4f);
		glTexCoord2f(0, 0);
		glVertex2f(-.5f, .2f);
		glTexCoord2f(1, 0);
		glVertex2f(.5f, .2f);
		glTexCoord2f(1, 1);
		glVertex2f(.5f, .4f);
		glEnd();

		textname = ilutGLLoadImage("Exit button.png");
		glBindTexture(GL_TEXTURE_2D, textname);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(-.5f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex2f(-.5f, -.2f);
		glTexCoord2f(1, 0);
		glVertex2f(.5f, -.2f);
		glTexCoord2f(1, 1);
		glVertex2f(.5f, 0.0f);
		glEnd();
	}
	else if (MenuPage == 2) {

		textname = ilutGLLoadImage("Easy button.png");
		glBindTexture(GL_TEXTURE_2D, textname);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(-.5f, .8f);
		glTexCoord2f(0, 0);
		glVertex2f(-.5f, .6f);
		glTexCoord2f(1, 0);
		glVertex2f(.5f, .6f);
		glTexCoord2f(1, 1);
		glVertex2f(.5f, .8f);
		glEnd();

		textname = ilutGLLoadImage("Normal button.png");
		glBindTexture(GL_TEXTURE_2D, textname);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(-.5f, .4f);
		glTexCoord2f(0, 0);
		glVertex2f(-.5f, .2f);
		glTexCoord2f(1, 0);
		glVertex2f(.5f, .2f);
		glTexCoord2f(1, 1);
		glVertex2f(.5f, .4f);
		glEnd();

		textname = ilutGLLoadImage("Hard button.png");
		glBindTexture(GL_TEXTURE_2D, textname);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(-.5f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex2f(-.5f, -.2f);
		glTexCoord2f(1, 0);
		glVertex2f(.5f, -.2f);
		glTexCoord2f(1, 1);
		glVertex2f(.5f, 0.0f);
		glEnd();

		textname = ilutGLLoadImage("Impossible button.png");
		glBindTexture(GL_TEXTURE_2D, textname);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(-.5f, -.4f);
		glTexCoord2f(0, 0);
		glVertex2f(-.5f, -.6f);
		glTexCoord2f(1, 0);
		glVertex2f(.5f, -.6f);
		glTexCoord2f(1, 1);
		glVertex2f(.5f, -.4f);
		glEnd();

		textname = ilutGLLoadImage("Exit button.png");
		glBindTexture(GL_TEXTURE_2D, textname);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex2f(-.5f, -.8f);
		glTexCoord2f(0, 0);
		glVertex2f(-.5f, -1.f);
		glTexCoord2f(1, 0);
		glVertex2f(.5f, -1.f);
		glTexCoord2f(1, 1);
		glVertex2f(.5f, -.8f);
		glEnd();
	}

}


int main(int argc, char* argv[]) {
	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	GLFWwindow* main;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	main = glfwCreateWindow(800, 800, "Brandon Wright Seminar Project", NULL, NULL);
	if (!main)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwMakeContextCurrent(main);
	glfwSwapInterval(1);
	glfwSetKeyCallback(main, key_callback);
	glfwSetMouseButtonCallback(main, mouse_button_callback);
	while (!glfwWindowShouldClose(main)) {
		createMenu(main);
		glfwSwapBuffers(main);
		glfwPollEvents();
	}
	if (GameChoice == 1) {
		glfwTerminate();
		CheckerHuman Player1(1);
		CheckerAI Player2(2, difficulty);
		Launched = Checkers(Player1, Player2);
	}
	else if (GameChoice == 2) {
		glfwTerminate();
		MancalaHuman Player1;
		MancalaAI Player2(2,difficulty);
		Mancala(Player1, Player2);
		//std::cout << "You chose a not game. lol" << std::endl;
	}
}
