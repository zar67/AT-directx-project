#include "TransformConstantBuffer.h"

TransformConstantBuffer::TransformConstantBuffer(Graphics& graphics, DrawableBase& parent) :
	m_parent(parent)
{
	m_pConstantBuffer = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(graphics);
}

void TransformConstantBuffer::Bind(Graphics& graphics)
{
	m_pConstantBuffer->Update(graphics, m_parent.GetTransform()->TransposeMatrix());
	m_pConstantBuffer->Bind(graphics);
}