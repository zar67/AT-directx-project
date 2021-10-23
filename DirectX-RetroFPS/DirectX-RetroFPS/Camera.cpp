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

void Camera::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	UpdateViewMatrix();
}

void Camera::AdjustPosition(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;

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