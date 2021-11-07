#pragma once
#include "Input.h"
#include "Transform.h"
#include "Collider.h"

class Camera
{
public:
	Camera(float movementSpeed, float rotationSpeed, DirectX::XMFLOAT2 deadZoneSize);

	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);

	const DirectX::XMMATRIX& GetViewMatrix() const;
	const DirectX::XMMATRIX& GetProjectionMatrix() const;

	Transform& GetTransform();

	void Update(float deltaTime, Input& input, int windowWidth, int windowHeight);

	void LockYPosition(float y);

	void SetPosition(float x, float y, float z);
	void AdjustPosition(float x, float y, float z);

	void SetRotation(float x, float y, float z);
	void AdjustRotation(float x, float y, float z);

	Collider& GetCollider();
	void UpdateViewMatrix();

private:
	void InitialiseCollider();

	Transform m_transform;
	Collider m_collider;

	float m_yLockPosition;

	float m_movementSpeed;
	float m_rotationSpeed;
	DirectX::XMFLOAT2 m_deadZoneSize;

	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_projectionMatrix;

	const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
};