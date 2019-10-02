#pragma once
#include<iostream>

#define RAD2DEG(x) (x * 57.295754f)
#define DEG2RAD(x) (x * 0.0174533f)

#define _H_MATH_VECTORS
namespace _Maths {

	typedef struct Vec2 {
		union{
			struct{
				float x;
				float y;
			};
			float asArray[2];	//Stores x and y automatically into this array
		};

		float& operator[](int index) {
			return asArray[index];
		}
		inline Vec2() {
			x = 0; y = 0;
		}
		inline Vec2(float a, float b){
			x = a; y = b;
		}

		void Draw();
	}vec2;

	typedef struct Vec3 {
		union {
			struct {
				float x;
				float y;
				float z;
			};
			float asArray[3];	//Stores x and y automatically into this array
		};

		float& operator[](int index) {
			return asArray[index];
		}
		inline Vec3() {
			x = 0; y = 0; z = 0;
		}
		inline Vec3(float a, float b, float c) {
			x = a; y = b; z = c;
		}

		void Draw();
		static Vec3 Zero() { return Vec3(0, 0, 0); }
		static Vec3 One() { return Vec3(1, 1, 1); }
	}vec3;

	typedef struct Vec4 {
		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};
			float asArray[4];	//Stores x and y automatically into this array
		};

		float& operator[](int index) {
			return asArray[index];
		}
		inline Vec4(float a, float b, float c, float d) {
			x = a; y = b; z = c; w = d;
		}

		//static Vec4 Zero() { return Vec4(0, 0, 0, 0); }
		//static Vec4 One() { return Vec4(1, 1, 1, 1); }
	}vec4;

	std::ostream& operator<<(std::ostream& stream, Vec2& vector);
	std::ostream& operator<<(std::ostream& stream, Vec3& vector);
	std::ostream& operator<<(std::ostream& stream, Vec4& vector);

	Vec2 operator+(const vec2& l, const vec2& r);
	Vec3 operator+(const vec3& l, const vec3& r);
	Vec4 operator+(const vec4& l, const vec4& r);

	Vec2 operator-(const vec2& l, const vec2& r);
	Vec3 operator-(const vec3& l, const vec3& r);
	Vec4 operator-(const vec4& l, const vec4& r);

	Vec2 operator*(const vec2& l, const vec2& r);
	Vec3 operator*(const vec3& l, const vec3& r);
	Vec4 operator*(const vec4& l, const vec4& r);

	vec2 operator*(const vec2& l, const float& num);
	vec3 operator*(const vec3& l, const float& num);
	vec4 operator*(const vec4& l, const float& num);

	Vec2 operator/(const vec2& l, const vec2& r);
	Vec3 operator/(const vec3& l, const vec3& r);
	Vec4 operator/(const vec4& l, const vec4& r);

	Vec2 operator/(const vec2& l, const float& num);
	Vec3 operator/(const vec3& l, const float& num);
	Vec4 operator/(const vec4& l, const float& num);

	bool operator==(const vec2& l, const vec2& r);
	bool operator==(const vec3& l, const vec3& r);
	bool operator==(const vec4& l, const vec4& r);

	bool operator!=(const vec2& l, const vec2& r);
	bool operator!=(const vec3& l, const vec3& r);
	bool operator!=(const vec4& l, const vec4& r);

	float Dot(const vec2& l, const vec2& r);
	float Dot(const vec3& l, const vec3& r);
	float Dot(const vec4& l, const vec4& r);

	float Magnitude(const vec2& v);
	float Magnitude(const vec3& v);
	float Magnitude(const vec4& v);

	float MagnitudeSq(const vec2& v);
	float MagnitudeSq(const vec3& v);
	float MagnitudeSq(const vec4& v);

	Vec2 Normalize(const vec2& v);
	Vec3 Normalize(const vec3& v);
	Vec4 Normalize(const vec4& v);

	vec3 Cross(const Vec3& l, const Vec3& r);

	float Angle(const vec2& l, const vec2& r);
	float Angle(const vec3& l, const vec3& r);
	float Angle(const vec4& l, const vec4& r);

	vec2 Projection(const vec2& l, const vec2& r);
	vec3 Projection(const vec3& l, const vec3& r);
	vec4 Projection(const vec4& l, const vec4& r);

	vec2 Perpendicular(const vec2& l, const vec2& r);
	vec3 Perpendicular(const vec3& l, const vec3& r);
	vec4 Perpendicular(const vec4& l, const vec4& r);

	vec2 Reflection(const vec2& v, const vec2& normal);
	vec3 Reflection(const vec3& v, const vec3& normal);
	vec4 Reflection(const vec4& v, const vec4& normal);
}
