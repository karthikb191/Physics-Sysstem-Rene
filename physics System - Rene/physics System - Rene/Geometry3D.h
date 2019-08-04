#pragma once
#ifndef _H_GEOMETRY3D
#define _H_GEOMETRY3D

#include "Vectors.h"
#include "Matrices.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Shader.h"
namespace _Geometry3D {
	using namespace _Maths;

	//Aliases for the functions goes here

	//3D objects
	typedef Vec3 Point;

	//Line is represented by a starting point and an ending point
	typedef struct Line {
		Line() {
			this->start = Vec3();
			this->end = Vec3(1, 1, 1);
		}
		Line(const Point &s, const Point &e) {
			this->start = s;
			this->end = e;
		}

		Point start;
		Point end;

		float Length();
		float LengthSq();

	}Line3D;

	//Ray is defined by a starting point and a direction
	typedef struct Ray {
		//Ray points right if nothing is provided in the constructor
		Ray() {
			this->start = Vec3();
			this->direction = Vec3(1, 0, 0);
		}
		Ray(const Point &start, const Vec3 &direction) {
			this->start = start;
			this->direction = direction;
		}
		Point start;
		Vec3 direction;
	}Ray3D;
	Ray CreateRayFromPoints(const Point &a, const Point &b);

	//Sphere is one of the very simplest shapes. It makes it very efficient for collision detection
	typedef struct Sphere : Renderer{
		inline Sphere(){
			center = Vec3();
			radius = 1.0f;
			Create();
		}
		inline Sphere(const Point &center, const float &radius) {
			this->center = center;
			this->radius = radius;
			Create();
		}

		Point center;
		float radius;
		Mesh *mesh;

		void Create();
		void Render(Shader *s) const override;

	}Sphere;

	//This is position-extents representation
	typedef struct AABB {
		inline AABB() {
			position = Point();
			extents = Vec3(1, 1, 1);
		}
		inline AABB(const Point &origin, const Vec3 &extents) {
			this->position = origin;
			this->extents = extents;
		}

		Point position;
		Vec3 extents;

		Point GetMin();
		Point GetMax();

		//virtual void Render() {}
	}AABB;
	AABB CreateAABBFromMinMax(const Point &min, const Point &max);

	typedef struct OBB {
		//Construct a OBB of unit size and no orientation by default, placed at origin
		inline OBB() {
			position = Vec3();	size = Vec3(1, 1, 1);
			orientation = Matrix3X3();
		}
		//Construct the OBB at specified size, default orientation and at specified position
		inline OBB(const Point& position, const vec3 &size) {
			this->position = position;
			this->size = size;
			orientation = Matrix3X3();
		}
		//Construct OBB at specified size, specified orientation and at specified position
		inline OBB(const Point& position, const vec3 &size, const Matrix3X3 &orientation) {
			this->position = position;
			this->size = size;
			this->orientation = orientation;
		}

		Point position;
		Vec3 size;
		Matrix3X3 orientation;
	}OBB;


	//A Plane is defined by a normal and distance from the origin
	typedef struct Plane {

		inline Plane() : normal(1, 0, 1) {}
		inline Plane(Vec3 normal, float distance) {
			this->normal = normal;
			this->distance = distance;
		}

		Vec3 normal;
		float distance;
		//Returns 1 if the point is infront of the plane and -1 if the point is behind the plane
		float PlaneEquation(const Point& point);
	}Plane;

	typedef struct Triangle {
		inline Triangle() {}
		inline Triangle(const Point &pt1, const Point &pt2, const Point &pt3) {
			a = pt1;	b = pt2;	c = pt3;
		}
		union {
			struct {
				Point a;
				Point b;
				Point c;
			};
			Point points[3];
			float values[9];
		};
	}Tri;

	//Point Intersetion Tests

}
#endif // !define _H_GEOMETRY3D