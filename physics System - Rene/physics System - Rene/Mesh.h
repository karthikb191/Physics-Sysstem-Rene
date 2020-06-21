#pragma once
#ifndef H_MESH
#define H_MESH

#include<GL\glew.h>
#include "Renderer.h"
#include "Transform.h"

//Forward Declares
class Transform;

using namespace _Maths;
//using namespace _Geometry3D;


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

namespace _Primitives {
	typedef Vec3 Point;
	

	class Primitive:IRenderer{
	public:
		//Creates a box of unit length
		Primitive();
		Primitive(Point position, Vec3 rotation, Vec3 scale);
		Primitive(Point position);
		
		Transform transform;

	protected:
		Point position;
		Vec3 scale;
		Vec3 rotation;
		Matrix3X3 orientation;

	public:

		Mesh *mesh;
		virtual void Render(Shader *s);
		virtual void Create() = 0;
		virtual ~Primitive() { delete mesh; }
	};

	class Box : public Primitive{
	public:
		Box();
		Box(Point position, vec3 size);

		virtual void Create();

	private:
		Vec3 size;
	};

	class Sphere : public Primitive {
	public:
		Sphere();
		Sphere(Point position);

		virtual void Create();
	};

};


#endif // !H_MESH
