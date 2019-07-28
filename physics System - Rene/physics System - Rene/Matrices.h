#pragma once
#include<iostream>
#include"Vectors.h"

namespace _Maths {

	typedef struct Matrix2X2 {

		inline Matrix2X2() {
			m11 = m22 = 1;
			m12 = m21 = 0;
		}

		inline Matrix2X2(float _11, float _12, float _21, float _22) {
			m11 = _11; m12 = _12;
			m21 = _21; m22 = _22;
		}

		union {
			struct {
				float m11, m12,
					m21, m22;
			};
			float asArray[4];
		};
		inline float* operator[](int index) {
			return &asArray[index * 2];	//Returns an array of elements
		}


	}m2x2;

	typedef struct Matrix3X3 {
		inline Matrix3X3() {
			m11 = m22 = m33 = 1;
			m12 = m13 = m21 = m23 = m31 = m32 = 0;
		}
		inline Matrix3X3(float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33) {
			m11 = _11; m12 = _12; m13 = _13;
			m21 = _21; m22 = _22; m23 = _23;
			m31 = _31; m32 = _32; m33 = _33;
		}

		union {
			struct {
				float m11, m12, m13,
					m21, m22, m23,
					m31, m32, m33;
			};
			float asArray[9];
		};
		inline float* operator[](int index) {
			return &asArray[index * 3];
		}

		

	}m3x3;

	typedef struct Matrix4X4 {


		inline Matrix4X4() {
			m11 = m22 = m33 = m44 = 1;
			m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0;
		}

		inline Matrix4X4(float _11, float _12, float _13, float _14, 
						float _21, float _22, float _23, float _24,
						float _31, float _32, float _33, float _34,
						float _41, float _42, float _43, float _44) {

			m11 = _11; m12 = _12; m13 = _13; m14 = _14;
			m21 = _21; m22 = _22; m23 = _23; m24 = _24;
			m31 = _31; m32 = _32; m33 = _33; m34 = _34;
			m41 = _41; m32 = _42; m33 = _43; m34 = _44;
		}

		union {
			struct {
				float m11, m12, m13, m14,
					m21, m22, m23, m24,
					m31, m32, m33, m34,
					m41, m42, m43, m44;
			};
			float asArray[16];
		};
		inline float* operator[](int index) {
			return &asArray[index * 4];
		}


	}m4x4;

	std::ostream& operator<<(std::ostream& stream, const m2x2 &matrix);
	std::ostream& operator<<(std::ostream& stream, const m3x3 &matrix);
	std::ostream& operator<<(std::ostream& stream, const m4x4 &matrix);
	
	void Transpose(const float* srcMatric, float* dstMatrix, int srcRows, int srcCols);
	m2x2 Transpose(const m2x2& matrix);
	m3x3 Transpose(const m3x3& matrix);
	m4x4 Transpose(const m4x4& matrix);

	float Determinant(const m2x2& matrix);
	float Determinant(const m3x3& matrix);
	float Determinant(const m4x4& matrix);

	bool MatrixAddition(float* out, const float *srcMat, const float *dstMat, int srcRows, int srcCols, int dstRows, int dstCols);
	m2x2 operator+(const m2x2& l, const m2x2& r);
	m3x3 operator+(const m3x3& l, const m3x3& r);
	m4x4 operator+(const m4x4& l, const m4x4& r);

	m2x2 operator*(const m2x2& matrix, float num);
	m3x3 operator*(const m3x3& matrix, float num);
	m4x4 operator*(const m4x4& matrix, float num);

	bool MatrixMultiplication(float* out, const float *aMat, const float *bMat, int aRows, int aCols, int bRows, int bCols);
	m2x2 operator*(const m2x2& l, const m2x2& r);
	m3x3 operator*(const m3x3& l, const m3x3& r);
	m4x4 operator*(const m4x4& l, const m4x4& r);

	m2x2 operator/(const m2x2& matrix, float num);
	m3x3 operator/(const m3x3& matrix, float num);
	m4x4 operator/(const m4x4& matrix, float num);


	m2x2 Cut(const m3x3& matrix, int row, int col);	//cutting a 3x3 matrix to get 2x2 matrix for finding determinant
	m2x2 Minor(const m2x2& matrix);					// get the minot matrix
	m3x3 Minor(const m3x3& matrix);					// get the minot matrix
	m3x3 Cut(const m4x4& matrix, int row, int col);
	m4x4 Minor(const m4x4& matrix);

	void Cofactor(float *out, const float *minor, int rows, int cols);
	m2x2 Cofactor(const m2x2& matrix);
	m3x3 Cofactor(const m3x3& matrix);
	m4x4 Cofactor(const m4x4& matrix);

	m2x2 Adjugate(const m2x2& matrix);
	m3x3 Adjugate(const m3x3& matrix);
	m4x4 Adjugate(const m4x4& matrix);

	m2x2 Inverse(const m2x2& matrix);
	m3x3 Inverse(const m3x3& matrix);
	m4x4 Inverse(const m4x4& matrix);

	void ZeroCheck(float* srcMat, int row, int col);


	m4x4 Translate(float x, float y, float z);
	m4x4 Translate(const vec3& translation);
	Vec3 GetTranslation(const m4x4& matrix);

	m4x4 Scale(float x, float y, float z);
	m4x4 Scale(const vec3& scale);
	Vec3 GetScale(const m4x4& matrix);

	//pitch - rotation around object's local lateral axis(x)
	//yaw - Rotation around object's perpendicular axis(y)
	//roll - Rotation around object's longitudional axis(z)
	m4x4 Rotate(float pitch, float yaw, float roll);
	m3x3 Rotate3X3(float pitch, float yaw, float roll);
	m4x4 Rotate(const Vec3& rotation);
	m3x3 Rotate3X3(const Vec3& rotation);
	m4x4 XRotation(float angle);
	m4x4 YRotation(float angle);
	m4x4 ZRotation(float angle);
	m3x3 XRotation3X3(float angle);
	m3x3 YRotation3X3(float angle);
	m3x3 ZRotation3X3(float angle);

	m4x4 AxisAngle(const Vec3& axis, float angle);
	m3x3 AxisAngle3X3(const Vec3& axis, float angle);

	//Multiplying vector with the respective matrix. We will be using the Row major notation here.
	Vec3 MultiplyPoint(const Vec3& vector, const m4x4& matrix);
	Vec3 MultiplyPointAndZDivide(const Vec3& vector, const m4x4& matrix);
	Vec3 MultiplyVector(const Vec3& vector, const m4x4& matrix);
	Vec3 MultiplyVector(const Vec3& vector, const m3x3& matrix);

	//Transformation Matrix
	m4x4 Transform(const Vec3& scale, const Vec3& rotation, const Vec3& position);
	m4x4 Transform(const Vec3& scale, const Vec3& axis, const float &angle, const Vec3& position);

	//Computing the View Matrix
	m4x4 LookAt(const Vec3& position, const Vec3& target, const Vec3& up);

	//Porjection Matrices to convert from view space to normalized device coordinates
	m4x4 Perspective(float fov, float aspect, float znear, float zfar);
	m4x4 Orthographic(float left, float right, float bottom, float top, float znear, float zfar);

}