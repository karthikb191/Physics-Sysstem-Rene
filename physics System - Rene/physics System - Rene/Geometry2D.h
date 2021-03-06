#pragma once
#ifndef _H_2D_GEOMETRY
#define _H_2D_GEOMETRY

#include "Vectors.h"
#include "Matrices.h"

namespace _Geometry2D {
	using namespace _Maths;

	//Creating Aliases for intuitive function calls
#define PointLine(point, line) PointOnLine(point, line);
#define LinePoint(line, point) PointOnLine(point, line);
#define CircleLine(circle, line) LineCircle(line, circle);
#define RectangleLine(rectangle, line) LineRectangle(line, rectangle);
#define OrientedRectangleLine(rectangle, line) LineOrientedRectangle(line, rectangle);
#define PointRectangle(point, rectangle) PointInRectangle(point, rectangle)
#define	PointOrientedRectangle(point, rectangle) PointInOrientedRectangle(point, rectangle);

#define RectangleCircle(rectangle, circle) CircleRectangle(circle, rectangle);
#define OrientedRectangleCircle(rectange, circle) CircleOrientedRectangle(circle, rectangle);
#define OrientedRectangleRectangle(orientedRectangle, rectangle) RectangleOrientedRectangle(rectangle, orientedRectangle);

	//A point is simply a 2D vector. Using typedef allows for intuitive representation of the point
	typedef vec2 Point2D;
	typedef vec3 Point3D;

	typedef struct Line2D {
		inline Line2D() {
			start = vec2();	end = vec2();
		}
		inline Line2D(const Point2D& start, const Point2D& end) {
			this->start = start;
			this->end = end;
		}
		vec2 start, end;

		//Member Functions
		float Length();
		float LengthSq();

		void Draw(const vec3& color = Vec3());
	}Line2D;

	typedef struct Circle {
		inline Circle() {
			//Default constructor Generates a circle of unit radius at origin
			this->center = Vec2();
			this->radius = 1.0f;
		}
		inline Circle(const Point2D& center, const float& radius) {
			this->center = center;
			this->radius = radius;
		}

		Point2D center;
		float radius;

		void Draw(const vec3& color = Vec3());
	}Circle;

	//Our Rectangle is represented in the Origin-Size notation
	//Size is a 2d vector that can have different values for different dimensions
	typedef struct Rectangle2D {
		//Default constructor initializes a rectangle os size (1, 1) at origin
		inline Rectangle2D() : origin(Point2D()), size(vec2(1, 1)) { }

		inline Rectangle2D(const Point2D& origin, const vec2& size) {
			this->origin = origin;	this->size = size;
		}

		Point2D origin;
		vec2 size;

		//Member Functions
		Point2D GetMax() const;
		Point2D GetMin() const;
		Rectangle2D FromMinMax(const vec2& min, const vec2& max);

		void Draw(const vec3& color = Vec3());

	}Rectangle2D;


	//We are going to represent the oriented rectangle using Center-Extents method
	typedef struct OrientedRectangle {

		inline OrientedRectangle() : center(0, 0), halfExtents(vec2(1, 1)), rotation(0) {}
		inline OrientedRectangle(const Point2D &center, const vec2 &halfExtents) {
			this->center = center;
			this->halfExtents = halfExtents;
			this->rotation = 0;
		}
		inline OrientedRectangle(const Point2D &center, const vec2 &halfExtents, const float& rotation) {
			this->center = center;
			this->halfExtents = halfExtents;
			this->rotation = rotation;
		}

		Point2D center;
		vec2 halfExtents;
		float rotation;	//Rotation for a 2D object is only meaningful in z-Axis 

		void Draw(const vec3& color = Vec3());
	}OrientedRectangle;

	//Point Containment Functions
	bool PointOnLine(const Point2D &point, const Line2D &line);
	bool PointInCircle(const Point2D &point, const Circle &circle);
	bool PointInRectangle(const Point2D &point, const Rectangle2D &rectangle);
	bool PointInOrientedRectangle(const Point2D &point, const OrientedRectangle &orientedRectangle);

	//Line Intersection tests
	bool LineCircle(const Line2D &line, const Circle &circle);	//TODO: need to change this to a better function
	bool LineRectangle(const Line2D &line, const Rectangle2D &circle);
	bool LineOrientedRectangle(const Line2D &line, const OrientedRectangle &circle);

	//Detecting Collision between two primitive shapes
	bool CircleCircle(const Circle &circle1, const Circle &circle2);
	bool CircleRectangle(const Circle &circle, const Rectangle2D &rectangle);
	bool CircleOrientedRectangle(const Circle &circle, const OrientedRectangle &rectangle);

	bool RectangleRectangle(const Rectangle2D &rectangle1, const Rectangle2D &rectangle2);
	bool RectangleOrientedRectangle(const Rectangle2D &rectangle, const OrientedRectangle &orientedRectangle);
	bool OrientedRectangleOrientedRectangle(const OrientedRectangle &orientedRectangle1, const OrientedRectangle &orientedRectangle2);

	//Separating Axis theorem Function
}
#endif