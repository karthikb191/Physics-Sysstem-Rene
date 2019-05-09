#include"Vectors.h"
#include"Header.h"
#include<iostream>
#include<cmath>
#include<cfloat>

#define CMP(x,y) (fabs(x-y) <= FLT_EPSILON * fmaxf(1, fmaxf(fabs(x), fabs(x))))

namespace _Maths {
	std::ostream& operator<<(std::ostream& stream, Vec2& vector) {
		stream << "<" << vector.x << "," << vector.y << ">" << std::endl;
		return stream;
	}
	std::ostream& operator<<(std::ostream& stream, Vec3& vector) {
		stream << "<" << vector.x << "," << vector.y << "," << vector.z << ">" << std::endl;
		return stream;
	}
	std::ostream& operator<<(std::ostream& stream, Vec4& vector) {
		stream << "<" << vector.x << "," << vector.y << "," << vector.z << "," << vector.w << ">" << std::endl;
		return stream;
	}

	void Vec2::Draw() {
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
	void Vec3::Draw() {
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex3f(x, y, z);
		glEnd();
	}


	Vec2 operator+(const vec2& l, const vec2& r) {
		//This might be the case of duck-typing. Look into it
		return { l.x + r.x, l.y + r.y };
	}
	Vec3 operator+(const vec3& l, const vec3& r) {
		return { l.x + r.x, l.y + r.y, l.z + r.z};
	}
	Vec4 operator+(const vec4& l, const vec4& r) {
		return { l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w};
	}

	Vec2 operator-(const vec2& l, const vec2& r) {
		return { l.x - r.x, l.y - r.y };
	}
	Vec3 operator-(const vec3& l, const vec3& r) {
		return { l.x - r.x, l.y - r.y, l.z - r.z};
	}
	Vec4 operator-(const vec4& l, const vec4& r) {
		return { l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w};
	}

	//Multiplication of the respective components of vector
	Vec2 operator*(const vec2& l, const vec2& r) {
		return { l.x * r.x, l.y * r.y };
	}
	Vec3 operator*(const vec3& l, const vec3& r) {
		return { l.x * r.x, l.y * r.y, l.z * r.z};
	}
	Vec4 operator*(const vec4& l, const vec4& r) {
		return { l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w};
	}

	vec2 operator*(const vec2& l, const float& num) {
		return { l.x * num, l.y * num };
	}
	vec3 operator*(const vec3& l, const float& num) {
		return { l.x * num, l.y * num, l.z * num };
	}
	vec4 operator*(const vec4& l, const float& num) {
		return { l.x * num, l.y * num, l.z * num, l.w * num };
	}
												
	//Division of the respective components of the vector
	Vec2 operator/(const vec2& l, const vec2& r) {
		return { l.x / r.x, l.y / r.y };
	}
	Vec3 operator/(const vec3& l, const vec3& r) {
		return { l.x / r.x, l.y / r.y, l.z / r.z };
	}
	Vec4 operator/(const vec4& l, const vec4& r) {
		return { l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w };
	}

	Vec2 operator/(const vec2& l, const float& num) {
		return { l.x / num, l.y / num };
	}
	Vec3 operator/(const vec3& l, const float& num) {
		return { l.x / num, l.y / num, l.z / num };
	}
	Vec4 operator/(const vec4& l, const float& num) {
		return { l.x / num, l.y / num, l.z / num, l.w / num };
	}

	bool operator==(const vec2& l, const vec2& r) {
		return CMP(l.x, r.x) && CMP(l.y, r.y);
	}
	bool operator==(const vec3& l, const vec3& r) {
		return CMP(l.x, r.x) && CMP(l.y, r.y) && CMP(l.z, r.z);
	}
	bool operator==(const vec4& l, const vec4& r) {
		return CMP(l.x, r.x) && CMP(l.y, r.y) && CMP(l.z, r.z) && CMP(l.w, r.w);
	}

	bool operator!=(const vec2& l, const vec2& r) {
		return !(l == r);
	}
	bool operator!=(const vec3& l, const vec3& r) {
		return !(l == r);
	}
	bool operator!=(const vec4& l, const vec4& r) {
		return !(l == r);
	}

	float Dot(const vec2& l, const vec2& r) {
		return l.x*r.x + l.y*r.y;
	}
	float Dot(const vec3& l, const vec3& r) {
		return l.x*r.x + l.y*r.y + l.z*r.z;
	}
	float Dot(const vec4& l, const vec4& r) {
		return l.x*r.x + l.y*r.y + l.z*r.z + l.w*r.w;
	}

	float Magnitude(const vec2& v) {
		return sqrtf(Dot(v, v));
	}
	float Magnitude(const vec3& v) {
		return sqrtf(Dot(v, v));
	}
	float Magnitude(const vec4& v) {
		return sqrtf(Dot(v, v));
	}

	float MagnitudeSq(const vec2& v) {
		return Dot(v, v);
	}
	float MagnitudeSq(const vec3& v) {
		return Dot(v, v);
	}
	float MagnitudeSq(const vec4& v) {
		return Dot(v, v);
	}

	Vec2 Normalize(const vec2& v) {
		return v / Magnitude(v);
	}
	Vec3 Normalize(const vec3& v) {
		return v / Magnitude(v);
	}
	Vec4 Normalize(const vec4& v) {
		return v / Magnitude(v);
	}

	vec3 Cross(const Vec3& l, const Vec3& r) {
		return {
			l.y * r.z - l.z * r.y,
			l.z * r.x - l.x * r.z,
			l.x * r.y - l.y * r.x
		};
	}

	float Angle(const vec2& l, const vec2& r) {
		float remainder = sqrtf(MagnitudeSq(l) * MagnitudeSq(r));
		return acos(Dot(l, r) / remainder);
	}
	float Angle(const vec3& l, const vec3& r) {
		float remainder = sqrtf(MagnitudeSq(l) * MagnitudeSq(r));
		return acos(Dot(l, r) / remainder);
	}
	float Angle(const vec4& l, const vec4& r) {
		float remainder = sqrtf(MagnitudeSq(l) * MagnitudeSq(r));
		return acos(Dot(l, r) / remainder);
	}


	//Projection of l onto r
	vec2 Projection(const vec2& l, const vec2& r) {
		return r * (Dot(l, r) / MagnitudeSq(r));
	}
	vec3 Projection(const vec3& l, const vec3& r) {
		return r * (Dot(l, r) / MagnitudeSq(r));
	}
	vec4 Projection(const vec4& l, const vec4& r) {
		return r * (Dot(l, r) / MagnitudeSq(r));
	}

	//Vector perpendicular to r
	vec2 Perpendicular(const vec2& l, const vec2& r) {
		vec2 parallel = Projection(l, r);
		return l - parallel;	// l = lparallel + lperpendicular
	}
	vec3 Perpendicular(const vec3& l, const vec3& r) {
		vec3 parallel = Projection(l, r);
		return l - parallel;
	}
	vec4 Perpendicular(const vec4& l, const vec4& r) {
		vec4 parallel = Projection(l, r);
		return l - parallel;
	}

	//Test the reflection code
	vec2 Reflection(const vec2& v, const vec2& normal) {
		//If the normal is not normalized, this formula must be used
		//return v - (Projection(v, normal) * 2);

		Vec2 normalizedNormal = Normalize(normal);

		return v - normalizedNormal * 2 * (Dot(v, normalizedNormal));
	}
	vec3 Reflection(const vec3& v, const vec3& normal) {
		Vec3 normalizedNormal = Normalize(normal);

		return v - normalizedNormal * 2 * (Dot(v, normalizedNormal));
	}
	vec4 Reflection(const vec4& v, const vec4& normal) {
		Vec4 normalizedNormal = Normalize(normal);

		return v - normalizedNormal * 2 * (Dot(v, normalizedNormal));
	}
}