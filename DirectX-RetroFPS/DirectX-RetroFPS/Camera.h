#pragma once
#include <DirectXMath.h>

class Camera
{
public:
	Camera();

	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);

	const DirectX::XMMATRIX& GetViewMatrix() const;
	const DirectX::XMMATRIX& GetProjectionMatrix() const;

	void SetPosition(float x, float y, float z);
	void AdjustPosition(float x, float y, float z);

	void SetRotation(float x, float y, float z);
	void AdjustRotation(float x, float y, float z);

private:
	void UpdateViewMatrix();

	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_rotation;

	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_projectionMatrix;

	const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
};