#include "Mesh.h"
#include<vector>
#include "Matrices.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices) {
	m_drawCount = numVertices;

	//Generated the specified number of vertex arrays and stores them in the specified variable
	glGenVertexArrays(1, &m_vertexArrayObject);

	//Now that we have generated vertex array object, we have to use it
	//To use a vertex array object, we have to bind
	//All the operations we do now will affect the bound vertex array
	glBindVertexArray(m_vertexArrayObject);

	std::vector<Vec3> positions;
	std::vector<vec2> texCoords;

	//Since we already know the amount of verices we will be dealing with,
	//We reserve the space before-hand
	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (int i = 0; i < numVertices; i++) {
		
		positions.push_back(*vertices[i].GetPosition());
		texCoords.push_back(*vertices[i].GetTexCoord());
	}

	//BUffer is just an arbitrary block of data
	//Allocates space on GPU as buffers
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	//After generating the buffers, we must bind the data into them
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);	//GL_ARRAY_BUFFER tells opengl to interpret buffer of data as array
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glBindVertexArray(0);


	//We bind the buffer data for the TEXCOORD 
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);	//We bind the texture coordinates to out array buffers
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}
Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}