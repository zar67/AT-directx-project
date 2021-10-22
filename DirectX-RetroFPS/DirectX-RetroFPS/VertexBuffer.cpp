/* ------------------------------------------------- */
/* Filename: VertexBuffer.cpp                        */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the VertexBuffer class.                           */
/* ------------------------------------------------- */

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Graphics& graphics, const std::vector<Vertex>& vertices)
{
	m_stride = sizeof(Vertex);
	D3D11_BUFFER_DESC vertexBufferDescription;
	ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));

	vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDescription.ByteWidth = sizeof(Vertex) * vertices.size();
	vertexBufferDescription.StructureByteStride = sizeof(Vertex);
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = 0;
	vertexBufferDescription.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));

	vertexBufferData.pSysMem = vertices.data();

	HRESULT hResult = graphics.GetDevice()->CreateBuffer(
		&vertexBufferDescription, &vertexBufferData,
		m_pVertexBuffer.GetAddressOf()
	);

	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Vertex Buffer");
		return;
	}
}

void VertexBuffer::Bind(Graphics& graphics)
{
	UINT offset = 0;
	graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &m_stride, &offset);
}
