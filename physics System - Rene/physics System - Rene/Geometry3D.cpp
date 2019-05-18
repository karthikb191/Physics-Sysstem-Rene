#include "Geometry3D.h"
#include<iostream>
#include"Header.h"
namespace _Geometry3D
{
	float Line::Length() {
		return Magnitude(end - start);
	}
	float Line::LengthSq() {
		return MagnitudeSq(end - start);
	}

	//Ray
	Ray CreateRayFromPoints(const Point &start, const Point &end) {
		Ray r(start, end - start);
		return r;
	}

	//AABB
	Point AABB::GetMin() {
		Point p1 = position + extents;
		Point p2 = position - extents;

		return Point{
			fminf(p1.x, p2.x),
			fminf(p1.y, p2.y),
			fminf(p1.z, p2.z)
		};
	}
	Point AABB::GetMax() {
		Point p1 = position + extents;
		Point p2 = position - extents;

		return Point{
			fmaxf(p1.x, p2.x),
			fmaxf(p1.y, p2.y),
			fmaxf(p1.z, p2.z)
		};
	}
	AABB CreateAABBFromMinMax(const Point &min, const Point &max) {
		Point position = (min + max) * 0.5f;
		Vec3 extents = (max - min) * 0.5f;
		return AABB(position, extents);
	}

	//Plane
	//Returns 1 if the point is infront of the plane and -1 if the point is behind the plane
	float Plane::PlaneEquation(const Point& point) {
		return Dot(point, normal) - distance;
	}


}