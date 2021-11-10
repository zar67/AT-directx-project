#include <DirectXMath.h>
#include <stdlib.h>

#include <iostream>
#include "Camera.h"
#include "Vector.h"

Camera::Camera(float movementSpeed, float rotationSpeed, DirectX::XMFLOAT2 deadZoneSize)
{
	m_movementSpeed = movementSpeed;
	m_rotationSpeed = rotationSpeed;
	m_deadZoneSize = deadZoneSize;

	m_transform.Position.Set(0.0f, 0.0f, 0.0f);
	m_transform.Rotation.Set(0.0f, 0.0f, 0.0f);

	InitialiseCollider();
	UpdateViewMatrix();

	m_transform.ApplyScalar(0.75f, 0.75f, 0.75f);

	m_transform.ConstrainYPosition = true;
}

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = DirectX::XMConvertToRadians(fovDegrees);
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

OBBCollider& Camera::GetCollider()
{
	return m_collider;
}

Ray& Camera::GetShootRay()
{
	return m_shootRay;
}

void Camera::Update(float deltaTime, Input& input, int windowWidth, int windowHeight)
{
	m_collider.ResetVelocity();

	UpdateMovement(deltaTime, input);;

	UpdateRotation(deltaTime, input, windowWidth, windowHeight);
	ClampRotation();

	UpdateShooting(deltaTime, input, windowWidth, windowHeight);
}

void Camera::OnCollision(CollisionUtilities::CollisionData collision)
{

}

void Camera::OnBulletCollision(CollisionUtilities::RayCollision collision)
{

}

void Camera::LockYPosition(float y)
{
	m_transform.ConstrainYPosition = false;
	m_yLockPosition = y;
	m_transform.ConstrainYPosition = true;
}

void Camera::AdjustPosition(float x, float y, float z)
{
	Vector translation = m_transform.ApplyTranslation(x, 0, z);
	m_collider.IncreaseVelocity(translation);
}

void Camera::AdjustRotation(float x, float y, float z)
{
	m_transform.ApplyRotation(x, y, z);
}

void Camera::UpdateViewMatrix()
{
	// Need this otherwise DirectXMathVector.inl won't be included and cameraTarget += cameraPosition will cause an error
	using namespace DirectX;

	DirectX::XMMATRIX cameraRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(m_transform.Rotation.X, m_transform.Rotation.Y, m_transform.Rotation.Z);

	DirectX::XMVECTOR cameraTarget = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, cameraRotationMatrix);
	const auto cameraPosition = DirectX::XMVectorSet(m_transform.Position.X, m_transform.Position.Y, m_transform.Position.Z, 0.0f);
	cameraTarget += cameraPosition;

	DirectX::XMVECTOR upDirection = DirectX::XMVector3Transform(DEFAULT_UP_VECTOR, cameraRotationMatrix);
	m_viewMatrix = DirectX::XMMatrixLookAtLH(cameraPosition, cameraTarget, upDirection);
}

void Camera::InitialiseCollider()
{
	m_collider.SetTransform(&m_transform);
	m_collider.SetRotationConstraints(true, true, true);

	m_collider.SetColliderData(Vector(-1.0f, -1.0f, -1.0f), Vector(1.0f, 1.0f, 1.0f));
}

void Camera::UpdateMovement(float deltaTime, Input& input)
{
	float forwardMovement = input.GetKeyboard().IsKeyDown('W') ? m_movementSpeed : 0.0f;
	float backwardMovement = input.GetKeyboard().IsKeyDown('S') ? -m_movementSpeed : 0.0f;
	float leftMovement = input.GetKeyboard().IsKeyDown('A') ? -m_movementSpeed : 0.0f;
	float rightMovement = input.GetKeyboard().IsKeyDown('D') ? m_movementSpeed : 0.0f;

	float xMovement = (leftMovement + rightMovement) * deltaTime;
	float zMovement = (forwardMovement + backwardMovement) * deltaTime;

	AdjustPosition(xMovement, 0.0f, zMovement);
}

void Camera::UpdateRotation(float deltaTime, Input& input, int windowWidth, int windowHeight)
{
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
}

void Camera::ClampRotation()
{
	if (m_transform.Rotation.X > DirectX::XMConvertToRadians(CAMERA_Y_CLAMP))
	{
		m_transform.Rotation.X = DirectX::XMConvertToRadians(CAMERA_Y_CLAMP);
	}
	else if (m_transform.Rotation.X < DirectX::XMConvertToRadians(-CAMERA_Y_CLAMP))
	{
		m_transform.Rotation.X = DirectX::XMConvertToRadians(-CAMERA_Y_CLAMP);
	}
}

void Camera::UpdateShooting(float deltaTime, Input& input, int windowWidth, int windowHeight)
{
	m_shootRay = Ray();

	bool shoot = input.GetMouse().GetLeftButtonState() == MouseEvent::ButtonState::PRESSED;

	if (shoot)
	{
		DirectX::XMMATRIX cameraRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(m_transform.Rotation.X, m_transform.Rotation.Y, m_transform.Rotation.Z);
		DirectX::XMVECTOR cameraTarget = DirectX::XMVector3TransformCoord(DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), cameraRotationMatrix);
		DirectX::XMFLOAT3 cameraForwardVector;
		DirectX::XMStoreFloat3(&cameraForwardVector, cameraTarget);

		Vector rayDirection = Vector(cameraForwardVector);
		rayDirection = rayDirection.GetNormalized();

		if (!m_shootRay.IsValid())
		{
			m_shootRay = Ray(m_transform.Position, rayDirection);
		}
	}
}