#pragma once
#include "Geometry3D.h"
#include<iostream>
#include"Header.h"
#include"GL\glew.h"
#include <math.h>
#include <vector>
#include"Globals.h"

namespace _Geometry3D
{
	using namespace _GlobalVariables;
#pragma region Sphere

	//void Sphere::Create() {
	//	//Change these later
	//	//std::vector<Vec3> vertices;
	//	//std::vector<int> indices;
	//	const int horizontalDivisions = 10;
	//	const int verticalDivisions = 10;

	//	Vertex verts[horizontalDivisions * verticalDivisions + 2];
	//	int indices[60 + horizontalDivisions * verticalDivisions * 6];


	//	float pi = DEG2RAD(180);
	//	float yDivisions = pi / verticalDivisions;
	//	float xDivisions = (pi * 2) / horizontalDivisions;
	//	std::cout << "x divisions: " << xDivisions << std::endl;

	//	//First Vertex
	//	float yAngle = 0;
	//	float y = 1;
	//	float x = 0;
	//	float z = 0;

	//	//Settting the initial vertex
	//	verts[0].position = { x, y, z };
	//	verts[0].texCoord = { x, z };

	//	for (int i = 0; i <= verticalDivisions - 1; i++) {
	//		//We make a unit circle initially. Radius and position is added during the matrix construction
	//		//Pivot will be at the center
	//		float y1 = cosf(yDivisions * (i+1));
	//		std::cout << "Y : " << y1 <<std::endl;
	//		float radiusOfRing = sinf(yDivisions * (i + 1));

	//		float x1 = radiusOfRing * cos(0);
	//		float z1 = radiusOfRing * sin(0);

	//		//std::cout << "vert number: " << i * horizontalDivisions + 1 << std::endl;
	//		//std::cout << " " << x1 << " " << y1 << " " << z1 << std::endl;

	//		verts[i * horizontalDivisions + 1].position = {x1, y1, z1};
	//		verts[i * horizontalDivisions + 1].texCoord = {x1, z1};

	//		std::cout << "index : " << i * horizontalDivisions + 1 << " vert: " << *verts[i * horizontalDivisions + 1].GetPosition() << std::endl;

	//		std::cout << " verts: " << std::endl;

	//		if (i == verticalDivisions - 1) {
	//			std::cout << "Last Vertex " << horizontalDivisions * (verticalDivisions - 1) + 1 << std::endl;
	//			//Last Vertex
	//			verts[horizontalDivisions * (verticalDivisions-1) + 1].position = { 0, -1, 0 };
	//			verts[horizontalDivisions * (verticalDivisions-1) + 1].texCoord = { 0, 0 };
	//		}

	//		for (int j = 1; j <= horizontalDivisions; j++) {
	//			
	//			if (i == verticalDivisions - 1) {
	//				int lastRowIndexBaseValue = 3 * horizontalDivisions + 6 * horizontalDivisions * (verticalDivisions - 2) + 3 * (j - 1);
	//				if (j == horizontalDivisions) {
	//					indices[lastRowIndexBaseValue] = horizontalDivisions * (verticalDivisions - 1) + 1;
	//					indices[lastRowIndexBaseValue + 2] = horizontalDivisions * (verticalDivisions - 1);
	//					indices[lastRowIndexBaseValue + 1] = horizontalDivisions * (verticalDivisions -	2) + 1;

	//					break;
	//				}

	//				//Last Mesh
	//				//Assign Indices for triangles
	//				indices[lastRowIndexBaseValue] = horizontalDivisions * (verticalDivisions-1) + 1;
	//				indices[lastRowIndexBaseValue + 2] = horizontalDivisions * (verticalDivisions - 2) + j;
	//				indices[lastRowIndexBaseValue + 1] = horizontalDivisions * (verticalDivisions - 2) + j + 1;

	//				continue;
	//			}

	//			//std::cout << "vert number: " << i * horizontalDivisions + 1 + j << std::endl;
	//			//std::cout << " " << x2 << " " << y1 << " " << z2 << std::endl;

	//			int vertNumber = i * horizontalDivisions + 1 + j;
	//			int indexBaseNumberForRow = (3 * horizontalDivisions) + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1);

	//			float x2 = radiusOfRing * cos(j * xDivisions);
	//			float z2 = radiusOfRing * sin(j * xDivisions);

	//			if (j == horizontalDivisions) {

	//				if (i == 0)
	//					break;

	//				//First Triangle 
	//				indices[indexBaseNumberForRow] = i * horizontalDivisions;
	//				indices[indexBaseNumberForRow + 1] = (i + 1) * horizontalDivisions;
	//				indices[indexBaseNumberForRow + 2] = i * horizontalDivisions + 1;
	//				//
	//				//Second Triangle
	//				indices[indexBaseNumberForRow + 3] = i * horizontalDivisions;
	//				indices[indexBaseNumberForRow + 4] = i * horizontalDivisions + 1;
	//				indices[indexBaseNumberForRow + 5] = (i-1) * horizontalDivisions + 1;

