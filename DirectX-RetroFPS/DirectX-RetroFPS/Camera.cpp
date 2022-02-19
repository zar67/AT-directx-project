#include <DirectXMath.h>
#include <stdlib.h>

#include "Camera.h"
#include "Vector.h"

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = DirectX::XMConvertToRadians(fovDegrees);
	m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

void Camera::SetTargetTransform(Transform& transform)
{
	m_pTargetTransform = &transform;
	UpdateViewMatrix();
}

Transform* Camera::GetTransform()
{
	return m_pTargetTransform;
}

const DirectX::XMMATRIX& Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

const DirectX::XMMATRIX& Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

void Camera::UpdateViewMatrix()
{
	// Need this otherwise DirectXMathVector.inl won't be included and cameraTarget += cameraPosition will cause an error
	using namespace DirectX;

	DirectX::XMMATRIX cameraRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(
		m_pTargetTransform->Rotation.X, 
		m_pTargetTransform->Rotation.Y, 
		m_pTargetTransform->Rotation.Z
	);

	DirectX::XMVECTOR cameraTarget = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, cameraRotationMatrix);
	const auto cameraPosition = DirectX::XMVectorSet(
		m_pTargetTransform->Position.X,
		m_pTargetTransform->Position.Y,
		m_pTargetTransform->Position.Z, 
		0.0f
	);

	cameraTarget += cameraPosition;

	DirectX::XMVECTOR upDirection = DirectX::XMVector3Transform(DEFAULT_UP_VECTOR, cameraRotationMatrix);
	m_viewMatrix = DirectX::XMMatrixLookAtLH(cameraPosition, cameraTarget, upDirection);
}