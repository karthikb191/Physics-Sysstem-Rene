#pragma once
#include"Geometry2D.h"
#include"Header.h"

#define CMP(x,y) (fabs(x-y) <= FLT_EPSILON * fmaxf(1, fmaxf(fabs(x), fabs(x))))

namespace _Geometry2D {

	bool OverlapAxis(vec2 axis, vec2 centerDirection, const vec2 maxExtentsDirection1[2], const vec2 maxExtentsDirection2[2]);

	//Line functions
	float Line2D::Length() {
		return Magnitude(end - start);
	}
	float Line2D::LengthSq() {
		return MagnitudeSq(end - start);
	}

	//Rectangle Functions
	Point2D Rectangle2D::GetMax() const {
		vec2 p1 = origin;
		vec2 p2 = origin + size;
		return Point2D{
			fmaxf(p1.x, p2.x),
			fmaxf(p1.y, p2.y)
		};
	}

	Point2D Rectangle2D::GetMin() const {
		vec2 p1 = origin;
		vec2 p2 = origin + size;
		return Point2D{
			fminf(p1.x, p2.x),
			fminf(p1.y, p2.y)
		};
	}

	Rectangle2D Rectangle2D::FromMinMax(const vec2& min, const vec2& max) {
		return Rectangle2D(min, max - min);
	}

	//Draw Functions
	void OrientedRectangle::Draw(const vec3& color) {
		
		Point3D one(-halfExtents.x, -halfExtents.y, 0);		//one = Point3D (one.x - center.x, one.y - center.y, 0);
		Point3D two(halfExtents.x, -halfExtents.y, 0);			//two = Point3D(two.x - center.x, two.y - center.y, 0);
		Point3D three(halfExtents.x, halfExtents.y, 0);			//three = Point3D(three.x - center.x, three.y - center.y, 0);
		Point3D four(-halfExtents.x, halfExtents.y, 0);		//four = Point3D(four.x - center.x, four.y - center.y, 0);

		Matrix3X3 zrotation = ZRotation3X3(rotation);

		one = MultiplyVector(one, zrotation);
		two = MultiplyVector(two, zrotation);
		three = MultiplyVector(three, zrotation);
		four = MultiplyVector(four, zrotation);


		one = Point3D(one.x + center.x, one.y + center.y, 0);
		two = Point3D(two.x + center.x, two.y + center.y, 0);
		three = Point3D(three.x + center.x, three.y + center.y, 0);
		four = Point3D(four.x + center.x, four.y + center.y, 0);

		
		//std::cout << "Drawing" << std::endl;
		//std::cout << "one " << one << std::endl;

		glBegin(GL_LINE_LOOP);
		glColor3f(color.x, color.y, color.z);
		glLineWidth(5);
		glVertex2f(one.x, one.y);
		glVertex2f(two.x, two.y);
		glVertex2f(three.x, three.y);
		glVertex2f(four.x, four.y);
		glEnd();
	}

	void Rectangle2D::Draw(const vec3& color) {

		Point3D one(0, 0, 0);
		Point3D two(size.x, 0, 0);
		Point3D three(size.x, size.y, 0);
		Point3D four(0, size.y, 0);

		one = Point3D(one.x + origin.x, one.y + origin.y, 0);
		two = Point3D(two.x + origin.x, two.y + origin.y, 0);
		three = Point3D(three.x + origin.x, three.y + origin.y, 0);
		four = Point3D(four.x + origin.x, four.y + origin.y, 0);

		glBegin(GL_LINE_LOOP);
		glColor3f(color.x, color.y, color.z);
		glLineWidth(5);
		glVertex2f(one.x, one.y);
		glVertex2f(two.x, two.y);
		glVertex2f(three.x, three.y);
		glVertex2f(four.x, four.y);
		glEnd();
	}

	void Line2D::Draw(const vec3& color) {
		glBegin(GL_LINES);
		glColor3f(color.x, color.y, color.z);
		glVertex2f(start.x, start.y);
		glVertex2f(end.x, end.y);
		glEnd();
	}

	void Circle::Draw(const vec3& color) {
		//Simple circle generation. Change this later
		int divisions = 10;
		float deltaAngle = (360.0f / divisions) * 0.0174533f;
		glBegin(GL_LINE_LOOP);
		glLineWidth(45);
		glColor3f(color.x, color.y, color.z);
		for (int i = 0; i < 10; i++) {
			float x = center.x + radius * (cosf(i * deltaAngle));
			float y = center.y + radius * (sinf(i * deltaAngle));
			//std::cout << "x and y: " << x << " " << y << std::endl;
			glVertex2f(x, y);
		}
		glEnd();
	}

