#pragma once
#include"Geometry2D.h"
#include"Header.h"

#define CMP(x,y) (fabs(x-y) <= FLT_EPSILON * fmaxf(1, fmaxf(fabs(x), fabs(x))))

namespace _Geometry2D {
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
}