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
	void Sphere::Create() {
		//Change these later
		//std::vector<Vec3> vertices;
		//std::vector<int> indices;
		const int horizontalDivisions = 10;
		const int verticalDivisions = 10;

		Vertex verts[horizontalDivisions * verticalDivisions + 1];
		Vec3 vertices[horizontalDivisions * verticalDivisions + 1];
		vec2 texCoords[horizontalDivisions * verticalDivisions + 1];
		int indices[30 + horizontalDivisions * verticalDivisions * 6];


		float pi = DEG2RAD(180);
		float yDivisions = pi / verticalDivisions;
		float xDivisions = (pi * 2) / horizontalDivisions;
		std::cout << "x divisions: " << xDivisions << std::endl;
		//First Vertex
		float yAngle = 0;
		float y = cosf(0);
		float x = 0;
		float z = 0;
		vertices[0] = { x, y, z };
		verts[0].position = { x, y, z };
		verts[0].texCoord = { x, z };

		for (int i = 0; i < verticalDivisions - 1; i++) {
			//We make a unit circle initially. Radius and position is added during the matrix construction
			//Pivot will be at the center
			float y1 = cosf(yDivisions * (i+1));
			float radiusOfRing = sinf(yDivisions * (i + 1));

			float x1 = radiusOfRing * cos(0);
			float z1 = radiusOfRing * sin(0);

			//std::cout << "vert number: " << i * horizontalDivisions + 1 << std::endl;
			//std::cout << " " << x1 << " " << y1 << " " << z1 << std::endl;

			vertices[i * horizontalDivisions + 1] = {x1, y1, z1};
			verts[i * horizontalDivisions + 1].position = {x1, y1, z1};
			verts[i * horizontalDivisions + 1].texCoord = {x1, z1};

			//std::cout << "index : " << i * horizontalDivisions + 1 << " vert: " << *verts[i * horizontalDivisions + i].GetPosition() << std::endl;

			std::cout << " verts: " << std::endl;
			for (int j = 1; j < horizontalDivisions; j++) {
				float x2 = radiusOfRing * cos(j * xDivisions);
				float z2 = radiusOfRing * sin(j * xDivisions);
				
				//std::cout << "vert number: " << i * horizontalDivisions + 1 + j << std::endl;
				//std::cout << " " << x2 << " " << y1 << " " << z2 << std::endl;

				//vertices[i * horizontalDivisions + 1 + j] = {x2, y1, z2};
				verts[i * horizontalDivisions + 1 + j].position = {x2, y1, z2};
				verts[i * horizontalDivisions + 1 + j].texCoord = {x2, z2};
				std::cout << " " << (i * horizontalDivisions) + 1 + j ;

				//std::cout << "index : " << i * horizontalDivisions + i + j << " vert: " << *verts[i * horizontalDivisions + i + j].GetPosition() << std::endl;

				if (i == 0) {
					indices[3 * (j - 1)] = 0;
					indices[3 * (j - 1) + 1] = j;
					indices[3 * (j - 1) + 2] = j + 1;
					std::cout << 3 * (j - 1) << 3 * (j - 1) + 1 << 3 * (j - 1) + 2 << std::endl;

					if (j == horizontalDivisions - 1) {
						indices[3 * (horizontalDivisions - 1)] = 0;
						indices[3 * (horizontalDivisions - 1) + 1] = 10;
						indices[3 * (horizontalDivisions - 1) + 2] = 1;

						//std::cout << "index : " << 3 * (horizontalDivisions - 1);
						//std::cout << "index : " << 3 * (horizontalDivisions - 1) + 1;
						//std::cout << "index : " << 3 * (horizontalDivisions - 1) + 2 << std::endl;


						//std::cout << 3 * (horizontalDivisions - 1) << 3 * (horizontalDivisions - 1) + 1 << 3 * (horizontalDivisions - 1) + 2 << std::endl;
					}
				}
				else
				{
					//First Triangle
					//indices[horizontalDivisions * 3 * i + 6 * (j - 1)] = (j - 1) * horizontalDivisions + 1;
					//indices[horizontalDivisions * 3 * i + 6 * (j - 1)] = (j - 1) * horizontalDivisions + 1;
					//indices[horizontalDivisions * 3 * i + 6 * (j - 1) + 1] = j * horizontalDivisions + 1;
					indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1)] = (i - 1) * horizontalDivisions + j;
					indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 1] = i * horizontalDivisions + j;
					indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 2] = i * horizontalDivisions + j + 1;

					//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i-1) + 6 * (j - 1);
					//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 1;
					//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 2 << std::endl;

					//Second Triangle
					//indices[horizontalDivisions * 3 * i + 6 * (j - 1) + 3] = (j - 1) * horizontalDivisions + 1;
					//indices[horizontalDivisions * 3 * i + 6 * (j - 1) + 4] = j * horizontalDivisions + 2;
					//indices[horizontalDivisions * 3 * i + 6 * (j - 1) + 5] = (j - 1) * horizontalDivisions + 1;

					indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 3] = (i - 1) * horizontalDivisions + j;
					indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 4] = i * horizontalDivisions + j + 1;
					indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 5] = (i - 1) * horizontalDivisions + j + 1;
					//std::cout << "index : " << i * horizontalDivisions + i + j << " vert: " << *verts[i * horizontalDivisions + i + j].GetPosition() << std::endl;

					//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i-1) + 6 * (j - 1) + 3;
					//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 4;
					//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 5 << std::endl;
				}
			}
			std::cout << "end" << std::endl;

			
		}
		//Creating a mesh
		//std::cout << "Vert Count : " << sizeof(verts) / sizeof(verts[0]) << std::endl;
		mesh = new Mesh(verts, horizontalDivisions * verticalDivisions, indices, 30 + horizontalDivisions * verticalDivisions * 6);
	}

	//Render a sphere and send the data to openGL
	void Sphere::Render(Shader *s) const{
		//std::cout << "Rendering sphere" << std::endl;

		//Create a model matrix
		//TODO: Create proper transform API for objects
		Matrix4X4 modelMatrix = Transform(Vec3(1 * 100, 1 * 100, 1 * 100), Vec3(0, 0, 0), Vec3(0, 0, 0));
		
		//std::cout << globalViewMatrix  << std::endl;

		Matrix4X4 mvp = (modelMatrix * globalViewMatrix) * globalProjectionMatrix;
		//Using the default shader. It has been created already. Only needs Updating
		s->Update(mvp);
		//Draw only after the shader is updated
		mesh->Draw();
	}

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

	//AABB
	Point AABB::GetMin() {
		Point p1 = position + extents;
		Point p2 = position - extents;

		return Point{
			fminf(p1.x, p2.x),
			fminf(p1.y, p2.y),
			fminf(p1.z, p2.z)
		};
	}
	Point AABB::GetMax() {
		Point p1 = position + extents;
		Point p2 = position - extents;

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

	//Plane
	//Returns >0 if the point is infront of the plane and < 0 if the point is behind the plane
	float Plane::PlaneEquation(const Point& point) {
		return Dot(point, normal) - distance;
	}


}