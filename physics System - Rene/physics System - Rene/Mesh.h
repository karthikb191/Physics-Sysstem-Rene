#pragma once
#ifndef H_MESH
#define H_MESH
#include"Vectors.h"
#include<GL\glew.h>
using namespace _Maths;

class Vertex {
public:
	Vertex(const Vec3& pos, const Vec2& texCord) : position(pos), texCoord(texCord) {}
	Vertex(const float& x, const float& y, const float& z, const float &tx, const float &ty) 
								: position(Vec3(x, y, z)), texCoord(vec2(tx, ty)){}

	inline Vec3* GetPosition() { return &position; }
	inline Vec2* GetTexCoord() { return &texCoord; }
private:
	Vec3 position;
	Vec2 texCoord;
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	~Mesh();
	void Draw();

private:
	Mesh(const Mesh& other);
	void operator=(const Mesh &other);

	enum {
		POSITION_VB,
		TEXCOORD_VB,	//We have another vertex buffer for out texture coordinates
		NUM_BUFFERS	//This member is only to keep track of the number of items in the enumeration
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;	//This keeps track of how many things or vertices we are going to draw
};

#endif // !H_MESH
