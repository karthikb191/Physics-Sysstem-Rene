#pragma once
#include "Mesh.h"
#include<vector>
#include "Globals.h"

using namespace _GlobalVariables;

//Static members define
//GLuint* VertexBuffer::m_rendererId = nullptr;
//GLuint* IndexBuffer::m_rendererId = nullptr;

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, int *indices, unsigned int numIndices) {
	//TODO: Create an interleaved version of vertexarrays

	m_drawCount = numVertices;
	this->numIndices = numIndices;

	//Generated the specified number of vertex arrays and stores them in the specified variable
	glGenVertexArrays(1, &m_vertexArrayObject);

	//Now that we have generated vertex array object, we have to use it
	//To use a vertex array object, we have to bind
	//All the operations we do now will affect the bound vertex array
	glBindVertexArray(m_vertexArrayObject);

	std::vector<Vec3> positions;
	std::vector<vec2> texCoords;

	//Since we already know the amount of verices we will be dealing with,
	//This reserves space linearly. Nothing special about this. It's a simple vector thing
	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	
	float* poisitionFloats;
	poisitionFloats = new float[numVertices * 3];
	for (int i = 0; i < numVertices; i++) {
		poisitionFloats[i * 3] = *vertices[i].GetPosition()->asArray;
		poisitionFloats[1 * 3 + 1] = *vertices[i].GetPosition()->asArray;
		poisitionFloats[i * 3 + 2] = *vertices[i].GetPosition()->asArray;
		positions.push_back(*vertices[i].GetPosition());
		texCoords.push_back(*vertices[i].GetTexCoord());
	}
	//Create bunch of vertex buffers
	//VertexBuffer vb = VertexBuffer();
	m_vertexArrayBuffers[POSITION_VB] = VertexBuffer::Create(&positions[0], numVertices * sizeof(positions[0]), numVertices);
	m_vertexArrayBuffers[TEXCOORD_VB] = VertexBuffer::Create(&texCoords[0], numVertices * sizeof(texCoords[0]), numVertices);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	VertexBuffer::Bind(&m_vertexArrayBuffers[POSITION_VB]);
	//BUffer is just an arbitrary block of data
	//Allocates space on GPU as buffers
	//glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	//
	////After generating the buffers, we must bind the data into them
	////This acts as the link to the shader's atributes
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);	//GL_ARRAY_BUFFER tells opengl to interpret buffer of data as array
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	std::cout << sizeof(&positions) * numVertices * 3 << " " << numVertices * sizeof(positions[0]) ;
	//glBufferData(GL_ARRAY_BUFFER, sizeof(poisitionFloats[0]) * numVertices * 3, poisitionFloats, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//int indices[] = { 0, 1, 2, 0, 3, 1};
	IndexBuffer::Create(indices, sizeof(int) * numIndices, numIndices);

	VertexBuffer::Bind(&m_vertexArrayBuffers[TEXCOORD_VB]);
	
	//VertexBuffer vb1;
	////glBindVertexArray(0);
	//m_vertexArrayBuffers[TEXCOORD_VB] = vb1.Create(&texCoords, numVertices);

	//We bind the buffer data for the TEXCOORD 
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);	//We bind the texture coordinates to out array buffers
	//glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	

	glBindVertexArray(0);
}
Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject);

	//glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}

namespace _Primitives {

	Primitive::Primitive() : position(0, 0, 0), rotation(vec3()), scale(100, 100, 100) {
		transform = Transform(position, rotation, scale);

		//Create();
	}
	Primitive::Primitive(Point position, Vec3 rotation, Vec3 scale) {
		this->position = position;
		this->rotation = rotation;
		this->scale = scale * 100;

		transform = Transform(position, rotation, scale);
		//Create();
	}
	Primitive::Primitive(Point position) {
		this->position = position;
		this->rotation = Vec3();
		this->scale = Vec3(1, 1, 1);

		this->transform = Transform(position, rotation, scale * 100);
		//Create();
	}

	Box::Box() :Primitive(), size(1, 1, 1) { Create(); }
	Box::Box(Point position, vec3 size) {
		this->position = position;
		this->size = size;
		this->scale = Vec3(1, 1, 1);
		this->rotation = Vec3();

		this->transform = Transform(position, rotation, scale * 100);
		Create();
	}
	Sphere::Sphere() :Primitive() { Create(); }
	Sphere::Sphere(Point position) : Primitive(position) { Create(); }

	void Primitive::Render(Shader *shader) {

		//Create the model matrix
		Matrix4X4 modelMatrix = transform.GetTRSMatrix();

		//Generate MVP Matrix
		Matrix4X4 mvp = (modelMatrix * globalViewMatrix) * globalProjectionMatrix;

		//Feed this to shader
		shader->SetTransform(mvp);
		shader->SetColor(mesh->color);

		mesh->Draw();

	}

