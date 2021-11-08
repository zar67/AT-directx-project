#pragma once
#include "Bindable.h"
#include "ErrorLogger.h"

template<typename T>
class VertexBuffer : public Bindable
{
public:
	VertexBuffer(Graphics& graphics, const std::vector<T>& vertices)
	{
		m_stride = sizeof(T);
		D3D11_BUFFER_DESC vertexBufferDescription;
		ZeroMemory(&vertexBufferDescription, sizeof(D3D11_BUFFER_DESC));

		vertexBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		vertexBufferDescription.ByteWidth = sizeof(T) * vertices.size();
		vertexBufferDescription.StructureByteStride = sizeof(T);
		vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
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

	void Update(Graphics& graphics, const std::vector<T>& data)
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;
		graphics.GetDeviceContext()->Map(m_pVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
		
		memcpy(mappedSubResource.pData, data.data(), data.size() * sizeof(T));

		graphics.GetDeviceContext()->Unmap(m_pVertexBuffer.Get(), 0);
	}

	virtual void Bind(Graphics & graphics) override
	{
		UINT offset = 0;
		graphics.GetDeviceContext()->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &m_stride, &offset);
	}

protected:
	UINT m_stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer = nullptr;
};