	//Point Containment Tests
	bool PointOnLine(const Point2D &point, const Line2D &line) {
		//Get the slope and intercept from the information available
		//Check if the line equation is satisfied using the given point
		float slope = (line.end.y - line.start.y) / (line.end.x - line.start.x);
		float y_intercept = line.start.y - (slope * line.start.x);

		return CMP(point.y, slope * point.x + y_intercept);
	}
	bool PointInCircle(const Point2D &point, const Circle &circle) {
		Line2D line(circle.center, point);

		return (line.LengthSq() <= circle.radius * circle.radius);
	}
	bool PointInRectangle(const Point2D &point, const Rectangle2D &rectangle) {
		Point2D max = rectangle.GetMax();
		Point2D min = rectangle.GetMin();

		return	point.x >= min.x && point.x <= max.x &&
				point.y >= min.y && point.y <= max.y;
	}
	bool PointInOrientedRectangle(const Point2D &point, const OrientedRectangle &orientedRectangle) {
		//Shifting the point's origin to the oriented rectangle's center
		vec2 directionToPoint = point - orientedRectangle.center;

		float angle = -DEG2RAD(orientedRectangle.rotation);
		//Inverse the rotation so that the rectangle is aligned to the center
		Matrix2X2 zrotation = {
			cosf(angle),	sinf(angle),
			-sinf(angle),	cosf(angle)
		};
		//std::cout << "matrix: " << zrotation << std::endl;
		//Multiply the vector with the rotation matrix so that we can get the point rotated in the local space of rectangle
		//We are trying to rotate the point WRT rectangle's center
		MatrixMultiplication(directionToPoint.asArray, 
								vec2(directionToPoint.x, directionToPoint.y).asArray, 
									zrotation.asArray, 1, 2, 2, 2);

		//Adding the translation back to the point because we haven't actually moved the box
		vec2 localPoint = directionToPoint + orientedRectangle.center;

		Rectangle2D localrect = Rectangle2D(
			Vec2(orientedRectangle.center.x - orientedRectangle.halfExtents.x, orientedRectangle.center.y - orientedRectangle.halfExtents.y),
			Vec2(orientedRectangle.halfExtents * 2)
		);

		//We can now check using PointInRectangle function as we now have the local point
		return PointInRectangle(localPoint, localrect);
	}


	bool LineCircle(const Line2D &line, const Circle &circle) {

		if (PointInCircle(line.start, circle) || PointInCircle(line.end, circle))
			return true;

		vec2 ab = line.end - line.start;
		float t = (Dot(ab, (circle.center - line.start))) / Dot(ab, ab);
		if (t < 0.0f || t > 1.0f)
			return false;
		Point2D closestPoint = line.start + ab * t;
		Line2D circleToClosest(circle.center, closestPoint);

		return circleToClosest.LengthSq() < circle.radius * circle.radius;
	}


	bool LineRectangle(const Line2D &line, const Rectangle2D &rectangle) {
		if (PointInRectangle(line.start, rectangle) || PointInRectangle(line.end, rectangle))
			return true;

		////Get the normal of the line.... normal = -dy / dx
		//vec2 normal = Normalize(vec2((line.end.y - line.start.y), -(line.end.x - line.start.x)));
		//vec2 parallel = Normalize(line.end - line.start);
		//
		////vec2 boxLocation(rectangle.GetMin().x, rectangle.GetMax().y);
		//
		////The normal obtained will be the separating axis
		////The projection of line onto the normal just projects its center
		//vec2 lineCenter = (line.start + line.end) / 2;
		//lineCenter.Draw();
		//
		//
		//vec2 rectCenter = ((rectangle.GetMax() + rectangle.GetMin()) / 2);
		//rectCenter.Draw();
		//
		////Simple checl along the axis parallel to the line first
		//float ra = abs(Dot(line.start - lineCenter, parallel));
		////float rb = abs(Dot(rectangle.GetMax() - rectCenter, parallel));
		//float rb = abs(Dot(rectangle.GetMin() - rectCenter, parallel));
		//float d1 = abs(Dot((lineCenter - rectCenter), parallel));
		//
		//if (ra + rb >= d1) {
		//
		//	Line2D(vec2(), normal * 75).Draw();
		//	
		//	//Note the line center...
		//	float d = Dot(normal, lineCenter);
		//
		//	float r = rectangle.size.x * 0.5f * abs(normal.x) + 
		//			rectangle.size.y * 0.5f * abs(normal.y);
		//
		//	float s = Dot(normal, rectCenter) - d;
		//
		//	std::cout << "r: " << r << "s: " << s << std::endl;
		//	return abs(s) < r;
		//	
		//	//if (ra + rb >= d1) return true;
		//}
		//return false;

#pragma region  backup function

		vec2 norm = (line.end - line.start);
		norm.x = (norm.x != 0) ? 1.0f / norm.x : 0;
		norm.y = (norm.y != 0) ? 1.0f / norm.y : 0;


		vec2 min = (rectangle.GetMin() - line.start) * norm;
		vec2 max = (rectangle.GetMax() - line.start) * norm;
		//std::cout << "minvector: " << m << std::endl;
		float tmin = FLT_MIN;
		float tmax = FLT_MAX;
		for (int i = 0; i < 2; i++) {
			if (min[i] > max[i]) {
				float temp = min[i];
				min[i] = max[i];
				max[i] = temp;
			}

			if (min[i] > tmin)	tmin = min[i];
			if (max[i] < tmax)	tmax = max[i];

			if (tmin > tmax) return false;
		}

		float t = (tmin < 0.0f) ? tmax : tmin;
		Line2D l = line;
		return t > 0.0f && t < 1;
		//float tmin = fmaxf(
		//	fminf(min.x, max.x), 
		//	fminf(min.y, max.y)
		//);
		//float tmax = fminf(
		//	fmaxf(min.x, max.x),
		//	fmaxf(min.y, max.y)
		//);
		//if (tmax < 0 || tmin > tmax)
		//	return false;
		//
		//float t = (tmin < 0.0f) ? tmax : tmin;
		//Line2D l = line;
		//return t > 0.0f && t*t < l.LengthSq();

#pragma endregion
	}
	bool LineOrientedRectangle(const Line2D &line, const OrientedRectangle &rectangle) {
		if (PointInOrientedRectangle(line.start, rectangle) || PointInOrientedRectangle(line.end, rectangle))
			return true;
	}

