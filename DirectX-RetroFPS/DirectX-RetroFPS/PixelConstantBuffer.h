#pragma once
#include "Bindable.h"
#include "ErrorLogger.h"

template<typename T>
class PixelConstantBuffer : public Bindable
{
public:
	PixelConstantBuffer(Graphics& graphics, T& constantData)
	{
		D3D11_BUFFER_DESC bufferDescription;
		bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		bufferDescription.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		bufferDescription.MiscFlags = 0;
		bufferDescription.ByteWidth = sizeof(T);
		bufferDescription.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subresourceData = {};
		subresourceData.pSysMem = &constantData;

		HRESULT hResult = graphics.GetDevice()->CreateBuffer(
			&bufferDescription, &subresourceData,
			m_pConstantBuffer.GetAddressOf()
		);

		if (FAILED(hResult))
		{
			ErrorLogger::Log(hResult, "Failed to Create Constant Buffer");
		}
	}

	PixelConstantBuffer(Graphics& graphics)
	{
		D3D11_BUFFER_DESC bufferDescription;
		bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDescription.Usage = D3D11_USAGE_DYNAMIC;
		bufferDescription.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		bufferDescription.MiscFlags = 0;
		bufferDescription.ByteWidth = sizeof(T);
		bufferDescription.StructureByteStride = 0;

		HRESULT hResult = graphics.GetDevice()->CreateBuffer(
			&bufferDescription, nullptr,
			m_pConstantBuffer.GetAddressOf()
		);

		if (FAILED(hResult))
		{
			ErrorLogger::Log(hResult, "Failed to Create Constant Buffer");
		}
	}

	virtual ~PixelConstantBuffer() = default;

	void Update(Graphics& graphics, const T& constantData)
	{
		D3D11_MAPPED_SUBRESOURCE mappedSubResource;
		graphics.GetDeviceContext()->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);

		memcpy(mappedSubResource.pData, &constantData, sizeof(constantData));

		graphics.GetDeviceContext()->Unmap(m_pConstantBuffer.Get(), 0);
	}

	virtual void Bind(Graphics & graphics) override
	{
		graphics.GetDeviceContext()->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer = nullptr;
};