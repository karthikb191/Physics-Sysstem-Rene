#pragma once
#ifndef _H_CAMERA
#define _H_CAMERA

#include"../Transform.h"
#include"../Globals.h"

using namespace _Maths;
using namespace _GlobalVariables;

enum  ECameraRenderMode
{
	M_Orthographic,
	M_Perspective
};

class Camera
{
public:
	Camera() {
		//transform = Transform(Vec3::Zero(), Vec3::Zero(), Vec3::One());
		transform = Transform(Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(1, 1, 1));

		SetupPerspectiveProjection(60, 1.33, 0.1f, 10000);
		SetupOrthographicProjection(-200, 200, -200, 200, 0.1, 1000);
		SetCameraRenderMode(ECameraRenderMode::M_Perspective);
	};
	Camera(Transform transform) {
		this->transform = transform;

		SetupPerspectiveProjection(60, 1.33, 0.1f, 10000);
		SetupOrthographicProjection(-200, 200, -200, 200, 0.1, 1000);
		SetCameraRenderMode(ECameraRenderMode::M_Perspective);
	};
	Camera(Vec3 pos, Vec3 rot, Vec3 scale) {
		transform = Transform(pos, rot, scale);

		SetupPerspectiveProjection(60, 1.33, 0.1f, 10000);
		SetupOrthographicProjection(-200, 200, -200, 200, 0.1, 1000);
		SetCameraRenderMode(ECameraRenderMode::M_Perspective);
	};
	~ Camera();


	Matrix4X4 GetViewMatrix() {
		std::cout << *&transform.Right();
		return InverseCameraMatrix(transform.GetTRSMatrix()); 
	};
	Matrix4X4 GetVPMatrix() { return GetViewMatrix() *globalProjectionMatrix; }

	void MoveCamera(Vec3 moveAmount) {
		Vec3 move = transform.Forward() * moveAmount.z + transform.Right() * moveAmount.x + Vec3(0, 1, 0) * moveAmount.y;
		//std::cout << transform.forward;
		transform.Position = transform.Position + move;
	}
	void SetCameraRoation(Vec3 rotation) {
		transform.Rotation = rotation;
	}

	//Always set up projection values before switching
	void SetupPerspectiveProjection(float fov, float aspectRatio, float nClip, float fClip) {
		this->fov = fov;	this->aspectRatio = aspectRatio;	
		this->nearClippingPlane = nClip;	this->farClippingPlane = fClip;

		perspectiveMatrix = Perspective(fov, aspectRatio, nearClippingPlane, farClippingPlane);
	}
	void SetupOrthographicProjection(const float left, const const float right, 
									const float bottom, const float top, 
									const float nClip, const float fClip) {
		this->left = left; this->right = right; this->top = top; this->bottom = bottom;
		this->nearClippingPlane = nClip; this->farClippingPlane = fClip;

		orthographicMatrix = Orthographic(left, right, bottom, top, nClip, fClip);
	}
	//Make sure you have set up the appropriate projection values
	void SetCameraRenderMode(ECameraRenderMode mode) { 
		eCameraRenderMode = mode;  
		switch (eCameraRenderMode)
		{
		case ECameraRenderMode::M_Orthographic:
			globalProjectionMatrix = orthographicMatrix;	
			break;
		case ECameraRenderMode::M_Perspective:
			globalProjectionMatrix = perspectiveMatrix;	
			break;
		default:
			globalProjectionMatrix = orthographicMatrix;
			break;
		}
	}

	Transform transform;

	void Update() {  }


private:
	ECameraRenderMode eCameraRenderMode;
	float nearClippingPlane;
	float farClippingPlane;
	float fov;
	float aspectRatio;
	float orthographicSize;
	float left;	float right; float top; float bottom;

	Matrix4X4 perspectiveMatrix;
	Matrix4X4 orthographicMatrix;
};

 Camera::~ Camera()
{
	 //delete (&transform);
}

#endif // !_H_CAMERA
