#pragma once
#ifndef _H_TRANSFORM
#define _H_TRANSFORM
#include"Vectors.h"
#include"Matrices.h"

using namespace _Maths;

typedef struct Transform {
	union
	{
		struct
		{
			Vec3 Position;
			Vec3 Rotation;
			Vec3 Scale;
		};
	};

	Transform(Vec3 pos, Vec3 rot, Vec3 scl) {
		Position = pos;	Rotation = rot;	Scale = scl;
	}
	Transform() {
		Position = { 0, 0 ,0 };	Rotation = { 0, 0, 0 };	Scale = { 1, 1, 1 };
	}


	
	Matrix4X4 GetTRSMatrix() {
		modelMatrix = GetTransformMatrix(Scale, Rotation, Position);
		return modelMatrix;
	}

	Vec3 GetPosition() { return Position; }
	Vec3 GetRotation() { return Rotation; }
	Vec3 GetScale() { return Scale; }

	Vec3 Right(){ return Vec3(modelMatrix.m11, modelMatrix.m12, modelMatrix.m13); }
	Vec3 Top() { return Vec3(modelMatrix.m21, modelMatrix.m22, modelMatrix.m23); }
	Vec3 Forward() {return Vec3(modelMatrix.m31, modelMatrix.m32, modelMatrix.m33); }
private:
	Matrix4X4 modelMatrix;
	



}Transform_Class;

#endif // !_H_TRANSFORM
