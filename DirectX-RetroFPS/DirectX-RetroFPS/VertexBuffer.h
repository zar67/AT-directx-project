#pragma once
#include "Bindable.h"

template<typename T>
class VertexBuffer : public Bindable
{
public:
	VertexBuffer(Graphics& graphics, const std::vector<T>& vertices)
	{
		m_stride = sizeof(T);
		D3D11_BUFFER_DESC vertexBufferDescription;
		ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));

		vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDescription.ByteWidth = sizeof(T) * vertices.size();
		vertexBufferDescription.StructureByteStride = sizeof(T);
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

	virtual ~VertexBuffer() = default;

	virtual void Bind(Graphics & graphics) override
	{
		UINT offset = 0;
		graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &m_stride, &offset);
	}

protected:
	UINT m_stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer = nullptr;
};