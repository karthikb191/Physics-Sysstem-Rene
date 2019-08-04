#include"Renderer.h"
#include<iostream>

//Static members define
GLuint VertexBuffer::m_rendererId = 0;
GLuint IndexBuffer::m_rendererId = 0;

//Generate the buffers, Bind the buffers and then feed the data into them
GLuint VertexBuffer::Create(const void* data, int size, int count) {

	glCreateBuffers(1, &m_rendererId);	//Use this for combining generation and binding steps
	//Generate a single buffer and bind it
	//glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);

	//After generating the buffers and binding them, input the data to the buffer
	std::cout << "size................" << size << std::endl;
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	return m_rendererId;
}
GLuint VertexBuffer::Create(const float* vertices, int size, int count) {

	glCreateBuffers(1, &m_rendererId);	//Use this for combining generation and binding steps
	//Generate a single buffer and bind it
	//glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);

	//After generating the buffers and binding them, input the data to the buffer
	std::cout << "size................" << size << std::endl;
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	return m_rendererId;
}

void VertexBuffer::Bind(GLuint *rendererId) {
	if (rendererId != nullptr) {
		glBindBuffer(GL_ARRAY_BUFFER, *rendererId);
		return;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
}

void VertexBuffer::UnBind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
	if (m_rendererId != 0) {
		glDeleteBuffers(1, &m_rendererId);
	}
}

/////////////////////////////////////////////////////////////////
//Index Buffer Region
////////////////////////////////////////////////////////////////
GLuint IndexBuffer::Create(int* indices, int size, int count) {
	//Generate and bind the buffers
	glGenBuffers(1, &m_rendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);

	//Feed the data into the buffer after after generation and binding
	std::cout << "Binding the Indices buffer of size : " << size << std::endl;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	return m_rendererId;
}
void IndexBuffer::Bind(GLuint *rendererId) {
	if (rendererId != nullptr) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *rendererId);
		return;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
}
void IndexBuffer::UnBind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer() {
	if (m_rendererId != 0) {
		glDeleteBuffers(1, &m_rendererId);
	}
}