	//				break;
	//			}


	//			//vertices[i * horizontalDivisions + 1 + j] = {x2, y1, z2};
	//			verts[vertNumber].position = {x2, y1, z2};
	//			verts[vertNumber].texCoord = {x2, z2};

	//			std::cout << " " << (i * horizontalDivisions) + 1 + j ;

	//			std::cout << "index : " << vertNumber << " vert: " << *verts[vertNumber].GetPosition() << std::endl;

	//			if (i == 0) {
	//				indices[3 * (j - 1)] = 0;
	//				indices[3 * (j - 1) + 1] = j;
	//				indices[3 * (j - 1) + 2] = j + 1;

	//				//std::cout << 3 * (j - 1) << 3 * (j - 1) + 1 << 3 * (j - 1) + 2 << std::endl;

	//				if (j == horizontalDivisions - 1) {
	//					indices[3 * (horizontalDivisions - 1)] = 0;
	//					indices[3 * (horizontalDivisions - 1) + 1] = 10;
	//					indices[3 * (horizontalDivisions - 1) + 2] = 1;

	//					//std::cout << "index : " << 3 * (horizontalDivisions - 1);
	//					//std::cout << "index : " << 3 * (horizontalDivisions - 1) + 1;
	//					//std::cout << "index : " << 3 * (horizontalDivisions - 1) + 2 << std::endl;

	//					//std::cout << 3 * (horizontalDivisions - 1) << 3 * (horizontalDivisions - 1) + 1 << 3 * (horizontalDivisions - 1) + 2 << std::endl;
	//				}
	//			}
	//			else
	//			{
	//				//First Triangle
	//				indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1)] = (i - 1) * horizontalDivisions + j;
	//				indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 1] = i * horizontalDivisions + j;
	//				indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 2] = i * horizontalDivisions + j + 1;

	//				//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i-1) + 6 * (j - 1);
	//				//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 1;
	//				//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 2 << std::endl;

	//				//Second Triangle

	//				indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 3] = (i - 1) * horizontalDivisions + j;
	//				indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 4] = i * horizontalDivisions + j + 1;
	//				indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 5] = (i - 1) * horizontalDivisions + j + 1;
	//				//std::cout << "index : " << i * horizontalDivisions + i + j << " vert: " << *verts[i * horizontalDivisions + i + j].GetPosition() << std::endl;

	//				//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i-1) + 6 * (j - 1) + 3;
	//				//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 4;
	//				//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 5 << std::endl;
	//			}
	//		}
	//		std::cout << "end" << std::endl;
	//	}

	//	//Creating a mesh
	//	//std::cout << "Vert Count : " << sizeof(verts) / sizeof(verts[0]) << std::endl;
	//	mesh = new Mesh(verts, horizontalDivisions * verticalDivisions, indices, 30 + horizontalDivisions * verticalDivisions * 6);
	//}

	////Render a sphere and send the data to openGL
	//void Sphere::Render(Shader *s) {
	//	//std::cout << "Rendering sphere" << std::endl;

	//	//Create a model matrix
	//	//TODO: Create proper transform API for objects
	//	//Matrix4X4 modelMatrix = Transform(Vec3(1 * 100, 1 * 100, 1 * 100), Vec3(0, 0, 0), center);
	//	Matrix4X4 modelMatrix = transform.GetTRSMatrix();
	//	
	//	//std::cout << modelMatrix;
	//	//std::cout << globalViewMatrix  << std::endl;

	//	Matrix4X4 mvp = (modelMatrix * globalViewMatrix) * globalProjectionMatrix;
	//	//Using the default shader. It has been created already. Only needs Updating
	//	s->SetTransform(mvp);
	//	s->SetColor(mesh->color);
	//	//s->SetColor(vec4(1, 1, 1, 1));
	//	//Draw only after the shader is updated
	//	mesh->Draw();
	//}


#pragma endregion

	float Line::Length() {
		return Magnitude(end - start);
	}
	float Line::LengthSq() {
		return MagnitudeSq(end - start);
	}

	//Ray
	Ray CreateRayFromPoints(const Point &start, const Point &end) {
		Ray r(start, end - start);
		return r;
	}

#pragma region AABB

	//void AABB::Create() {

	//	Vec3 cubePoints[8];
	//	Vertex vertices[24];
	//	int indices[36];

	//	Vec3 extents = size / 2;

