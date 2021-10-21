#pragma once
#include "Bindable.h"
#include "VertexConstantBuffer.h"
#include "DrawableBase.h"

class TransformConstantBuffer : public Bindable
{
public:
	TransformConstantBuffer(Graphics& graphics, DrawableBase& parent);
	virtual ~TransformConstantBuffer() = default;

	virtual void Bind(Graphics & graphics) override;

protected:
	DrawableBase& m_parent;
	std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> m_pConstantBuffer;
};