#include "Camera.h"

Camera::Camera()
{
	SetPosition(0, 0, 0);
	SetRotation(0, 0, 0);

	UpdateViewMatrix();
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

void Camera::Update(float deltaTime, float movementSpeed, Input& input)
{
	// Update Camera Movement
	float forwardMovement = input.GetKeyboard()->IsKeyPressed('W') ? movementSpeed : 0.0f;
	float backwardMovement = input.GetKeyboard()->IsKeyPressed('S') ? -movementSpeed : 0.0f;
	float leftMovement = input.GetKeyboard()->IsKeyPressed('A') ? -movementSpeed : 0.0f;
	float rightMovement = input.GetKeyboard()->IsKeyPressed('D') ? movementSpeed : 0.0f;

	float upMovement = input.GetKeyboard()->IsKeyPressed('E') ? movementSpeed : 0.0f;
	float downMovement = input.GetKeyboard()->IsKeyPressed('Q') ? -movementSpeed : 0.0f;

	float xMovement = (leftMovement + rightMovement) * deltaTime;
	float yMovement = (upMovement + downMovement) * deltaTime;
	float zMovement = (forwardMovement + backwardMovement) * deltaTime;

	AdjustPosition(xMovement, yMovement, zMovement);
}

void Camera::SetPosition(float x, float y, float z)
{
	m_transform.Position.x = x;
	m_transform.Position.y = y;
	m_transform.Position.z = z;

	UpdateViewMatrix();
}

void Camera::AdjustPosition(float x, float y, float z)
{
	m_transform.ApplyTranslation(x, y, z);
	UpdateViewMatrix();
}

void Camera::SetRotation(float x, float y, float z)
{
	m_transform.Rotation.x = x;
	m_transform.Rotation.y = y;
	m_transform.Rotation.z = z;

	UpdateViewMatrix();
}

void Camera::AdjustRotation(float x, float y, float z)
{
	m_transform.ApplyRotation(x, y, z);
	UpdateViewMatrix();
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