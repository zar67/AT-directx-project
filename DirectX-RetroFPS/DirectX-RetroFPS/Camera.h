#pragma once
#include "Input.h"
#include "Transform.h"
#include "CollisionUtilities.h"

class Camera
{
public:
	Camera(float movementSpeed, float rotationSpeed, DirectX::XMFLOAT2 deadZoneSize);

	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);

	const DirectX::XMMATRIX& GetViewMatrix() const;
	const DirectX::XMMATRIX& GetProjectionMatrix() const;

	Transform& GetTransform();
	OBBCollider& GetCollider();
	Ray& GetShootRay();

	void Update(float deltaTime, Input& input, int windowWidth, int windowHeight);

	void OnCollision(CollisionUtilities::CollisionData collision);
	void OnBulletCollision(CollisionUtilities::RayCollision collision);

	void LockYPosition(float y);

	void AdjustPosition(float x, float y, float z);
	void AdjustRotation(float x, float y, float z);

	void UpdateViewMatrix();

private:
	void InitialiseCollider();

	void UpdateMovement(float deltaTime, Input& input);
	void UpdateRotation(float deltaTime, Input& input, int windowWidth, int windowHeight);
	void ClampRotation();
	void UpdateShooting(float deltaTime, Input& input, int windowWidth, int windowHeight);

	Transform m_transform;
	OBBCollider m_collider;

	Ray m_shootRay;

	float m_yLockPosition;

	float m_movementSpeed;
	float m_rotationSpeed;
	DirectX::XMFLOAT2 m_deadZoneSize;

	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_projectionMatrix;

	const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	const float CAMERA_Y_CLAMP = 45.0f;
};