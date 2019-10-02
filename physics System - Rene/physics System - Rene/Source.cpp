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
#include"Camera\Camera.h"

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

	float camSpeed = 10;
	float camMoveX = 0;
	float camMoveY = 0;
	float camMoveZ = 0;
	float camAngleX = 0;
	float camAngleY = 0;
	double oldMouseX = 0;
	double oldMouseY = 0;
	
	Matrix4X4 m = GetTransformMatrix(Vec3(1, 1, 1), Vec3(0, 0, 0), Vec3(0, 0, 0));
	//Matrix4X4 o = Orthographic(-200, 200, -200, 200, 0.1, 1000);//(60, 1, 0.1f, 1000);
	Matrix4X4 p = Perspective(60, 1.33, 0.1f, 10000);
	globalProjectionMatrix = p;

	Vertex verts[] = {
		Vertex(Vec3(-50.5, 0, 0), vec2(0, 1)),
		Vertex( Vec3(50.5, 0, 0),  vec2(1, 1)),
		Vertex( Vec3(0.0, 50.5, 0), vec2(0.5, 0)),
		Vertex( Vec3(0.0, -50.5, 0), vec2(0.5, 0.5))
	};

	Vec3 cameraMove = GetTranslation(m);

	std::string shaderFolder = "./Shaders/sample";
	std::string imageFolder = "./Textures/ichigo.jpg";

	Shader s(shaderFolder);
	Texture t(imageFolder);
	
	//If there's some issue, put these in the while loop
	s.Bind();
	t.Bind(0);


	Mesh mesh(verts, sizeof(verts) / sizeof(verts[0]), new int[3] {0, 1, 2}, 3);

	Sphere sp(Point(50, 50, 550), 3);
	AABB box(Point(30, 230, 550), Vec3(2, 1, 1));

	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);

	

	Matrix4X4 cameraMatrix = GetTransformMatrix(Vec3(1, 1, 1), vec3(), vec3());
	Camera camera(Vec3(1, 1, 1), vec3(), vec3(1, 1, 1));

	bool deltasSet = false;
	while (!glfwWindowShouldClose(win))
	{

#pragma region Move
		moveX = moveY = moveZ = 0;
		camMoveX = camMoveY = camMoveZ = 0;

		//Sample rotation
		if (glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS)
			angle += 1.0f * rotSpeed + rotBoost;
		if (glfwGetKey(win, GLFW_KEY_O) == GLFW_PRESS)
			angle -= 1.0f* rotSpeed + rotBoost;

		if (glfwGetKey(win, GLFW_KEY_V) == GLFW_PRESS)
			rotBoost += 0.01;

		if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE) {
			deltasSet = false;
		}

		//Camera Movement Logic
		if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
			
			if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
				camMoveZ = 1.0f * camSpeed;
			if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
				camMoveZ = -1.0f * camSpeed;

			if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
				camMoveX = -1.0f * camSpeed;
			if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
				camMoveX = 1.0f * camSpeed;

			if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS)
				camMoveY = 1.0f * camSpeed;
			if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS)
				camMoveY = -1.0f * camSpeed;


			double mouseX, mouseY = 0;
			glfwGetCursorPos(win, &mouseX, &mouseY);

			if (!deltasSet) {
				deltasSet = true;
				oldMouseX = mouseX;	oldMouseY = mouseY;
			}

			float deltaX = (mouseX - oldMouseX) / 3;
			float deltaY = (mouseY - oldMouseY) / 3;

			camAngleY += deltaX;	camAngleX += deltaY;

			oldMouseX = mouseX;	oldMouseY = mouseY;
		}
		else {
			//Sample movement
			if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
				moveZ = 1.0f * speed;
			if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
				moveZ = -1.0f * speed;

			if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
				moveX = -1.0f * speed;
			if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
				moveX = 1.0f * speed;

			if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS)
				moveY = 1.0f * speed;
			if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS)
				moveY = -1.0f * speed;

		}


#pragma endregion

		
		//View Matrix calculation

		camera.MoveCamera(Vec3(camMoveX, camMoveY, camMoveZ));
		camera.SetCameraRoation(Vec3(camAngleX, camAngleY, 0));

		camera.Update();
		globalViewMatrix = camera.GetViewMatrix();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		//s.Update(MVP_Matrix);
		//mesh.Draw();
		sp.transform.Position = { sp.transform.Position.x + moveX, sp.transform.Position.y + moveY, sp.transform.Position.z + moveZ};

		sp.Render(&s);
		//box.mesh->color = vec4(1, 1, 0, 1);
		box.Render(&s);
		

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

}