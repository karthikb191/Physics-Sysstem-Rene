#pragma once
#include"Matrices.h"
#include<cmath>
#include<cfloat>
#include<iostream>

#define CMP(x,y) (fabs(x-y) <= FLT_EPSILON * fmaxf(1, fmaxf(fabs(x), fabs(x))))


namespace _Maths {

	//static m4x4 GetViewMatrix() {
	//	return viewMatrix;
	//}
	//static m4x4 GetProjectionMatrix() {
	//	return projectionMatrix;
	//}
	//static m4x4 SetProjectionMatrix(m4x4 matrix) {
	//	projectionMatrix = matrix;
	//}
	//static m4x4 SetViewMatrix(m4x4 matrix) {
	//	viewMatrix = matrix;
	//}
	
	std::ostream& operator<<(std::ostream& stream, const m2x2 &matrix) {
		stream << std::endl;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				stream << matrix.asArray[i * 2 + j] << "\t";
			}
			stream << std::endl;
		}
		return stream;
	}
	std::ostream& operator<<(std::ostream& stream, const m3x3 &matrix) {
		stream << std::endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				stream << matrix.asArray[i * 3 + j] << "\t";
			}
			stream << std::endl;
		}
		return stream;
	}
	std::ostream& operator<<(std::ostream& stream, const m4x4 &matrix) {
		stream << std::endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				stream << matrix.asArray[i * 4 + j] << "\t";
			}
			stream << std::endl;
		}
		return stream;
	}

	//Transpose function takes array of floats for source and destination matrices
	void Transpose(const float* srcMatrix, float* dstMatrix, int srcRows, int srcCols) {
		for (int i = 0; i < srcRows * srcCols; i++) {
			int row = i / srcCols;
			int col = i % srcRows;
			dstMatrix[i] = srcMatrix[col * srcCols + row];
		}
	}
	m2x2 Transpose(const m2x2& matrix) {
		Matrix2X2 result;
		Transpose(matrix.asArray, result.asArray, 2, 2);
		return result;
	}
	m3x3 Transpose(const m3x3& matrix) {
		Matrix3X3 result;
		Transpose(matrix.asArray, result.asArray, 3, 3);
		return result;
	}
	m4x4 Transpose(const m4x4& matrix) {
		Matrix4X4 result;
		Transpose(matrix.asArray, result.asArray, 4, 4);
		return result;
	}
	

	bool MatrixAddition(float* out, const float *srcMat, const float *dstMat, int srcRows, int srcCols, int dstRows, int dstCols) {
		if (srcRows == dstRows && srcCols == dstCols) {
			for (int i = 0; i < srcRows * srcCols; i++) {
				out[i] = srcMat[i] + dstMat[i];
			}
		}
		else{
			return false;
		}
	}
	m2x2 operator+(const m2x2& l, const m2x2& r) {
		Matrix2X2 result;
		MatrixAddition(result.asArray, l.asArray, r.asArray, 2, 2, 2, 2);
		return result;
	}
	m3x3 operator+(const m3x3& l, const m3x3& r) {
		Matrix3X3 result;
		MatrixAddition(result.asArray, l.asArray, r.asArray, 3, 3, 3, 3);
		return result;
	}
	m4x4 operator+(const m4x4& l, const m4x4& r) {
		Matrix4X4 result;
		MatrixAddition(result.asArray, l.asArray, r.asArray, 4, 4, 4, 4);
		return result;
	}

	m2x2 operator*(const m2x2& matrix, float num) {
		Matrix2X2 result;
		for (int i = 0; i < 4; i++) {
			result.asArray[i] = matrix.asArray[i] * num;
		}
		return result;
	}
	m3x3 operator*(const m3x3& matrix, float num) {
		Matrix3X3 result;
		for (int i = 0; i < 9; i++) {
			result.asArray[i] = matrix.asArray[i] * num;
		}
		return result;
	}
	m4x4 operator*(const m4x4& matrix, float num) {
		Matrix4X4 result;
		for (int i = 0; i < 16; i++) {
			result.asArray[i] = matrix.asArray[i] * num;
		}
		return result;
	}

	bool MatrixMultiplication(float* out, const float *aMat, const float *bMat, int aRows, int aCols, int bRows, int bCols) {
		if (aCols != bRows)
			return false;

		for (int i = 0; i < aRows; i++) {
			for (int j = 0; j < bCols; j++) {
				out[i * bCols + j] = 0;
				for (int k = 0; k < bRows; k++) {
					out[i * bCols + j] += aMat[i * aCols + k] * bMat[k * bCols + j];
				}
			}
		}
		return true;
	}
	m2x2 operator*(const m2x2& l, const m2x2& r) {
		Matrix2X2 result;
		MatrixMultiplication(result.asArray, l.asArray, r.asArray, 2, 2, 2, 2);
		return result;
	}
	m3x3 operator*(const m3x3& l, const m3x3& r) {
		Matrix3X3 result;
		MatrixMultiplication(result.asArray, l.asArray, r.asArray, 3, 3, 3, 3);
		return result;
	}
	m4x4 operator*(const m4x4& l, const m4x4& r) {
		Matrix4X4 result;
		MatrixMultiplication(result.asArray, l.asArray, r.asArray, 4, 4, 4, 4);
		return result;
	}

	m2x2 operator/(const m2x2& matrix, float num) {
		Matrix2X2 result;
		for (int i = 0; i < 4; i++) {
			result.asArray[i] = matrix.asArray[i] / num;
		}
		return result;
	}
	m3x3 operator/(const m3x3& matrix, float num) {
		Matrix3X3 result;
		for (int i = 0; i < 9; i++) {
			result.asArray[i] = matrix.asArray[i] / num;
		}
		return result;
	}
	m4x4 operator/(const m4x4& matrix, float num) {
		Matrix4X4 result;
		for (int i = 0; i < 16; i++) {
			result.asArray[i] = matrix.asArray[i] / num;
		}
		return result;
	}

	float Determinant(const m2x2& matrix) {
		return (matrix.m11*matrix.m22 - matrix.m21 * matrix.m12);
	}
	m2x2 Minor(const m2x2& matrix) {
		return {
			matrix.m22, matrix.m21,
			matrix.m12, matrix.m11
		};
	}
	//cutting a 3x3 matrix to get 2x2 matrix for finding determinant
	m2x2 Cut(const m3x3& matrix, int row, int col) {
		Matrix2X2 result;
		int index = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i == row || j == col)
					continue;

				int targetIndex = i * 3 + j;
				result.asArray[index] = matrix.asArray[targetIndex];
				index++;
			}
		}
		return result;
	}
	m3x3 Minor(const m3x3& matrix) {
		Matrix3X3 minorMatrix;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				minorMatrix.asArray[i * 3 + j] = Determinant(Cut(matrix, i, j));
			}
		}

		return minorMatrix;
	}

	void Cofactor(float *out, const float *minor, int rows, int cols) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				int index = i * cols + j;
				out[index] = minor[index] * powf(-1.0f, i + j);
			}
		}
	}
	m2x2 Cofactor(const m2x2& matrix) {
		Matrix2X2 result;
		Cofactor(result.asArray, Minor(matrix).asArray, 2, 2);
		return result;
	}
	m3x3 Cofactor(const m3x3& matrix) {
		Matrix3X3 result;
		Cofactor(result.asArray, Minor(matrix).asArray, 3, 3);
		return result;
	}

	float Determinant(const m3x3& matrix) {
		float result = 0.0f;
		Matrix3X3 cofactorMatrix = Cofactor(matrix);
		for (int j = 0; j < 3; j++) {
			result += matrix.asArray[j] * cofactorMatrix[0][j];
		}
		return result;
	}

	m3x3 Cut(const m4x4& matrix, int row, int col) {
		Matrix3X3 result;
		int index = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (i == row || j == col)
					continue;

				int targetIndex = i * 4 + j;
				result.asArray[index] = matrix.asArray[targetIndex];
				index++;
			}
		}
		return result;
	}
	m4x4 Minor(const m4x4& matrix) {
		Matrix4X4 minorMatrix;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				minorMatrix[i][j] = Determinant(Cut(matrix, i, j));
			}
		}
		return minorMatrix;
	}
	m4x4 Cofactor(const m4x4& matrix) {
		Matrix4X4 result;
		Cofactor(result.asArray, Minor(matrix).asArray, 4, 4);
		return result;
	}
	float Determinant(const m4x4& matrix) {
		float result = 0;
		Matrix4X4 cofactorMatrix = Cofactor(matrix);
		for (int j = 0; j < 4; j++) {
			result += matrix.asArray[j] * cofactorMatrix[0][j];
		}
		return result;
	}

	//Adjugate matrix is the transpose of the cofactor matrix
	m2x2 Adjugate(const m2x2& matrix) {
		return Transpose(matrix);
	}
	m3x3 Adjugate(const m3x3& matrix) {
		return Transpose(matrix);
	}
	m4x4 Adjugate(const m4x4& matrix) {
		return Transpose(matrix);
	}

	//Inverse of the matrix is it's adjugate matrix, divided by it's determinant: adj(M)/|M|
	m2x2 Inverse(const m2x2& matrix) {
		float determinant = Determinant(matrix);
		if (CMP(determinant, 0.0f)) return m2x2();

		return Adjugate(matrix) / determinant;
	}
	m3x3 Inverse(const m3x3& matrix) {
		float determinant = Determinant(matrix);
		if (CMP(determinant, 0.0f)) return m3x3();

		return Adjugate(matrix) / determinant;
	}
	m4x4 Inverse(const m4x4& matrix) {
		float determinant = Determinant(matrix);
		if (CMP(determinant, 0.0f)) return m4x4();

		return Adjugate(matrix) / determinant;
	}

	void ZeroCheck(float* srcMat, int row, int col);

	m4x4 Translate(float x, float y, float z) {
		Matrix4X4 translationMatrix;
		translationMatrix.m41 = x;
		translationMatrix.m42 = y;
		translationMatrix.m43 = z;
		translationMatrix.m44 = 1;

		return translationMatrix;
	}
	m4x4 Translate(const vec3& translation) {
		Matrix4X4 translationMatrix;
		translationMatrix.m41 = translation.x;
		translationMatrix.m42 = translation.y;
		translationMatrix.m43 = translation.z;
		translationMatrix.m44 = 1;

		return translationMatrix;
	}
	Vec3 GetTranslation(const m4x4& matrix) {
		return Vec3(matrix.m41, matrix.m42, matrix.m43);
	}

	m4x4 Scale(float x, float y, float z) {
		Matrix4X4 scaleMatrix;
		scaleMatrix.m11 = x;
		scaleMatrix.m22 = y;
		scaleMatrix.m33 = z;
		scaleMatrix.m44 = 1;
		return scaleMatrix;
	}
	m4x4 Scale(const vec3& scale) {
		Matrix4X4 scaleMatrix;
		scaleMatrix.m11 = scale.x;
		scaleMatrix.m22 = scale.y;
		scaleMatrix.m33 = scale.z;
		scaleMatrix.m44 = 1;
		return scaleMatrix;
	}
	Vec3 GetScale(const m4x4& matrix) {
		return Vec3(matrix.m11, matrix.m22, matrix.m33);
	}

	//pitch - rotation around object's local lateral axis(x)
	//yaw - Rotation around object's perpendicular axis(y)
	//roll - Rotation around object's longitudional axis(z)
	m4x4 Rotate(float pitch, float yaw, float roll) {
		return ZRotation(roll) * XRotation(pitch) * YRotation(yaw);
	}
	m3x3 Rotate3X3(float pitch, float yaw, float roll) {
		return ZRotation3X3(roll) * XRotation3X3(pitch) * YRotation3X3(yaw);
	}
	m4x4 Rotate(const Vec3& rotation) {
		return Rotate(rotation.x, rotation.y, rotation.z);
	}
	m3x3 Rotate3X3(const Vec3& rotation) {
		return Rotate3X3(rotation.x, rotation.y, rotation.z);
	}

	m4x4 XRotation(float theta) {
		m4x4 xRotMatrix;
		float angle = DEG2RAD(theta);
		xRotMatrix.m22 = cosf(angle);
		xRotMatrix.m23 = sinf(angle);

		xRotMatrix.m32 = -sinf(angle);
		xRotMatrix.m33 = cosf(angle);
		return xRotMatrix;
	}
	m4x4 YRotation(float theta) {
		m4x4 yRotMatrix;
		float angle = DEG2RAD(theta);
		yRotMatrix.m11 = cosf(angle);
		yRotMatrix.m13 = -sinf(angle);

		yRotMatrix.m31 = sinf(angle);
		yRotMatrix.m33 = cosf(angle);
		return yRotMatrix;
	}
	m4x4 ZRotation(float theta) {
		m4x4 zRotMatrix;
		float angle = DEG2RAD(theta);
		zRotMatrix.m11 = cosf(angle);
		zRotMatrix.m12 = sinf(angle);

		zRotMatrix.m21 = -sinf(angle);
		zRotMatrix.m22 = cosf(angle);
		return zRotMatrix;
	}
	m3x3 XRotation3X3(float theta) {
		m3x3 xRotMatrix;
		float angle = DEG2RAD(theta);
		xRotMatrix.m22 = cosf(angle);
		xRotMatrix.m23 = sinf(angle);

		xRotMatrix.m32 = -sinf(angle);
		xRotMatrix.m33 = cosf(angle);
		return xRotMatrix;
	}
	m3x3 YRotation3X3(float theta) {
		m3x3 yRotMatrix;
		float angle = DEG2RAD(theta);
		yRotMatrix.m11 = cosf(angle);
		yRotMatrix.m13 = -sinf(angle);

		yRotMatrix.m31 = sinf(angle);
		yRotMatrix.m33 = cosf(angle);
		return yRotMatrix;
	}
	m3x3 ZRotation3X3(float theta) {
		m3x3 zRotMatrix;
		float angle = DEG2RAD(theta);
		zRotMatrix.m11 = cosf(angle);
		zRotMatrix.m12 = sinf(angle);

		zRotMatrix.m21 = -sinf(angle);
		zRotMatrix.m22 = cosf(angle);
		return zRotMatrix;
	}

	//Rotation of a point around an arbitrary axis that passes through the origin
	m4x4 AxisAngle(const Vec3& axis, float theta) {
		Matrix4X4 result;
		float angle = DEG2RAD(theta);
		float cTheta = cosf(angle);
		float sTheta = sinf(angle);
		float oneMinusCTheta = 1 - cTheta;

		float x, y, z;
		//If the magnitude of the axis is not equal to one, then we must get the normalized values
		if (!CMP(MagnitudeSq(axis), 1.0f)) {
			//The axis must be normalized
			float magnitude = Magnitude(axis);
			x = axis.x / magnitude;
			y = axis.y / magnitude;
			z = axis.z / magnitude;
		}

		result.m11 = (x * x * oneMinusCTheta) + cTheta;
		result.m12 = (x * y  * oneMinusCTheta) + (z * sTheta);
		result.m13 = (x * z * oneMinusCTheta) - (y * sTheta);
		result.m14 = 0;

		result.m21 = (x * y * oneMinusCTheta) - (z * sTheta);
		result.m22 = (y * y * oneMinusCTheta) + (cTheta);
		result.m23 = (y * z * oneMinusCTheta) + (x * sTheta);
		result.m24 = 0;

		result.m31 = (x * z * oneMinusCTheta) + (y * sTheta);
		result.m32 = (y * z * oneMinusCTheta) - (x * sTheta);
		result.m33 = (z * x * oneMinusCTheta) + (cTheta);
		result.m34 = 0;
		
		result.m41 = result.m42 = result.m43 = 0; result.m44 = 1;

		return result;
	}
	m3x3 AxisAngle3X3(const Vec3& axis, float theta) {
		Matrix4X4 mat = AxisAngle(axis, theta);
		return Matrix3X3{
			mat.m11,	mat.m12,	mat.m13,
			mat.m21,	mat.m22,	mat.m33,
			mat.m32,	mat.m32,	mat.m33
		};
	}

	//Multiplying vector with the respective matrix. We will be using the Row major notation here.
	//w = 1 is hardcoded to the multiplyPoint Function because, multiplying a point with a matrix should also cause translation
	Vec3 MultiplyPoint(const Vec3& vector, const m4x4& matrix) {
		return Vec3{
			vector.x * matrix.m11 + vector.y * matrix.m21 + vector.z * matrix.m31 + 1 * matrix.m41,
			vector.x * matrix.m12 + vector.y * matrix.m22 + vector.z * matrix.m32 + 1 * matrix.m42,
			vector.x * matrix.m13 + vector.y * matrix.m23 + vector.z * matrix.m33 + 1 * matrix.m43
		};
	}
	Vec3 MultiplyPointAndZDivide(const Vec3& vector, const m4x4& matrix) {
		Vec3 vec(
			vector.x * matrix.m11 + vector.y * matrix.m21 + vector.z * matrix.m31 + 1 * matrix.m41,
			vector.x * matrix.m12 + vector.y * matrix.m22 + vector.z * matrix.m32 + 1 * matrix.m42,
			vector.x * matrix.m13 + vector.y * matrix.m23 + vector.z * matrix.m33 + 1 * matrix.m43
		);
		return vec / vec.z;
	}
	//Vector only has direction and doesn't have any position in space.
	//So, w = 0 is hard-coded in the vector-Matrix multiplication
	Vec3 MultiplyVector(const Vec3& vector, const m4x4& matrix) {
		return Vec3{
			vector.x * matrix.m11 + vector.y * matrix.m21 + vector.z * matrix.m31,
			vector.x * matrix.m12 + vector.y * matrix.m22 + vector.z * matrix.m32,
			vector.x * matrix.m13 + vector.y * matrix.m23 + vector.z * matrix.m33
		};
	}
	Vec3 MultiplyVector(const Vec3& vector, const m3x3& matrix) {
		return Vec3{
			vector.x * matrix.m11 + vector.y * matrix.m21 + vector.z * matrix.m31,
			vector.x * matrix.m12 + vector.y * matrix.m22 + vector.z * matrix.m32,
			vector.x * matrix.m13 + vector.y * matrix.m23 + vector.z * matrix.m33
		};
	}

	//This gives us the transformation matrix of the spatial represetation of the object
	//Helper function that takes scale, rotation and position to return the complete transformation matrix
	//Scale - Rotate - Transform
	m4x4 GetTransformMatrix(const Vec3& scale, const Vec3& rotation, const Vec3& position) {
		return m4x4{
			Scale(scale) * Rotate(rotation) * Translate(position)
			//Translate(position) * Rotate(rotation) * Scale(scale)
		};
	}
	m4x4 GetTransformMatrix(const Vec3& scale, const Vec3& axis, const float &angle, const Vec3& position) {
		return{
			//Scale(scale) * AxisAngle(axis, angle) * Translate(position)
			Translate(position) * AxisAngle(axis, angle)  * Scale(scale) 
		};
	}

	m4x4 LookAt(const Vec3& position, const Vec3& target, const Vec3& up) {
		Vec3 directionVec = Normalize(target - position);
		Vec3 forward = Normalize(directionVec);
		Vec3 right = Normalize(Cross(up, forward));
		Vec3 newUp = Normalize(Cross(forward, right));
		//std::cout << "sfdsf : " << *&(target - position) << std::endl;
		//The matrix we are using for basis vectors is orthonormal.
		//So, the inverse of the matrix will be it's transpose
		//We are doing the reverse transformation of the camera here.
		//So, first, we need the inverse transformation and then it must be multiplied with the inverse orientation
		//Inverse of translation multiplied with the inverse of rotation(Order is reversed because we are finiding inverse)
		
		Matrix4X4 result;
		
		result.m11 = right.x;	result.m12 = newUp.x;	result.m13 = forward.x;	result.m14 = 0;
		result.m21 = right.y;	result.m22 = newUp.y;	result.m23 = forward.y;	result.m24 = 0;
		result.m31 = right.z;	result.m32 = newUp.z;	result.m33 = forward.z;	result.m34 = 0;
		result.m41 = -Dot(position, right);	
		result.m42 = -Dot(position, newUp);	
		result.m43 = -Dot(position, forward);	
		result.m44 = 1.0f;

		//std::cout << "view::::: " << result<< std::endl;
		return result;
	}
	m4x4 InverseCameraMatrix(Matrix4X4 cameraMat) {
		Matrix4X4 result;
		vec3 camPos = vec3(cameraMat.m41, cameraMat.m42, cameraMat.m43);
		result.m11 = cameraMat.m11;	result.m12 = cameraMat.m21;	result.m13 = cameraMat.m31;	result.m14 = 0;
		result.m21 = cameraMat.m12;	result.m22 = cameraMat.m22;	result.m23 = cameraMat.m32;	result.m24 = 0;
		result.m31 = cameraMat.m13;	result.m32 = cameraMat.m23;	result.m33 = cameraMat.m33;	result.m34 = 0;
		//The negative dot is technically the distance in the opposite direction
		result.m41 = -Dot(camPos, vec3(cameraMat.m11, cameraMat.m12, cameraMat.m13));
		result.m42 = -Dot(camPos, vec3(cameraMat.m21, cameraMat.m22, cameraMat.m23));
		result.m43 = -Dot(camPos, vec3(cameraMat.m31, cameraMat.m32, cameraMat.m33));
		result.m44 = 1.0f;

		return result;
	}

	//Projection matrices
	m4x4 Perspective(float fov, float aspect, float znear, float zfar) {
		//FOV must be converted to radians
		float cotHalfFOV = 1.0f / tanf(DEG2RAD(fov * 0.5f));
		Matrix4X4 result;
		result.m11 = cotHalfFOV / aspect;
		result.m22 = cotHalfFOV;
		result.m33 = zfar / (zfar - znear);
		result.m34 = 1.0f;
		result.m43 = 2 * -znear * result.m33;
		result.m44 = 0;

		//result = result * Orthographic(-200, 200, -200, 200, znear, zfar);

		return result;
	}

	m4x4 Orthographic(float left, float right, float bottom, float top, float znear, float zfar) {
		float fMinusN = zfar - znear;
		Matrix4X4 result;
		result.m11 = 2.0f / (right - left);
		result.m22 = 2.0f / (top - bottom);
		result.m33 = 1 / (fMinusN);
		result.m43 = znear / (-fMinusN);
		return result;
	}

}