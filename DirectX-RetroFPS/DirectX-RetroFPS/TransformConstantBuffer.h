#pragma once
#include "Bindable.h"
#include "VertexConstantBuffer.h"
#include "DrawableBase.h"

class Transform;

class TransformConstantBuffer : public Bindable
{
public:
	TransformConstantBuffer(Graphics& graphics, DrawableBase& parent);
	virtual ~TransformConstantBuffer() = default;

	virtual void Bind(Graphics & graphics) override;
protected:
	struct BufferData
	{
		DirectX::XMMATRIX Transform;
		DirectX::XMMATRIX ViewProjectionMatrix;
	};
protected:
	DrawableBase& m_parent;
	std::unique_ptr<VertexConstantBuffer<BufferData>> m_pConstantBuffer;
};