#pragma once
#ifndef H_MESH
#define H_MESH
#include"Vectors.h"
#include<GL\glew.h>
#include"Renderer.h"
using namespace _Maths;



class Vertex {
public:
	Vertex() : position({ 0, 0, 0 }), texCoord({0, 0}) {}
	Vertex(const Vec3& pos, const Vec2& texCord) : position(pos), texCoord(texCord) {}
	Vertex(const float& x, const float& y, const float& z, const float &tx, const float &ty) 
								: position(Vec3(x, y, z)), texCoord(vec2(tx, ty)){}

	inline Vec3* GetPosition() { return &position; }
	inline Vec2* GetTexCoord() { return &texCoord; }
public:
	Vec3 position;
	Vec2 texCoord;
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices, int *indices, unsigned int numIndices);
	~Mesh();
	void Draw();
	//void AssignShader();

private:
	Mesh(const Mesh& other);
	void operator=(const Mesh &other);

	enum {
		POSITION_VB,
		TEXCOORD_VB,	//We have another vertex buffer for out texture coordinates
		NUM_BUFFERS	//This member is only to keep track of the number of items in the enumeration
	};

	Shader *m_shader = nullptr;
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	GLuint numIndices;
	unsigned int m_drawCount;	//This keeps track of how many things or vertices we are going to draw

public:
	vec4 color = vec4(1, 1, 1, 1);
};

#endif // !H_MESH
