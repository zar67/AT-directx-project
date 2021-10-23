#include "Camera.h"

Camera::Camera()
{
	m_position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

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

	float xMovement = (leftMovement + rightMovement) * deltaTime;
	float zMovement = (forwardMovement + backwardMovement) * deltaTime;

	AdjustPosition(xMovement, 0.0f, zMovement);
}

void Camera::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	UpdateViewMatrix();
}

void Camera::AdjustPosition(float x, float y, float z)
{
	DirectX::XMFLOAT3 translation = DirectX::XMFLOAT3(x, y, z);

	DirectX::XMStoreFloat3(
		&translation,
		DirectX::XMVector3Transform(
			DirectX::XMLoadFloat3(&translation),
			DirectX::XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z)
		));

	m_position.x += translation.x;
	m_position.y += translation.y;
	m_position.z += translation.z;

	UpdateViewMatrix();
}

void Camera::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;

	UpdateViewMatrix();
}

void Camera::AdjustRotation(float x, float y, float z)
{
	m_rotation.x += x;
	m_rotation.y += y;
	m_rotation.z += z;

	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	// Need this otherwise DirectXMathVector.inl won't be included and cameraTarget += cameraPosition will cause an error
	using namespace DirectX;

	DirectX::XMMATRIX cameraRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);

	DirectX::XMVECTOR cameraTarget = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, cameraRotationMatrix);
	const auto cameraPosition = DirectX::XMVectorSet(m_position.x, m_position.y, m_position.z, 0.0f);
	cameraTarget += cameraPosition;

	DirectX::XMVECTOR upDirection = DirectX::XMVector3Transform(DEFAULT_UP_VECTOR, cameraRotationMatrix);
	m_viewMatrix = DirectX::XMMatrixLookAtLH(cameraPosition, cameraTarget, upDirection);
}