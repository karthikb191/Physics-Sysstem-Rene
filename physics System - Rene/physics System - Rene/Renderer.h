#pragma once
#include"GL\glew.h"
#include"Shader.h"


//Vertex and index buffers are being designed as state machines.
//Create first, then follow up with other operations

///Functions within these buffers are static. Classes operating on these functions are responsible for 
///Destruction operations. The destructor function of this class doesnt handle that scenario
class VertexBuffer {
public:
	//TODO: Consider adding same parameters as the create function to the constructor
	//VertexBuffer() {}

	//This creates a buffer from the specified vertices
	static GLuint Create(const void* data, int size, int count);
	static GLuint Create(const float* data, int size, int count);

	static void Bind(GLuint *rendererId = nullptr);
	static void UnBind();

	~VertexBuffer();

public:
	static GLuint m_rendererId;
};

class IndexBuffer {
public:
	//IndexBuffer();
	//This creates a buffer from the specified indices
	static GLuint Create(int* indices, int size, int count);

	static void Bind(GLuint *rendererId = nullptr);
	static void UnBind();
	~IndexBuffer();

public:
	static GLuint m_rendererId;
};

class IRenderer {
public:
	virtual ~IRenderer() {};
	virtual void Render(Shader *s) = 0;
	
};