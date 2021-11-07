#include "TransformConstantBuffer.h"

TransformConstantBuffer::TransformConstantBuffer(Graphics& graphics, DrawableBase& parent) :
	m_parent(parent)
{
	m_pConstantBuffer = std::make_unique<VertexConstantBuffer<BufferData>>(graphics);
}

void TransformConstantBuffer::Bind(Graphics& graphics)
{
	BufferData data = {
		   DirectX::XMMatrixTranspose(m_parent.GetTransform().GetTransformMatrix()),
		   DirectX::XMMatrixTranspose(
			   m_parent.GetTransform().GetTransformMatrix() * 
			   graphics.GetCamera()->GetViewMatrix() * 
			   graphics.GetCamera()->GetProjectionMatrix()
		   )
	};

	m_pConstantBuffer->Update(graphics, data);
	m_pConstantBuffer->Bind(graphics);
}