	void Sphere::Create(){
		//Change these later
		//std::vector<Vec3> vertices;
		//std::vector<int> indices;
		const int horizontalDivisions = 10;
		const int verticalDivisions = 10;

		Vertex verts[horizontalDivisions * verticalDivisions + 2];
		int indices[60 + horizontalDivisions * verticalDivisions * 6];


		float pi = DEG2RAD(180);
		float yDivisions = pi / verticalDivisions;
		float xDivisions = (pi * 2) / horizontalDivisions;
		std::cout << "x divisions: " << xDivisions << std::endl;

		//First Vertex
		float yAngle = 0;
		float y = 1;
		float x = 0;
		float z = 0;

		//Settting the initial vertex
		verts[0].position = { x, y, z };
		verts[0].texCoord = { x, z };

		for (int i = 0; i <= verticalDivisions - 1; i++) {
			//We make a unit circle initially. Radius and position is added during the matrix construction
			//Pivot will be at the center
			float y1 = cosf(yDivisions * (i + 1));
			std::cout << "Y : " << y1 << std::endl;
			float radiusOfRing = sinf(yDivisions * (i + 1));

			float x1 = radiusOfRing * cos(0);
			float z1 = radiusOfRing * sin(0);

			//std::cout << "vert number: " << i * horizontalDivisions + 1 << std::endl;
			//std::cout << " " << x1 << " " << y1 << " " << z1 << std::endl;

			verts[i * horizontalDivisions + 1].position = { x1, y1, z1 };
			verts[i * horizontalDivisions + 1].texCoord = { x1, z1 };

			std::cout << "index : " << i * horizontalDivisions + 1 << " vert: " << *verts[i * horizontalDivisions + 1].GetPosition() << std::endl;

			std::cout << " verts: " << std::endl;

			if (i == verticalDivisions - 1) {
				std::cout << "Last Vertex " << horizontalDivisions * (verticalDivisions - 1) + 1 << std::endl;
				//Last Vertex
				verts[horizontalDivisions * (verticalDivisions - 1) + 1].position = { 0, -1, 0 };
				verts[horizontalDivisions * (verticalDivisions - 1) + 1].texCoord = { 0, 0 };
			}

			for (int j = 1; j <= horizontalDivisions; j++) {

				if (i == verticalDivisions - 1) {
					int lastRowIndexBaseValue = 3 * horizontalDivisions + 6 * horizontalDivisions * (verticalDivisions - 2) + 3 * (j - 1);
					if (j == horizontalDivisions) {
						indices[lastRowIndexBaseValue] = horizontalDivisions * (verticalDivisions - 1) + 1;
						indices[lastRowIndexBaseValue + 2] = horizontalDivisions * (verticalDivisions - 1);
						indices[lastRowIndexBaseValue + 1] = horizontalDivisions * (verticalDivisions - 2) + 1;

						break;
					}

					//Last Mesh
					//Assign Indices for triangles
					indices[lastRowIndexBaseValue] = horizontalDivisions * (verticalDivisions - 1) + 1;
					indices[lastRowIndexBaseValue + 2] = horizontalDivisions * (verticalDivisions - 2) + j;
					indices[lastRowIndexBaseValue + 1] = horizontalDivisions * (verticalDivisions - 2) + j + 1;

					continue;
				}

				//std::cout << "vert number: " << i * horizontalDivisions + 1 + j << std::endl;
				//std::cout << " " << x2 << " " << y1 << " " << z2 << std::endl;

				int vertNumber = i * horizontalDivisions + 1 + j;
				int indexBaseNumberForRow = (3 * horizontalDivisions) + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1);

				float x2 = radiusOfRing * cos(j * xDivisions);
				float z2 = radiusOfRing * sin(j * xDivisions);

				if (j == horizontalDivisions) {

					if (i == 0)
						break;

					//First Triangle 
					indices[indexBaseNumberForRow] = i * horizontalDivisions;
					indices[indexBaseNumberForRow + 1] = (i + 1) * horizontalDivisions;
					indices[indexBaseNumberForRow + 2] = i * horizontalDivisions + 1;
					//
					//Second Triangle
					indices[indexBaseNumberForRow + 3] = i * horizontalDivisions;
					indices[indexBaseNumberForRow + 4] = i * horizontalDivisions + 1;
					indices[indexBaseNumberForRow + 5] = (i - 1) * horizontalDivisions + 1;

					break;
				}


				//vertices[i * horizontalDivisions + 1 + j] = {x2, y1, z2};
				verts[vertNumber].position = { x2, y1, z2 };
				verts[vertNumber].texCoord = { x2, z2 };

				std::cout << " " << (i * horizontalDivisions) + 1 + j;

				std::cout << "index : " << vertNumber << " vert: " << *verts[vertNumber].GetPosition() << std::endl;

				if (i == 0) {
					indices[3 * (j - 1)] = 0;
					indices[3 * (j - 1) + 1] = j;
					indices[3 * (j - 1) + 2] = j + 1;

					//std::cout << 3 * (j - 1) << 3 * (j - 1) + 1 << 3 * (j - 1) + 2 << std::endl;

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
					indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1)] = (i - 1) * horizontalDivisions + j;
					indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 1] = i * horizontalDivisions + j;
					indices[30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 2] = i * horizontalDivisions + j + 1;