	//Collision Detection among the primitive shapes
	bool CircleCircle(const Circle &circle1, const Circle &circle2) {
		float radSumSq = (circle1.radius + circle2.radius);
		radSumSq *= radSumSq;
		return MagnitudeSq(circle1.center - circle2.center) <= radSumSq;
	}
	bool CircleRectangle(const Circle &circle, const Rectangle2D &rectangle) {
		Point2D closestPoint = circle.center;
		//Checking x axis
		if (rectangle.GetMin().x >= circle.center.x)
			closestPoint.x = rectangle.GetMin().x;

		if (rectangle.GetMax().x <= circle.center.x)
			closestPoint.x = rectangle.GetMax().x;

		//Checking y axis
		rectangle.GetMin().Draw();
		if (rectangle.GetMin().y >= circle.center.y)
			closestPoint.y = rectangle.GetMin().y;

		if (rectangle.GetMax().y <= circle.center.y)
			closestPoint.y = rectangle.GetMax().y;

		closestPoint.Draw();
		//We now check if the point is inside the circle using the function previously defined
		return PointInCircle(closestPoint, circle);
	}
	bool CircleOrientedRectangle(const Circle &circle, const OrientedRectangle &rectangle) {
		//First we need to transfer the circle into the local space of the rectangle
		//This statement effectively makes the Rectangle's center as origin and points to the circle center
		vec2 directionVector = circle.center - rectangle.center;

		//To bring the vector on the x, y, z axis, we need to remove the rotation
		float theta = -DEG2RAD(rectangle.rotation);
		//Z rotation creates a reverse rotation in the local axis of the oriented rectangle
		float zRotation[] = {
			cosf(theta),	sinf(theta),
			-sinf(theta),	cosf(theta)
		};
		//Multiplying the vector with the resultant matrix will give us the point in local space of the rectangle
		MatrixMultiplication(directionVector.asArray, vec2(directionVector.x, directionVector.y).asArray, zRotation, 1, 2, 2, 2);

		Rectangle2D localrect = Rectangle2D(
			Vec2(-rectangle.halfExtents.x,  -rectangle.halfExtents.y),
			Vec2(rectangle.halfExtents * 2)
		);
		Circle localCircle(directionVector, circle.radius);

		return CircleRectangle(localCircle, localrect);
	}

	bool RectangleRectangle(const Rectangle2D &rectangle1, const Rectangle2D &rectangle2) {
		Point2D minA = rectangle1.GetMin();
		Point2D maxA = rectangle1.GetMax();
		Point2D minB = rectangle2.GetMin();
		Point2D maxB = rectangle2.GetMax();

		bool x = (minB.x <= maxA.x) && (maxB.x >= minA.x);	//Checking if x is the separating axis
		bool y = (minB.y <= maxA.y) && (maxB.y >= minA.y);	//Checking if y is the separating axis

		return x && y;
	}

