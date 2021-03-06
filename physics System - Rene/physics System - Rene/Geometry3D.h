#pragma once
#ifndef _H_GEOMETRY3D
#define _H_GEOMETRY3D

#include "Transform.h"
#include "Vectors.h"
#include "Matrices.h"
#include "Renderer.h"
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
	typedef struct Sphere : IRenderer{
		inline Sphere(){
			center = Vec3();
			radius = 1.0f;
			transform.Scale = transform.Scale * 100;
			//Create();
		}
		inline Sphere(const Point &center, const float &radius) {
			this->center = center;
			this->radius = 1.0f;
			transform.Position = center;
			transform.Scale = transform.Scale * 100;
			//Create();
		}

		Transform_Class transform;
		Point center;
		float radius;
		//Mesh *mesh;
		
		void Create();
		void Render(Shader *s) override {}

	}Sphere;

	//This is position-extents representation
	typedef struct AABB : IRenderer{
		inline AABB() {
			position = Point();
			size = Vec3(1, 1, 1);
			size = size * 100;
			//Create default transform data 
			transform = Transform(position, Vec3(), size);
			
			//Create();
		}
		inline AABB(const Point &origin, const Vec3 &size) {
			this->position = origin;
			//this->size = size;
			this->size = size * 100;
			//Create new transform data from specified location and scale
			transform = Transform_Class(position, Vec3(), size);
			std::cout << "Position of Box Spawn: " << transform.Position << std::endl;
			//Create();
		}

		//Mesh *mesh;					//Mesh data is populated in the create function
		Transform transform;
		Point position;
		Vec3 size;

		Point GetMin() const;
		Point GetMax() const;

		void Create();
		void Render(Shader *s) override {}
		//virtual void Render() {}
	}AABB;
	AABB CreateAABBFromMinMax(const Point &min, const Point &max);

	typedef struct OBB : IRenderer {
		//Construct a OBB of unit size and no orientation by default, placed at origin
		inline OBB() {
			position = Vec3();	size = Vec3(1, 1, 1);
			orientation = Matrix3X3();
			Create();
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

		Transform_Class transform;
		Point position;
		Vec3 size;
		Matrix3X3 orientation;

		void Create();
		void Render(Shader *s) override {}
	}OBB;


	//A Plane is defined by a normal and distance from the origin
	typedef struct Plane {

		inline Plane() : normal(0, 0, 1) {}
		inline Plane(Vec3 normal, float distance) {
			this->normal = normal;
			this->distance = distance;
		}

		Vec3 normal;
		float distance;
		//Returns 1 if the point is infront of the plane and -1 if the point is behind the plane
		float PlaneEquation(const Point& point);

		//void Create();
		//void Render(Shader *s) const override;
	}Plane;

	typedef struct Triangle : IRenderer {
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

		void Create();
		void Render(Shader *s) override;
	}Tri;

	//Point Intersetion Tests
	bool PointInSphere(const Point &point, const Sphere &sphere);
	Point ClosestPoint(const Point &point, const Sphere &sphere);
	bool PointInAABB(const Point &point, const AABB &aabb);
	Point ClosestPoint(const Point &point, const AABB &aabb);
	bool PointInOBB(const Point &point, const OBB &obb);
	Point ClosestPoint(const Point &point, const OBB &obb);
	bool PointOnPlane(const Point& point, const Plane& plane);
	Point ClosestPoint(const Point& point, const Plane& plane);
	bool PointOnLine(const Point& point, const Line &line);
	Point ClosestPoint(const Point& point, const Line &line);
	bool PointOnRay(const Point& point, const Ray &ray);
	Point ClosestPoint(const Point& point, const Ray &ray);

};
#endif // !define _H_GEOMETRY3D