					//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i-1) + 6 * (j - 1);
					//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 1;
					//std::cout << " index : " << 30 + horizontalDivisions * 6 * (i - 1) + 6 * (j - 1) + 2 << std::endl;

					//Second Triangle

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

	void Box::Create() {


		Vec3 cubePoints[8];
		Vertex vertices[24];
		int indices[36];

		Vec3 extents = size / 2;

		cubePoints[0] = Vec3(-extents.x, -extents.y, -extents.z);
		cubePoints[1] = Vec3(extents.x, -extents.y, -extents.z);
		cubePoints[2] = Vec3(extents.x, extents.y, -extents.z);
		cubePoints[3] = Vec3(-extents.x, extents.y, -extents.z);
		cubePoints[4] = Vec3(-extents.x, -extents.y, extents.z);
		cubePoints[5] = Vec3(extents.x, -extents.y, extents.z);
		cubePoints[6] = Vec3(extents.x, extents.y, extents.z);
		cubePoints[7] = Vec3(-extents.x, extents.y, extents.z);

		//Face 1
		vertices[0] = Vertex(cubePoints[0], vec2(0, 1));
		vertices[1] = Vertex(cubePoints[1], vec2(1, 1));
		vertices[2] = Vertex(cubePoints[2], vec2(1, 0));
		vertices[3] = Vertex(cubePoints[3], vec2(0, 0));
		indices[0] = 0; indices[1] = 1; indices[2] = 3;
		indices[3] = 1; indices[4] = 2; indices[5] = 3;

		//Face 2
		vertices[4] = Vertex(cubePoints[1], vec2(0, 1));
		vertices[5] = Vertex(cubePoints[5], vec2(1, 1));
		vertices[6] = Vertex(cubePoints[6], vec2(1, 0));
		vertices[7] = Vertex(cubePoints[2], vec2(0, 0));
		indices[6] = 4; indices[7] = 5; indices[8] = 7;
		indices[9] = 5; indices[10] = 6; indices[11] = 7;

		//Face 3
		vertices[8] = Vertex(cubePoints[5], vec2(0, 1));
		vertices[9] = Vertex(cubePoints[4], vec2(1, 1));
		vertices[10] = Vertex(cubePoints[7], vec2(1, 0));
		vertices[11] = Vertex(cubePoints[6], vec2(0, 0));
		indices[12] = 8; indices[13] = 9; indices[14] = 11;
		indices[15] = 9; indices[16] = 10; indices[17] = 11;

		//Face 4
		vertices[12] = Vertex(cubePoints[4], vec2(0, 1));
		vertices[13] = Vertex(cubePoints[0], vec2(1, 1));
		vertices[14] = Vertex(cubePoints[3], vec2(1, 0));
		vertices[15] = Vertex(cubePoints[7], vec2(0, 0));
		indices[18] = 12; indices[19] = 13; indices[20] = 15;
		indices[21] = 13; indices[22] = 14; indices[23] = 15;

		//Face 5
		vertices[16] = Vertex(cubePoints[3], vec2(0, 1));
		vertices[17] = Vertex(cubePoints[2], vec2(1, 1));
		vertices[18] = Vertex(cubePoints[6], vec2(1, 0));
		vertices[19] = Vertex(cubePoints[7], vec2(0, 0));
		indices[24] = 16; indices[25] = 17; indices[26] = 19;
		indices[27] = 17; indices[28] = 18; indices[29] = 19;

		//Face 6
		vertices[20] = Vertex(cubePoints[4], vec2(0, 1));
		vertices[21] = Vertex(cubePoints[5], vec2(1, 1));
		vertices[22] = Vertex(cubePoints[1], vec2(1, 0));
		vertices[23] = Vertex(cubePoints[0], vec2(0, 0));
		indices[30] = 20; indices[31] = 21; indices[32] = 23;
		indices[33] = 21; indices[34] = 22; indices[35] = 23;

		mesh = new Mesh(vertices, 24, indices, 36);

	}
}