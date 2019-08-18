#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include<Windows.h>
#include<iostream>
#include<string>
#include<GL\glew.h>
//#include<gl/GL.h>
//#include<gl/GLU.h>
//#include<GLFW\glfw3.h>
#include"Header.h"
#include "Geometry2D.h"
#include"Shader.h"
#include"Mesh.h"
#include "Texture.h"
#include"Geometry3D.h"
#include"Globals.h"

using namespace _Maths;
using namespace _Geometry2D;
using namespace _Geometry3D;
using namespace _GlobalVariables;

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
	
	


	

	Matrix3X3 mat{ 1, 2, 3, 0, 4, 5, 1, 0, 6 };

	m4x4 scaleMat = Scale(Vec3(2, 2, 2));

	std::cout << scaleMat << std::endl;

	Matrix3X3 cofactorMatrix = Cofactor(mat);

	std::cout << cofactorMatrix;

	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glutInitWindowSize(500, 500);

	

	//glutCreateWindow("Sample Window");
	//
	//init();
	//
	//glutDisplayFunc(lineSegment);
	//
	//glutMainLoop();
	

	if (glfwInit()) {
		std::cout << "GLFW Initiated" << std::endl;
	}
	//GLUT WINDOW
	GLFWwindow *win = glfwCreateWindow(500, 500, "Sample", NULL, NULL);
	glfwMakeContextCurrent(win);
	
	//GLEW must be initialized after creating a window context
	glewInit();
	if (glewInit()) {
		std::cout << "GLEW initiated";
	}
	else {
		std::cout << "GLEW not initiated";
	}


	std::cout << "sdfsdf" << glGetString(GL_VERSION);
	//glOrtho(-200, 200, -200, 200, -50, 100);
	
	//glOrtho(-2, 2, -2, 2, -50, 100);
	glClearColor(0.3, 0.3, 0.3, 1);
	float angle = 0;
	float moveX = 0;
	float moveY = 0;
	float moveZ = 0;
	float speed = 5.0f;
	float rotSpeed = 5.0f;
	float rotBoost = 1.0f;
	float time = 0;

	
	Matrix4X4 m = Transform(Vec3(1, 1, 1), Vec3(0, 0, 0), Vec3(0, 0, 0));
	//Matrix4X4 o = Orthographic(-200, 200, -200, 200, 0.1, 1000);//(60, 1, 0.1f, 1000);
	Matrix4X4 p = Perspective(60, 1.33, 0.1f, 10000);
	globalProjectionMatrix = p;

	Vertex verts[] = {
		Vertex(Vec3(-50.5, 0, 0), vec2(0, 1)),
		Vertex( Vec3(50.5, 0, 0),  vec2(1, 1)),
		Vertex( Vec3(0.0, 50.5, 0), vec2(0.5, 0)),
		Vertex( Vec3(0.0, -50.5, 0), vec2(0.5, 0.5))
	};


	std::string shaderFolder = "./Shaders/sample";
	std::string imageFolder = "./Textures/ichigo.jpg";

	Shader s(shaderFolder);
	Texture t(imageFolder);
	
	Mesh mesh(verts, sizeof(verts) / sizeof(verts[0]), new int[3] {0, 1, 2}, 3);

	Sphere sp(Point(50, 50, 150), 3);

	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);

	while (!glfwWindowShouldClose(win))
	{

#pragma region Move
		moveX = moveY = moveZ = 0;
		//Sample rotation
		if (glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS)
			angle += 1.0f * rotSpeed + rotBoost;
		if (glfwGetKey(win, GLFW_KEY_O) == GLFW_PRESS)
			angle -= 1.0f* rotSpeed + rotBoost;

		if (glfwGetKey(win, GLFW_KEY_V) == GLFW_PRESS)
			rotBoost += 0.01;

		//Sample movement
		if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
			moveZ = 1.0f * speed;
		if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
			moveZ = -1.0f * speed;

		if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
			moveX = -1.0f * speed;
		if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
			moveX = 1.0f * speed;

		if (glfwGetKey(win, GLFW_KEY_R) == GLFW_PRESS)
			moveY = 1.0f * speed;
		if (glfwGetKey(win, GLFW_KEY_F) == GLFW_PRESS)
			moveY = -1.0f * speed;


#pragma endregion

		//viewMatrix = 
		Matrix4X4 v = LookAt(Vec3(0, 0, -100 ), GetTranslation(m), Vec3(0, 1, 0));
		sp.transform.Position = { sp.transform.Position.x + moveX, sp.transform.Position.y + moveY, sp.transform.Position.z + moveZ};
		globalViewMatrix = v;
		
		Matrix4X4 MVP_Matrix = (m * v) * p;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		s.Update(MVP_Matrix);
		s.Bind();
		t.Bind(0);

		mesh.Draw();

		sp.Render(&s);

		//Matrix4X4 v = LookAt(Vec3(0 + moveX, 0, -100 + moveY), Vec3(0 + angle , 0, -100 + moveY + 500), Vec3(0, 1, 0));
		

		//

		//glColor3f(1.0f, 0.5f, 0.5f);
		//Point3D one(-50.5f, 0, -30.0f);
		//Point3D two(50.5f, 0, 30.0f);
		//Point3D three(50.5f, 0, 100.0f);
		//Point3D four(-50.5f, 0, 100.0f);

		////one = MultiplyPoint(one, v);
		////std::cout << "one: " << one << std::endl;
		////one = MultiplyPoint(one, pers) / 200;
		////std::cout << "one: " << one << std::endl;

		////std::cout << "View: " << v << std::endl;
		//
		////The Z divide step is hard wired into the graphics hardware. This is only for demonstration purpose
		//one = MultiplyPointAndZDivide(one, (m * v) * p);
		//two = MultiplyPointAndZDivide(two, (m * v) * p);
		//three = MultiplyPointAndZDivide(three, (m * v) * p);
		//four = MultiplyPointAndZDivide(four, (m * v) * p);

		////one = one / one.z;
		////two = two / two.z;
		////three = three / three.z;
		////four = four / four.z;

		////std::cout << "two: " << one << std::endl;

		////std::cout << "two: " << one << std::endl;

		//glPolygonMode(GL_FRONT, GL_FILL);
		//glPolygonMode(GL_BACK, GL_LINE);

		//glBegin(GL_QUADS);
		//glVertex3f(one.x, one.y, one.z);
		//glColor3f(0, 0, 0);
		//glVertex3f(two.x, two.y, two.z);
		//glColor3f(0, 0, 1);
		//glVertex3f(three.x, three.y, three.z);
		//glColor3f(0, 1, 0);
		//glVertex3f(four.x, four.y, four.z);
		////glVertex2f(0.0f, 100.0f);
		////glVertex2f(100.0f, 0.5f);
		////glVertex2f(-100.0f, 0.5f);
		//glEnd();


		//glColor3f(0, 0, 0);
		//

		//
		//Point2D check(75, 45);
		////check.Draw();

		//vec2 p1 = vec2(3, 8);
		//vec2 p2 = vec2(7.5, 3);

		//vec2 n = Normalize(p2 - p1);
		////Line2D(vec2(), n).Draw();
		//vec2 w = vec2(1.0f / n.x, 1.0f / n.y);
		////Line2D(vec2(), w).Draw();
		//time += 1.0f;

		////Line2D line(vec2(15, -14), vec2(95, -32));
		//Line2D line(vec2(10 * cos(DEG2RAD(time)), 10 * sinf(DEG2RAD(time))), 
		//			vec2(150 * cos(DEG2RAD(time)), 150 * sinf(DEG2RAD(time))));
		//////Point2D m((line.end.y - line.start.y), -(line.end.x - line.start.x));
		//////Line2D norm(vec2(), m);
		//////norm.Draw();
		//Rectangle2D rect = Rectangle2D(vec2(0 + moveX, 0 + moveY), vec2(40, 60));
		//
		//if (LineRectangle(line, rect)) {
		//	rect.Draw(vec3(1, 0, 1.0f));
		//	line.Draw(vec3(1, 0, 1.0f));
		//}
		//else {
		//	rect.Draw();
		//	line.Draw();
		//}


		//Circle c(Point2D(10, 60), 100);
		//OrientedRectangle rect1(Point2D(0 + moveX, 0 + moveY), Point2D(50, 50), angle);
		//OrientedRectangle rect2(Point2D(112 + moveX * 0.8f, 47 + moveY * 0.8f), Point2D(80, 50), -angle * 0.8f);
		//Rectangle2D rectA = Rectangle2D(vec2(0 + moveX, 0 + moveY), vec2(40, 127));
		//Rectangle2D rectB = Rectangle2D(vec2(-50 , -50), vec2(-40, -127));
		//
		//if (OrientedRectangleOrientedRectangle(rect1, rect2)) {
		//	rect1.Draw(vec3(1, 0, 1.0f));
		//	rect2.Draw(vec3(1, 0, 1.0f));
		//	//rectB.Draw(vec3(1, 0, 1.0f));
		//}
		//else {
		//	rect1.Draw();
		//	rect2.Draw();
		//	//rectB.Draw();
		//}

		//if (CircleOrientedRectangle(c, rect1)) {
		//	c.Draw(vec3(1, 0, 1.0f));
		//	rect1.Draw(vec3(1, 0, 1.0f));
		//}
		//else {
		//	c.Draw();
		//	rect1.Draw();
		//}
		//
		//
		//if (LineCircle(line, c)) {
		//	c.Draw(vec3(1, 0, 1.0f));
		//	line.Draw(vec3(1, 0, 1.0f));
		//}
		//else {
		//	c.Draw();
		//	line.Draw();
		//}

		//
		////bool pointCheck = PointInOrientedRectangle(check, rect1);
		//bool pointCheck = PointOrientedRectangle(check, rect1);
		//if (pointCheck)
		//	rect1.Draw(vec3(1, 0, 1));
		//else
		//	rect1.Draw(vec3(0, 0, 0));
			

		
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