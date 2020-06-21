#pragma once
#include "Geometry3D.h"
#include<iostream>
#include"Header.h"
#include"GL\glew.h"
#include <math.h>
#include <vector>
#include"Globals.h"

namespace _Geometry3D
{
	using namespace _GlobalVariables;
#pragma region Sphere


#pragma endregion

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

#pragma region AABB

	//AABB
	Point AABB::GetMin() const{
		Point p1 = position + size/2;
		Point p2 = position - size/2;

		return Point{
			fminf(p1.x, p2.x),
			fminf(p1.y, p2.y),
			fminf(p1.z, p2.z)
		};
	}
	Point AABB::GetMax() const{
		Point p1 = position + size/2;
		Point p2 = position - size/2;

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

#pragma region PointIntersectionTests
	bool PointInSphere(const Point & point, const Sphere & sphere)
	{
		Vec3 centerToPoint = sphere.center - point;
		float distanceSq = MagnitudeSq(centerToPoint);

		return distanceSq < (sphere.radius * sphere.radius);
	}

	Point ClosestPoint(const Point & point, const Sphere & sphere)
	{
		Point closestPoint;
		Vec3 normalizedDirection = Normalize(sphere.center - point);


		return sphere.center + (normalizedDirection * sphere.radius);
	}

	bool PointInAABB(const Point & point, const AABB & aabb)
	{
		Point min = aabb.GetMin();
		Point max = aabb.GetMax();
		return (point.x > min.x && point.x < max.x &&
				point.y > min.y && point.y < max.y &&
				point.z > min.z && point.z < max.z);
	}

	Point ClosestPoint(const Point & point, const AABB & aabb)
	{
		Point closestPoint = Point();

		Point min = aabb.GetMin();
		Point max = aabb.GetMax();

		closestPoint.x = point.x < min.x ? min.x : point.x;
		closestPoint.x = point.x > max.x ? max.x : point.x;
		closestPoint.y = point.y < min.y ? min.y : point.y;
		closestPoint.y = point.y > max.y ? max.y : point.y;
		closestPoint.z = point.z < min.z ? min.z : point.z;
		closestPoint.z = point.z > max.z ? max.z : point.z;

		return closestPoint;
	}

	bool PointInOBB(const Point & point, const OBB & obb)
	{
		Vec3 directionToPoint = point - obb.position;

		for (int i = 0; i < 3; i++) {
			//Get the address of the first element of axes
			const float *axis = &obb.orientation.asArray[i * 3];
			Vec3 axisVector = Vec3(axis[0], axis[1], axis[2]);

			//Project the point on this axis
			float projectionValue = Dot(directionToPoint, axisVector);
			if (abs(projectionValue) > obb.size.asArray[i])
				return false;
		}

		//The point is inside OBB if the length of projections on all three axes of OBB
		//is less than the size of OBB in the respective axes
		return true;
	}

	Point ClosestPoint(const Point & point, const OBB & obb)
	{
		Point closestPoint = obb.position;
		Vec3 directionToPoint = point - obb.position;

		for (int i = 0; i < 3; i++) {
			const float *axis = &obb.orientation.asArray[i * 3];
			Vec3 axisVector = Vec3(axis[0], axis[1], axis[2]);

			float projectionValue = Dot(directionToPoint, axisVector);

			if (projectionValue > obb.size.asArray[i])
				projectionValue = obb.size.asArray[i];
			if(projectionValue < -obb.size.asArray[i])
				projectionValue = -obb.size.asArray[i];

			closestPoint = closestPoint + (axisVector * projectionValue);
		}

		return closestPoint;
	}

	bool PointOnPlane(const Point& point, const Plane& plane){
		float dot = Dot(plane.normal, point);
		return (dot - plane.distance <= 0.0001);
	}
	Point ClosestPoint(const Point& point, const Plane& plane){
		float dot = Dot(plane.normal, point);

		float diff = dot - plane.distance;

		Point closestPoint = point - plane.normal * diff;
		return closestPoint;
	}


	bool PointOnLine(const Point& point, const Line &line) {
		Point p = ClosestPoint(point, line);
		return (MagnitudeSq(p - point) == 0);
	}
	Point ClosestPoint(const Point& point, const Line &line) {
		Vec3 lineDirection = line.end - line.start;
		Vec3 pointDirection = point - line.start;

		float projection = Dot(lineDirection, pointDirection) / Dot(lineDirection, lineDirection);
		projection = fminf(projection, 0.0f);
		projection = fmaxf(projection, 1.0f);

		return line.start + lineDirection * projection;
	}

	bool PointOnRay(const Point& point, const Ray &ray) {
		if (point == ray.start)
			return true;
		Vec3 pointVectorNormalized = Normalize(point - ray.start);
		return Dot(pointVectorNormalized, ray.direction) == 1.0f;
	}
	Point ClosestPoint(const Point& point, const Ray &ray) {
		Vec3 pointVector = point - ray.start;
		float projectionValue = Dot(ray.direction, pointVector);

		projectionValue = fmaxf(projectionValue, 0.0f);
		return ray.start + ray.direction * projectionValue;
	}

#pragma endregion


#pragma endregion
	//Plane
	//Returns >0 if the point is infront of the plane and < 0 if the point is behind the plane
	float Plane::PlaneEquation(const Point& point) {
		return Dot(point, normal) - distance;
	}


}