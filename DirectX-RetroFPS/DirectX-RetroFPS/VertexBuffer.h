/* ------------------------------------------------- */
/* Filename: VertexBuffer.h                          */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the VertexBuffer class     */
/* ------------------------------------------------- */

#pragma once
#include "Bindable.h"
#include "Vertex.h"

class VertexBuffer : public Bindable
{
public:
	VertexBuffer(Graphics& graphics, const std::vector<Vertex>& vertices);
	virtual ~VertexBuffer() = default;

	virtual void Bind(Graphics & graphics) override;

protected:
	UINT m_stride;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;
};