	//	cubePoints[0] = Vec3(-extents.x, -extents.y, -extents.z);
	//	cubePoints[1] = Vec3(extents.x, -extents.y, -extents.z);
	//	cubePoints[2] = Vec3(extents.x, extents.y, -extents.z);
	//	cubePoints[3] = Vec3(-extents.x, extents.y, -extents.z);
	//	cubePoints[4] = Vec3(-extents.x, -extents.y, extents.z);
	//	cubePoints[5] = Vec3(extents.x, -extents.y, extents.z);
	//	cubePoints[6] = Vec3(extents.x, extents.y, extents.z);
	//	cubePoints[7] = Vec3(-extents.x, extents.y, extents.z);

	//	//Face 1
	//	vertices[0] = Vertex(cubePoints[0], vec2(0, 1));
	//	vertices[1] = Vertex(cubePoints[1], vec2(1, 1));
	//	vertices[2] = Vertex(cubePoints[2], vec2(1, 0));
	//	vertices[3] = Vertex(cubePoints[3], vec2(0, 0));
	//	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	//	indices[3] = 1; indices[4] = 2; indices[5] = 3;
	//	
	//	//Face 2
	//	vertices[4] = Vertex(cubePoints[1], vec2(0, 1));
	//	vertices[5] = Vertex(cubePoints[5], vec2(1, 1));
	//	vertices[6] = Vertex(cubePoints[6], vec2(1, 0));
	//	vertices[7] = Vertex(cubePoints[2], vec2(0, 0));
	//	indices[6] = 4; indices[7] = 5; indices[8] = 7;
	//	indices[9] = 5; indices[10] = 6; indices[11] = 7;

	//	//Face 3
	//	vertices[8] = Vertex(cubePoints[5], vec2(0, 1));
	//	vertices[9] = Vertex(cubePoints[4], vec2(1, 1));
	//	vertices[10] = Vertex(cubePoints[7], vec2(1, 0));
	//	vertices[11] = Vertex(cubePoints[6], vec2(0, 0));
	//	indices[12] = 8; indices[13] = 9; indices[14] = 11;
	//	indices[15] = 9; indices[16] = 10; indices[17] = 11;

	//	//Face 4
	//	vertices[12] = Vertex(cubePoints[4], vec2(0, 1));
	//	vertices[13] = Vertex(cubePoints[0], vec2(1, 1));
	//	vertices[14] = Vertex(cubePoints[3], vec2(1, 0));
	//	vertices[15] = Vertex(cubePoints[7], vec2(0, 0));
	//	indices[18] = 12; indices[19] = 13; indices[20] = 15;
	//	indices[21] = 13; indices[22] = 14; indices[23] = 15;

	//	//Face 5
	//	vertices[16] = Vertex(cubePoints[3], vec2(0, 1));
	//	vertices[17] = Vertex(cubePoints[2], vec2(1, 1));
	//	vertices[18] = Vertex(cubePoints[6], vec2(1, 0));
	//	vertices[19] = Vertex(cubePoints[7], vec2(0, 0));
	//	indices[24] = 16; indices[25] = 17; indices[26] = 19;
	//	indices[27] = 17; indices[28] = 18; indices[29] = 19;

	//	//Face 6
	//	vertices[20] = Vertex(cubePoints[4], vec2(0, 1));
	//	vertices[21] = Vertex(cubePoints[5], vec2(1, 1));
	//	vertices[22] = Vertex(cubePoints[1], vec2(1, 0));
	//	vertices[23] = Vertex(cubePoints[0], vec2(0, 0));
	//	indices[30] = 20; indices[31] = 21; indices[32] = 23;
	//	indices[33] = 21; indices[34] = 22; indices[35] = 23;

	//	mesh = new Mesh(vertices, 24, indices, 36);
	//}
	//void AABB::Render(Shader *s) {
	//	Matrix4X4 modelMatrix = transform.GetTRSMatrix();
	//	Matrix4X4 mvp = (modelMatrix * globalViewMatrix) * globalProjectionMatrix;

	//	s->SetTransform(mvp);
	//	s->SetColor(mesh->color);

	//	mesh->Draw();
	//}

	//AABB
	Point AABB::GetMin() {
		Point p1 = position + size/2;
		Point p2 = position - size/2;

		return Point{
			fminf(p1.x, p2.x),
			fminf(p1.y, p2.y),
			fminf(p1.z, p2.z)
		};
	}
	Point AABB::GetMax() {
		Point p1 = position + size/2;
		Point p2 = position - size/2;

		return Point{
			fmaxf(p1.x, p2.x),
			fmaxf(p1.y, p2.y),
			fmaxf(p1.z, p2.z)
		};
	}
	AABB CreateAABBFromMinMax(const Point &min, const Point &max) {
		Point position = (min + max) * 0.5f;
		Vec3 extents = (max - min) * 0.5f;
		return AABB(position, extents);
	}

#pragma endregion
	//Plane
	//Returns >0 if the point is infront of the plane and < 0 if the point is behind the plane
	float Plane::PlaneEquation(const Point& point) {
		return Dot(point, normal) - distance;
	}


}