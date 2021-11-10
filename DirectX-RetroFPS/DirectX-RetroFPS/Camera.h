#pragma once

#include "Transform.h"

class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);
	void SetTargetTransform(Transform& transform);

	const DirectX::XMMATRIX& GetViewMatrix() const;
	const DirectX::XMMATRIX& GetProjectionMatrix() const;

	void UpdateViewMatrix();

private:
	Transform* m_pTargetTransform = nullptr;

	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_projectionMatrix;

	const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
};