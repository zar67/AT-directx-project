#include <DirectXMath.h>
#include <stdlib.h>

#include "Camera.h"

Camera::Camera(float movementSpeed, float rotationSpeed, DirectX::XMFLOAT2 deadZoneSize)
{
	m_movementSpeed = movementSpeed;
	m_rotationSpeed = rotationSpeed;
	m_deadZoneSize = deadZoneSize;

	SetPosition(0, 0, 0);
	SetRotation(0, 0, 0);

	InitialiseCollider();
	UpdateViewMatrix();

	m_transform.ApplyScalar(0.75f, 0.75f, 0.75f);
}

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = (fovDegrees / 360.0f) * DirectX::XM_2PI;
	m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

const DirectX::XMMATRIX& Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

const DirectX::XMMATRIX& Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

Transform& Camera::GetTransform()
{
	return m_transform;
}

void Camera::Update(float deltaTime, Input& input, int windowWidth, int windowHeight)
{
	m_collider.ResetVelocity();

	// Update Camera Movement
	float forwardMovement = input.GetKeyboard().IsKeyDown('W') ? m_movementSpeed : 0.0f;
	float backwardMovement = input.GetKeyboard().IsKeyDown('S') ? -m_movementSpeed : 0.0f;
	float leftMovement = input.GetKeyboard().IsKeyDown('A') ? -m_movementSpeed : 0.0f;
	float rightMovement = input.GetKeyboard().IsKeyDown('D') ? m_movementSpeed : 0.0f;

	float xMovement = (leftMovement + rightMovement) * deltaTime;
	float zMovement = (forwardMovement + backwardMovement) * deltaTime;

	AdjustPosition(xMovement, 0.0f, zMovement);

	// Update Camera Rotation
	DirectX::XMFLOAT2 windowCenter = DirectX::XMFLOAT2(windowWidth / 2, windowHeight / 2);
	DirectX::XMFLOAT2 mousePosition = DirectX::XMFLOAT2(input.GetMouse().GetXPos(), input.GetMouse().GetYPos());
	DirectX::XMFLOAT2 deadZone = DirectX::XMFLOAT2(windowWidth / 2 - m_deadZoneSize.x / 2, windowHeight / 2 - m_deadZoneSize.y / 2);

	DirectX::XMFLOAT2 mouseDirectionVector = DirectX::XMFLOAT2(mousePosition.x - windowCenter.x, mousePosition.y - windowCenter.y);
	float mouseDirectionLength = sqrt(pow(mouseDirectionVector.x, 2) + pow(mouseDirectionVector.y, 2));
	DirectX::XMFLOAT2 normalisedMouseDirection = DirectX::XMFLOAT2(mouseDirectionVector.x / mouseDirectionLength, mouseDirectionVector.y / mouseDirectionLength);

	float normalisedDirectionLengthX = abs(mouseDirectionVector.x / (windowWidth / 2));
	float normalisedDirectionLengthY = abs(mouseDirectionVector.y / (windowHeight / 2));

	float horizontalRotation = normalisedMouseDirection.x * normalisedDirectionLengthX * deltaTime * m_rotationSpeed;
	float verticalRotation = normalisedMouseDirection.y * normalisedDirectionLengthY * deltaTime * m_rotationSpeed;

	if (mousePosition.x >= deadZone.x && mousePosition.x <= deadZone.x + m_deadZoneSize.x &&
		mousePosition.y >= deadZone.y && mousePosition.y <= deadZone.y + m_deadZoneSize.y)
	{
		horizontalRotation = 0.0f;
		verticalRotation = 0.0f;
	}

	AdjustRotation(verticalRotation, horizontalRotation, 0.0f);

	// Clamp the Y to the correct Y position for the Level.
	m_transform.Position.y = m_yLockPosition;

	// Clamp the vertical rotation to 45 degrees.
	if (m_transform.Rotation.x > 45.0f * (DirectX::XM_PI / 180.0f))
	{
		m_transform.Rotation.x = 45.0f * (DirectX::XM_PI / 180.0f);
		verticalRotation = 0;
	}
	else if (m_transform.Rotation.x < -45.0f * (DirectX::XM_PI / 180.0f))
	{
		m_transform.Rotation.x = -45.0f * (DirectX::XM_PI / 180.0f);
		verticalRotation = 0;
	}
}

void Camera::LockYPosition(float y)
{
	m_yLockPosition = y;
}

void Camera::SetPosition(float x, float y, float z)
{
	m_transform.Position.x = x;
	m_transform.Position.y = y;
	m_transform.Position.z = z;
}

void Camera::AdjustPosition(float x, float y, float z)
{
	DirectX::XMFLOAT3 translation = m_transform.ApplyTranslation(x, y, z);
	m_collider.IncreaseVelocity(translation);
}

void Camera::SetRotation(float x, float y, float z)
{
	m_transform.Rotation.x = x;
	m_transform.Rotation.y = y;
	m_transform.Rotation.z = z;
}

void Camera::AdjustRotation(float x, float y, float z)
{
	m_transform.ApplyRotation(x, y, z);
}

Collider& Camera::GetCollider()
{
	return m_collider;
}

void Camera::InitialiseCollider()
{
	m_collider.SetTransform(&m_transform);
	m_collider.SetRotationConstraints(true, true, true);

	// The camera is treated as a point, so all the vertices are the same, but we still need the normals.
	m_collider.SetColliderData({
		{DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)}, // Left Side
		{DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)}, // Right Side
		{DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)}, // Front Side
		{DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)}, // Back Side
		{DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)}, // Top Side
		{DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)} // Bottom Side
		});
}

void Camera::UpdateViewMatrix()
{
	// Need this otherwise DirectXMathVector.inl won't be included and cameraTarget += cameraPosition will cause an error
	using namespace DirectX;

	DirectX::XMMATRIX cameraRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(m_transform.Rotation.x, m_transform.Rotation.y, m_transform.Rotation.z);

	DirectX::XMVECTOR cameraTarget = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, cameraRotationMatrix);
	const auto cameraPosition = DirectX::XMVectorSet(m_transform.Position.x, m_transform.Position.y, m_transform.Position.z, 0.0f);
	cameraTarget += cameraPosition;

	DirectX::XMVECTOR upDirection = DirectX::XMVector3Transform(DEFAULT_UP_VECTOR, cameraRotationMatrix);
	m_viewMatrix = DirectX::XMMatrixLookAtLH(cameraPosition, cameraTarget, upDirection);
}