#pragma once
#include<Windows.h>
#include<iostream>
#include<string>
//#include<gl/GL.h>
//#include<gl/GLU.h>
//#include<GLFW\glfw3.h>
#include"Header.h"
#include "Geometry2D.h"
using namespace _Maths;
using namespace _Geometry2D;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100.0, 100.0, -150.0, 150.0);
}

void lineSegment() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	std::cout << "datw";
	glFlush();
	glutSwapBuffers();	//If the double buffering system is used, this line of code is necessary to swap buffers
}

int main(int argc, char** argv) {
	
	

	//Creating a rectangle
	const Rectangle2D rect(Point2D(0, 1), Point2D(3, 4));
	std::cout << rect.GetMax().y;

	Matrix3X3 mat{ 1, 2, 3, 0, 4, 5, 1, 0, 6 };

	m4x4 scaleMat = Scale(Vec3(2, 2, 2));

	std::cout << scaleMat << std::endl;

	Matrix3X3 cofactorMatrix = Cofactor(mat);

	std::cout << cofactorMatrix;

	
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glutInitWindowSize(500, 500);

	if (glfwInit()) {
		std::cout << "GLFW Initiated" << std::endl;
	}

	//glutCreateWindow("Sample Window");
	//
	//init();
	//
	//glutDisplayFunc(lineSegment);
	//
	//glutMainLoop();

	if (glewInit()) {
		std::cout << "GLEW initiated";
	}
	else {
		std::cout << "GLEW not initiated";
	}

	//GLUT WINDOW
	GLFWwindow *win = glfwCreateWindow(500, 500, "Sample", NULL, NULL);
	glfwMakeContextCurrent(win);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-200, 200, -200, 200, -50, 100);
	glClearColor(1, 1, 1, 1);
	float angle = 0;
	float moveX = 0;
	float moveY = 0;
	float speed = 3.5f;
	float rotSpeed = 3.5f;
	float rotBoost = 1.0f;
	while (!glfwWindowShouldClose(win))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		//Sample rotation
		if (glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS)
			angle += 1.0f * rotSpeed + rotBoost;
		if (glfwGetKey(win, GLFW_KEY_O) == GLFW_PRESS)
			angle -= 1.0f* rotSpeed + rotBoost;

		if (glfwGetKey(win, GLFW_KEY_V) == GLFW_PRESS)
			rotBoost += 0.01;

		//Sample movement
		if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
			moveY += 1.0f * speed;
		if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
			moveY -= 1.0f * speed;

		if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
			moveX -= 1.0f * speed;
		if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
			moveX += 1.0f * speed;

		
		Point2D check(75, 45);
		check.Draw();
		OrientedRectangle rect1(Point2D(0 + moveX, 0 + moveY), Point2D(-50, 50), angle);

		bool pointCheck = PointInOrientedRectangle(check, rect1);
		if (pointCheck)
			rect1.Draw(vec3(1, 0, 1));
		else
			rect1.Draw(vec3(0, 0, 0));
			

		
		//OrientedRectangle rect2(Point2D(-74, 48), Point2D(80, 46), angle * 2);
		//rect2.Draw();
		//OrientedRectangle rect3(Point2D(87, -95), Point2D(45, 4), angle * 0.6f);
		//rect3.Draw();
		//OrientedRectangle rect4(Point2D(-47, -46), Point2D(8, 20), angle * 3.0f);
		//rect4.Draw();
		//glFlush();

		//glBegin(GL_LINES);
		//glLineWidth(5);
		//glColor3f(0, 0, 0);
		//glVertex2f(0, 0);
		//glVertex2f(150, 150);
		//glEnd();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

}