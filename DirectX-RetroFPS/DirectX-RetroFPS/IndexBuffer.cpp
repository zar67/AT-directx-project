/* ------------------------------------------------- */
/* Filename: IndexBuffer.cpp                         */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the IndexBuffer class.                            */
/* ------------------------------------------------- */

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& graphics, const std::vector<unsigned short>& indices)
{
	m_count = indices.size();

	D3D11_BUFFER_DESC indexBufferDescription;
	ZeroMemory(&indexBufferDescription, sizeof(D3D11_BUFFER_DESC));

	indexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDescription.ByteWidth = UINT(m_count * sizeof(unsigned short));
	indexBufferDescription.StructureByteStride = sizeof(unsigned short);
	indexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDescription.CPUAccessFlags = 0;
	indexBufferDescription.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData;
	ZeroMemory(&indexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));

	indexBufferData.pSysMem = indices.data();

	HRESULT hResult = graphics.GetDevice()->CreateBuffer(
		&indexBufferDescription, &indexBufferData,
		m_pIndexBuffer.GetAddressOf()
	);

	if (FAILED(hResult))
	{
		ErrorLogger::Log(hResult, "Failed to Create Index Buffer");
	}
}

void IndexBuffer::Bind(Graphics& graphics)
{
	graphics.GetDeviceContext()->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

UINT IndexBuffer::GetCount()
{
	return m_count;
}