	bool RectangleOrientedRectangle(const Rectangle2D &rectangle, const OrientedRectangle &orientedRectangle) {
		vec2 nonOrientedCenter = (rectangle.GetMax() + rectangle.GetMin()) * 0.5f;

		float theta = DEG2RAD(orientedRectangle.rotation);
		float zRot[] = {
			cosf(theta),	sinf(theta),
			-sinf(theta),	cosf(theta)
		};
		//std::cout << "axis: " << zRot[0] << " " << zRot[1] << std::endl;
		vec2 centerDirection = orientedRectangle.center - nonOrientedCenter;

		vec2 nonOrientedAxesSet[2] = {
			rectangle.GetMax() - nonOrientedCenter,
			vec2(rectangle.GetMax().x, rectangle.GetMin().y) - nonOrientedCenter
		};
		vec2 orientedAxesSet[2] = {
			orientedRectangle.halfExtents,
			vec2(orientedRectangle.halfExtents.x, -orientedRectangle.halfExtents.y)
		};

		//vec2 nonOrientedExtentDirection = rectangle.GetMax() - nonOrientedCenter;
		//
		//vec2 orientedExtentDirection1 = orientedRectangle.halfExtents;

		//TODO: Add a transform component and consider just using it instead of 
		//Rotating the extents. Should work the same way
		MatrixMultiplication(orientedAxesSet[0].asArray,
							vec2(orientedAxesSet[0].x, orientedAxesSet[0].y).asArray,
								zRot, 1, 2, 2, 2);
		MatrixMultiplication(orientedAxesSet[1].asArray,
			vec2(orientedAxesSet[1].x, orientedAxesSet[1].y).asArray,
			zRot, 1, 2, 2, 2);

		(orientedRectangle.center + orientedAxesSet[0]).Draw();
		(orientedRectangle.center + orientedAxesSet[1]).Draw();

		vec2 axes[] = {
			vec2(1, 0), vec2(0,1),
			vec2(), vec2()
		};
		
		//Getting remaining two axes
		vec2 axis = vec2(0, 1);
		MatrixMultiplication(axes[2].asArray, axis.asArray, zRot, 1, 2, 2, 2);
		//std::cout << "axis: " << (axes[2]) << std::endl;
		//(orientedRectangle.center + axes[2] * 50).Draw();
		axis = vec2(1, 0);
		MatrixMultiplication(axes[3].asArray, axis.asArray, zRot, 1, 2, 2, 2);
		//std::cout << "axis: " << axes[3] << std::endl;
		//(orientedRectangle.center + axes[3] * 50).Draw();

		for (int i = 0; i < 4; i++) {
			if (!OverlapAxis(axes[i], centerDirection, nonOrientedAxesSet, orientedAxesSet))
				return false;
				//std::cout << "hello";
		}
		return true;
	}

	bool OverlapAxis(vec2 axis, vec2 centerDirection, const vec2 maxExtentsDirection1[], const vec2 maxExtentsDirection2[]) {
		
		vec2 normalizedAxis = Normalize(axis);
		float ra = FLT_MIN;
		float rb = FLT_MIN;
		for (int i = 0; i < 2; i++) {
			float a = abs(Dot(normalizedAxis, maxExtentsDirection1[i]));
			if (a > ra)
				ra = a;

			float b = abs(Dot(normalizedAxis, maxExtentsDirection2[i]));
			if (b > rb)
				rb = b;
		}

		float d = abs(Dot(normalizedAxis, centerDirection));
		std::cout << "ra: " << ra << "rb: " << rb << "d: " << d << std::endl;
		if (ra + rb > d) return true;
		return false;
	}

	bool OrientedRectangleOrientedRectangle(const OrientedRectangle &rectangle1, const OrientedRectangle &rectangle2) {
		//Bring one rectangle into the local space of another.
		//Once that's done, repeat perform the Rectangle-Oriented rectangle check

		//We bring the rectangle2 into rectangle 1's space. rectangle 2 will be oriented and 1 will be aligned to axis
		float theta = -DEG2RAD(rectangle1.rotation);
		float zRot[] = {
			cosf(theta),	sinf(theta),
			-sinf(theta),	cosf(theta)
		};
		vec2 directionVector = rectangle2.center - rectangle1.center;
		MatrixMultiplication(directionVector.asArray, 
												vec2(directionVector.x, directionVector.y).asArray,
												zRot, 1, 2, 2, 2);

		float localOrientedRectRotation = rectangle2.rotation - rectangle1.rotation;

		Rectangle2D axisAlignedRect(
			rectangle1.halfExtents * -1,
			rectangle1.halfExtents * 2
		);
		OrientedRectangle localOrientedRect(
			directionVector,
			rectangle2.halfExtents,
			localOrientedRectRotation
		);
		return RectangleOrientedRectangle(axisAlignedRect, localOrientedRect);
	}


}