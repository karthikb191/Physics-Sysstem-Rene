#include "Mesh.h"
#include<vector>
#include "Matrices.h"

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
	//This reserves space linearly.
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